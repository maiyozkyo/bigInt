#ifndef __BIGHEX_H__
#define __BIGHEX_H__

#pragma once

#include <iostream>
#include <string>

#define MAX_SIZE 2047
using namespace std;

class BigHex 
{
  private:
    string    value;
    bool      isNegative;

  public:
    BigHex();
    BigHex(string number);
    BigHex(const BigHex& number);
    ~BigHex();
    
    friend ostream& operator<<(ostream& stream, BigHex number);
    friend istream& operator>>(istream& stream, BigHex* &number);
    
    int CharToInt(char character);
    char IntToChar(int n);
    void Trim();
    void Reverse();
    bool EqualZero();
    void changeSigned();
    BigHex& changeSignedCopy();

    BigHex& operator=(const BigHex& number);
    bool operator<(const BigHex& number);
    bool operator>(const BigHex& number);
    bool operator==(const BigHex& number);
    bool operator!=(const BigHex& number);

    BigHex& operator+(BigHex& number);

    BigHex& operator-(BigHex& number);
    BigHex& operator*(BigHex& number);
    BigHex& operator%(BigHex& number);
    BigHex& operator/(BigHex& number);
    BigHex& operator^(BigHex& number);

    BigHex& gcd(BigHex& a, BigHex& b);
    BigHex& powerMod(BigHex& b, BigHex& n);

    BigHex& REDC(BigHex& R, BigHex& N, BigHex& T);
    BigHex& MultiprecisionREDC(BigHex& N, BigHex& R, BigHex& N1, BigHex& T);

    BigHex& Montgomery(BigHex& a, BigHex& b, BigHex& R, BigHex& N);
};

#endif // __BIGHEX_H__