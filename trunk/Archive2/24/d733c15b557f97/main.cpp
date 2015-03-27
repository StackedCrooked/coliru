class MatrixElement
{
    private: // data
        unsigned int columnNr;
        double value;
        MatrixElement *next;
    public: // constructor and functions
        MatrixElement(unsigned int columnNr, MatrixElement* next, double value): columnNr(columnNr), value(value), next(next) {}
        unsigned int getColumnNr();
        double getValue();
        MatrixElement* getNext();
        void setNext(MatrixElement *next);
};

unsigned int MatrixElement::getColumnNr()
{
    return columnNr;
}

int main() {}
