require 'rubygems'
require 'fileutils'
require 'mongrel'
require 'popen4'
require 'pp'
require 'thread'

POpen4::popen4("whoami") do |stdout, stderr, stdin, pid|
    puts "whoami: #{stdout.read()}"
end



$local = false
$command = "./timeout 1 nice -n 10 systrace -a -t -d . -e ./test >>output 2>&1"
if $local
    $command = "./timeout 1 nice -n 10 ./test >>output 2>&1"
end


$host = $local ? "localhost" : "stacked-crooked.com"
$port = $local ? "4000" : 80

$semaphore = Mutex.new


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
        File.open("main.cpp", 'w') { |f| f.write(request.body.string) }

        # COMPILE
        status = POpen4::popen4("g++-4.7 -o test -Wall -Werror -Wextra -pedantic-errors -std=c++0x -pthread -I/usr/local/include main.cpp >output 2>&1") do |stdout, stderr, stdin, pid|
            stdin.close()
        end

        if status == 0
            status = POpen4::popen4($command) do |stdout, stderr, stdin, pid|
                stdin.close()
            end
            if status != 0
                out << "Runtime error.\n"
            end
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

