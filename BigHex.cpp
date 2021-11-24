#include "BigHex.h"

BigHex::BigHex()
{
  this->isNegative = false;
  this->value = "";
}

BigHex::BigHex(string number) 
{
  if(number[0] == '-')
  {
    this->isNegative = true;
    this->value = number.substr(1, number.size());
  }
  else
  {
    this->isNegative = false;
    this->value = number;
  }
}

BigHex::BigHex(const BigHex& number)
{
  this->isNegative = number.isNegative;
  this->value = number.value;
}

BigHex::~BigHex() {}

// return -1 if character is not a hexa number
int BigHex::CharToInt(char character) 
{
  if(48 <= character && character <= 57)
  {
    return character - 48;
  }
  else
  {
    if(65 << character && character <=70)
    {
      return (character - 65) + 10;
    }
  }
  return -1;
}

char BigHex::IntToChar(int number)
{
  if(0 <= number && number <=9)
  {
    return number + 48;
  }
  else
  {
    if(10 << number && number <=15)
    {
      return (number - 10) + 65;
    }
  }
  return 0;
}

void BigHex::Trim()
{
  while(this->value.size() > 1 && this->value[0] == '0')
  {
    this->value = this->value.substr(1, this->value.size());
  }
}

void BigHex::Reverse()
{
  int length = this->value.size();
  for(int i = 0; i < length / 2; i++)
  {
    char temp = this->value[i];
    this->value[i] = this->value[length - i - 1];
    this->value[length - i - 1] = temp;
  }
}

bool BigHex::EqualZero()
{
  for(int i = 0; i < this->value.size(); i++)
  {
    if(this->value[i] != '0')
      return false;
  }
  return true;
}

void BigHex::changeSigned()
{
  this->isNegative = !this->isNegative; 
}

BigHex& BigHex::changeSignedCopy()
{
  BigHex* result = new BigHex();
  result->value = this->value;
  result->isNegative = !this->isNegative;
  return *result;
}

ostream& operator<<(ostream& stream, BigHex number) 
{
  if(number.isNegative)
    stream << "-";
  stream << number.value;
  return stream;
}

istream& operator>>(istream& stream, BigHex* &number)
{
  cout << "Enter Hexa number: "; 
  string sValue;
  stream >> sValue;
  number = new BigHex(sValue);
  return stream;
}

BigHex& BigHex::operator=(const BigHex& number)
{
  if(this != &number)
  {
    this->isNegative = number.isNegative;
    this->value = number.value;
  }
  return *this;
}

bool BigHex::operator<(const BigHex& number)
{
  if(this->isNegative && !number.isNegative)
    return true;
  else if (!this->isNegative && number.isNegative)
    return false;
  else if(this->value.size() < number.value.size())
    return true;
  else if(this->value.size() > number.value.size())
    return false;
  else
  {
    bool isEqual = true;
    for(int i = 0; i < this->value.size(); i++)
    {
      if(this->value[i] != number.value[i])
        isEqual = false;
      if(this->value[i] > number.value[i])
        return false;
    }
    if(isEqual)
      return false;
    else
      return true;
  }
}

bool BigHex::operator>(const BigHex& number)
{
  if(this->isNegative && !number.isNegative)
    return false;
  else if (!this->isNegative && number.isNegative)
    return true;
  else if(this->value.size() < number.value.size())
    return false;
  else if(this->value.size() > number.value.size())
    return true;
  else
  {
    bool isEqual = true;
    for(int i = 0; i < this->value.size(); i++)
    {
      if(this->value[i] != number.value[i])
        isEqual = false;
      if(this->value[i] < number.value[i])
        return false;
    }
    if(isEqual)
      return false;
    else
      return true;
  }
}

bool BigHex::operator==(const BigHex& number)
{
  if(this->isNegative != number.isNegative)
    return false;
  if(this->value.size() != number.value.size())
    return false;
  for(int i = 0; i < this->value.size(); i++)
    if(this->value[i] != number.value[i])
      return false;
  return true;
}

bool BigHex::operator!=(const BigHex& number)
{
  if(this->isNegative != number.isNegative)
    return true;
  if(this->value.size() != number.value.size())
    return true;
  for(int i = 0; i < this->value.size(); i++)
    if(this->value[i] != number.value[i])
      return true;
  return false;
}

BigHex& BigHex::operator+(BigHex& number)
{
  BigHex* result = new BigHex();

  // Check Signed to change operator to sub
  if(this->isNegative && !number.isNegative)
  {
    *result = number - this->changeSignedCopy();
    return *result;
  }

  if(!this->isNegative && number.isNegative)
  {
    *result = *this - number.changeSignedCopy();
    return *result;
  }

  int lengthThis = this->value.size();
  int lengthNumber = number.value.size();

  int maxLength = 0;
  int minLength = 0;
  if (lengthThis > lengthNumber)
  {
    maxLength = lengthThis;
    minLength = lengthNumber;
  }
  else
  {
    maxLength = lengthNumber;
    minLength = lengthThis;
  }

  int memoryValue = 0;
  int i;
  for(i = 0; i < minLength; i++)
  {
    char digitThis = this->value[lengthThis - i - 1];
    char digitNum = number.value[lengthNumber - i - 1];

    int intValueThis = CharToInt(digitThis);
    int intValueNumber = CharToInt(digitNum);

    int intResult = intValueThis + intValueNumber + memoryValue;
    memoryValue = intResult / 16;
    intResult = intResult % 16;

    result->value += IntToChar(intResult);
  }
  
  if(lengthThis > lengthNumber)
  {
    for(; i < maxLength; i++)
    {
      char digitThis = this->value[lengthThis - i - 1];

      int intValueThis = CharToInt(digitThis);

      int intResult = intValueThis + memoryValue;
      memoryValue = intResult / 16;
      intResult = intResult % 16;

      result->value += IntToChar(intResult);
    }
  }
  else
  {
    for(; i < maxLength; i++)
    {
      char digitNum = number.value[lengthNumber - i - 1];

      int intValueNumber = CharToInt(digitNum);

      int intResult = intValueNumber + memoryValue;
      memoryValue = intResult / 16;
      intResult = intResult % 16;

      result->value += IntToChar(intResult);
    }
  }
  if(memoryValue > 0)
    result->value += IntToChar(memoryValue);
  
  result->Reverse();
  result->isNegative = this->isNegative;
  result->Trim();
  return *result;
}

BigHex& BigHex::operator-(BigHex& number)
{
  BigHex* result = new BigHex();
  
  // Check Signed to change operator to plus
  if(this->isNegative && !number.isNegative)
  {
    return *this + number.changeSignedCopy();
  }
  if(!this->isNegative && number.isNegative)
  {
    return *this + number.changeSignedCopy();
  }
  if(this->isNegative && number.isNegative)
  {
    return number.changeSignedCopy() + *this;
  }

  if(*this < number)
  {
    *result = number - *this;
    result->isNegative = true;
    return *result;
  }

  int lengthThis = this->value.size();
  int lengthNumber = number.value.size();
  int maxLength = 0;
  int minLength = 0;
  if (lengthThis > lengthNumber)
  {
    maxLength = lengthThis;
    minLength = lengthNumber;
  }
  else
  {
    maxLength = lengthNumber;
    minLength = lengthThis;
  }

  int memoryValue = 0;
  int i;
  for(i = 0; i < minLength; i++)
  {
    char digitThis = this->value[lengthThis - i - 1];
    char digitNum = number.value[lengthNumber - i - 1];

    int intValueThis = CharToInt(digitThis);
    int intValueNumber = CharToInt(digitNum);

    int intResult = 0;
    if(intValueThis < (intValueNumber + memoryValue))
    {
      intResult = (intValueThis + 16) - (intValueNumber + memoryValue);
      memoryValue = 1;
    }
    else
    {
      intResult = intValueThis - (intValueNumber + memoryValue);
      memoryValue = 0;
    }
    result->value += IntToChar(intResult);
  }
  
  if(lengthThis == maxLength)
  {
    for(; i < maxLength; i++)
    {
      char digitThis = this->value[lengthThis - i - 1];

      int intValueThis = CharToInt(digitThis);

      int intResult = 0;
      if(intValueThis <  memoryValue)
      {
        intValueThis += 16;
        intResult = intValueThis - memoryValue;
        memoryValue = 1;
      }
      else
      {
        intResult = intValueThis - memoryValue;
        memoryValue = 0;
      }

      result->value += IntToChar(intResult);
    }
  }
  else
  {
    for(; i < maxLength; i++)
    {
      char digitNum = number.value[lengthNumber - i - 1];

      int intValueNumber = CharToInt(digitNum);

      int intResult = intValueNumber;

      result->value += IntToChar(intResult);
    }
  }
  
  result->Reverse();
  result->isNegative = this->isNegative;
  result->Trim();
  return *result;
}

BigHex& BigHex::operator*(BigHex& number)
{
  BigHex* result = new BigHex("0");

  if(this->EqualZero() == true || number.EqualZero() == true)
    return *result;

  int lengthThis = this->value.size();
  int lengthNumber = number.value.size();

  for(int i = 0; i < lengthNumber; i++)
  {
    char digitNum = number.value[lengthNumber - i - 1];
    int intValueNumber = CharToInt(digitNum);
    BigHex* temp = new BigHex();
    int memoryValue = 0;
    for(int j = 0; j < lengthThis; j++)
    {
      char digitValue = this->value[lengthThis - j - 1];
      int intValueThis = CharToInt(digitValue);
      int value = (intValueThis * intValueNumber) + memoryValue; 
      
      temp->value += IntToChar(value % 16);
      memoryValue = value / 16;
    }
    if(memoryValue > 0)
    {
      temp->value += IntToChar(memoryValue);
    }

    temp->Reverse();

    int lengthTemp = temp->value.size();
    for(int k = 0; k < i; k++)
    {
      temp->value += '0';
    }
    
    *result = *result + *temp;
  }
  result->isNegative = (this->isNegative != number.isNegative) ? true : false;
  
  return *result;
}

// Return -1 if number <= 0 => Error Code
BigHex& BigHex::operator%(BigHex& number)
{
  BigHex* result = new BigHex(*this);
  BigHex* zero = new BigHex("0");
  
  if(number < *zero || number == *zero)
  {
    BigHex* errorValue = new BigHex("-1");
    return *errorValue;
  }

  while(*result > number)
  {
    //*result = *result - (number * (*result / number));
    *result = *result - number;
    //cout << *result << " - " << number << endl;
  }
    
  return *result;
}

BigHex& BigHex::operator/(BigHex& number)
{
  BigHex* result = new BigHex(*this);
  BigHex* p = new BigHex();
  BigHex* one = new BigHex("1"); 

  while (*result > number)
  {
    *p = *p + *one;
    *result = *result - number;
    //cout << *p << endl;
  }
  return *p;
}

BigHex& BigHex::powerMod(BigHex& n, BigHex& N)
{
  BigHex* p = new BigHex("1");
  BigHex* one = new BigHex("1");
  //*p = a * b;

  while(n > *one || n == *one)
  {
    //cout << *p << endl;
    *p = *p * *this;
    //cout << *p << end 
    if(*p == N || *p > N)
      *p = *p % N;

    n = n - *one;
  }   
  
  return *p;
}

BigHex& BigHex::REDC(BigHex& R, BigHex& N, BigHex& T)
{
  BigHex* m = new BigHex();
  BigHex* N1 = new BigHex("40859195");
  BigHex* t = new BigHex();
  cout << "RDEC" << endl;
  *m = ((T % R) * *N1) % R;
  *t = (T + *m * N) / R;
  //cout << *m << " - " << *t << endl;
  if(*t > N || *t == N){
    cout << "OK" << endl;
    return *t - N;
  }
  else
  {
    cout << "HI" << endl;
    return *t;
  }
}

BigHex& BigHex::Montgomery(BigHex& a, BigHex& b,  BigHex& R, BigHex& N)
{
  BigHex* p = new BigHex();
  cout << "Montgomery" << endl;
  a = a * R % N;
  b = b * R % N;
  //cout << a << " - " << b << endl;
  *p = a * b;
  
  while(*p > N || *p == N)
  {
    *p = a * b;
    *p = p->REDC(*p, R, N);
    //cout << *p << endl;
    cout << "In REDC" << endl;
  }

  *p = p->REDC(*p, R, N);

  return *p;
}