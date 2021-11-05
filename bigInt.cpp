#include "bigInt.h"

bigInt::bigInt(){
    this->sign = 1;
    this->numbers = "";
    this->bin = "";
}

bigInt::bigInt(const string s){
    if (s[0] == '-'){
        this->sign = 0;
        this->numbers = s.substr(1);
    }
    else {
        this->numbers = s;
        this->sign = 1;
    }
    this->bin = this->to_Bin(this->numbers);
}

bigInt::bigInt(const string s, int si) {
    this->numbers = s;
    this->setSign(si);
    this->bin = this->to_Bin(numbers);
}

bigInt::bigInt(const bigInt& b) {
    this->setSign(b.sign);
    this->setNumb(b.numbers);
    this->bin = b.bin;
}

bigInt::~bigInt() {

}

int bigInt::getSign() {
    return sign;
}

void bigInt::output() {
    if (this->sign == 0) cout << "-";
    cout << this->numbers;
}

void bigInt::output(bigInt a, bigInt b, char opera) {
    a.output();
    cout << " " << opera << " ";
    b.output();
    cout << " = "; 
    this->output();
    cout << endl;
}

void bigInt::setSign(int s) {
    if (s > 0) this->sign = 1;
    else this->sign = 0;
}

void bigInt::setNumb(string n) {
    this->numbers = n;
}

void bigInt::set_Bin(string b) {
    while (b[0] == '0') b = b.substr(1);
    this->bin = b;
}
bool bigInt::greater_ValueThan(bigInt b) {
    if (this->bin.length() > b.bin.length()) return true;
    else if (this->numbers.length() < b.numbers.length()) return false;
    else {
        for (int i1 = 0, i2 = 0; i1 < b.numbers.length(); i1++, i2++) {
            if (this->numbers[i1] != b.numbers[i2]) {
                if (this->numbers[i1] > b.numbers[i2]) return true;
                else return false;
            }
        }
        return true;
    }
}

string bigInt::get_Hexa() {
    return this->numbers;
}

bigInt bigInt::add(bigInt b){
   
    bigInt result;
    string number1 = this->get_Hexa();
    string number2 = b.get_Hexa();
    int carry = 0;
    int res;
    int value;
    if (this->sign == b.sign) {
        result.sign = b.sign;
        int index1, index2;
        for (index1 = number1.length() - 1, index2 = number2.length() - 1; index1 > -1 || index2 > -1;) {
            value = 0;
            //chuyen ve so nguyen
            if (index1 > -1) {
                if (64 < number1[index1] && number1[index1] < 71)
                    value += number1[index1] - 55;
                else if (47 < number1[index1] && number1[index1] < 58)
                    value += number1[index1] - 48;
            }
            if (index2 > -1) {
                if (64 < number2[index2] && number2[index2] < 71)
                    value += number2[index2] - 55;
                else if (47 < number2[index2] && number2[index2] < 58)
                    value += number2[index2] - 48;
            }
            //tinh
            value += carry;
            if (value > 15) {
                value -= 16;
                carry = 1;
            }
            else
                carry = 0;
            if (value > 9)
                result.numbers = char(value + 55) + result.numbers;
            else
                result.numbers = char(value + 48) + result.numbers;

            if (index1 > -1) index1--;
            if (index2 > -1) index2--;
        }
    }

    else {
        //bool greater = this->greaterValue(b);
        if (this->sign == 1 && b.sign == 0) {
            result.sign = this->sign;
            int index1, index2;
            for (index1 = number1.length() - 1, index2 = number2.length() - 1; index1 > -1 || index2 > -1;) {
                value = 0;
                //chuyen ve so nguyen
                if (index1 > -1) {
                    if (64 < number1[index1] && number1[index1] < 71)
                        value += number1[index1] - 55;
                    else if (47 < number1[index1] && number1[index1] < 58)
                        value += number1[index1] - 48;
                }
                if (index2 > -1) {
                    if (64 < number2[index2] && number2[index2] < 71)
                        value -= number2[index2] - 55;
                    else if (47 < number2[index2] && number2[index2] < 58)
                        value -= number2[index2] - 48;
                }
                //tinh
                value += carry;
                if (value > 15) {
                    value -= 16;
                    carry = 1;
                }
                else if (-1 < value && value < 16) {
                    carry = 0;
                }
                else {
                    carry = -1;
                    value += 16;
                }
                if (value > 9)
                    result.numbers = char(value + 55) + result.numbers;
                else
                    result.numbers = char(value + 48) + result.numbers;

                if (index1 > -1) index1--;
                if (index2 > -1) index2--;
            }
        }
        else {
            result.sign = b.sign;
            int index1, index2;
            for (index1 = number1.length() - 1, index2 = number2.length() - 1; index1 > -1 || index2 > -1;) {
                value = 0;
                //chuyen ve so nguyen
                if (index1 > -1) {
                    if (64 < number1[index1] && number1[index1] < 71)
                        value -= number1[index1] - 55;
                    else if (47 < number1[index1] && number1[index1] < 58)
                        value -= number1[index1] - 48;
                }
                if (index2 > -1) {
                    if (64 < number2[index2] && number2[index2] < 71)
                        value += number2[index2] - 55;
                    else if (47 < number2[index2] && number2[index2] < 58)
                        value += number2[index2] - 48;
                }
                //tinh
                value += carry;
                if (value > 15) {
                    value -= 16;
                    carry = 1;
                }
                else if (-1 < value && value < 10) {
                    carry = 0;
                }
                else {
                    carry = -1;
                    value = abs(value);
                }
                if (value > 9)
                    result.numbers = char(value + 55) + result.numbers;
                else
                    result.numbers = char(value + 48) + result.numbers;

                if (index1 > -1) index1--;
                if (index2 > -1) index2--;
            }            
        }
    }
    if (carry == -1) result.sign = 0;
    else if (carry == 1) result.numbers = char(carry + 48) + result.numbers;
    if (result.numbers[0] == '0') result.numbers = result.numbers.substr(1);
    return result;
}

bigInt bigInt::subtract(bigInt b) {
    bigInt temp(b.get_Hexa());
    if (b.getSign() == 0) temp.setSign(1);
    else temp.setSign(0);
    return this->add(temp);
}

bigInt bigInt::multiply(bigInt b) {

    bigInt result;
    
    string n1 = this->numbers;
    string n2 = b.numbers;
    string t;
    string x10 = "";

    int v1, v2, v;
    for (int i1 = n1.length() - 1; i1 > -1; i1--) {
        bigInt temp;
        if (64 < n1[i1] && n1[i1] < 71) v1 = n1[i1] - 55;
        else if (47 < n1[i1] && n1[i1] < 58) v1 = n1[i1] - 48;
        x10 = "";
        for (int i = n1.length() - 1; i > i1; i--) x10 += "0";

        for (int i2 = n2.length() - 1; i2 > -1; i2--) {
            t = "";
            if (64 < n2[i2] && n2[i2] < 71) v2 = n2[i2] - 55;
            else if (47 < n2[i2] && n2[i2] < 58) v2 = n2[i2] - 48;

            v = v1 * v2;

            if (v % 16 > 9) t = char(v % 16 + 55) + t;
            else t = char(v % 16 + 48) + t;
            if (v / 16 > 9) t = char(v / 16 + 55) + t;
            else t = char(v / 16 + 48) + t;
            t = t + x10;
            temp.numbers = t;
            result = result.add(temp);
            x10 = x10 + "0";
        }
    }
    if (this->sign == b.sign) result.sign = 1;
    else result.sign = 0;
    return result;
}

string bigInt::get_Bin() {
    while (this->bin[0] == '0') this->bin = this->bin.substr(1);
    return this->bin;
}
string bigInt::to_Bin(string s) {
    string bin = "";
    for (int i = 0; i < s.length(); i++) {
        switch (s[i])
        {
        case '0':
            bin += "0000" ;
            break;
        case '1':
            bin += "0001" ;
            break;
        case '2':
            bin += "0010" ;
            break;
        case '3':
            bin += "0011" ;
            break;
        case '4':
            bin += "0100" ;
            break;
        case '5':
            bin += "0101" ;
            break;
        case '6':
            bin += "0110" ;
            break;
        case '7':
            bin += "0111" ;
            break;
        case '8':
            bin += "1000" ;
            break;
        case '9':
            bin += "1001" ;
            break;
        case 'A':
            bin += "1010" ;
            break;
        case 'B':
            bin += "1011" ;
            break;
        case 'C':
            bin += "1100" ;
            break;
        case 'D':
            bin += "1101" ;
            break;
        case 'E':
            bin += "1110" ;
            break;
        case 'F':
            bin += "1111" ;
            break;
        }
    }
    return bin;
}

string bigInt::to_Hex(string bin) {
    string res = "";
    string s1 = bin;
    while (s1.length() % 4 != 0) s1 = '0' + s1;
    for (int i = 0; i < s1.length(); i += 4) {
        string temp = s1.substr(i, 4);
        if (temp == "0000") res += '0';
        else if (temp == "0001") res += '1';
        else if (temp == "0010") res += '2';
        else if (temp == "0011") res += '3';
        else if (temp == "0100") res += '4';
        else if (temp == "0101") res += '5';
        else if (temp == "0110") res += '6';
        else if (temp == "0111") res += '7';
        else if (temp == "1000") res += '8';
        else if (temp == "1001") res += '9';
        else if (temp == "1010") res += 'A';
        else if (temp == "1011") res += 'B';
        else if (temp == "1100") res += 'C';
        else if (temp == "1101") res += 'D';
        else if (temp == "1110") res += 'E';
        else res += 'F';
    }
    return res;
}

bigInt bigInt::subtract_Bin(bigInt b) {
    int carry = 0;
    string s1 = this->bin;
    string s2 = b.bin;
    while (s1.length() > s2.length()) s2 = '0' + s2;
    while (s1.length() < s2.length()) s1 = '0' + s1;
    string res = "";
    for (int i = this->bin.length() - 1; i > -1 ; i--) {
        if (s1[i] == s2[i]) {
            if (carry == 0) res = '0' + res;
            else res ='1' + res;
        }
        else if (s1[i] == '1' && s2[i] == '0') {
            if (carry == 0) res = '1' + res;
            else {
                res = '0' + res;
                carry = 0;
            }
        }
        else {
            if (carry == 0) {
                res = '1' + res;
                carry = 1;
            }
            else 
                res = '0' + res;           
        }
        
    }
    bigInt result;
    result.set_Bin(res);
    result.numbers = result.to_Hex(res);
    if (this->greater_ValueThan(b)) {
        if (this->sign == 1) result.setSign(1);
        else result.setSign(0);
    }
    else {
        if (b.sign == 0) result.setSign(1);
        else result.setSign(0);
    }
    return result;
}

bigInt bigInt::mod(bigInt b) {
    if (!this->greater_ValueThan(b)) return *this;

    string s1 = this->get_Bin();
    string s2 = b.get_Bin();
    string temp = s1.substr(0, s2.length());
    int index = s2.length();
    bigInt t(this->to_Hex(temp));
    do {
        //t < b
        while (index < s1.length() && b.greater_ValueThan(t)) {
            t.bin = t.get_Bin() + s1[index++];
            t.numbers = t.to_Hex(t.bin);
        }
        if (!b.greater_ValueThan(t))
            t = t.subtract_Bin(b);
        else 
            break;
        
     } while (index < s1.length());
    t.numbers = t.to_Hex(t.get_Bin());
    t.sign = this->sign;
    return t;
}




