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

class Expression
{
    string expression;
    int toekn_type[8] = { 0, 1, 2, 3, 4, 5, 6, 7 }; // (, ), +, -, *, /, '\0', ¼ýÀÚ
    int isp[7] = { 0, 19, 12, 12, 13, 13, 0 };
    int icp[7] = { 20, 19, 12, 12, 13, 13, 0 };

    string operators[6] = { "(", ")", "+", "-", "*", "/" };

    std::stack<std::string> op_stack;
    std::queue<std::string> num_queue;


public:
    void to_postfix(string infix_exp);
    bool check_valid(string exp);
    int get_token(char syombl);
    string get_exp(void);

};
#endif
