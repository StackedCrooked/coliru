require 'rubygems'
require 'json'
require 'fileutils'
require 'mongrel'
require 'net/http'
require 'popen4'
require 'cgi'
require 'pp'
require 'thread'

$semaphore = Mutex.new
$pid = 0
$timeout = 10
$archive = ENV["COLIRU_ARCHIVE"]
puts "$archive: #{$archive}"


class SimpleHandler < Mongrel::HttpHandler
  def process(request, response)
    response.start(200) do |head,out|
      head["Content-Type"] = "text/html"
      location = get_location(request)

      match_data = %r(([\w-]+\.html).*).match(location)
      if match_data
        FileUtils.copy_stream(File.new(match_data[1]), out)
        return
      else
        case location
        when "": FileUtils.copy_stream(File.new("index.html"), out)
        when "compile": $semaphore.synchronize { safe_compile(request, "sandbox", out) }
        when "share": $semaphore.synchronize { share(request, out) }
        when "external": load_external(request, out)
        when "embed"
          html =  File.open("embed.html", "r").read
          query = request.params["QUERY_STRING"]
          url_params = CGI::parse(query)
          video_id = url_params['v'][0]
          html['{{YOUTUBE_URL}}'] = "http://youtube.com/embed/" + (video_id ? video_id : "video_id_goes_here")
          out << html
        when "favicon.ico": FileUtils.copy_stream(File.new("favicon.png", "rb"), out)
        else $semaphore.synchronize {
          p = Proc.new { |name| begin ; File.read("#{$archive}/#{location}/#{name}") ; rescue Errno::ENOENT => e ; e.to_s ; end }
          out.write({
            'src' => p.call("main.cpp").rstrip,
            'cmd' => cmd = p.call("cmd.sh").rstrip,
            'output' => p.call("output").rstrip
          }.to_json)
        }
      end
    end
  end
end

def load_external(req, out)

  # get url params
  req_params=CGI::parse(req.params["QUERY_STRING"])
  
  # get external url from paramas
  external_url = req_params['url'][0]
  
  # download url
  uri = URI.parse(external_url)
  http_get_request = Net::HTTP::Get.new(uri.path)
  result = Net::HTTP.start(uri.host, uri.port){ |http| http.request(http_get_request) }
  
  # send to out
  out.write(result.body)
end

def share(req, out)
  $pid = 0;
  begin
    Timeout.timeout($timeout) do
      obj = JSON.parse(req.body.string)
      File.open("main.cpp", 'w') { |f| f.write(obj['src']) }
      File.open("cmd.sh", 'w') { |f| f.write(obj['cmd']) }
      status = POpen4::popen4("./share.sh 2>&1") do |stdout, stderr, stdin, pid|
        $pid = pid
        stdin.close()
        output = ""
        while not stdout.eof?
          output += stdout.read(1)
        end
        out.write(%r(ID=(\S+)).match(output)[1])
      end
    end
  rescue Timeout::Error => e
    puts e
  end
end


def safe_compile(req, script, out)
  $pid = 0;
  begin
    Timeout.timeout($timeout) do
      compile(req, script, out)
    end
  rescue Timeout::Error => e
    out.write("The operation timed out.")
    Thread.new do 
      puts "Killing myself to live."
      sleep(0.01)
      POpen4::popen4("pkill -u 2002") {} 
      POpen4::popen4("pkill -u 2001") {} 
    end
  end
end

def compile(req, script, out)
  obj = JSON.parse(req.body.string)
  File.open("main.cpp", 'w') { |f| f.write(obj['src']) }
  File.open("cmd.sh", 'w') { |f| f.write(obj['cmd']) }
  status = POpen4::popen4("./#{script}.sh 2>&1") do |stdout, stderr, stdin, pid|
    $pid = pid
    stdin.close()
    while not stdout.eof?
      out.write(stdout.read(1))
    end
  end
end

# Returns the location. E.g: if the URL is "http://localhost.com/compile" then "ccompile" will be returned.
def get_location(req)
  return req.params["REQUEST_PATH"][1..-1]
end

end


if ARGV.length != 2
  puts "Usage ruby webserver.rb Host Port"
  exit
end


$host = ARGV[0]
$port = ARGV[1]


puts "Start listening to #{$host}:#{$port}"
h = Mongrel::HttpServer.new($host, $port)
h.register("/", SimpleHandler.new)
h.register("/Archive", Mongrel::DirHandler.new($archive))
puts "h.num_processors: #{h.num_processors}"
h.run.join

