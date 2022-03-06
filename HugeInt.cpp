#include<iostream>
#include<string>
#include<stdexcept>//for invalid argument exception class
#include"HugeInt.h"
using namespace std;


HugeInt::HugeInt() : length(0), digits(0, 0), sign(0) {}

HugeInt::HugeInt(int value) {
	length = 0;
	if (value < 0) sign = 1;
	else sign = 0;
	value = abs(value);
	while (value > 0) {
		digits.push_back(value % 10);
		value /= 10;
		length++;
	}
}

HugeInt::HugeInt(string value) {
	//check if value is can be assigned as string
	//the first charcter should be either '-' or number from 1 to 9
	int len = value.length();
	if (len == 0) {

	}

	else if (value[0] != '-') {

		sign = 0;

		if ((value[0] - '0' > 10) || (value[0] - '0') < 0) {
			throw invalid_argument("invalid integer type");
		}
		length = value.length();

		for (int i = len - 1; i >= 0; i--) {
			digits.push_back(value[i] - '0');
		}

	}
	else {
		if (len == 1) {
			throw invalid_argument("invalid integer type");
		}
		if ((value[1] - '0' > 10) || (value[1] - '0') < 0) {
			throw invalid_argument("invalid integer type");
		}
		length = value.length() - 1;
		sign = 1;
		for (int i = len - 1; i >= 1; i--) {
			digits.push_back(value[i] - '0');
		}
	}


}



//return true if a > b
//else return false

int HugeInt::cmp(const HugeInt& b)const {
	if (this->length > b.length) return 1;
	else if (this->length < b.length) return -1;
	else {
		int len = b.length;
		for (int i = len - 1; i >= 0; i--) {
			if (this->digits[i] > b.digits[i]) return 1;
			else if (this->digits[i] < b.digits[i]) return -1;
		}
		return 0;
	}
}


HugeInt HugeInt::addNum(const HugeInt& b)const {
	HugeInt temp;
	temp.sign = this->sign;
	if (this->length > b.length) {
		int carry = 0;
		int len = b.length;
		for (int i = 0; i < len; i++) {
			int s = this->digits[i] + b.digits[i] + carry;
			temp.digits.push_back(s % 10);
			carry = s / 10;
		}

		for (int i = len; i < this->length; i++) {
			int s = this->digits[i] + carry;
			temp.digits.push_back(s % 10);
			carry = s / 10;
		}
		if (carry > 0) temp.digits.push_back(carry);

	}
	else {
		int carry = 0;
		int len = this->length;
		for (int i = 0; i < len; i++) {
			int s = this->digits[i] + b.digits[i] + carry;
			temp.digits.push_back(s % 10);
			carry = s / 10;
		}

		for (int i = len; i < b.length; i++) {
			int s = b.digits[i] + carry;
			temp.digits.push_back(s % 10);
			carry = s / 10;
		}
		if (carry > 0) temp.digits.push_back(carry);
	}
	temp.length = temp.digits.size();

	return temp;



}

HugeInt HugeInt::subNum(const HugeInt& b)const {

	int c = this->cmp(b);
	if (c == 1) {
		HugeInt temp;
		int carry = 0;
		temp.sign = this->sign;
		int len = b.length;
		for (int i = 0; i < len; i++) {
			if (this->digits[i] >= (b.digits[i] + carry)) {
				temp.digits.push_back(this->digits[i] - (b.digits[i] + carry));
				carry = 0;
			}
			else {
				int s = 10 + this->digits[i] - b.digits[i];
				temp.digits.push_back(s);
				carry = 1;
			}
		}

		for (int i = len; i < this->length; i++) {
			if (this->digits[i] >= carry) {
				temp.digits.push_back(this->digits[i] - carry);
				carry = 0;
			}
			else {
				int s = 10 + this->digits[i] - carry;
				temp.digits.push_back(s);
				carry = 1;
			}
		}

		temp.length = temp.digits.size();
		return temp;

	}
	else if (c == 0) {
		HugeInt temp(0);
		temp.length = temp.digits.size();
		return temp;
	}

	else {
		HugeInt temp;
		temp.sign = 1;
		int len = this->length;
		int carry = 0;
		for (int i = 0; i < len; i++) {
			if (b.digits[i] >= (this->digits[i] + carry)) {
				temp.digits.push_back(b.digits[i] - (this->digits[i] + carry));
				carry = 0;
			}
			else {
				int s = 10 + b.digits[i] - this->digits[i];
				temp.digits.push_back(s);
				carry = 1;
			}
		}

		for (int i = len; i < b.length; i++) {
			if (b.digits[i] >= carry) {
				temp.digits.push_back(b.digits[i] - carry);
				carry = 0;
			}
			else {
				int s = 10 + b.digits[i] - carry;
				temp.digits.push_back(s);
				carry = 1;
			}
		}
		temp.length = temp.digits.size();
		return temp;

	}
}


HugeInt HugeInt:: operator + (const HugeInt& arg) const {

	if (this->sign == arg.sign) {
		HugeInt temp = this->addNum(arg);
		return temp;
	}
	else {
		HugeInt temp = this->subNum(arg);
		return temp;
	}

}

HugeInt HugeInt:: operator * (const HugeInt& arg) const {
	int n = this->length;
	int m = arg.length;
	HugeInt temp(string(n * m + 3, '0'));
	temp.sign = (this->sign != arg.sign) ? 1 : 0;
	int carry = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int s = this->digits[i] * arg.digits[j];
			temp.digits[i + j] += s;
		}
	}

	int len = n * m + 3;
	int s;

	for (int i = 0; i < len; i++) {
		s = temp.digits[i] + carry;
		temp.digits[i] = s % 10;
		carry = s / 10;
	}


	//find last non-zero digit
	int last = -1;

	for (int i = n * m - 1; i >= 0; i--) {
		if (temp.digits[i] != 0) {
			last = i;
			break;
		}
	}

	//trim additional 0's
	vector<int>::iterator it;
	it = temp.digits.begin();

	if (last == -1) {
		while (temp.digits.size() > 1) {
			temp.digits.pop_back();
		}
	}
	else {
		int cnt = len - last - 1;
		while (cnt--) {
			temp.digits.pop_back();
		}
	}
	temp.length = temp.digits.size();
	return temp;
}

ostream& operator<<(ostream& out, const HugeInt& a) {
	if (a.sign == 1) cout << '-';
	for (int i = a.digits.size() - 1; i >= 0; i--)
		cout << a.digits[i];
	return cout;
}
