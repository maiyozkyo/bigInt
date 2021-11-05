#include "iostream"
#include "string"
#include "fstream"
using namespace std;

class bigInt{
    private:
        string numbers;
        string bin;
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
        string to_Bin(string);
        string to_Hex(string);
        string get_Bin();
        bool greater_ValueThan(bigInt);

        void set_Bin(string);
        string get_Hexa();
        
        bigInt add(bigInt);
        bigInt subtract(bigInt);
        bigInt subtract_Bin(bigInt);
        bigInt multiply(bigInt);
        bigInt mod(bigInt);

        ~bigInt();
};