require 'fileutils'
require 'json'
require 'popen4'
require 'pp'
require 'rubygems'
require 'sinatra'


# @param [String] cmd Command to be executed.
def safe_popen(cmd)
  begin
    Timeout.timeout(20) do
      @stdout = IO.popen(cmd)
      until @stdout.eof?
        line = @stdout.readline
        yield line
      end
      Process.wait @stdout.pid
    end
  rescue Timeout::Error => e
    Process.kill 9, @stdout.pid
    Process.wait @stdout.pid
    yield e.to_s
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
  File.open('cmd.sh') { |f| f << json_obj['cmd'] }
  File.open('main.cpp') { |f| f << json_obj['src'] }
  safe_popen('./sandbox.sh') { |line| out << line }
end


post '/share' do
  safe_popen('./share.sh') { |line| out << line }
end


get '/view' do
  File.read('view.html')
end


get '/*' do
  get_contents = Proc.new do |name|
    begin
      File.read(name)
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