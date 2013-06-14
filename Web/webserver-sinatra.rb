require 'rubygems' # must be first!
require 'fileutils'
require 'json'
require 'net/http'
require 'popen4'
require 'pp'
require 'sinatra'


get '/' do
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
    $feedback_semaphore.synchronize do
        File.open('feedback.txt', 'a') do |file|
            file.puts(request.body.read)
        end
    end
end


get '/feedback' do
    stream do |out|
        out << '<html><body><ul>'
        $feedback_semaphore.synchronize do
            File.readlines('feedback.txt').reverse.each { |l| out << "<li>#{l.gsub('<', '&lt;').gsub('>', '&gt;')}</li>" }
        end
        out << '</ul></body></html>'
    end
end


post '/compile' do
    json_obj = JSON.parse(request.body.read)
    id = "#{Time.now.to_i}-#{rand(Time.now.to_i)}"
    dir = "/tmp/coliru/#{id}"
    FileUtils.mkdir_p(dir)

    File.open("#{dir}/cmd.sh", 'w') { |f| f << json_obj['cmd'] }
    File.open("#{dir}/main.cpp", 'w') { |f| f << json_obj['src'] }
    stream do |out|
        safe_popen("INPUT_FILES_DIR=#{dir} ./sandbox.sh") { |line| out << line }
    end
end


get '/sh' do
    File.read('sh.html')
end


post '/sh' do
    id = "#{Time.now.to_i}-#{rand(Time.now.to_i)}"
    dir = "/tmp/coliru/#{id}"
    FileUtils.mkdir_p(dir)
    File.open("#{dir}/cmd.sh", 'w') { |f| f << request.body.read }
    stream do |out|
        safe_popen("INPUT_FILES_DIR=#{dir} ./sandbox.sh") { |line| out << line }
    end
end


get '/timeout' do
    get_timeout
end


post '/timeout' do
    set_timeout(request.body.read.to_i)
    get_timeout
end


post '/share' do
    result = ''
    id = "#{Time.now.to_i}-#{rand(Time.now.to_i)}"
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
    stream { |out| out << result }
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
        real_file = "#{ENV['COLIRU_ARCHIVE']}/#{file}"
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
    get_contents = Proc.new do |name|       
        begin       
            File.read("#{ENV['COLIRU_ARCHIVE']}/#{params[:id]}/#{name}")        
        rescue Exception => _
          ''
        end     
    end     

    {       
        :cmd => get_contents.call('cmd.sh'),        
        :src => get_contents.call('main.cpp'),      
        :output => get_contents.call('output')      
    }.to_json       
end     


get '/log' do
    content_type :txt
    stream do |out|
        safe_popen('tail -n1024 /var/log/syslog') do |line|
            out << line
        end
    end
end


get '/random_image' do 
    content_type :jpg
    entries = [ Dir['./images/*.jpg'], Dir['./images/*.png'] ].flatten
    if entries.empty?
        raise 'not found'
    end

    File.open(entries[rand(entries.size)], 'rb') do |io|
        io.read
    end
end


# Implementation details..


set :port, ENV['COLIRU_PORT']
$feedback_semaphore = Mutex.new


configure do
  mime_type :js, 'application/javascript'
  mime_type :jpg, 'image/jpeg'
  mime_type :txt, 'text/plain'
end


def get_timeout
    begin
        [60, File.read('timeout.txt').to_i ].min.to_s
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
            @stdout = IO.popen("#{cmd} 2>&1 ")
            count = 0
            max_count = 128 * 1024
            until @stdout.eof?
                count += 1
                raise "\nError: output size exceeds #{max_count}" if count > max_count
                yield @stdout.read(1)
            end
            Process.wait @stdout.pid
        end
    rescue Timeout::Error => e
        # Kill the process group that started the sandbox
        IO.popen("./ps.sh | grep 2002 | grep -v grep | awk '{print $1}' | sort | uniq | xargs -I {} kill -9 -{}") {||}
        Process.kill 9, @stdout.pid
        Process.wait @stdout.pid
        yield e.to_s
    rescue Exception => e
        yield e.to_s
    end
end

