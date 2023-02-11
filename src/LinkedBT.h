#pragma once
#include<queue>
#include<vector>
#include<functional>
#include<stack>
#include<iostream>
using namespace std;

template<class ElemType>
class Node
{
public:
    ElemType data;
    Node<ElemType>* leftChild,*rightChild;
    Node(){
        this->leftChild=nullptr;
        this->rightChild=nullptr;
    }
    Node(const ElemType& _data):data(_data){}
    Node(const ElemType& _data,
    Node<ElemType>* _leftChild,
    Node<ElemType>* _rightChild):data(_data),leftChild(_leftChild),rightChild(_rightChild){}
    Node(const Node<ElemType>& other):data(other.data),leftChild(other.leftChild),rightChild(other.rightChild){}
    ~Node(){}
    void defaultLink(Node<ElemType>* other){
        if(this->leftChild==NULL){
            this->leftChild=other;
        }else{
            this->rightChild=other;
        }
    }
    void leftLink(Node<ElemType>* other){
        this->leftChild=other;
    }
    void rightLink(Node<ElemType>* other){
        this->rightChild=other;
    }
};

template<class ElemType>
class LinkedBT
{
protected:
    Node<ElemType>* root=nullptr;
public:
    LinkedBT(){}
    bool IsEmpty(){
        if(!this->root) 
            return false;
        else
            return true;
    }
    Node<ElemType>* GetRoot(){
        return this->root;
    }
    void CreateRoot(const ElemType& d){
        if(this->root){
            root->data=d;
        }else{
            this->root=new Node<ElemType>(d);
        }
        return;
    }
    void PreOrderTravers(Node<ElemType>* r,function<void(Node<ElemType>*)> Visit) const{
        if(r){
            Node<ElemType> tmp(*r);
            Node<ElemType>* ptmp=&tmp;
            Visit(r);
            PreOrderTravers(ptmp->leftChild,Visit);
            PreOrderTravers(ptmp->rightChild,Visit);
        }
    }
    void InOrderTravers(Node<ElemType>* r,function<void(Node<ElemType>*)> Visit) const{
        if(r){
            Node<ElemType>* ptmp=&Node<ElemType>(*r);
            InOrderTravers(ptmp->leftChild,Visit);
            Visit(r);
            InOrderTravers(ptmp->rightChild,Visit);
        }
    }
    void PostOrderTravers(Node<ElemType>* r,function<void(Node<ElemType>*)> Visit) const{
        if(r){
            Node<ElemType>* ptmp=&Node<ElemType>(*r);
            PostOrderTravers(ptmp->leftChild,Visit);
            PostOrderTravers(ptmp->rightChild,Visit);
            Visit(r);
        }
    }
    void LevelOrderTravers(Node<ElemType>* r,function<void(Node<ElemType>*)> Visit) const{
        queue<Node<ElemType>*> que;
        if(r) que.push(r);
        while(!que.empty()){
            Node<ElemType>* tmp=que.front();
            que.pop();
            if(tmp->leftChild!=NULL) que.push(tmp->leftChild);
            if(tmp->rightChild!=NULL) que.push(tmp->rightChild);
            Visit(tmp);
        }
    }
    void InsertLeftChild(Node<ElemType>* p,ElemType e){
        if(p->leftChild){
            Node<ElemType>* ptmp=p->leftChild;
            p->leftChild=new Node<ElemType>(e);
            p->leftChild->leftChild=ptmp;
        }else{
            p->leftChild=new Node<ElemType>(e);
        }
    }
    void InsertRightChild(Node<ElemType>* p,ElemType e){
        if(p->RightChild){
            Node<ElemType>* ptmp=p->RightChild;
            p->RightChild=new Node<ElemType>(e);
            p->RightChild->RightChild=ptmp;
        }else{
            p->RightChild=new Node<ElemType>(e);
        }
    }
    void DeleteLeftChild(Node<ElemType>* p){
        auto destruct=[](Node<ElemType>* target){
            delete target;
        };
        PreOrderTravers(p->leftChild,*destruct);
    }
    void DeleteRightChild(Node<ElemType>* p){
        auto destruct=[](Node<ElemType>* target){
            delete target;
        };
        PreOrderTravers(p->rightChild,*destruct);
    }
    ~LinkedBT(){
        if(this->root){
            DeleteLeftChild(root);
            DeleteRightChild(root);
            delete root;
        }
    }
    void arrange(const vector<ElemType>& src){
        if(this->root){
            DeleteLeftChild(root);
            DeleteRightChild(root);
            delete root;
        }
        queue<Node<ElemType>*> que;
        this->root=new Node<ElemType>();
        que.push(this->root);
        for(auto it:src){
            Node<ElemType>* tmp=que.front();
            que.pop();
            tmp->data=it;
            tmp->leftChild=new Node<ElemType>();
            tmp->rightChild=new Node<ElemType>();
            que.push(tmp->leftChild);
            que.push(tmp->rightChild);
        }
        auto cutLeaf=[](Node<ElemType>* target){
            Node<ElemType>*& l=target->leftChild;
            #define ll l->leftChild
            #define lr l->rightChild
            Node<ElemType>*& r=target->rightChild;
            #define rl r->leftChild
            #define rr r->rightChild
            if(l==NULL&&r==NULL){
                delete target;
                return;
            }
            if(ll==NULL&&lr==NULL){
                l=nullptr;

            }
            if(rl==NULL&&rr==NULL){
                r=nullptr;
            }
        };
        LevelOrderTravers(this->root,cutLeaf);
        #undef ll
        #undef lr
        #undef rl
        #undef rr
    }
    int CountLeaf(){
        int sum=0;
        auto count=[&sum](Node<ElemType>* target){
            if(target->leftChild==nullptr&&target->rightChild==nullptr){
                sum++;
            }
        };
        PreOrderTravers(this->root,count);
        return sum;
    }
    void Revolut(){
        auto rev=[](Node<ElemType>* target){
            Node<ElemType>*& a=target->leftChild;
            Node<ElemType>*& b=target->rightChild;
            Node<ElemType>* tmp=a;
            a=b;
            b=tmp;
        };
        this->LevelOrderTravers(this->root,rev);
    }
    int CountBreadth(){
        int max_n=0;
        if(this->root==nullptr) return 0;
        queue<Node<ElemType>*> que;
        que.push(this->root);
        while(!que.empty()){
            max_n=(que.size()>max_n)?que.size():max_n;
            queue<Node<ElemType>*> tmp;
            while(!que.empty()){
                Node<ElemType>* x=que.front();
                que.pop();
                if(x->leftChild) tmp.push(x->leftChild);
                if(x->rightChild) tmp.push(x->rightChild);
            }
            que=tmp;
        }
        return max_n;
    }
    void NonRecurringInOrder(Node<ElemType>* r,function<void(Node<ElemType>*)> Visit){
        if(r==nullptr) return;
        stack<Node<ElemType>*> stk;
        Node<ElemType>* x=r;
        while(x){
            stk.push(x);
            x=x->leftChild;
        }
        while(!stk.empty()){
            Node<ElemType>* tmp=stk.top();stk.pop();
            Visit(tmp);
            if(tmp->rightChild){
                x=tmp->rightChild;
                while(x){
                    stk.push(x);
                    x=x->leftChild;
                }
            }
        }
    }
    int GetHeight(){
        int height=0;
        queue<Node<ElemType>*> que;
        if(this->root==nullptr){
            return 0;
        }
        que.push(this->root);
        while(!que.empty()){
            ++height;
            queue<Node<ElemType>*> tmp;
            while(!que.empty()){
                Node<ElemType>* x=que.front();que.pop();
                if(x->leftChild) tmp.push(x->leftChild);
                if(x->rightChild) tmp.push(x->rightChild);
            }
            que=tmp;
        }
        return height;
    }

    bool vec_left[1000] = {0};
    void Display(Node<ElemType>* root, int ident=0)
    {
        if(ident > 0)
        {
            for(int i = 0; i < ident - 1; ++i)
            {
                if(vec_left[i]){
                    cout<<"||  ";
                }else{
                    cout<<"    ";
                }
            }
            if(vec_left[ident-1]){
                cout<<"||__";
            }else{
                cout<<"\\\\__";
            }
        }
 
        if(! root)
        {
            cout<<"(null)\n";
            return;
        }
 
        cout<<root->data<<endl;
        if(!root->leftChild && !root->rightChild)
        {
            return;
        }
 
        vec_left[ident] = 1;
        Display(root->leftChild, ident + 1);
        vec_left[ident] = 0;
        Display(root->rightChild, ident + 1);
    }

};