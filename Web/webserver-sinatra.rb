require 'rubygems' # must be first!
require 'fileutils'
require 'json'
require 'popen4'
require 'pp'
require 'sinatra'


set :port, ENV['COLIRU_PORT']


# @param [String] cmd Command to be executed.
def safe_popen(cmd)
  begin
    Timeout.timeout(10) do
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


get '/*.*' do |file, ext|
  File.read("#{file}.#{ext}")
end


post '/compile' do
  json_obj = JSON.parse(request.body.read)
  File.open('cmd.sh', 'w') { |f| f << json_obj['cmd'] }
  File.open('main.cpp', 'w') { |f| f << json_obj['src'] }
  stream do |out|
    safe_popen('./sandbox.sh') { |line| out << line }
  end
end


post '/share' do
  json_obj = JSON.parse(request.body.read)
  File.open('cmd.sh', 'w') { |f| f << json_obj['cmd'] }
  File.open('main.cpp', 'w') { |f| f << json_obj['src'] }

  result = nil
  safe_popen('./share.sh') do |line|
    result = result || line
    next # we want to wait for the process to completely finish
  end
  result
end


get '/view' do
  File.read('view.html')
end


get '/archive' do
  get_contents = Proc.new do |name|
    begin
      pp ENV
      File.read("#{ENV['COLIRU_ARCHIVE']}/#{params[:id]}/#{name}")
    rescue Exception => e
      e.to_s
    end
  end

  return {
      :cmd => get_contents.call('cmd.sh'),
      :src => get_contents.call('main.cpp'),
      :output => get_contents.call('output')
  }.to_json
end

