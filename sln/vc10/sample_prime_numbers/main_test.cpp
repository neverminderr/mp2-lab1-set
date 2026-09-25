#include "tbitfield.h"

int main() {
	/*
	TBitField tbf(10);
	tbf.SetBit(3);
	tbf.SetBit(5);
	cout <<"tbf.SetBit(3); tbf.SetBit(5); " << tbf << endl;
	tbf.ClrBit(3);
	cout << "tbf.ClrBit(3); " << tbf << endl;
	cout << "tbf.GetBit(3); " << tbf.GetBit(3) << endl;
	cout << "tbf.GetBit(5); " << tbf.GetBit(5) << endl;
	TBitField tbf1(tbf);
	cout << "TBitField tbf1(tbf); " << tbf1 << endl;
	TBitField tbf2(3);
	cout <<"TBitField tbf2(3); " << tbf2 << endl;
	tbf2 = tbf;
	cout<<"tbf2 = tbf; " << tbf2 << endl;
	*/
	/*TBitField bf1(10);
	cin >> bf1;
	cout << bf1 << endl;
	TBitField bf2(3);
	cin >> bf2;
	cout << bf2 << endl;
	TBitField bf3 = bf1 | bf2;
	cout << "|: " << bf3 << endl;
	TBitField bf4 = bf1 & bf2;
	cout <<"&: " << bf4 << endl;
	TBitField bf5 = ~bf1;
	cout << "~bf1: " << bf5 << endl;
	*/
	TBitField f1(10), f2(10);
	cin >> f1;
	cin >> f2;
	if (f1 == f2) cout << "==" << endl;
	else cout << "!=" << endl;


	return 0;

}