#include<iostream>
#include"expressionTree.h"

int main()
{
    string a="a-(b-c)/(e*(f+g))";
    string b=I2P(a);
    ExpressionTree tree(b);
    system("pause");
    return 0;
}