#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>

int32_t getSeqnum(const char* text) {
    int32_t seqn = 0;

    // Get expected_seqnum from the message.
    // If processing wrong message, return 0
    for (const char *token = text; token; token = strchr(token, ' ')) {
      token = token + 1;    
      char *end;
      seqn=std::strtol(token, &end, 10);
      if (seqn && (token != end)) {
        return seqn;
      }
    }
    return 0;
}


int main () {
  std::string text = "MsgSeqNum too low, expecting 2589 but received 1";
  std::cout << getSeqnum(text.c_str()) << std::endl;
}