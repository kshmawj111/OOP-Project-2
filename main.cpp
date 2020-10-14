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

int main()
{
	debug_valid_check();
}