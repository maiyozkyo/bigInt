#include "bigInt.h"
#include <time.h>
using namespace std;

void working_WithFile() {
    ifstream fin;
    ofstream fout;
    fin.open("input.txt");
    fout.open("output.txt");

    string data, cal;
    if (fin.is_open()) {
        while (!fin.eof()) {
            getline(fin, data);
            bigInt n1(data);
            getline(fin, cal);
            getline(fin, data);
            bigInt n2(data);
            if (cal == "+") n1 = n1.add(n2);
            else if (cal == "-") n1 = n1.subtract_Bin(n2);
            else if (cal == "*") n1 = n1.multiply(n2);
            else if (cal == "%") 
                n1 = n1.mod(n2);
            if (n1.getSign() == 0) cal = "-";
            else cal = "";
            fout << cal << n1.get_Hexa() << endl;
        }
        cout << "Successfully!" << endl;
    }
    else {
        fout << "Some error happend" << endl;
        cout << "Fail!!!" << endl;
    }
    fout.close();
    fin.close();
}


int main() {
    // Week 1
    // working_WithFile();
    // Week 4
    /*bigInt a("7");
    bigInt b("10");
    bigInt R("80");
    bigInt N("6D");
    bigInt c = a.Montgomery(a, b, R, N);
    c.output();*/
    // Week 5
    /*bigInt d("F");
    bigInt n("33");
    bigInt e = d.quick_Pow_Mod_N("100111", n);
    e.output();*/
    bigInt f("33");
    cout << f.miller_Rabin();
    return 0;
}