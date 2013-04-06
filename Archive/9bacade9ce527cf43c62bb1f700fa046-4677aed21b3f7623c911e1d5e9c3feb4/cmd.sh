function json_escape(){
  echo -n "$1" | python -c 'import json,sys; print json.dumps(sys.stdin.read())'
}
json_escape 'abc'