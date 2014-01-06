require 'rubygems' # must be first!
require 'fileutils'
require 'json'
require 'net/http'
require 'popen4'
require 'pp'
require 'sinatra'
require 'sinatra/cross_origin'


get '/' do
    File.read('index.html')
end


get %r{\/tag=\w+} do
    File.read('index.html')
end


get '/mobile' do |_|
    File.read('mobile.html')
end


get '/*.html' do |file|
    File.read("#{file}.html")
end


get '/*.js' do |file|
    content_type :js
    File.read("#{file}.js")
end


get '/favicon.ico' do
    File.read('favicon.ico')
end


post '/feedback' do
    Thread.new do
        $mutex.synchronize do
            File.open('feedback.txt', 'a') do |file|
                file.puts(request.body.read)
            end
        end
    end.join
end


get '/hash' do
    content_type :txt
    Thread.new do
        result = ""
        $mutex.synchronize do
            result = $cache.to_s
        end
        stream do |out|
            out << result
        end
    end.join
end


get '/feedback' do
    Thread.new do
        stream do |out|
            out << '<html><body><ul>'
            $mutex.synchronize do
                File.readlines('feedback.txt').reverse.each { |l| out << "<li>#{l.gsub('<', '&lt;').gsub('>', '&gt;')}</li>" }
            end
            out << '</ul></body></html>'
        end
    end.join
end


post '/compile' do
    Thread.new do 
        result = ""
        $mutex.synchronize do
            request_text = request.body.read
            cached_result = $cache[request_text]
            if cached_result
                result = cached_result
            else
                json_obj = JSON.parse(request_text)
                id = "#{Time.now.utc.to_i}-#{rand(Time.now.utc.to_i)}"
                dir = "/tmp/coliru/#{id}"
                FileUtils.mkdir_p(dir)

                File.open("#{dir}/cmd.sh", 'w') { |f| f << json_obj['cmd'] }
                File.open("#{dir}/main.cpp", 'w') { |f| f << json_obj['src'] }
                safe_popen("INPUT_FILES_DIR=#{dir} ./sandbox.sh") { |line| result += line }

                # erase random key from hash if size > 5000
                if $cache.size >= 5000
                    $cache.delete $cache.keys.sample
                end
                $cache[request_text] = result
            end
        end
        stream do |out|
            out << result
        end
    end.join
end


get '/sh' do
    File.read('sh.html')
end


post '/sh' do
    Thread.new do 
        id = ""
        dir = ""
        $mutex.synchronize do
            id = "#{Time.now.utc.to_i}-#{rand(Time.now.utc.to_i)}"
            dir = "/tmp/coliru/#{id}"
            FileUtils.mkdir_p(dir)
            File.open("#{dir}/cmd.sh", 'w') { |f| f << request.body.read }
        end
        stream do |out|
            safe_popen("INPUT_FILES_DIR=#{dir} ./sandbox.sh") { |line| out << line }
        end
    end.join
end


get '/timeout' do
    return "#{get_timeout}\n"
end


post '/timeout' do
    set_timeout(request.body.read.to_i)
    return "Timeout is now #{get_timeout} seconds\n"
end


post '/share' do
    Thread.new do
        result = ''
        $mutex.synchronize do
            id = "#{Time.now.utc.to_i}-#{rand(Time.now.utc.to_i)}"
            dir = "/tmp/coliru/#{id}"
            FileUtils.mkdir_p(dir)

            json_obj = JSON.parse(request.body.read)
            File.open("#{dir}/cmd.sh", 'w') { |f| f << json_obj['cmd'] }
            File.open("#{dir}/main.cpp", 'w') { |f| f << json_obj['src'] }

            skip = false
            safe_popen("export INPUT_FILES_DIR=#{dir} ; ./share.sh") do |b|
                next if skip
                skip = (b == '\n')
                result += b
            end
        end
        stream { |out| out << result }
    end.join
end


get '/a/:id/:file' do
    id = params[:id]
    file = params[:file]
    File.read("../Archive2/#{id[0..1]}/#{id[2..-1]}/#{file}")
end



get '/a/*' do
    File.read('view.html')
end


get '/A/*' do
    File.read('view.html')
end


get '/view' do
    File.read('view.html')
end


get '/external' do
    uri = URI.parse(params[:url])
    http_get_request = Net::HTTP::Get.new(uri.path)
    result = Net::HTTP.start(uri.host, uri.port) { |http| http.request(http_get_request) }
    result.body
end


get '/Archive/*' do |file|
    content_type :txt
    begin
        real_file = "#{ENV['COLIRU_ARCHIVE2']}/#{file}"

        if File.directory? real_file
            Dir.entries(real_file).join("\n").to_s
        else
            File.read(real_file)
        end
    rescue Exception => e
        e.to_s
    end
end


get '/archive' do       
    get_contents = Proc.new do |path, name|       
        begin       
            file = "#{path}/#{name}"
            File.read(file)
        rescue Exception => e
          e.to_s
        end     
    end     


    id = "#{params[:id]}"
    stdout = IO.popen("./id2existingpath.sh #{id}")
    path = stdout.read.strip
    Process.wait stdout.pid
    {       
        :cmd => get_contents.call(path, 'cmd.sh'),        
        :src => get_contents.call(path, 'main.cpp'),      
        :output => get_contents.call(path, 'output')      
    }.to_json       
end     


get '/history' do
    content_type :txt
    stream do |out|
        safe_popen('./history.sh') do |line|
            out << line
        end
    end
end


get '/log' do
    count = params[:count] || 1000
    grep = params[:grep] || nil
    content_type :txt
    cmd = grep ? "tail -n#{count} /var/log/syslog 2>&1 | grep -i '#{grep}'" : "tail -n#{count} /var/log/syslog 2>&1"
    stream do |out|
        out << "Log command: " << cmd << "\n"
        out << IO.popen(cmd).read
    end
end


# Implementation details..


set :port, ENV['COLIRU_PORT']
$mutex = Mutex.new
$cache = {}

options '/*' do
  response["Access-Control-Allow-Headers"] = "origin, x-requested-with, content-type"
end


configure do
  enable :cross_origin
  disable :protection
  mime_type :json, 'application/json'
  mime_type :js, 'application/javascript'
  mime_type :jpg, 'image/jpeg'
  mime_type :png, 'image/png'
  mime_type :txt, 'text/plain'
end


def get_timeout
    begin
        result = [60, File.read('timeout.txt').to_i ].min.to_s
        return result
    rescue Exception => _
        20.to_s
    end
end


def set_timeout(t)
    begin
        File.open('timeout.txt', 'w') { |f| f << t }
    rescue Exception => e
        puts e.to_s
    end
end


def safe_popen(cmd)
    begin
        Timeout.timeout(get_timeout.to_i) do
            set_timeout(20)
            @stdout = IO.popen("#{cmd} 2>&1 ")
            count = 0
            max_count = 256 * 1024
            until @stdout.eof?
                count += 1
                raise "\nError: output size exceeds #{max_count}" if count > max_count
                yield @stdout.read(1)
            end
            Process.wait @stdout.pid
        end
    rescue Timeout::Error => e
        #First kill the innermost processes
        IO.popen("./ps.sh | grep 2002 | grep -v grep | awk '{print $1}' | sort | uniq | xargs -I {} kill -9 -{}") {||}

        # Then we can kill the top-level process.
        Process.kill 9, @stdout.pid
        Process.wait @stdout.pid
        yield e.to_s
    rescue Exception => e
        yield e.to_s
    end
end

