require 'rubygems' # must be first!
require 'fileutils'
require 'date'
require 'json'
require 'net/http'
require 'popen4'
require 'pp'
require 'sinatra'
require 'sinatra/cross_origin'


get '/' do
    File.read('index.html')
end


get '/ping' do
	""
end


get '/mobile' do
    File.read('mobile.html')
end


get '/*.html' do |file|
    File.read("#{file}.html")
end


get '/*.zip' do |file|
    content_type :zip
    File.read("#{file}.zip")
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
                text = request.body.read.gsub('NOTE', 'REMARK').split("\n")[0]
                return if text == 'undefined' # for some reason this happens a lot
                return if text =~ /jform/ # this blocks commercial spam that contains the string 'jform'
                return if text == ''
                return if text.length >= 1000 # max length is 1000 characters
                file.puts(text)
            end
        end
    end.join
end


get '/feedback' do
    Thread.new do
        stream do |out|
            out << '<html><body><ul>'
			#out << '<h3>New comments will are added to queue for moderation.</h3>'
            $mutex.synchronize do
                File.readlines('feedback.txt').reverse.each { |l| out << "<li style=\"margin-bottom: 4px;\">#{l.gsub('<', '&lt;').gsub('>', '&gt;').gsub("NOTE", "&nbsp;<b>NOTE</b>")}</li>" }
            end
            out << '</ul></body></html>'
        end
    end.join
end


$request_id = 0
post '/compile' do
    begin
        Thread.new do 
            result = ""
            rid = $request_id += 1
            log_request(rid, "/compile", "waiting")
            $mutex.synchronize do
                log_request(rid, "/compile", "running")
                request_text = request.body.read
                json_obj = JSON.parse(request_text)
                id = "#{Time.now.utc.to_f}"
                dir = "/tmp/coliru/#{id}"
                FileUtils.mkdir_p(dir)

                File.open("#{dir}/cmd.sh", 'w') { |f| f << json_obj['cmd'] }
                File.open("#{dir}/main.cpp", 'w') { |f| f << json_obj['src'] }
                safe_popen("INPUT_FILES_DIR=#{dir} setsid ./sandbox.sh 2>&1") { |line| result += line }
                FileUtils.rmtree(dir)
                log_request(rid, "/compile", "done")
            end
			response["Access-Control-Allow-Origin"] = "*"
            stream do |out|
                out << result
            end
        end.join
    rescue Exception => e
        stream do |out|
			out << e.to_s
		end
    end
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
            safe_popen("INPUT_FILES_DIR=#{dir} setsid ./sandbox.sh") { |line| out << line }
        end
    end.join
end


get '/timeout' do
    return "#{get_timeout}\n"
end


post '/timeout' do
    ask_timeout = request.body.read.to_i
    set_timeout(ask_timeout)
    got_timeout = get_timeout
    $stderr.puts "webserver-sinatra.rb: /timeout POST: ask_timeout=#{ask_timeout} got_timeout=#{got_timeout}"
    
    return "Timeout is now #{got_timeout} seconds\n"
end


post '/share' do
    begin
        Thread.new do
            result = ''
            rid = $request_id += 1
            log_request(rid, "/share", "waiting")
            $mutex.synchronize do
                log_request(rid, "/share", "running")
                id = "#{Time.now.utc.to_i}-#{rand(Time.now.utc.to_i)}"
                dir = "/tmp/coliru/#{id}"
                FileUtils.mkdir_p(dir)

                json_obj = JSON.parse(request.body.read)
                File.open("#{dir}/cmd.sh", 'w') { |f| f << json_obj['cmd'] }
                File.open("#{dir}/main.cpp", 'w') { |f| f << json_obj['src'] }

                skip = false
                safe_popen("INPUT_FILES_DIR=#{dir} setsid ./share.sh") do |b|
                    next if skip
                    skip = (b == '\n')
                    result += b
                end
                log_request(rid, "/share", "done")
            end
			response["Access-Control-Allow-Origin"] = "*"
            stream { |out| out << result }
        end.join
    rescue Exception => e
        e.to_s
    end
end


get '/a/:id/:file' do
    content_type (params[:ct] || 'text/plain') 
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
		File.read("#{path}/#{name}")
    end     


    id = "#{params[:id]}"
    stdout = IO.popen("./id2existingpath.sh #{id}")
    Process.detach stdout.pid
    path = stdout.read.strip
    begin
		return "{ \"cmd\": \"#{get_contents.call(path, 'cmd.sh')}\", \"src\": \"#{get_contents.call(path, 'main.cpp')}\", \"output\": \"#{get_contents.call(path, 'output')}\" }"
    rescue Exception => e
		return "{ \"output\": \"#{e.to_s}\" }"
    end
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
        fd = IO.popen(cmd)
        Process.detach fd.pid
        out << fd.read
    end
end


# Implementation details..


set :allow_origin, :any
set :port, ENV['COLIRU_PORT']
$mutex = Mutex.new

options '/*' do
  response["Access-Control-Allow-Headers"] = "origin, x-requested-with, content-type"
end


configure do
  enable :cross_origin
  disable :protection
  mime_type :zip, 'application/octet-stream'
  mime_type :json, 'application/json'
  mime_type :js, 'application/javascript'
  mime_type :jpg, 'image/jpeg'
  mime_type :png, 'image/png'
  mime_type :txt, 'text/plain'
end


$request_rate = 1

def get_timeout
    begin
        result = [120, File.read('timeout.txt').to_i ].min.to_s
        return [ [ 5 * result.to_i / $request_rate, 5 ].max, 60 ].min.to_s
    rescue Exception => _
        ([5 * 20.to_i / $request_rate, 5].max).to_s
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
    fd = IO.popen("#{cmd} 2>&1")
    pgid = fd.readline
    Timeout.timeout(get_timeout.to_i) do
        set_timeout(20)

        cur_char_count = 0
        max_char_count = 256 * 1024

        until fd.eof?
            if cur_char_count <= max_char_count
                yield fd.read(1)
            else
                # discard the rest
                # only read one byte at a time to prevent memory out of memory in case it's huge
                fd.read(1)
            end
            cur_char_count += 1
        end
    end
rescue Exception => e
    yield e.to_s
    log(e.to_s)
    # kill process group 
    cmd="kill -9 -#{pgid}"
    log("Kill PGID: #{cmd}")
    IO.popen(cmd) {||}

    # kill normally as well
    cmd="kill -9 #{pgid}"
    log("Also kill as normal PID: #{cmd}")
    IO.popen(cmd) {||}

    # also kill master process 
    cmd = "kill -9 #{fd.pid}"
    log("Kill master process: #{cmd}")
    IO.popen(cmd) {||}
ensure
    Process.detach fd.pid
end

$start_time = DateTime.now.strftime('%s').to_i

def log(str)
    begin
      $stderr.puts "webserver-sinatra.rb: #{str}"
    rescue  Exception => e
    end
end

def log_request(rid, method, message)
  begin 
      timeout = get_timeout.to_i
      current_time = DateTime.now.strftime('%s').to_i
      elapsed_time = current_time - $start_time

      # Each hour the start_time is reset.
      # So the request rate is not diluted.
      if elapsed_time > 3600
          $start_time = current_time
          $request_id = 0
          elapsed_time = 0
      end

      if elapsed_time == 0
        elapsed_time = 1 # avoid division by zero
      end
      $request_rate = [ 60.0 * rid / [elapsed_time, 60].max, 1].max
      $request_rate = (100 * $request_rate).round / 100.0
      $stderr.puts "webserver-sinatra.rb: request_id=#{rid} elapsed_time=#{elapsed_time} rate=#{$request_rate}/min timeout=#{timeout} method=\"#{method}\" message=#{message}"
  rescue Exception => e
    # Cannot handle the exception here.
  end
end


