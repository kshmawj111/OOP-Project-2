#include "./inf_int.h"
#pragma warning(disable:4996)
<<<<<<< Updated upstream
/*
Originally written by
컴퓨터공학부
정진경
*/

using namespace std;

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

inf_int::inf_int(string str)
{	
	if (str[0] == '-') this->thesign = false;
	else this->thesign = true;

	unsigned int size;

	this->thesign == false ? size = str.size() - 1 : size = str.size();
	this->length = size;

	reverse(str.begin(), str.end());

	char* temp = new char[size];
	strcpy(temp, str.c_str());

	this->digits = temp;

	// 0번째 값 인식 후 -면 부호 false
	// for를 뒤에서부터 돌려서 reverse 후 새로운 객체에 저장
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
<<<<<<< Updated upstream
    // we assume 0 is always positive.
    if ( (strcmp(a.digits , b.digits)==0) && a.thesign==b.thesign )	// 부호가 같고, 절댓값이 일치해야함.
        return true;
    return false;
}
=======
	inf_int result;
	string digit_result = "";
	unsigned long long int max_length = (unsigned long long)a.length + (unsigned long long)b.length;		// 곱셈 결과의 최대 길이
	int final_digit, carry;
	int* digit_mult = new int[max_length]();	// result는 각 자리수 간 곱셈의 결과를 저장하는 정수형 배열. () 통해 0으로 초기화
												// result의 배열의 인덱스 자체가 자릿수 역할을 함. result[2] = 10^2의 자리

	// 둘 중 하나가 0이면 
	if (a.digits[0] == '0' || b.digits[0] == '0') {
		result.digits[0] = NULL;
		result.length = 0;
		result.thesign = true;

	}

	// 부호 결정
	if (a.thesign != b.thesign) result.thesign = false;
	else result.thesign = true;

	// 절대값끼리 곱셈
	for (unsigned int a_digit=0; a_digit < a.length; a_digit++) {

		for (unsigned int b_digit=0; b_digit < b.length; b_digit++) {
			// 각 자리수의 값을 계산 후 digit_mult에 합산
			digit_mult[a_digit + b_digit] += (a.digits[a_digit] - '0') * (b.digits[b_digit] - '0');
		}
	}
>>>>>>> Stashed changes

bool operator!=(const inf_int& a, const inf_int& b)
{
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b)
{
	// 절대값 비교 로직
	// 길이 비교 후 더 긴 것이 큼
	// 같은 길이의 경우 큰 자릿수의 문자 비교
	// to be filled
	// 절대값 비교
	// 둘 다 양수일 경우 절댓값 비교한 것을 그대로 return
	// 둘 다 음수일 경우 절댓값 비교의 것을 반전하여 return
	// 부호가 다를 경우, a가 양수일 경우 b는 음수, a가 음수일 경우 b는 양수이기에 a의 부호진리값을 반환하면 됨
	return true;
}

bool operator<(const inf_int& a, const inf_int& b)
{
	if(operator>(a, b) || operator==(a, b)) {
		return false;
	}else{
		return true;
	}
}

/*
inf_int operator+(const inf_int& a, const inf_int& b)
{
	inf_int c;
	unsigned int i;

	if(a.thesign==b.thesign){	// 이항의 부호가 같을 경우 + 연산자로 연산
		for(i=0; i<a.length; i++){
			c.Add(a.digits[i], i+1);	// c의 i+1의 자릿수에 a.digits[i]의 값을 더함. ??? 왜 이렇게 하는 것인가?
		}	
		for(i=0; i<b.length; i++){
			c.Add(b.digits[i], i+1);
		}

<<<<<<< Updated upstream
		c.thesign=a.thesign;	
=======
		char* digit_char_ary = new char[digit_result.length() + 1];	// 1은 '\n'용
		strcpy(digit_char_ary, digit_result.c_str());
		result.digits = digit_char_ary;
		result.length = digit_result.length();
		return result;
	}
	else {
		result.digits = NULL;
		result.length = 0;
		result.thesign = false;
>>>>>>> Stashed changes

		return c;
	}else{	// 이항의 부호가 다를 경우 - 연산자로 연산
		c=b;	// 두번째 항을 c에 할당
		c.thesign=a.thesign;	// -55 + 699999999999999999999
								// c=-6999999999999999999999999
		return a-c;
	}
<<<<<<< Updated upstream
}*/
=======

}
>>>>>>> Stashed changes

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

inf_int operator-(const inf_int& a, const inf_int& b)
{
	inf_int result;
	unsigned long long int i;

	if (a.thesign == b.thesign) {
		result = a + b;
		result.thesign = a.thesign;

		return result;
	}
	else {	// 96 - 1000
		result = a;
		// Sub method 정의 후 실행
	}
	
	// 부호가 다른 경우 뒤의 길이가 더 길면 부호를 -
	// 차의 절댓값 계산
	// 길이가 더 긴 스트링에서 짧은 스트링 뺌
	// 각 자릿수에서 빼는데 만약 뺀 값이 0 미만이면 빌림을 함.
	// 자릿수 값 계산 = a[i] - b[i] + borrowed - lend
	// borrow는 빌려왔으면 1, lend는 빌려줬으면 1.
	// 그냥 무조건 빌려온 다음에 남은 값을 캐리로 다음 자릿수 값에 넘겨주는 방법도 있음. 코드가 더 간결해짐
	// a[i] - b[i] + 10 -> 나중에 배열에 저장된 두 자리 수 값을 다시 변환해야 하는 불편함 존재 
	//
	return result;
}

inf_int operator*(const inf_int& a, const inf_int& b)
{
	inf_int result;
	string digit_result = "";
	unsigned int max_length = a.length + b.length;
	int final_digit, carry;
	int* digit_mult = new int[a.length + b.length]();	// result는 각 자리수 간 곱셈의 결과를 저장하는 정수형 배열. () 통해 0으로 초기화
														// result의 배열의 인덱스 자체가 자릿수 역할을 함. result[2] = 10^2의 자리
	for (unsigned int a_digit=0; a_digit < a.length; a_digit++) {
		for (unsigned int b_digit=0; b_digit < b.length; b_digit++) {
			digit_mult[a_digit + b_digit] += (a.digits[a_digit] - '0') * (b.digits[b_digit] - '0');	// 각 자리수의 값을 계산
		}
	}

	for (unsigned int i = 0; i < max_length-1; i++) {
		final_digit = digit_mult[i] % 10;
		carry = digit_mult[i] / 10;

		char final_digit_char = final_digit + '0';
		digit_result.append(1, final_digit_char);
		digit_mult[i + 1] += carry;

	}

	return result;
}

/*
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
*/

string inf_int::fill_zero(const string& target, unsigned int num_add, bool right)
{
	string temp(num_add, '0');
	return right == true ? target + temp : temp + target;

}

inf_int karatsuba(const inf_int& a, const inf_int& b)
{
	unsigned int a_length = a.length, b_length = b.length, length;
	length = max(a_length, b_length);

	inf_int result;

	string adigit, bdigit, a0, a1, b0, b1;

	adigit = a.digits;
	reverse(adigit.begin(), adigit.end());
	bdigit = b.digits;
	reverse(bdigit.begin(), bdigit.end());

	//a나 b가 0
	if (a_length == 0 || b_length == 0) {
		char* temp = new char[2];
		result.digits[0] = '\0';
		result.length = 0;
		result.thesign = true;
		return result;
	}

	unsigned int half = length / 2;

	a1 = adigit.substr(0, half);
	a0 = adigit.substr(half, length - half);
	b1 = bdigit.substr(0, half);
	b0 = bdigit.substr(half, length - half);

	inf_int infa1(a1), infa0(a0), infb1(b1), infb0(b0);

	//z2 = a1 * b1
	inf_int z2 = karatsuba(infa1, infb1);

	//z0 = a0 * b0
	inf_int z0 = karatsuba(infa0, infb0);

	//z1 = ((a0 + a1) * (b0 + b1)) - z0 - z2
	inf_int z1 = ((infa0 + infa1) * (infb0 + infb1)) - z0 - z2;

	string strz2, strz1;
	strz2 = z2.digits;
	strz1 = z1.digits;

	for (unsigned int i = 0; i < 2 * (length - length / 2); i++) 
		strz2.append("0");

		
	for (int i = 0; i < length - length / 2; i++)
		strz1.append("0");

	result = (z2 + z0) + z1;

	return result;
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
=======

>>>>>>> Stashed changes

/*
*****************************************************************************************************************************************************
* Expression class implemented below															
* 
*****************************************************************************************************************************************************/

void Expression::get_exp(void)
{
	bool valid_input;
	string temp;
	do {
		cout << "Enter an infix expression.\n"
			"Expression format: (num1) (space) (operator) (space) (num2)\n"
			">> ";

		getline(cin, temp);
		valid_input = check_valid(temp);

		if (valid_input == false) cout << "Wrong expression. Please check\n\n";

	} while (!valid_input);

	this->expression = temp;
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

	// 공백 제거
	string::iterator end_pos = remove(exp.begin(), exp.end(), ' ');
	exp.erase(end_pos, exp.end());

	if ('0' <= exp[0] && exp[0] <= '9') return false;	// 식이 숫자로 시작하지 않는 경우 바로 false

	for (size_t i = 0; i < exp.length(); i++) {
		char token = exp[i];

		bool cond1 = '0' <= token && token <= '9';
		bool cond2 = (token == '+' || token == '-' || token == '*' || token == '/');
		bool cond3 = (token == '(' || token == ')');

		if (!(cond1 && cond2 && cond3)) {
			// 허용되지 않는 토큰이 들어왔을 때
			
			return false;
		}

		else if (cond2) {
			// 연산자 토큰이 들어왔을 때 그 전과 앞이 숫자인지 확인.
			if (i < exp.length()) {
				char temp1, temp2;
				temp1 = exp[i - 1];
				temp2 = exp[i + 1];

				if (temp1 == '+' || temp1 == '-' || temp1 == '*' || temp1 == '/' || temp1 == '(') return false;

				if (temp2 == '+' || temp2 == '-' || temp2 == '*' || temp2 == '/' || temp2 == ')') return false;

			}
		}
	}

	return true;
}