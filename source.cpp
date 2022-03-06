#include"HugeInt.h"
#include<iostream>
using namespace std;
int main(){
	HugeInt a(1232);
	HugeInt b("-999999999999912345416");
	HugeInt c=a+b;
	cout<<c<<endl;
	HugeInt d=a*b;
	cout<<d<<endl;
}