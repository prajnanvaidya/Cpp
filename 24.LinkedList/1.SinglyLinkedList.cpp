#include<bits/stdc++.h>

using namespace std;


//LinkedList
// Whats it?
// Its a data structure which helps u to incrment and decrease size dynamically because a c arr once declared size cannot be changed as it will be contigously located on heap memory
//Linkedlsist it stores elems in non contigous location, it does it by storing data along with next ptr in a node or say value

//Where LinkedList is used?
// - In DSA: its used in stack and queue implementation
// - In real life its used in Browser

// In Browser: the back arrow and front arrow is used to go back at location or url or link u were previously in that tab, It uses Linkedlist internally to implement it

// How Linkedlist is implemented - Its implemented using User Defined DataType like struct in cpp or class in java.

// Implementing LinkedList in cpp: 
// Uses pointer: pointer stores address of a variable
// - Normal variable declaration & Iniatialization: int x=5;  |5| - x, Writes a heap memopry block and stores x variable name in stack which points to that heap memory block
// - Pointer variable declaration & Intialization: int *y = &x, here y is a variable that stores address of heap where x points to, say heap address x points to is 76869, then y is on stack pointing to heap mempory block which has |76869|
// Note: DataType of pointer variable depends on data which is being stored in memory address it stores
// For ex: char x='c';
//         char *y = &x;

// So inorder to create a linkedlist we need a data structure that stores both data and address in a heap memory block but there is none so we create our own DS using struct

// struct Node{
//     int data;
//     Node* next; //Node to be DT as next points to a variable of type User defined Datatype: Node
//     Node(data1, next1){
//         data = data1;
//         next = next1;
//     }
// };

// Now how to declare a LinkedList in main;
// either as:
// 1.Simplified: 
// Node x = Node(2, nullptr); //Here x is a variable of type Node, x is on stack pointing to a heap block which has [2, nullptr] 
// Node *y = &x; //Here y is a pointer variable storing address of x, here y is on stack pointing to a block on heap storing address of heap block pointed by x

// Why we require y: here y acts as Head pointer which points to first block of a Linkedlist

// 2.One line declaration
// Node* y=new Node(2, nullptr); //where y is head ptr and new creates a space on heap which is of Node DataType and stores data: 2 and nullptr and y stores address of that block of heap

// If done as:
// Node y=Node(2, nullptr) //here y directly points to a block in heap of type Node which has 2 parts y.data and y.next

// A clarification:
// Node x = Node(2, nullptr);
// or 
// Node x(2, nullptr);
// here x is stored on stack and its a Node object , its not like x is stored on stack and has address of heap memory in where actual Node object with dqata=2, next=nullptr exist, no!

// Node* y=new Node(3, nullptr);
// here new is keyword which creates space on heap and returns its address, So y is on stack storing address of heap space storing Node object with data=3, next=nullptr

// U cannot do:
// Node* y=&Node(2, nullptr); //because here Node(2, nullptr) is a temporary object and u cannot access address of temp object
// Node x=new Node(3, nullptr); //as new returns a address x is a Node object and not Node ptr
// // Node ptr is different from Node object

// Node* y=Node(4, nullptr) //as y is a Node ptr and cannot store Node object 


// If u want to access data and next of a Node ptr use either 
// 1. (*y).data, (*y).next
// 2. y->data, y->next

// If u want to access the variable of a struct object
// say struct name is Noe and vars are data and next
// Use: x.data, x.next

// Note: Inorder to avail the benefits of OOP such as abstraction, inheritence, etc changes struct to class 

//----------------------------------------------------------------------------------------------------------------

//Memory space used

// In 32bits system
// int data - 4 bytes
// Node* next - 4 bytes
// Whole struct - 8 bytes

// In 64bits system
// int data - 4 bytes
// Node* next - 8 bytes
// Whole struct - 12 bytes

//----------------------------------------------------------------------------------------------------------------



// Ex:
// struct Node {
//     public:
//     int data;
//     Node* next;

//     public:
//     Node(int data1, Node* next1){
//         data=data1;
//         next=next1;
//     }

//     Node(int data1){
//         data=data1;
//         next=nullptr;
//     }
// };

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

Node* convertArrToLL(vector<int>& arr){
    Node* head = new Node(arr[0]);
    Node* mover = head;
    for(int i=1;i<arr.size();i++){
        Node* temp = new Node(arr[i]);
        mover->next=temp;
        mover=temp;
    }
    return head;
}
//Tc - O(n), Sc = O(1)(auxillary space , return space O(n))

//--------------------------------------------------------------------------------------------
// Traversing in LL:
// Never tamper the head just keep a temperory ptr to head and loop print each time and update temp ptr

void printLL(Node* head){
    Node* mover=head;
    while(mover!=nullptr){
        cout<<mover->data<<" ";
        mover=mover->next;
    }
}
//Tc - o(n), Sc - O(1)

//--------------------------------------------------------------------------------------------

int LengthOfLL(Node* head){
    int cnt=0;
    Node* mover=head;
    while(mover!=nullptr){
        cnt++;
        mover=mover->next;
    }
    return cnt;
}
//------------------------------------------------------------------------
//Search a element in a LL
bool searchInLL(Node* head, int key){
    Node* mover=head;
    while(mover!=nullptr){
        if(key==mover->data)
            return true;
        mover = mover->next;
    }
    return false;
}
//Tc - o(n), Sc - o(1)
//-------------------------------------------------------------------------------

//Delete a node from a LL
void deleteNodeLL(Node* &head, int key){
    if(head->data == key){
        Node* temp=head;
        head = head->next;
        delete temp;
        return;
    }

    Node* previous=head;
    Node* current=head->next;
    while(current!=nullptr){
        if(current->data == key){
            Node* temp=current;
            previous->next = current->next;
            current=current->next;
            delete temp;
            return; //if want to delete multiple duplicate elems then use continue instead of return
        }
        previous=current;
        current=current->next;
    }
}
//Tc - O(n){when key to delete is not present}, Sc - O(1)

//Remove head node only
void removeHeadLL(Node* &head){
    Node* temp=head;
    head=head->next;
    delete temp;
}

//Remove tail only
void removeTailLL(Node* head){
    Node* current = head;
    while(current->next->next != nullptr){
        current = current->next;
    }
    delete current->next; 
    current->next = nullptr;
}

//delete kth node
void deleteKPos(Node* &head, int p){
    if(head == nullptr){
        return;
    }
    else if(p<=0 || p>LengthOfLL(head)){
        return;
    }
    else if(p==1){
        Node* temp=head;
        head=head->next;
        delete temp;
        return;
    }
    Node* previous = head;
    Node* current = head->next;
    p=p-2;
    while(p>0){
        previous = current;
        current = current->next;
        p--;
    }
    previous->next = current->next;
    delete current;
}


Node* deleteKPosHis(Node* head, int k){
    if(head==nullptr){
        return head;
    }
    else if(k==1){
        Node* temp=head;
        head = head->next;
        delete temp;
        return head; 
    }

    Node* temp=head;
    Node* previous=nullptr;
    int cnt=0;
    while(temp != nullptr){
        cnt++;
        if(cnt==k){
            previous->next = previous->next->next;
            delete temp;
            break;
        }
        previous=temp;
        temp = temp->next;
    }
    return head;
}

//-----------------------------------------------------------------

//Insert a node in LL:
//Insert as head
Node* insertAsHeadLL(Node* head, int key){
    Node* temp = new Node(key, head);
    return temp;
}

//Insert at tail
Node* insertAsTailLL(Node* head, int k){
    if(head == NULL){
        return new Node(k);
    }
    Node* temp = new Node(k);
    Node* current = head;
    while(current->next != nullptr){
        current = current->next;
    }
    current->next = temp;
    return head;
}

//Inserting based on position
void insertNodeLL(Node* &head, int key, int pos){
    if(head==nullptr){
        cout<<"No elems"<<endl;
        return;
    }
    else if(pos <= 0 || pos > LengthOfLL(head)+1){
        cout<<"Invalid Position"<<endl;
        return;
    }
    else if(pos==1){
        Node* temp=new Node(key);
        temp->next = head;
        head=temp;
        return;
    }
    Node* temp=new Node(key);
    int cnt=pos-2;
    Node* current=head;
    while(cnt>0){
        current=current->next;
        cnt--;
    }
    temp->next=current->next;
    current->next = temp;
}
//Tc - O(pos-1), Sc-O(1)

Node* insertNodePosLLHis(Node* head, int key, int pos){
    if(head == nullptr){
        if(pos==1)
            return new Node(key);
        else
            return head;
    }
    else if(pos<=0 && pos>LengthOfLL(head)+1){ 
        return head;
    }
    else if(pos == 1){
        Node* temp = new Node(key, head);
        return temp;
    }
    else if(pos == LengthOfLL(head)+1){
        Node* temp = new Node(key);
        Node* current = head;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = temp;
        return head;
    }

    int cnt=0;
    Node* current=head;
    while(current != nullptr){
        cnt++;
        if(cnt == pos-1){
            Node* temp = new Node(key, current->next);
            current->next = temp;
            break;
        }
        current = current->next;
    }
    return head;
}

//Insert an element before the value x

Node* insertValByXLL(Node* head, int el, int x){
    if(head == NULL){
        return head;
    }
    else if(head->data == x ){
        Node* temp = new Node(el, head);
        return temp;
    }
    Node* current = head;
    while(current != nullptr){
        if(current->next != nullptr && current->next->data == x )
            break;
        current = current->next;
    }
    if(current==nullptr){
        return head;
    }
    
    Node* temp = new Node(el, current->next);
    current->next = temp;
    return head;
}

//-------------------------------------------------------------------------------------------------------------------------------


int main(){
    // vector<int> arr={1,2,3,4};
    // Node* y= new Node(arr[0], nullptr);
    // cout<<y<<endl;
    // cout<<(*y).data<<" "<<y->next<<endl;
    // delete y; // should delete it as new creates a object on heap and never destroys it, should be done manually

    // Node x=Node(arr[2], nullptr);
    // // cout<<x; //error
    // cout<<x.data<<" "<<x.next<<endl;

    vector<int> arr={10, 20, 30, 40, 50};
    Node* head= convertArrToLL(arr);
    // cout<<head->data<<endl;

    // printLL(head);

    // cout<<LengthOfLL(head)<<endl;

    // cout<<searchInLL(head, 60)<<endl;

    // deleteKPos(head, 6);
    Node* updated_head = insertValByXLL(head, 70, 80);
    printLL(updated_head);
    cout<<endl;

    // insertNodeLL(head, 60, 4);
    // printLL(head);
    // cout<<endl;

 
    return 0;
}