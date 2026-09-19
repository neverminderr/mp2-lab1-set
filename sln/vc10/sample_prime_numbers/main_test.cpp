#include "tbitfield.h"

int main() {
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


	return 0;

}