

struct Logger;

struct Console {
    Console(Logger * L): L(L) {}// Copy pointer
    Logger* L;
};

struct Logger {
    Logger(Console * C): C(C) {}
    Console* C;
};

extern Logger L;

Console C(&L); // BUT L IS NOT DEFINED YET
Logger L(&C);

int main()
{

}


