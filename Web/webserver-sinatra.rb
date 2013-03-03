require 'rubygems'
require 'fileutils'
require 'json'
require 'popen4'
require 'pp'
require 'sinatra'

get '/' do
  pp params
  File.read('index.html')
end

get '/*.*' do |file, ext|
  File.read("#{file}.#{ext}")
end

post '/compile' do
  json_obj = JSON.parse(request.body.read)
  {:cmd => 'cmd.sh', :src => 'main.cpp'}.each do |field_name, file_name|
    File.open(file_name, 'w') do |file|
      file << json_obj["#{field_name}"]
    end
  end

  stream do |out|
    POpen4.popen4('./sandbox.sh 2>&1') do |stdout, _, stdin, _|
      stdin.close
      until stdout.eof? do
        out << stdout.readline
      end
    end
  end
end

post '/share' do
  stream do |out|
    POpen4.popen4('./share.sh 2>&1') do |stdout, _, stdin, _|
      stdin.close
      until stdout.eof? do
        out << stdout.readline.sub(/ID=/, '')
      end
    end
  end
end

get '/view' do
  File.read('view.html')
end


get '/*' do
  dir = "../Archive/#{params[:captures]}"
  {
      :cmd => (begin ; File.read("#{dir}/cmd.sh") ; rescue Exception => e ; e.to_s ; end),
      :src => (begin ; File.read("#{dir}/main.cpp") ; rescue Exception => e ; e.to_s ; end),
      :output =>  (begin ; File.read("#{dir}/output") ; rescue Exception => e ; e.to_s ; end),
  }.to_json

end