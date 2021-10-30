#include "iostream"
#include "string"
#include "fstream"
using namespace std;

class bigInt{
    private:
        string numbers;
        int sign;

    public:
        bigInt();
        bigInt(const string);
        bigInt(const string, int);
        bigInt(const bigInt&);

        void output();
        void output(bigInt, bigInt, char);
        void setSign(int);
        void setNumb(string);

        int getSign();
        
        bool greater_ValueThan(bigInt);

        string getString();
        
        bigInt add(bigInt);
        bigInt subtract(bigInt);
        bigInt multiply(bigInt);
        bigInt mod(bigInt);
};