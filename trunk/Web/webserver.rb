require 'rubygems'
require 'fileutils'
require 'mongrel'
require 'popen4'
require 'pp'
require 'thread'

$semaphore = Mutex.new


POpen4::popen4("whoami") { |stdout, stderr, stdin, pid|
    user = stdout.read().chomp
    if user != "webserver" then
        abort("Current user is #{user}. This script must be run by webserver.\n")
    end
}


class SimpleHandler < Mongrel::HttpHandler
	def process(request, response)
		response.start(200) do |head,out|
			head["Content-Type"] = "text/html"
            loc = get_location(request)
			case loc
			when ""
				FileUtils.copy_stream(File.new("cmd.html"), out)
			when "compile"
				$semaphore.synchronize {
					compile(request, out)
				}
            when /archive.*/
                FileUtils.copy_stream(File.new("archive.html"), out)
			when "favicon.ico"
				# Don't respond to favicon..
			else
				puts "Don't know how to respond to the request to #{location}."
			end
		end
    end

    def compile(request, out)
        File.open("request.txt", 'w') { |f| f.write(request.body.string) }
        status = POpen4::popen4("sudo -u sandboxer sh bin/process-request-sandboxed.sh 2>&1") do |stdout, stderr, stdin, pid|
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

