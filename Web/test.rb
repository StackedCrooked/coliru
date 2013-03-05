require 'timeout'
require 'pp'

def safe_popen(cmd)
  begin
    Timeout.timeout(3) do
      @my_pipe = IO.popen(cmd)
      until @my_pipe.eof?
        line = @my_pipe.readline
        yield line
      end
      Process.wait @my_pipe.pid
    end
  rescue Timeout::Error => e
    Process.kill 9, @my_pipe.pid
    yield e.to_s
  end
end

safe_popen('for i in `seq 100` ; do echo $i ; sleep 1 ; done') { |line|
  puts line
}
