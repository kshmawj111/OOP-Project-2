#include "./inf_int.h"

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

inf_int::inf_int(const char* str)
{	
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

inf_int operator*(const inf_int& a, const inf_int& b)
{
	inf_int result;
	string digit_result = "";
	unsigned int max_length = a.length + b.length;		// 곱셈 결과의 최대 길이
	int final_digit, carry;
	int* digit_mult = new int[max_length]();	// result는 각 자리수 간 곱셈의 결과를 저장하는 정수형 배열. () 통해 0으로 초기화
														// result의 배열의 인덱스 자체가 자릿수 역할을 함. result[2] = 10^2의 자리

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

	// 각 자릿수에 맞는 숫자 남기기
	for (unsigned int i = 0; i < max_length; i++) {
		final_digit = digit_mult[i] % 10;
		carry = digit_mult[i] / 10;

		char final_digit_char = final_digit + '0';
		digit_result.append(1, final_digit_char);
		digit_mult[i + 1] += carry;

	}

	delete[] digit_mult;	// 더 이상 사용하지 않아서 할당 해제

	if (digit_result.length() > 0) {	
		// string에 최종 결과를 저장한 뒤 inf_int의 멤버 digit에 할당 시도하였으나 
		// type cast 에러가 떠서 char * 배열에 넣어서 바꿈

		char* digit_char_ary = (char*)malloc(sizeof(char) * digit_result.length());
		strcpy(digit_char_ary, digit_result.c_str());
		result.digits = digit_char_ary;
		result.length = digit_result.length();
		return result;
	}
	else {
		result.digits = NULL;
		result.length = 0;
		result.thesign = false;

		return result;
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

