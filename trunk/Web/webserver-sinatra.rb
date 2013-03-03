require 'rubygems'
require 'fileutils'
require 'json'
require 'popen4'
require 'pp'
require 'sinatra'


def safe_popen(cmd, out) 
  begin 
    process_id = 0
    Timeout::timeout(1) do
      POpen4.popen4("#{cmd} 2>&1") do |stdout, _, stdin, pid|
        process_id = pid
        system("ps -ef | grep #{process_id} | grep -v grep")
        stdin.close
        until stdout.eof? do
          out << stdout.readline
        end
      end
    end
  rescue Exception => e
    out << e.to_s
    puts process_id
    puts "before kill"
    system("ps -ef | grep #{process_id} | grep -v grep")
    puts Process.kill(9, process_id).to_s
    puts "after kill"
    system("ps -ef | grep #{process_id} | grep -v grep")
    sleep(1)
    puts "after sleep"
    system("ps -ef | grep #{process_id} | grep -v grep")
  end
end


get '/' do
  File.read('index.html')
end


get '/*.*' do |file, ext|
  begin
    File.read("#{file}.#{ext}")
  rescue Exception => e
    e.to_s
  end
end


post '/compile' do
  json_obj = JSON.parse(request.body.read)
  {:cmd => 'cmd.sh', :src => 'main.cpp'}.each do |field_name, file_name|
    File.open(file_name, 'w') do |file|
      file << json_obj["#{field_name}"]
    end
  end

  stream do |out|
    safe_popen('./sandbox.sh', out)
  end
end


post '/share' do
  stream do |out|
    safe_popen('./share.sh', out)
  end
end


get '/view' do
  File.read('view.html')
end


get '/*' do
  get_contents = Proc.new do |name|
    begin
      File.read("../Archive/#{params[:captures]}/#{name}")
    rescue Exception => e;
      e.to_s
    end
  end

  return {
    :cmd => get_contents.call('cmd.sh'),
    :src => get_contents.call('main.cpp'),
    :output => get_contents.call('output')
  }.to_json
end


def log
  Logger.new(STDOUT)
end


before do
  @path_info = request.path_info
  @request_start = Time.now.to_f
  log.info("before #{@path_info}")
end


after do
  log.info("after  #{@path_info}")
end

