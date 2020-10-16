#include "inf_int.h"

/*
Originally written by
컴퓨터공학부
정진경
*/


inf_int::inf_int()
{
	this->digits=new char[2];	// 동적할당

	this->digits[0]='0';		// default 값 0 설정
	this->digits[1]='\0';
	this->length=1;
	this->thesign=true;
}

inf_int::inf_int(int n){
	char buf[100];

	if(n<0){		// 음수 처리
		this->thesign=false;
		n=-n;
	}else{
		this->thesign=true;
	}

	int i=0;

	while(n>0){			// 숫자를 문자열로 변환하는 과정
		buf[i]=n%10+'0';// 문자열 값으로 변환 후 저장

		n/=10;
		i++;
	}

	if(i==0){	// 숫자의 절댓값이 0일 경우
		new (this) inf_int();	// 생성자 재호출...gcc에서 컴파일에러가 있다고 함. inf_int()의 경우 별개의 인스턴스가 생성됨. ?
	}else{
		buf[i]='\0';	// 왜?

		this->digits=new char[i+1];
		this->length=i;
		strcpy(this->digits, buf);
	}
}

inf_int::inf_int(string exp)
{
	// sign
	char sign = exp.at(0);
	if (sign == '-') this->thesign = false;
	else this->thesign = true;

	// length
	this->length = exp.length();

	// digits
	reverse(exp.begin(), exp.end());
	char* reversed = new char[length + 1];
	strcpy(reversed, exp.c_str());
	this->digits = reversed;

}

inf_int::inf_int(const char* str)
{
	int cnt = 0;
	if (str[0] == '-') {
		this->thesign = false;
	}
	else {
		this->thesign = true;

	}
	while (str[cnt] != '\0') {
		cnt++;
	}
	char* buf = new char[cnt + 1];

	for (int i = 0; i < cnt; i++) {
		printf("%c", str[cnt - i - 1]);
		buf[i] = str[cnt - i - 1];
	}
	if (this->thesign = false) {
		buf[cnt] = '\0';
	}
	strcpy(this->digits, buf); //분명히 buf까지 잘 저장되는데 strcpy에서 Exception이 뜨는데 왜그런지 모르겠어욤..
	// to be filled 
	// 부호 처리 
	// "100"이 들어왔다면 내부 표현에 맞게 "001"로 변환
	// ex) "-1053" -> thesign=false, digits="3501", len=4
}


inf_int::inf_int(const inf_int& a){
	this->digits=new char[a.length+1];

	strcpy(this->digits, a.digits);
	this->length=a.length;
	this->thesign=a.thesign;
}

inf_int::~inf_int(){
	delete digits;		// 메모리 할당 해제
}


inf_int& inf_int::operator=(const inf_int& a)
{
	if(this->digits) {
		delete this->digits;		// 이미 문자열이 있을 경우 제거.
	}
	this->digits=new char[a.length+1];

	strcpy(this->digits, a.digits);
	this->length=a.length;
	this->thesign=a.thesign;

	return *this; 
}

bool operator==(const inf_int& a, const inf_int& b)
{
    // we assume 0 is always positive.
    if ( (strcmp(a.digits , b.digits)==0) && a.thesign==b.thesign )	// 부호가 같고, 절댓값이 일치해야함.
        return true;
    return false;
}

bool operator!=(const inf_int& a, const inf_int& b)
{
	return !operator==(a, b);
}

/*
bool operator>(const inf_int& a, const inf_int& b)
{
	
	if (a.thesign != b.thesign) {
		if (a.thesign == true && b.thesign == false) return true;
		else return false;
	}

	else {
		// sign same case
		if (a.length > b.length) {
			return true;
		}
		else if (a.length == b.length) {
			for (unsigned int i = a.length; i < 0; i--) {
				if (a.digits[i] > b.digits[i]) return true;
			}
			return false;
		}
		else return false;
	}

}
*/

bool operator>(const inf_int& a, const inf_int& b)
{
	
	bool result;
	if (a.length > b.length) {
		result = true;
	}
	else if (a.length < b.length) {
		result = false;
	}
	else {
		for (int i = 1; i <= a.length; i++) {
			char A = a.digits[a.length - i];
			char B = b.digits[b.length - i];
			if (A > B) {
				result = true;
				break;
			}
			else if (A < B) {
				result = false;
				break;
			}
			else if (i == a.length) result = false;
		}

	}

	bool a_sign = a.thesign;
	bool b_sign = b.thesign;
	if ((a_sign = true) && (b_sign = true)) {
		return result;
	}
	else if ((a_sign = false) && (b_sign = false)) {
		if (result = true) {
			return false;
		}
		else {
			return true;
		}
	}
	return true;
	// to be filled
	// 절대값 비교
	// 둘 다 양수일 경우 절댓값 비교한 것을 그대로 return
	// 둘 다 음수일 경우 절댓값 비교의 것을 반전하여 return
	// 부호가 다를 경우, a가 양수일 경우 b는 음수, a가 음수일 경우 b는 양수이기에 a의 부호진리값을 반환하면 됨
}

bool operator<(const inf_int& a, const inf_int& b)
{
	if(operator>(a, b) || operator==(a, b)) {
		return false;
	}else{
		return true;
	}
}

inf_int operator+(const inf_int& a, const inf_int& b)
{
	inf_int c;
	unsigned int i;

	if (a.thesign == b.thesign) {	// 이항의 부호가 같을 경우 + 연산자로 연산
		for (i = 0; i < a.length; i++) {
			c.Add(a.digits[i], i + 1);	// c의 i+1의 자릿수에 a.digits[i]의 값을 더함. ??? 왜 이렇게 하는 것인가?
		}
		for (i = 0; i < b.length; i++) {
			c.Add(b.digits[i], i + 1);
		}

		c.thesign = a.thesign;

		return c;
	}
	else {	// 이항의 부호가 다를 경우 - 연산자로 연산
		c = b;	// 두번째 항을 c에 할당
		c.thesign = a.thesign;	// -55 + 699999999999999999999
								// c=-6999999999999999999999999
		return a - c;
	}
}


inf_int operator-(const inf_int& a, const inf_int& b) {
	if (a.thesign == b.thesign) {
		inf_int c;
		if ((a > b) && (a.thesign == true)) {

			for (int i = 0; i < a.length; i++) {
				c.Add(a.digits[i], i + 1);
			}
			for (int i = 0; i < b.length; i++) {
				c.Sub(b.digits[i], i + 1);
			}

			if (c.digits[a.length - 1] == 0)
				c.length = a.length - 1;
			else
				c.length = a.length;
			c.thesign = true;
		}

		else if ((a < b) && (a.thesign == true)) {
			return b - a;
		}

		else if ((a > b) && (a.thesign == false)) {

			for (int i = 0; i < b.length; i++) {
				c.Add(b.digits[i], i + 1);
			}
			for (int i = 0; i < a.length; i++) {
				c.Sub(a.digits[i], i + 1);
			}

			if (c.digits[a.length - 1] == 0)
				c.length = a.length - 1;
			else
				c.length = a.length;
			c.thesign = false;
		}

		else if ((a < b) && (a.thesign == false)) {
			return b - a;
		}


		else {
			inf_int c(0);
			return c;
		}

	}

	else {
		inf_int c;
		for (int i = 0; i < b.length; i++) {
			c.Add(b.digits[i], i + 1);
		}
		c.length = b.length;
		c.thesign = a.thesign;
		return a + c;
	}

}




void inf_int::Sub(const char num, const unsigned int index) {
	this->digits[index - 1] -= num - '0';

	if (this->digits[index - 1] < '0') {
		this->digits[index - 1] += 10;
		Sub('1', index + 1);
	}
}


inf_int operator*(const inf_int& a, const inf_int& b)
{
	inf_int result;
	string digit_result = "";
	unsigned int max_length = a.length + b.length;
	int final_digit, carry;
	int* digit_mult = new int[a.length + b.length]();	// result는 각 자리수 간 곱셈의 결과를 저장하는 정수형 배열. () 통해 0으로 초기화
														// result의 배열의 인덱스 자체가 자릿수 역할을 함. result[2] = 10^2의 자리
	for (unsigned int a_digit = 0; a_digit < a.length; a_digit++) {
		for (unsigned int b_digit = 0; b_digit < b.length; b_digit++) {
			digit_mult[a_digit + b_digit] += (a.digits[a_digit] - '0') * (b.digits[b_digit] - '0');	// 각 자리수의 값을 계산
		}
	}

	// 각 배열에 저장된 수에 알맞은 자리값만 남기고 다음 행으로 캐리
	for (unsigned int i = 0; i < max_length; i++) {
		final_digit = digit_mult[i] % 10;
		carry = digit_mult[i] / 10;

		if (i < max_length) digit_mult[i + 1] += carry;

		char final_digit_char = final_digit + '0';
		digit_result.append(1, final_digit_char);


	}

	while (digit_result[digit_result.length()-1] == '0'){
		digit_result.pop_back();
	}

	char* _result = new char[digit_result.length()+1];

	strcpy(_result, digit_result.c_str());
	_result[digit_result.length()] = '\0';
	result.digits = _result;
	result.length = digit_result.length();

	return result;
}

/*
inf_int operator*(const inf_int& a, const inf_int& b)
{
	inf_int c;
	inf_int d;
	unsigned int i;
	for (i = 0; i < a.length; i++) {
		c.Add(a.digits[i], i + 1);
		d.Add(a.digits[i], i + 1);
	}

	d.digits = (char*)realloc(d.digits, a.length  b.length);
	for (i = 0; i < b.digits[i]; i++) {   // b의 digits 값 만큼 a+a...+a 를 연산
		if (i >= 1) {
			

			if (d.digits == NULL) {		// 할당 실패 예외처리
				cout << "Memory reallocation failed, the program will terminate." << endl;
				exit(0);
			}

			d.length++;			// 길이 지정
			d.digits[d.length - 1] = 0;

		}
		c.Add(d.digits[i], i + 1);

	}


	if (a.thesign == b.thesign)
		c.thesign = true;
	else
		c.thesign = false;

	return c;

}
*/

inf_int operator/(const inf_int& a, const inf_int& b) {

	inf_int c;
	inf_int d;
	inf_int e(1);
	c.thesign = a.thesign == b.thesign;
	if (a.length >= b.length)
	{
		c.length = a.length - b.length + 1;
	}
	else return c; //b가 더크면 0 반환

	int i;

	for (i = 0; i < a.length; i++) {
		d.Add(a.digits[i], i + 1); //d에 a를 넣어준다.
	}

	while (1)
	{

		if (d < b)
			break;

		d = d - b;

		c = c + e;
	}

	return c;

}


ostream& operator<<(ostream& out, const inf_int& a)
{
	int i;

	if(a.thesign==false){
		out<<'-';
	}
	for(i=a.length-1; i>=0; i--){
		out<<a.digits[i];
	}
	return out;
}


void inf_int::Add(const char num, const unsigned int index)	// a의 index 자리수에 n을 더한다. 0<=n<=9, ex) a가 391일때, Add(a, 2, 2)의 결과는 411
{
	if(this->length<index){ // 더해지는 객체의 길이가 index보다 작다면
		this->digits=(char*)realloc(this->digits, index+1);

		if(this->digits==NULL){		// 할당 실패 예외처리
			cout<<"Memory reallocation failed, the program will terminate."<<endl;

			exit(0);
		}

		this->length=index;					// 길이 지정
		this->digits[this->length]='\0';	// 널문자 삽입
	}

	if(this->digits[index-1]<'0'){	// 연산 전에 '0'보다 작은 아스키값인 경우 0으로 채움. 쓰여지지 않았던 새로운 자리수일 경우 발생
		this->digits[index-1]='0';
	}

	this->digits[index-1]+=num-'0';	// 값 연산


	if(this->digits[index-1]>'9'){	// 자리올림이 발생할 경우
		this->digits[index-1]-=10;	// 현재 자릿수에서 (아스키값) 10을 빼고
		Add('1', index+1);			// 윗자리에 1을 더한다
	}
}

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
	if (exp.find("  ") != string::npos) return true;	// find에서 인자 문자열 못찾으면 npos 리턴. 찾으면 갯수 리턴. 따라서 npos를 리턴한 것은 올바른 식임
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

	string postfix;	// 최종 저장할 postfix 식
	std::stack<std::string> op_stack;	// 연산자가 들어가는 stack

	int infix_idx = 0, stack_idx = 0, token;

	// 공백 제거
	string::iterator end_pos = remove(infix.begin(), infix.end(), ' ');
	infix.erase(end_pos, infix.end());

	while (infix[infix_idx] != '\0') {
		token = get_token(infix[infix_idx]);

		if (token == 0) {
			// token == '('
			op_stack.push("(");
			infix_idx++;
		}
		else if (token == 1) {
			// token == ')'
			string temp;

			do {
				temp = op_stack.top();

				if (temp != "(") postfix.append(temp);

				op_stack.pop();

			} while (temp != "(");

			infix_idx++;
		}

		else if (token == 2 || token == 3 || token == 4 || token == 5) {

			if (op_stack.empty() == false) {

				string temp = op_stack.top();
				int stack_token = get_token(temp.at(0));

				while (isp[stack_token] >= icp[token]) {
					postfix.append(op_stack.top());
					op_stack.pop();

					if (op_stack.empty() == false) {
						temp = op_stack.top();
						stack_token = get_token(temp.at(0));
					}
					else break;
				}
			}

			infix_idx++;
			string op = operators[token];
			op.push_back(',');
			op_stack.push(op);
		}

		else {
			// numbers
			string num_temp;
			while (get_token(infix[infix_idx]) == 7) {
				num_temp.push_back(infix[infix_idx]);
				infix_idx++;
			}
			num_temp.push_back(',');
			postfix.append(num_temp);
		}

	}

	// 스택에 남은 기호 전부 뱉어냄
	while (op_stack.empty() == false) {
		postfix.append(op_stack.top());
		op_stack.pop();
	}

	// expression 멤버 변수에 저장
	expression = postfix;
}

inf_int Expression::eval()
{
	stack <inf_int> eval_stack;		// 연산하기 위한 숫자가 나오면 inf_int로 변환해 넣음.
	unsigned long long idx = 0;		// 식 idx
	string postfix = expression;	// 멤버 변수의 식을 새로운 주소 공간에 할당

	//postfix.pop_back();
	//postfix.push_back('\0');

	while (idx < postfix.length()) { 
		string token;	// 토큰 변수.

		while (postfix[idx] != ',') {	// posftfix의 식은 토큰+' '로 되어 있기 때문에 토큰을 판별하는 공백이 나올 때 까지의 모든 문자를 토큰 스트링에 추가한다.
										// 그런데 만약 postfix의 다음 값이 공백이 아니라 NULL 이라면 
			token.push_back(postfix[idx]);
			idx++;

		}
		idx++;
		//if (postfix[idx + 1] == '\0' ) token.push_back(postfix[idx]);

		int tkn_num = get_token(token.at(0));

		if (tkn_num == 7) {
			// 토큰이 숫자일 때

			inf_int new_num(token);
			eval_stack.push(new_num);

		}

		else {
			// opeartor 나왔을 때
			inf_int op2 = eval_stack.top();
			eval_stack.pop();

			inf_int op1 = eval_stack.top();
			eval_stack.pop();

			// +, -, *, / 의 tkn_num 값 차례대로: 2, 3, 4, 5
			switch (tkn_num) {
			case 2: // +
				eval_stack.push(op1 + op2);
				break;

			case 3:	// -
				eval_stack.push(op1 - op2);
				break;

			case 4: // *
				eval_stack.push(op1 * op2);
				break;

			/*case 5:	// /
				eval_stack.push(op1 / op2);
				break;
				*/
			}
		}
	
	}

	return eval_stack.top();

}
