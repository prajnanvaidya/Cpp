#include<bits/stdc++.h>

using namespace std;

//Doubly LinkedList
// each node has next and previous ptr
//prev ptr of head points NULL and next ptr of tail points to NULL

//Representation
class Node{
    public: 
    int data;
    Node* next;
    Node* prev;

    Node(int data1, Node* next1, Node* prev1){
        data = data1;
        next = next1;
        prev = prev1;
    }
    Node(int data1){
        data = data1;
        next = nullptr;
        prev = nullptr;
    }
};

//------------------------------------------------------------------------------------------------------------------------

//Convert an array to LinkedList
Node* convertArrDLL(vector<int>& arr){
    if(arr.size() == 0)
        return nullptr;
    Node* head = new Node(arr[0]);
    Node* mover = head;
    for(int i=1;i<arr.size();i++){
        Node* temp = new Node(arr[i]);
        mover->next = temp;
        temp->prev = mover;

        mover = mover->next;
    }
    return head;
}

void printDLL(Node* head){
    if(head == NULL)
        return;
    Node* temp = head;
    while(temp != nullptr){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

int LengthOfDLL(Node* head){
    int n=0;
    Node* current = head;
    while(current!=nullptr){
        n++;
        current=current->next;
    }
    return n;
}

//------------------------------------------------------------------------------------------------------------------------------
//Deletion of a node
//deleting the head node
Node* deleteHeadDLL(Node* head){
    if(head == nullptr || head->next == nullptr){
        return nullptr;
    }
    Node* temp=head;
    head->next->prev = nullptr;
    head = temp->next;

    delete temp;
    return head;
}


//Delete tail node
Node* deleteTailDLL(Node* head){
    if(head == nullptr){
        return head;
    }
    else if(head->next == nullptr){
        return nullptr;
    }
    Node* temp = head;
    while(temp->next->next != nullptr){
        temp=temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
    return head;
}

//deleting a node at kth position
Node* deleteKPosDLL(Node* head, int k){
    if(head == nullptr || k<=0 || k>LengthOfDLL(head)){
        return head;
    }
    else if(k == LengthOfDLL(head)){
        return deleteTailDLL(head);
    }
    else if(k==1){
        return deleteHeadDLL(head);
    }
    int cnt=0;
    Node* current=head;
    while(current != nullptr){
        cnt++;
        if(cnt == k-1){
            Node* temp = current->next;
            temp->next->prev = current;
            current->next = temp->next;

            delete temp;
            break;
        }
        current = current->next;
    }
    return head;
}

Node* deleteKPosHis(Node* head, int k){
    if(head == nullptr){
        return head;
    }
    Node* temp = head;
    int cnt=0;
    while(temp->next!=nullptr){
        cnt++;
        if(cnt == k)
            break;
        temp = temp->next;
    }
    Node* back = temp->prev;
    Node* front = temp->next;
    
    if(front==nullptr && back==nullptr){
        if(k==1){
            return nullptr;
        }
        else{
            return head;
        }
    }
    else if(back == nullptr){
        return deleteHeadDLL(head);
    }
    else if(front == nullptr){
        return deleteTailDLL(head);
    }
    back->next = temp->next;
    front->prev = temp->prev;

    temp->next = nullptr;
    temp->prev = nullptr;
    delete temp;
    return head;
}

//Given a noed delete it
Node* deleteNodeDLL(Node* head, int key){
    if(head == nullptr){
        return head;
    }
    else if(head->data == key){
        return deleteHeadDLL(head);
    }
    Node* temp = head;
    while(temp!=nullptr){
        if(temp->data == key){
            if(temp->next != nullptr){
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
                break;
            }
            else{
                temp->prev->next = nullptr;
                delete temp;
                break;
            }    
        }
        temp = temp->next;
    }
    return head;
}

//-------------------------------------------------------------------------------------------------------------------------------
//inserting a node to DLL
//Insert node before the head
Node* insertNodeBHeadDLL(Node* head, int el){
    if(head == nullptr){
        Node* temp = new Node(el);
        return temp;
    }
    Node* temp = new Node(el, head, nullptr);
    head->prev = temp;
    return temp;
}

//inserting node before tail
Node* insertNodeBTailDLL(Node* head, int el){
    if(head == nullptr){
        Node* temp = new Node(el);
        return temp;
    }
    Node* current = head;
    while(current->next != nullptr){
        current = current->next;
    }
    Node* temp = new Node(el, current, current->prev); 
    current->prev->next = temp;
    current->prev = temp;
    return head;
}

//insertng a el at pos p
Node* insertElPosDLL(Node* head, int el, int p){
    if(head == nullptr){
        if(p==1){
            Node* temp = new Node(el);
            return temp;
        }
        else{
            return head;
        }
    }
    else if(p<=0 || p> LengthOfDLL(head)+1){
        return head;
    }
    else if(p == LengthOfDLL(head)+1){
        Node* current = head;
        while(current->next != nullptr){
            current = current->next;
        }
        Node* temp = new Node(el, nullptr, current);
        current->next = temp;
        return head;
    }
    int cnt=0;
    Node* current = head;

    while(current->next != nullptr){
        cnt++;
        if(cnt==p)
            break;
        current = current->next;
    }

    Node* front = current->next;
    Node* back = current->prev;

    if(front == nullptr && back == nullptr){
        if(p==1){
            return insertNodeBHeadDLL(head, el);
        }
        else if(p==2){
            return insertNodeBTailDLL(head, el);
        }
        else{
            return head;
        }
    }

    else if(back == nullptr){
        return insertNodeBHeadDLL(head, el);
    }

    else if(front == nullptr){
        return insertNodeBTailDLL(head, el);
    }
    
    Node* temp = new Node(el, current, current->prev);
    current->prev->next = temp;
    current->prev = temp;

    return head;
}

//insert el behind a x
Node* insertElBXDLL(Node* head, int el, int x){
    if(head == nullptr){
        return head;
    }
    else if(head->data == x){
        Node* temp = new Node(el, head, nullptr);
        head->prev = temp;
        return temp;
    }
    Node* current = head;
    while(current != nullptr){
        if(current->data == x){
            Node* temp = new Node(el, current, current->prev);
            current->prev->next = temp;
            current->prev = temp;
            break;
        }
        current = current->next;
    }
    return head;
}

//--------------------------------------------------------------------------------------------------------------------------------
//Reversing a DLL
// Just swapping the elems

Node* reverseBySwapDLL(Node* head){
    if(head ==  nullptr || head->next == nullptr){
        return head;
    }
    Node* temp = head;
    stack<int> st;
    while(temp != nullptr){
        st.push(temp->data);
        temp = temp->next;
    }
    temp = head;
    while(temp!=nullptr){
        temp->data = st.top();
        st.pop();
        temp = temp->next;
    }
    return head;
}
//Tc - O(2*n), Sc - O(n)

// Reversing a DLL by reversing the links
Node* reverseDLLByRevLinks(Node* head){
    if(head == nullptr || head->next == nullptr){
        return head;
    }
    Node* temp = head;
    Node* back = nullptr;
    
    while(temp != nullptr){
        back = temp->prev;
        temp->prev = temp->next;
        temp->next = back;

        temp = temp->prev;
    }

    head = back->prev;
    return head;
}
//Tc - O(n), Sc - O(1)



int main(){
    vector<int> arr={10, 20, 30, 40, 50};
    Node* head = convertArrDLL(arr);
    printDLL(head);
    cout<<endl;

    // head = insertElBXDLL(head,9, 70);
    head = reverseDLLByRevLinks(head);
    printDLL(head);

    return 0;
}