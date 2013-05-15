require 'rubygems' # must be first!
require 'fileutils'
require 'json'
require 'net/http'
require 'popen4'
require 'pp'
require 'sinatra'


set :port, ENV['COLIRU_PORT']
$feedback_semaphore = Mutex.new

configure do
  mime_type :js, 'application/javascript'
  mime_type :jpg, 'image/jpeg'
end

def get_timeout
    begin
        [60, File.read('timeout.txt').to_i ].min.to_s
    rescue Exception => e
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

# @param [String] cmd Command to be executed.
def safe_popen(cmd)
    begin
        Timeout.timeout(get_timeout.to_i) do
            @stdout = IO.popen("#{cmd} 2>&1 ")
            until @stdout.eof?
                yield @stdout.readline
            end
            Process.wait @stdout.pid
        end
    rescue Timeout::Error => e
        Process.kill 9, @stdout.pid
        Process.wait @stdout.pid
        yield e.to_s
    rescue Exception => e
        e.to_s
    end
end


get '/' do
    File.read('index.html')
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
            File.readlines("feedback.txt").reverse.each { |l| out << "<li>#{l.gsub('<', '&lt;').gsub('>', '&gt;')}</li>" }
        end
        out << '</ul></body></html>'
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
        safe_popen("TMP_DIR=#{dir} ./sandbox.sh") { |line| out << line }
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
        safe_popen("TMP_DIR=#{dir} ./sandbox.sh") { |line| out << line }
    end
end


post '/sh' do
    id = "#{Time.now.to_i}-#{rand(Time.now.to_i)}"
    dir = "/tmp/coliru/#{id}"
    FileUtils.mkdir_p(dir)
    File.open("#{dir}/cmd.sh", 'w') { |f| f << request.body.read }
    stream do |out|
        safe_popen("TMP_DIR=#{dir} ./sandbox.sh") { |line| out << line }
    end
end


post '/compile2' do
    parts = request.body.read.split("__COLIRU_SPLIT__");
    id = "#{Time.now.to_i}-#{rand(Time.now.to_i)}"
    dir = "/tmp/coliru/#{id}"
    FileUtils.mkdir_p(dir)

    File.open("#{dir}/cmd.sh", 'w') { |f| f << parts[0] }
    File.open("#{dir}/main.cpp", 'w') { |f| f << parts[1] }
    stream do |out|
        safe_popen("TMP_DIR=#{dir} ./sandbox.sh") { |line| out << line }
    end
end


post '/timeout' do
    stream do |out|
        set_timeout(request.body.read.to_i)
        get_timeout
    end
end


get '/timeout' do
    get_timeout
end


post '/share' do
    result = nil
    id = "#{Time.now.to_i}-#{rand(Time.now.to_i)}"
    dir = "/tmp/coliru/#{id}"
    FileUtils.mkdir_p(dir)

    json_obj = JSON.parse(request.body.read)
    File.open("#{dir}/cmd.sh", 'w') { |f| f << json_obj['cmd'] }
    File.open("#{dir}/main.cpp", 'w') { |f| f << json_obj['src'] }

    safe_popen("export TMP_DIR=#{dir} ; ./share.sh") do |line|
        result = result || line
        next # we want to wait for the process to completely finish
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
    out << result.body
end


get '/images/?' do |file|
    page_start = "<!DOCTYPE html>\n<html><body><span>"
    page_end = '</span></body></html>'
    link = '<a href="/images/FILE"><img style="max-width: 500px ; max-height: 500px" src="/images/small/FILE"></a>'
    page = page_start
    Dir.entries("./images").each do |file|
        if [".jpg", ".jpeg", ".png" ].include?(File.extname(file))
            page += link.sub(/HREF/, "/images/#{file}").gsub(/FILE/, "#{file}")
        end
    end
    page += page_end
    return page
end

get '/random_image' do 
    content_type :jpg
    entries = [ Dir["./images/*.jpg"], Dir["./images/*.png"] ].flatten
    if entries.empty?
        raise "not found"
    end

    File.open(entries[rand(entries.size)], "rb") do |io|
        io.read
    end
end

get '/images/*' do |file|
    content_type :jpg
    File.open("images/#{file}", "rb") do |io|
        io.read
    end
end


get '/Archive/*' do |file|
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
        rescue Exception => e
            ""
        end
    end

    {
        :cmd => get_contents.call('cmd.sh'),
        :src => get_contents.call('main.cpp'),
        :output => get_contents.call('output')
    }.to_json
end
