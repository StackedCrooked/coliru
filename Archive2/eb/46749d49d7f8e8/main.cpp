struct LinkStack
{
    LinkStack();
    bool isEmptyStack() const;
    bool isFullStack() const;
    LinkStack* stackTop;
};

#define NULL nullptr

LinkStack::LinkStack()
{
    stackTop = NULL;
}

bool LinkStack::isEmptyStack() const
{
    return(stackTop == NULL);
}

bool LinkStack::isFullStack() const
{
    return false;
}