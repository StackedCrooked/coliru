void fillValues(xmlNodePtr nodePtr, Puzzle::iterator it) {
    xmlNodePtr trPtr = nodePtr->children;
trstart:
    xmlNodePtr tdPtr = trPtr->children;
tdstart:
    xmlNodePtr inputPtr = tdPtr->children;
inputstart:
    std::string nodename = (char*) inputPtr->name;
    if (nodename == "input") {
        int val = hasValue(inputPtr);
        *it = val;
        it++;
    }
    inputPtr = inputPtr->next;
    if (inputPtr)
        goto inputstart;

    tdPtr = tdPtr->next;
    if (tdPtr)
        goto tdstart;

    trPtr = trPtr->next;
    if (trPtr)
        goto trstart;
}
