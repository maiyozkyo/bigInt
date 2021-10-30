#include "bigInt.h"

bigInt::bigInt(){
    this->sign = 1;
    this->numbers = "";
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
}

bigInt::bigInt(const string s, int si) {
    this->numbers = s;
    this->setSign(si);
}

bigInt::bigInt(const bigInt& b) {
    this->setSign(b.sign);
    this->setNumb(b.numbers);
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

bool bigInt::greater_ValueThan(bigInt b) {
    if (this->numbers.length() > b.numbers.length()) return true;
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

string bigInt::getString() {
    return this->numbers;
}

bigInt bigInt::add(bigInt b){
   
    bigInt result;
    string number1 = this->getString();
    string number2 = b.getString();
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
    bigInt temp(b.getString());
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

bigInt bigInt::mod(bigInt b) {
    while (this->greater_ValueThan(b)) 
        *this = this->subtract(b);
    return *this;
}


