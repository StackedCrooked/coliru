function trace()
{
    echo "COMMAND $BASH_COMMAND"
}

set -o functrace
shopt -s extdebug
trap trace DEBUG

echo 1 && echo 11
echo 2
3