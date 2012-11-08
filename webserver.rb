require 'rubygems'
require 'fileutils'
require 'mongrel'
require 'popen4'
require 'pp'
require 'thread'


$local = false


$host = $local ? "localhost" : "stacked-crooked.com"
$port = $local ? "4000" : 80

$semaphore = Mutex.new
$counter = Time.now.to_i


class SimpleHandler < Mongrel::HttpHandler
    def process(request, response)
        response.start(200) do |head,out|
            head["Content-Type"] = "text/html"
            case get_location(request)
            when ""
                FileUtils.copy_stream(File.new("cmd.html"), out)
            when "compile"
                $semaphore.synchronize {
                    compile(request, out)
                }
            when "favicon.ico"
                # Don't respond to favicon..
            else
                puts "Don't know how to respond to the request to #{location}."
            end
        end
    end

    def compile(request, out)
        # WRITE MAIN
	#$counter += 1
        File.open("main_#{$counter}.cpp", 'w') { |f| f.write(request.body.string) }

        # COMPILE
        status = POpen4::popen4("g++-4.7 -o test -Wall -Werror -Wextra -pedantic-errors -std=c++0x -pthread main_#{$counter}.cpp >output 2>&1") do |stdout, stderr, stdin, pid|
            stdin.close()
        end

        if status == 0
            status = POpen4::popen4("./timeout 5 nice -n 10 systrace -a -t -d . -e ./test >>output 2>&1") do |stdout, stderr, stdin, pid|
                stdin.close()
            end
            if status != 0
                out << "Runtime error.\n"
            end
        else
            out << "Compilation failed with the following errors:\n\n"
        end
        FileUtils.copy_stream(File.new("output"), out)
    end

    # Returns the location. E.g: if the URL is "http://localhost.com/compile" then "ccompile" will be returned.
    def get_location(request)
        return request.params["REQUEST_PATH"][1..-1]
    end

end


puts "Listening to #{$host}:#{$port}"
h = Mongrel::HttpServer.new($host, $port)
h.register("/", SimpleHandler.new)
puts "h.num_processors: #{h.num_processors}"
h.run.join

