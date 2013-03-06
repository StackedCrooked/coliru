require 'timeout'
require 'pp'

def safe_popen(cmd)
  begin
    Timeout.timeout(3) do
      @stdout = IO.popen(cmd)
      until @stdout.eof?
        line = @stdout.readline
        yield line
      end
      Process.wait @stdout.pid
    end
  rescue Timeout::Error => e
    Process.kill 9, @stdout.pid
    yield e.to_s
  end
end

safe_popen('for i in `seq 100` ; do echo $i ; sleep 1 ; done') { |line|
  puts line
}
