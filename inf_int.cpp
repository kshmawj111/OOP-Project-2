#include "./inf_int.h"
#pragma warning(disable:4996)

/*
*****************************************************************************************************************************************************
* Expression class implemented below
*
*****************************************************************************************************************************************************/

string Expression::get_exp(void)
{
	bool valid_input;
	string temp;
	do {
		valid_input = 0;
		cout << "Enter an infix expression.\n"
			"Expression format: (num1) (space) (operator) (space) (num2)\n"
			">> ";

		getline(cin, temp);
		if (temp.size() < 1) cout << "Expression must be entered\n";

		else {
			// 입력 식에 뭐라도 들어왔을 때만 검사 실행
			valid_input = check_valid(temp);
			if (valid_input == false) cout << "Wrong expression. Please check\n\n";
		}

	} while (!valid_input);

	this->expression = temp;
	return temp;
}

bool Expression::check_valid(string exp)
{
	/*
	*  입력값은 공백을 없애서 확인을 함
		문자가 있으면 false

		operator 이후에 공백 없이 ( 나오는건 괜찮음. 5 +(6.
		(이후에 operator가 나오면 안됨 5+(5*5 "*)"
		괄호 카운트도 필요.

	*/

	// 변수 선언
	string temp_exp;
	temp_exp = exp;
	int bracket_count = 0;

	// 가장 앞에서 나오는 문자 검사
	int first_digit_token = get_token(temp_exp.at(0));
	if (first_digit_token != 7) return false;	// 식이 숫자로 시작하지 않는 경우 바로 false
	if (exp.at(0) == ' ') return false;
	

	// 공백 제거
	string::iterator end_pos = remove(temp_exp.begin(), temp_exp.end(), ' ');
	temp_exp.erase(end_pos, temp_exp.end());


	for (size_t i = 0; i < temp_exp.length(); i++) {
		char token = temp_exp[i];

		bool cond1 = '0' <= token && token <= '9';
		bool cond2 = (token == '+' || token == '-' || token == '*' || token == '/');
		bool cond3 = (token == '(' || token == ')');

		if (!(cond1 || cond2 || cond3))	return false; // 허용되지 않는 토큰이 들어왔을 때

		else if (cond2) {
			// 연산자 토큰이 들어왔을 때 그 전과 앞이 숫자인지 확인.
			if (i < exp.length()) {
				char temp1, temp2;
				temp1 = temp_exp[i - 1];
				temp2 = temp_exp[i + 1];

				if (temp1 == '+' || temp1 == '-' || temp1 == '*' || temp1 == '/' || temp1 == '(') return false;

				if (temp2 == '+' || temp2 == '-' || temp2 == '*' || temp2 == '/' || temp2 == ')') return false;

			}
		}

		else if (cond3) {
			// 괄호 토큰 들어오면 괄호 갯수 파악
			// 여는 괄호 없이 ) 이 나오면 false 반환. ( 는 값을 증가, )는 감소
			if (token == '(') bracket_count++;
			else bracket_count--;

			if (bracket_count < 0) {	// 닫는 괄호가 먼저 나오면 음수가 되므로 false 반환
				return false;
			}
		}


	}

	if (bracket_count != 0) return false;
	else return true;

	// 공백 잘못 입력 된거 확인
	if (exp.find("  ") != string::npos) return true;
	else return false;

}

int Expression::get_token(char symbol)
{
	switch (symbol)
	{
	case '(': return 0;
	case ')': return 1;
	case '+': return 2;
	case '-': return 3;
	case '*': return 4;
	case '/': return 5;
	case '\0': return 6;
	default: return 7;

	}
}

void Expression::to_postfix(string infix)
{
	//int toekn_type[8] = { 0, 1, 2, 3, 4, 5, 6, 7 }; // (, ), +, -, *, /, '\0', 숫자

	string postfix;
	std::stack<std::string> op_stack;
	std::queue<std::string> num_queue;

	op_stack.push(NULL);
	int infix_idx = 0, stack_idx = 0, token;

	while (infix[infix_idx] != NULL) {
		token = get_token(infix[infix_idx]);

		if (token == 0) {
			// token == '('
			op_stack.push("(");
			infix_idx++;
		}
		else if (token == 1) {
			string temp;
			do {
				temp = op_stack.top();
				postfix.append(temp);
				op_stack.pop();
			} while (temp != "(");
			infix_idx++;
		}

		else if (token == 2 || token == 3 || token == 4 || token == 5) {
			string temp = op_stack.top();
			int stack_token = get_token(temp.at(0));

			while (isp[stack_token] >= icp[token]) {
				postfix.append(op_stack.top());
				op_stack.pop();

			}
			op_stack.push(operators[token]);
		}

		else {
			// numbers
			string num_temp;
			while (get_token(infix[++infix_idx]) == 7) {
				num_temp.push_back(infix[infix_idx]);
			}
			num_temp.push_back(' ');
			num_queue.push(num_temp);
		}

	}
}