#include<string>
#include<vector>

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
	HugeInt(std::string);
	HugeInt();
	HugeInt operator + (const HugeInt&) const;
	HugeInt operator * (const HugeInt&) const;
	int cmp(const HugeInt& b)const;
	friend std::ostream &operator<<(std::ostream &,const HugeInt &);
	std::string digits;
	int length;
	int getSign();
	int sign;
private:
	std::string addNum(const HugeInt& b)const;
	std::string subNum(const HugeInt& b)const;
	HugeInt(int, std::string);
};

#endif
