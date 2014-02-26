(time -p curl -s stacked-crooked.com/compile -d "{ \"cmd\": \"echo $(echo "$(date +%Y-%m-%d\ %H:%M:%S)")\"}") 2>&1 | head -n2 | xargs | perl -pe 's,real ,,'
