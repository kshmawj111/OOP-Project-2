#include <stdio.h>
#include "inf_int.h"

using namespace std;

void debug_valid_check()
{
	vector <string> example_ary = 
	{ "10 + ( 20  * 30 + 20 )" ,
		"10 + 20 * 30 + 20 )"
		"10 + 20  * ) 30 + 20",
		"10 + 2 ) 30 + 20",
		"10 + 2 * (30 + 20)",
		"10 + 2 * (30 + 20",
		"10 + 2 * ) 30 + 20",
		"10 + 2 * + 30 + 20",
		"10  2 * + 30 + 20",	// 스페이스가 두개 이상 연달아 있는 경우
		"+ 2 - 5",
		" "

	};


	Expression exp;
	string infix_exp;

	vector <string> ::iterator iter;
	for (iter = example_ary.begin(); iter < example_ary.end(); iter++) {
		bool check = exp.check_valid(*iter);

		cout << "valid result for " << *iter << ": ";
		if (check == false) cout << "Wrong\n";
		else cout << "Right\n";

	}
}

void debug_postfix()
{

	/* vector <string> example_ary =
	{ "10 + ( 20  * 30 + 20 )" ,
		"10 + 20 * 30 + 20 )"
		"10 + 20  * ) 30 + 20",
		"10 + 2 ) 30 + 20",
		"10 + 2 * (30 + 20)",
		"10 + 2 * (30 + 20",
		"10 + 2 * ) 30 + 20",
		"10 + 2 * + 30 + 20",
		"10  2 * + 30 + 20",	// 스페이스가 두개 이상 연달아 있는 경우
		"+ 2 - 5",
		" "
		"1 * (2 + 3 ) * 4"

	};
	*/
	vector <string> example_ary = { "1 * (2 + 3 ) * 4" };


	Expression exp;

	vector <string> ::iterator iter;
	for (iter = example_ary.begin(); iter < example_ary.end(); iter++) {
		bool check = exp.check_valid(*iter);

		if (check == true) {
			exp.to_postfix(*iter);
			cout << "Infix: " << *iter << " -> Postfix: " <<  exp.expression << endl;

		}
		else {
			cout << "Wrong expression\n" << endl;
		}


	}

}

int main()
{
	debug_postfix();
}