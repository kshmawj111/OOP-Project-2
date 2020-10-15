#include <stdio.h>
#include "inf_int.h"

using namespace std;

int main()
{
	Expression exp;
	string new_exp = exp.get_exp();
	exp.to_postfix(new_exp);
	inf_int temp = exp.eval();

	cout << temp.digits << endl;

}