#include <stdio.h>
#include "inf_int.h"

using namespace std;

int sub()
{
	while (1) {
		Expression exp;
		string new_exp = exp.get_exp();
		cout << "input expression: " << exp.expression << endl;
		exp.to_postfix(new_exp);
		cout << "postfix expression: " << exp.expression << endl;
		inf_int temp = exp.eval();

		cout << temp << endl;
	}
	return 0;
}

void debug_postfix_eval()
{
	Expression exp;
	string test = "10 + ( 20 * ( 10 + 30 ) )";
	exp.to_postfix(test);
	inf_int temp = exp.eval();

	cout << temp << endl;

}

int main()
{
	sub();
}