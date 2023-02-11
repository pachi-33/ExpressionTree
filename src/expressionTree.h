#pragma once
#include<iostream>
#include<map>
#include<utility>
#include<vector>
#include<queue>
#include<stack>
#include"LinkedBT.h"
using namespace std;

string I2P(const string& pat)
{
    stack<char> InfStack,PoStack;
    map<char,int> pt;
    pt['+']=1;pt['-']=1;pt['*']=2;pt['/']=2;pt['(']=0;
    for(int it=0;it<pat.size();){
        if(pat[it]!='+'&&pat[it]!='-'&&pat[it]!='*'&&pat[it]!='/'&&pat[it]!='('&&pat[it]!=')'){
            PoStack.push(pat[it]);
        }else if((InfStack.empty()||pt[pat[it]]>pt[InfStack.top()]||pat[it]=='(')&&pat[it]!=')'){
            InfStack.push(pat[it]);
        }else if(pt[pat[it]]<=pt[InfStack.top()]&&pat[it]!=')'){
            PoStack.push(InfStack.top());
            InfStack.pop();
        }else if(pat[it]==')'){
            while (1)
            {
                if(InfStack.top()=='('){
                    InfStack.pop();
                    break;
                }else{
                    PoStack.push(InfStack.top());
                    InfStack.pop();
                }
            }
        }
        it++;
    } 
    while(InfStack.empty()!=true)
    {
        PoStack.push(InfStack.top());
        InfStack.pop();
    }
    string out(PoStack.size(),'\0');
    for(int it=PoStack.size()-1;it>=0;--it)
    {
        out[it]=PoStack.top();
        PoStack.pop();
    }
    return out;
}

class ExpressionTree
{
protected:
    Node<char>* root;
    vector<Node<char>*> elems;
public:
    bool isOper(Node<char>* n){
        if(n->data=='+'||n->data=='-'||n->data=='*'||n->data=='/'){
            return true;
        }else{
            return false;
        }
    }
    Node<char>* buildTree(){
        stack<Node<char>*> mid;
        for(auto e:elems){
            if(!isOper(e)){
                mid.push(e);
            }else{
                Node<char>* a=mid.top();mid.pop();
                Node<char>* b=mid.top();mid.pop();
                e->leftChild=a;
                e->rightChild=b;
                mid.push(e);
            }
        }
        Node<char>* out=mid.top();mid.pop();
        return out;
    }
    ExpressionTree(const string& src){
        for(int it=0;it<src.size();++it){
            elems.push_back(new Node<char>(src[it]));
        }
        this->root=buildTree();
    }
    ~ExpressionTree(){
        for(auto it:elems){
            delete it;
        }
    }
};



