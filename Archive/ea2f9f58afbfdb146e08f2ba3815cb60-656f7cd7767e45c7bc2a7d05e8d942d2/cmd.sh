find /Archive -type f -name timestamp \
  | xargs -I {} bash -c 'mkdir -p $(cat {}) && cp "$(dirname {})/main.cpp" > "$(cat {})/"'