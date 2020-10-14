#ifndef _INF_INT_H_
#define _INF_INT_H_
#include <ostream>
#include <iostream>
#include <istream>
#include <vector>
#include <stack>
#include <queue>
#include <string>

using namespace std;

class inf_int
{
public :
    char* digits;
    unsigned int length;
    bool thesign;   // true if positive , false if negative.
    // ex) 15311111111111111 -> digits="11111111111111351", length=17, thesign=true;
    // ex) -12345555555555 -> digits="55555555554321", length=14, thesign=false
    // you may insert additional private members here.

public :
    inf_int();               // assign 0 as a default value
    inf_int(int);
    inf_int(string str);
    inf_int(const inf_int&); // copy constructor
    ~inf_int(); // destructor

    inf_int& operator=(const inf_int&); // assignment operator

    friend bool operator==(const inf_int& , const inf_int&);
    friend bool operator!=(const inf_int& , const inf_int&);
    friend bool operator>(const inf_int& , const inf_int&);
    friend bool operator<(const inf_int& , const inf_int&);

    friend inf_int operator+(const inf_int& , const inf_int&);
    friend inf_int operator-(const inf_int& , const inf_int&);
    friend inf_int operator*(const inf_int& , const inf_int&);
   
    friend inf_int karatsuba(const inf_int& a, const inf_int& b);

    void Add(const char num, const unsigned int index);
    string fill_zero(const string& target, unsigned int num_add, bool right);
    // friend ostream& operator<<(ostream& , const inf_int&);

};

class Expression
{
    string expression;
    int toekn_type[8] = { 0, 1, 2, 3, 4, 5, 6, 7 }; // (, ), +, -, *, /, '\0', ¼ýÀÚ
    int isp[7] = { 0, 19, 12, 12, 13, 13, 0 };
    int icp[7] = { 20, 19, 12, 12, 13, 13, 0 };

    string operators[6] = { "(", ")", "+", "-", "*", "/" };

    std::stack<std::string> op_stack;
    std::queue<std::string> num_queue;

    bool check_valid(string exp);
    int get_token(char syombl);

public:
    void to_postfix(string infix_exp);
    string get_exp(void);
    
   
};

#endif
