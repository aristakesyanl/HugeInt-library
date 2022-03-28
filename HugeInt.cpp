#include<iostream>
#include<string>
#include<stdexcept>//for invalid argument exception class
#include<algorithm>
#include<vector>
#include"HugeInt.h"
using namespace std;


HugeInt::HugeInt() : length(0), digits(""), sign(0) {}

HugeInt::HugeInt(int value) {
	length = 0;
	if (value < 0) sign = 1;
	else sign = 0;
	value = abs(value);
	if(value==0){
		digits="0";
		sign=0;
		length=1;
	}
	while (value > 0) {
		digits.push_back(char(value % 10+'0'));
		value /= 10;
		length++;
	}
}

HugeInt::HugeInt(string value) {
	//check if value is can be assigned as string
	//the first charcter should be either '-' or number from 1 to 9
	int len = value.length();
	

	if (value[0] != '-') {

		sign = 0;

		//first digits if value should not be '0'
		if (((value[0] - '0' > 10) || (value[0] - '0') < 1) && value.length()!=1) {
			throw invalid_argument("Invalid Integer Type: Leading Zero");
		}

		//following digits  should be between 0 to 9
		for(int i=1; i<len; i++){
			if((value[i]-'0'>10) || (value[i]-'0')<0){
				throw invalid_argument("Invalid Integer Type:Contains non-valid character");
			}
		}

		length = value.length();
		reverse(value.begin(), value.end());
		digits=value;

	}
	else {
		//check that string is not "-"
		if (len == 1) {
			throw invalid_argument("Invalid Integer Type: Not an Integer");
		}
		//first digit should not be '0'
		if ((value[1] - '0' > 10) || (value[1] - '0') < 1) {
			throw invalid_argument("Invalid Integer Type: Leading Zero");
		}
		//check that following digits are between 0 to 9
		for(int i=2; i<len; i++){
			if((value[i]-'0')>10 || (value[i]-'0')<0){
				throw invalid_argument("Invalid Integer Type:Contains non-valid character");
			}
		}
		length = value.length() - 1;
		sign = 1;
		reverse(value.begin()+1, value.end());
		digits=value.substr(1);
	}

}

HugeInt::HugeInt(int s, string d){
	sign=s;
	digits=d;
	length=d.length();
}



//if a==b return 0
//if a>b return 1
//if a<b return -1

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


string HugeInt::addNum(const HugeInt& b)const {
	string temp;
	string s1=this->digits;
	string s2=b.digits;
	int len1=(int)s1.size();
	int len2=(int)s2.size();
	if (len1<len2){
		swap(s1,s2);
		swap(len1,len2);
	}
	int carry = 0;
	for (int i = 0; i < len2; i++) {
		int sa=s1[i]-'0';
		int sb=s2[i]-'0';
		int s = sa+sb + carry;
		temp.push_back(char(s % 10+'0'));
		carry = s / 10;
	}

	for (int i = len2; i < len1; i++) {
		int sa=s1[i]-'0';
		int s = sa + carry;
		temp.push_back(char(s % 10+'0'));
		carry = s / 10;
	}
	if (carry > 0) temp.push_back(char(carry+'0'));
	return temp;
}

string HugeInt::subNum(const HugeInt& b)const {

	int c = this->cmp(b);
	if(c==0){
		string temp="0";
		return temp;
	}
	string s1=this->digits;
	string s2=b.digits;
	int len1=(int)s1.size();
	int len2=(int)s2.size();
	if(c==-1){
		swap(s1,s2);
		swap(len1, len2);
	}
	
	string temp;
	int carry = 0;

	for (int i = 0; i < len2; i++) {
		int sa=s1[i]-'0';
		int sb=s2[i]-'0';
		if (sa >= (sb + carry)) {
			temp.push_back(char(sa - (sb + carry)+'0'));
			carry = 0;
		}
		else {
			int s = 10 + sa - (sb+carry);
			temp.push_back(char(s+'0'));
			carry = 1;
		}
	}

	for (int i = len2; i < len1; i++) {
		int sa=s1[i]-'0';
		if (sa >= carry) {
			temp.push_back(char(sa - carry+'0'));
			carry = 0;
		}
		else {
			int s = 10 + sa - carry;
			temp.push_back(char(s+'0'));
			carry = 1;
		}
	}
	//if the first digit is 0 remove it
	while(temp.back()=='0'){
		temp.pop_back();
	}
	
	
	return temp;
}


HugeInt HugeInt:: operator + (const HugeInt& arg) const {

	if (this->sign == arg.sign) {
		
		string t=this->addNum(arg);
		HugeInt temp(this->sign,t);
		return temp;
	}

	else {
		string t=this->subNum(arg);
		if(this->cmp(arg)==-1){
			HugeInt temp(arg.sign, t);
			return temp;
		}
		else if(this->cmp(arg)==1){
			HugeInt temp(this->sign, t);
			return temp;
		}
		else{
			HugeInt temp(0);
			return temp;
		}
	}
}

HugeInt HugeInt:: operator * (const HugeInt& arg) const {
	HugeInt zero(0);
	if(this->cmp(zero)==0 || arg.cmp(zero)==0){
		HugeInt tmp(0);
		return tmp; 
	}
	int n = this->length;
	int m = arg.length;
	vector<int> temp(n * m + 3, 0);
	int carry = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int a=this->digits[i]-'0';
			int b=arg.digits[j]-'0';
			int s = a * b;
			temp[i + j] += s;
		}
	}

	int len = n * m + 3;
	int s;

	for (int i = 0; i < len; i++) {
		s = temp[i] + carry;
		temp[i] = s % 10;
		carry = s / 10;
	}


	//find last non-zero digit
	int last = -1;

	for (int i = n * m - 1; i >= 0; i--) {
		if (temp[i] != 0) {
			last = i;
			break;
		}
	}

	//trim additional 0's
	vector<int>::iterator it;
	it = temp.begin();

	if (last == -1) {
		while ((int)temp.size() > 1) {
			temp.pop_back();
		}
	}
	else {
		int cnt = len - last - 1;
		while (cnt--) {
			temp.pop_back();
		}
	}
	
	string str;
	for(int i=0; i<(int)temp.size(); i++){
		str.push_back(char(temp[i]+'0'));
	}
	int tsign = (this->sign != arg.sign) ? 1 : 0;
	HugeInt tmp(tsign,str);
	return tmp;
}

ostream& operator<<(ostream& out, const HugeInt& a) {
	if (a.sign == 1) cout << '-';
	for (int i = a.digits.size() - 1; i >= 0; i--)
		cout << a.digits[i];
	return cout;
}
