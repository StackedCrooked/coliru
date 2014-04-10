#include <stdlib.h>
#include <stdio.h>

typedef void(*cmdf)();

void command1_undo();
void command1_redo();
void command2_undo();
void command2_redo();

int main()
{
    static const struct { cmdf undo,redo; } cmd = { command1_undo, command1_redo };
    cmdf action[] = { cmd.undo, cmd.redo };

    for (int i=1; i<100000; i*=42)
        action[rand()%2]();
}

void command1_undo() { puts(__FUNCTION__); }
void command1_redo() { puts(__FUNCTION__); }
void command2_undo() { puts(__FUNCTION__); }
void command2_redo() { puts(__FUNCTION__); }
