require 'rubygems'
require 'fileutils'
require 'mongrel'
require 'popen4'
require 'pp'
require 'thread'

$semaphore = Mutex.new


class SimpleHandler < Mongrel::HttpHandler
    def process(request, response)
        response.start(200) do |head,out|
            head["Content-Type"] = "text/html"
            loc = get_location(request)
            case loc
            when ""
                FileUtils.copy_stream(File.new("index.html"), out)
            when "cmd.html"
                FileUtils.copy_stream(File.new("cmd.html"), out)
            when "index.html"
                FileUtils.copy_stream(File.new("index.html"), out)
            when "frame-top.html"
                FileUtils.copy_stream(File.new("frame-top.html"), out)
            when "frame-bottom.html"
                FileUtils.copy_stream(File.new("frame-bottom.html"), out)
            when "md5-min.js"
                FileUtils.copy_stream(File.new("md5-min.js"), out)
            when "compile"
                $semaphore.synchronize {
                    compile(request, out)
                }
            when "share"
                $semaphore.synchronize {
                    share(request, out)
                }
            when "view"
                FileUtils.copy_stream(File.new("view.html"), out)
            when "favicon.ico"
                # Don't respond to favicon..
            else
                $semaphore.synchronize {
                  out.write(File.read("Archive/#{loc}/main.cpp").gsub(/\t/, "\\t") + "\t" + File.read("Archive/#{loc}/output").gsub(/\t/, "\\t"))
                }
            end
        end
    end

    def compile(request, out)
        File.open("main.cpp", 'w') { |f| f.write(request.body.string) }
        status = POpen4::popen4("./sandbox.sh 2>&1") do |stdout, stderr, stdin, pid|
            stdin.close()
            out.write(stdout.read())
        end
    end

    def share(request, out)
        File.open("main.cpp", 'w') { |f| f.write(request.body.string) }
        status = POpen4::popen4("./share.sh 2>&1") do |stdout, stderr, stdin, pid|
            stdin.close()
            out.write(stdout.read())
        end
    end

    # Returns the location. E.g: if the URL is "http://localhost.com/compile" then "ccompile" will be returned.
    def get_location(request)
        return request.params["REQUEST_PATH"][1..-1]
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
h.register("/Archive", Mongrel::DirHandler.new("Archive"))
puts "h.num_processors: #{h.num_processors}"
h.run.join

