#include<bits/stdc++.h>

using namespace std;

//Stack and Queue

//Stack; Its DS that stores a particular type(can also hold multiple type of data using customization) of data like it can be a int, float, pair, custome type

//Principle: LIFO

//methods provided:
// -push
// -pop
// -top
// -size

//Queue: Allows FIFO, similar DS that allows to hold a particular data type like int, float, pair, custom
// Operations:
// push
// pop
// front
// back
// size

//-------------------------------------------------------------------------------------------------------------------------

//Implementing stack using arrays
//The size should be predefined it canot be dynamic

class stackP{

    private:
    int ptr = -1;
    int maxSize = 10;
    int arr[10] = {0};

    public:

    void push(int n){
        if(ptr < maxSize){
            arr[++ptr] = n;
        }
        else
            cout<<"Alert Exceeds Limit";
    }

    void pop(){
        if(ptr != -1){
            ptr--;
        }
        else
            cout<<"Alert no element to pop!";
    }

    int size(){
        return ptr+1;
    }

    int top(){
        if(ptr != -1)
            return arr[ptr];
        else
            cout<<"Stack is empty: ";
        return -1;
    }
};
//Here push, pop, top, size all takes O(1) TC
//Here i cannot take maxSize while creating the object as im using C style arr and for it the size inputed should not be in variable even if its in var the var should be declared as const int sz-10; int arr[sz]; and sz cannot be runtime known it should be compile time constant i.e below not possible or even inputting through a constructor not possible
// const int sz;
// cin>>sz;
// int arr[sz];
//If u indeed want size to be user inputed then go with vector not C-style arr

//-------------------------------------------------------------------------------------------------------------------------

//Implementing queue with arr
class queueP{
    private:
    int start =-1, end=-1;
    int cur_size=0;
    int arr[4];
    int maxSize=4;

    public:
    void push(int n){
        if(cur_size == 0){
            start++;
            end++;
            arr[end]=n;
            cur_size++;
        }
        else if(cur_size >= maxSize){
            cout<<"Max Size crossed!"<<endl;
        }
        else{
            end = (end+1)%maxSize;
            arr[end] = n;
            cur_size++;
        }
    }
    int pop(){
        if(cur_size == 0){
            cout<<"Queue Empty!: ";
            return -1;
        }
        else if(cur_size == 1){
            int temp = arr[start];
            start = -1, end=-1;
            cur_size--;
            return temp;
        }
        else{
            int temp =arr[start];
            start = (start+1)%maxSize;
            cur_size--;
            return temp;
        }
    }

    int front(){
        if(cur_size==0){
            cout<<"Queue is empty!: ";
            return -1;
        }
        else{
            return arr[start];
        }
    }

    int back(){
        if(cur_size==0){
            cout<<"Queue is empty!: ";
            return -1;
        }
        else{
            return arr[end];
        }
    }

    int size(){
        return cur_size;
    }
};

//Implement stack using LinkedList
class Node{
    public:
    int data;
    Node* next;

    Node(int data1, Node* next1){
        data = data1;
        next = next1;
    }

    Node(int data1){
        data = data1;
        next = nullptr;
    }
};

class stackLL{
    private:
    int cur_size=0;
    Node* tp=nullptr;

    public:
    void push(int n){
        Node* temp = new Node(n);
        temp->next = tp;
        tp = temp; 
        cur_size++;
    }
    void pop(){
        if(cur_size == 0){
            cout<<"Stack is empty!: "<<endl;
        }
        else{
            Node* temp = tp;
            tp = tp->next;
            delete temp;
            cur_size--;
        }
    }
    int top(){
        if(cur_size==0){
            cout<<"Stack empty!: ";
            return -1;
        }
        else{
            return tp->data;
        }
    }

    int size(){
        return cur_size;
    }

    void print(){
        Node* cur=tp;
        while(cur!=nullptr){
            cout<<cur->data<<" ";
            cur = cur->next;
        }
    }

};

//-------------------------------------------------------------------------------------------------------------------------

//Implement queue using LL

class queueLL{
    private:
    int cur_size=0;
    Node* fr=nullptr;
    Node* bc=nullptr;

    public:
    void push(int n){
        Node* temp = new Node(n);
        if(cur_size == 0){
            fr = temp;
            bc = temp;
        }
        else{
            temp->next = bc;
            bc = temp;
        }
        cur_size++;
    }

    void pop(){
        Node* temp = fr;
        if(cur_size == 0){
            cout<<"Queue is empty!"<<endl;
        }
        else if(cur_size == 1){
            fr = nullptr;
            bc = nullptr;
            delete temp;
            cur_size--;
        }
        else{
            Node* cur = bc;
            while(cur->next != fr){
                cur=cur->next;
            }
            fr = cur;
            delete temp;
            cur_size--;
        }
    }

    int front(){
        if(cur_size==0){
            cout<<"Queue empty!: ";
            return -1;
        }
        else{
            return fr->data;
        }
    }

    int back(){
        if(cur_size==0){
            cout<<"Queue empty!: ";
            return -1;
        }
        else{
            return bc->data;
        }
    }

    int size(){
        return cur_size;
    }

    void print(){
        Node* temp = bc;
        while(temp != nullptr){
            cout<<temp->data<<" ";
            temp = temp->next;
        }
    }
};
//Here to pop when there exist more then 1 node it needs to traverse entire LL inorder to make fr point the node back of it this is because we made all nodes point from back to front but this problem wont arise if we made all node point from front to back!

//-------------------------------------------------------------------------------------------------------------------------

//Implementing Queue using LL such that node point in direction front to back inorder to make all operations TC as O(1)
class queueLLC{
    public:
    Node* fr=nullptr;
    Node* bc = nullptr;
    int cur_size=0;

    public:
    void push(int n){
        Node* temp = new Node(n);
        if(cur_size==0){
            bc=temp;
            fr=temp;
        }
        else{
            bc->next = temp;
            bc=temp;
        }
        cur_size++;
    }

    void pop(){
        Node* temp = fr;
        if(cur_size == 0){
            cout<<"Queue is empty!"<<endl;
            return;
        }
        else{
            fr = fr->next;
            if(fr == nullptr)
                bc = fr;
            delete temp;
            cur_size--;
        }
    }

    int front(){
        if(cur_size==0){
            cout<<"Queue is empty!: ";
            return -1;
        }
        return fr->data;
    }

    int back(){
        if(cur_size==0){
            cout<<"Queue is empty!: ";
            return -1;
        }
        return bc->data;
    }

    int size(){
        return cur_size;
    }

    void print(){
        Node* temp = fr;
        while(temp!=nullptr){
            cout<<temp->data<<" ";
            temp = temp->next;
        }
    }
};
//TC - O(1) all operations, SC - O(size of queue)

//-------------------------------------------------------------------------------------------------------------------------

//Implementing a stack from queue

class stackQ{
    public:
    queueLLC q;

    void push(int n){
        Node* temp = new Node(n);
        if(q.cur_size == 0){
            q.bc = temp;
            q.fr = temp;
        }
        else{
            temp->next = q.fr;
            q.fr = temp;
        }
        q.cur_size++;
    }

    void pop(){
        if(q.cur_size==0){
            cout<<"Stack is empty!: ";
            return;
        }
        q.pop();
    }

    int top(){
        if(q.cur_size==0){
            cout<<"Stack is empty!: ";
            return -1;
        }
        return q.front();
    }

    int size(){
        return q.size();
    }
};

//Apparently his approach involved not to access a custom imlemented queues private memebers and do the job

//We can consider our custom class as well but we will take stl queue

class stackQC{
  private:
  queue<int> q;
  
  public:
  void push(int n){
    q.push(n);
    int s = q.size();
    for(int i=1;i<s;i++){
        q.push(q.front());
        q.pop();
    }
  }

  void pop(){
    q.pop();
  }

  int top(){
    if(q.size()==0){
        cout<<"Stack is empty!: ";
        return -1;
    }
    return q.front();
  }

  int size(){
    return q.size();
  }

};
//TC - O(n) for push, all other O(1)

//------------------------------------------------------------------------------------------
//Implementing queue using stack

class queueS{
    private:
    stack<int> s;

    public:
    void push(int n){
        int sz = s.size();
        vector<int> arr;
        
        for(int i=0;i<sz;i++){
            arr.push_back(s.top());
            s.pop();
        }
        s.push(n);
        for(int i=(sz-1);i>=0;i--){
            s.push(arr[i]);
        }
    }
    
    void pop(){
        if(s.size() == 0){
            cout<<"Queue is empty!"<<endl;
            return;
        }
        s.pop();
    }

    int front(){
        if(s.size() == 0){
            cout<<"Queue is empty!: ";
            return -1;
        }
        return s.top();
    }

    int back(){
        if(s.size() == 0){
            cout<<"Queue is empty!: ";
            return -1;
        }
        int sz = s.size();
        vector<int> arr;
        for(int i=0;i<sz-1;i++){
            arr.push_back(s.top());
            s.pop();
        }
        int back = s.top();
        for(int i=sz-2;i>=0;i--){
            s.push(arr[i]);
        }
        return back;
    }

    int size(){
        return s.size();
    }
};
//TC - for push and back - O(n), all other O(1), Sc - for push and back - O(n) all other O(1)

//Apparently the optimal approach is to use 2 stacks one for pushing and the other for popping

class QueueSC{
    private:
    //S1 stores data back to front in stack(top to bottom)
    //S2 stores data front to back in stack(top to bottom)
    stack<int> s1, s2;

    public:

    void push(int n){
        s1.push(n);
    }
    void pop(){
        if(s1.empty() && s2.empty()){
            cout<<"Stack is empty!"<<endl;
            return;
        }
        else if(s2.empty()){
            while(!s1.empty()){
               s2.push(s1.top());
               s1.pop();
            }
        }
        s2.pop();
    }

    int front(){
        if(s1.empty() && s2.empty()){
            cout<<"Stack is empty!";
            return -1;
        }
        else if(s2.empty()){
            while(!s1.empty()){
               s2.push(s1.top());
               s1.pop();
            }
            return s2.top();
        }
        else {    //If s1 and s2 both have some value then u need to return s2.top cuz its the front elem which has been poped out of S1 before pushing some more vals to s1 again
            return s2.top();
        }
    }

    int back(){
        if(s1.empty() && s2.empty()){
            cout<<"Stack is empty!";
            return -1;
        }
        else if(s1.empty()){
            while(!s2.empty()){
                s1.push(s2.top());
                s2.pop();
            }
        }
        return s1.top();
    }

    int size(){
        return s1.size()+s2.size();
    }

    void print(){
        if(s1.empty() && s2.empty()){
            cout<<"Stack is empty!";
            return;
        }
        else if(s1.empty()){
            cout<<"Front->Back: ";
            while(!s2.empty()){
                cout<<s2.top()<<" ";
                s1.push(s2.top());
                s2.pop();
            }
        }
        else if(s2.empty()){
            cout<<"Back->Front: ";
            while(!s1.empty()){
                cout<<s1.top()<<" ";
                s2.push(s1.top());
                s1.pop();
            }
        }
        else{
            int s2_sz=s2.size(), s1_sz=s1.size();
            cout<<"Back->Front: ";
            while(!s1.empty()){
                cout<<s1.top()<<" ";
                s2.push(s1.top());
                s1.pop();
            }
            while(!s2.empty()){
                s1.push(s2.top());
                s2.pop();
            }

            while(s2_sz>0){
                cout<<s1.top()<<" ";
                s2.push(s1.top());
                s1.pop();
                s2_sz--;
            }
        }
    }

};
//TC - pop, front, back - amortaised O(1){worst case O(n)}, push, size - O(1), print - O(n)
//Sc - O(n) 

//In above approach we made the push to be taking unit time and top and pop to be O(n) - use it when ur usecase has lot of push than the pop and top

//Approach - 2: which is optimized for pop and top 
// in here when said push(n)
// - transfer all elems from s1 to s2
// - push n to s1
// - transfer back all elems from s2 to s1

// This ensures s1 stores elems in order of Front->Back{in stack top-bottom} so top(front in his sense) and pop can be done in O(1)

class QueueSC2{
    private:
    stack<int> s1, s2;

    public:

    void push(int n){
        if(s1.empty()){
            s1.push(n);
            return;
        }
        while(s1.size()){
            s2.push(s1.top());
            s1.pop();
        }
        s1.push(n);
        while(s2.size()){
            s1.push(s2.top());
            s2.pop();
        }
    }

    void pop(){
        if(s1.empty()){
            cout<<"Stack is empty!: ";
        }
        s1.pop();
    }

    int front(){
        if(s1.empty()){
            cout<<"Stack is empty!: ";
            return -1;
        }
        return s1.top();
    }

    int back(){
        if(s1.empty()){
            cout<<"Stack is empty!: ";
            return -1;
        }
        while(s1.size()){
            s2.push(s1.top());
            s1.pop();
        }
        int bc = s2.top();
        while(s2.size()){
            s1.push(s2.top());
            s2.pop();
        }
        return bc;
    }

    int size(){
        if(s1.empty()){
            cout<<"Stack is empty!: ";
            return -1;
        }
        return s1.size();
    }

};
//push, back - O(n), front, pop - O(1)

//-------------------------------------------------------------------------------------------------------------------------

int main(){

    // stackP st;

    // st.push(2);
    // st.push(5);
    // st.push(0);
    // st.pop();
    // cout<<st.top()<<endl;
    // st.pop();
    // cout<<st.size()<<endl;
    // st.pop();
    // cout<<st.top()<<endl;
    // cout<<st.size()<<endl;

    // ===========================================================

    // queueP q;
    // q.push(2);
    // q.push(23);
    // q.push(12);

    // q.pop();
    // cout<<q.front()<<endl;
    // q.pop();

    // cout<<q.back()<<endl;
    // cout<<q.size()<<endl;

    // q.push(8);

    // cout<<q.size()<<endl;

    // q.push(6);
    // q.push(7);
    // q.pop();
    // q.push(3);

    // cout<<q.size()<<endl;

    // q.pop();
    // q.push(12);
    // q.push(32);

    // cout<<q.back()<<endl;

    // ===========================================================

    return 0;
}