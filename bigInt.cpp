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
    this->set_Bin(this->to_Bin(n));
}

void bigInt::set_Bin(string b) {
    while (b[0] == '0') b = b.substr(1);
    this->bin = b;
    this->numbers = this->to_Hex(b);
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
    if (this->getSign() != b.sign) return this->subtract_Bin(b);

    string carry = "0";
    string s1, s2, res;
    s1 = this->get_Bin();
    s2 = b.bin;
    while (s1.length() < s2.length()) s1 = '0' + s1;
    while (s1.length() > s2.length()) s2 = '0' + s2;
    int i = s1.length() - 1;
    res = "";
    while (i > -1) {
        if (carry == "1") {
            if (s2[i] == '0') {
                s2[i] = '1';
                carry = "0";
            }
            else s2[i] = '0';
        }
        if (s1[i] == s2[i]) {
            if (s1[i] == '1') carry = "1";
            res = '0' + res;
        }
        else res = '1' + res;
        i--;
    }
    if (carry == "1") res = '1' + res;
    bigInt result(this->to_Hex(res));
    if (this->getSign() == 1) result.setSign(1);
    else result.setSign(0);
    return result;
}

//bigInt bigInt::subtract(bigInt b) {
//    bigInt temp(b.get_Hexa());
//    if (b.getSign() == 0) temp.setSign(1);
//    else temp.setSign(0);
//    return this->add(temp);
//}

bigInt bigInt::multiply(bigInt b) {
    if (b.bin == "0000" || this->bin == "0000") return bigInt("0");
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
            temp.setNumb(t);
            result = result.add(temp);
            x10 = x10 + "0";
        }
    }
    if (this->sign == b.sign) result.sign = 1;
    else result.sign = 0;
    result.bin = result.to_Bin(result.get_Hexa());
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
    
    if (this->sign != b.sign) {
        bigInt revB(b.get_Hexa());
        if (b.sign == 0) revB.setSign(1);
        else revB.setSign(0);
        return this->add(revB);
    }
    
    bigInt result;
    string carry = "0";
    string s1, s2;
    if (this->greater_ValueThan(b)) {
        s1 = this->bin;
        s2 = b.bin;
        if (this->sign == 1) result.setSign(1);
        else result.setSign(0);
    }
    else {
        s1 = b.bin;
        s2 = this->bin;
        if (b.sign == 0) result.setSign(1);
        else result.setSign(0);
    }

    while (s1.length() > s2.length()) s2 = '0' + s2;
    while (s1.length() < s2.length()) s1 = '0' + s1;
    string res = "";
    for (int i = s1.length() - 1; i > -1 ; i--) {
        if (s1[i] == s2[i]) res = carry + res;
        else if (s1[i] == '1' && s2[i] == '0') {
            if (carry == "0") res = '1' + res;
            else {
                res = '0' + res;
                carry = "0";
            }
        }
        else {
            if (carry == "0") {
                carry = "1";
                res = '1' + res;
            }
            else 
                res = '0' + res;
        }
        
    }
    result.set_Bin(res);
    return result;
}

bigInt bigInt::mod(bigInt b) {
    if (b.bin == "1") return bigInt("0");
    if (!this->greater_ValueThan(b)) return *this;
    else if (this->equal(b)) return bigInt("0");

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
        else if (b.equal(t))
            return bigInt("0");
        else 
            break;
        
     } while (index < s1.length());
    t.numbers = t.to_Hex(t.get_Bin());
    t.sign = this->sign;
    return t;
}

bigInt bigInt::divide(bigInt b) {
    if (!this->greater_ValueThan(b)) return bigInt("0");

    string s1 = this->get_Bin();
    string s2 = b.get_Bin();
    string temp = s1.substr(0, s2.length());
    int index = s2.length();
    bigInt t(this->to_Hex(temp));
    string res = "";
    do {
        //t < b
        while (index < s1.length() && b.greater_ValueThan(t)) {
            t.bin = t.get_Bin() + s1[index++];
            t.numbers = t.to_Hex(t.bin);
            res.push_back('0');
        }
        if (!b.greater_ValueThan(t)) {
            res.push_back('1');
            t = t.subtract_Bin(b);
            t.bin = t.get_Bin() + s1[index++];
            t.numbers = t.to_Hex(t.bin);
            if (index == s1.length()) {
                if (b.greater_ValueThan(t)) res += '0';
                else res += '1';
            }
            t.numbers = t.to_Hex(t.bin);
        }
        else
            break;

    } while (index < s1.length());
    bigInt result(t.to_Hex(res));
    return result;
}

bool bigInt::equal(bigInt b) {
    string s1 = this->get_Bin();
    string s2 = b.get_Bin();
    if (s1.length() != s2.length()) return false;
    for (int i = 0; i < s1.length(); i++)
        if (s1[i] != s2[i])
            return false;
    return true;
}

vector<bigInt> bigInt::expand_Euclid(bigInt a, bigInt b) {
    vector<bigInt> r, x, y, q, res;

    if (a.greater_ValueThan(b)) {
        r.push_back(a);
        r.push_back(b);
    }
    else {
        r.push_back(b);
        r.push_back(a);
    }
    bigInt zero("0");
    bigInt one("1");
    bigInt tempa(a);
    bigInt tempb(b);
    x = { zero, one };
    y = { one, zero };
    q = { zero, zero };
    int i = 2;
    while (!r[r.size() - 1].equal(zero)) {
        a = r[i - 2];
        b = r[i - 1];
        r.push_back(a.mod(b));
        q.push_back(a.divide(b));
        bigInt qxi = q[i].multiply(x[i - 1]);
        x.push_back(x[i - 2].subtract_Bin(qxi));
        bigInt qyi = q[i].multiply(y[i - 1]);
        y.push_back(y[i - 2].subtract_Bin(qyi));
        i++;
    }

    bigInt v1 = x[x.size() - 2].multiply(tempa);
    bigInt v2 = y[y.size() - 2].multiply(tempb);
    v1 = v1.add(v2);
    if (v1.equal(b)) 
        res = { b, x[x.size() - 2], y[y.size() - 2] };
    else
        res = { b, y[y.size() - 2], x[x.size() - 2] };
    return res;
}


bigInt bigInt::Montgomery(bigInt a, bigInt b, bigInt R, bigInt N) {
    cout << "\nMontgomery" << endl;
    a = a.multiply(R);
    a = a.mod(N);
    b = b.multiply(R);
    b = b.mod(N);
    vector<bigInt> f_R1_N1 = this->expand_Euclid(R, N);

    bigInt c_ = a.multiply(b);
    c_ = c_.multiply(f_R1_N1[1]);
    c_ = c_.mod(N);
    bigInt c = c_.multiply(f_R1_N1[1]);
    c = c.mod(N);
   
    return c;
}

//k la chuoi nhi phan
bigInt bigInt::quick_Pow_Mod_N(string k, bigInt N) {
    if (k.length() == 1) return this->mod(N);
    bigInt temp = this->quick_Pow_Mod_N(k.substr(0, k.length() - 1), N);
    //chan
    if (k[k.length() - 1] == '0') return temp.multiply(temp).mod(N);
    //le
    else return temp.multiply(temp).mod(N).multiply(*this).mod(N);     
}

//miller rabin ==> n is prime ?
bool bigInt::miller_Rabin() {
    /*
        1. find n-1 = 2^k . m
        2. choose 1 < a < n-1
        3. compute b_0 = a^m (mod n), b_i = (b_i-1)^2 (mod n)
    */
    // n - 1 = 2^k . m
    bigInt n_1 = this->subtract_Bin(bigInt("1"));

    // string n - 1
    string sn_1 = n_1.get_Bin();

    //find k & m
    long k = 0;
    while (sn_1[sn_1.length() - 1] == '0') {
        k++;
        sn_1 = sn_1.substr(0, sn_1.length() - 1);
    }
    if (k == 0) return false; //so chan
    bigInt m;
    m.set_Bin(sn_1);

    bigInt a("2");// = n.subtract_Bin(m);
    bigInt b0 = a.quick_Pow_Mod_N(m.get_Bin(), *this);
    if (b0.get_Bin() == "1" || b0.get_Bin() == n_1.get_Bin()) return true;

    while (k-- > 0) {
        b0 = b0.multiply(b0).mod(*this);
        if (b0.get_Bin() == "1" || b0.get_Bin() == n_1.get_Bin()) return true;
    }
    return false;
}


