#include<string>
#include<vector>
using namespace std;

/*****************************************
**Class HugeInt define integer values up to
**several thousand digits long.
**
**It uses operator overloading to define
**operations of addition and multiplication 
**on these numbers
*****************************************/

#ifndef HUGEINT_H
#define HUGEINT_H

class HugeInt{
public:
	HugeInt(int);
	HugeInt(string);
	HugeInt();
	HugeInt operator + (const HugeInt&) const;
	HugeInt operator * (const HugeInt&) const;
	int cmp(const HugeInt& b)const;
	friend ostream &operator<<(ostream &,const HugeInt &);
	vector<int> digits;
	int length;
	int sign;
private:
	HugeInt addNum(const HugeInt& b)const;
	HugeInt subNum(const HugeInt& b)const;
	
};

#endif