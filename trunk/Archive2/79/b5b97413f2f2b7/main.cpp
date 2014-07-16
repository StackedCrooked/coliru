

struct Logger; //forward declare Logger

struct Console {
    Console(Logger * L): L(L) {}
    Logger* L;
};

struct Logger {
    Logger(Console * C): C(C) {}
    Console* C;
};

extern Logger L;  //forward declare Logger L

Console C(&L);
Logger L(&C);

int main()
{

}


