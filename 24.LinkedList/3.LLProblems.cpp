#include<bits/stdc++.h>

using namespace std;

class NodeL{
    public:
    int data;
    NodeL* next;

    NodeL(int data1, NodeL* next1){
        data = data1;
        next = next1;
    }
    NodeL(int data1){
        data = data1;
        next = nullptr;
    }
};

class NodeD{
    public:
    int data;
    NodeD* next;
    NodeD* prev;

    NodeD(int data1, NodeD* next1, NodeD* prev1){
        data = data1;
        next = next1;
        prev = prev1;
    }
    NodeD(int data1){
        data = data1;
        next = nullptr;
        prev = nullptr;
    }
};

void print(NodeL* head){
    if(head == nullptr) return;
    NodeL* temp = head;
    while(temp!=nullptr){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

NodeL* ConvertArr(vector<int>& arr){
    NodeL* head=nullptr;

    NodeL* prev = head;
    for(int i=0;i<arr.size();i++){
        NodeL* temp = new NodeL(arr[i]);
        if(i == 0){
            head = temp;
            prev = temp;
        }
        else{
            prev->next = temp;
            prev = temp;
        }
    }
    return head;
}



NodeD* convertArrD(vector<int>& arr){
    int n = arr.size();
    if(n==0) return nullptr;

    NodeD* dummyNode = new NodeD(-1);
    NodeD* mover = dummyNode;
    for(int i=0;i<n;i++){
        NodeD* temp = new NodeD(arr[i], nullptr, mover);
        mover->next = temp;
        mover = temp;
    }
    NodeD* head = dummyNode->next;
    head->prev = nullptr;
    dummyNode->next = nullptr;
    delete dummyNode;
    return head;
}

void printD(NodeD* head){
    NodeD* temp = head;
    while(temp){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

//--------------------------------------------------------------------------------------------------------------------------------

// Adding 2 numbers in LL
// Given L1 and L2 as:
// l1 - 2->4->6
// l2 - 3->8->7
// Both exist in reverse order: so l1 = 648, l2 = 783
// l1 + l2 = 1425
// sumList - 5->2->4->1
// should return head of sumList

// Ex2:
// l1 - 3->5 = 53
// l2 - 4->5->9->9 = 9954
// l1+l2 - 10007 - 7->0->0->0->1

NodeL* add2Nos(NodeL* l1, NodeL* l2){
    int a=0,b=0;
    NodeL* temp = l1;
    int p=1;
    while(temp!=nullptr){
        a += ((temp->data) * p);
        p=p*10;
        temp = temp->next;
    }
    temp = l2, p=1;
    while(temp!=nullptr){
        b += ((temp->data) * p);
        p = p*10;
        temp = temp->next;
    }
    int sum = a+b;
    NodeL* sumHead = nullptr;
    NodeL* prev = sumHead;
    while(sum>0){
        NodeL* temp = new NodeL(sum%10);
        if(sum == a+b){
            sumHead = temp;
            prev = temp;
        }
        else{
            prev->next = temp;
            prev = temp;
        }
        sum = sum/10;
    }
    return sumHead;
}
//TC - o(n + m + sum(n,m)), SC - o(sum(n,m)){o/p space}

NodeL* add2NosBet(NodeL* l1, NodeL* l2){
    NodeL* temp1 = l1, *temp2 = l2;
    NodeL *sumHead=nullptr, *prev=nullptr;
    int inter=0, rem=0;
    while(temp1 != nullptr || temp2 != nullptr){
        if(temp1 == nullptr){
            inter = temp2->data + rem;
        }
        else if(temp2 == nullptr){
            inter = temp1->data + rem;
        }
        else{
            inter = temp1->data + temp2->data + rem;
        }
        rem=0;

        NodeL *newNode=nullptr, *remNode = nullptr;
        
        if(inter/10 != 0){
            rem = inter/10;
            inter = inter%10;
        }
        newNode = new NodeL(inter);

        if( (temp1==nullptr && temp2!=nullptr && temp2->next==nullptr) 
        || (temp1!=nullptr && temp1->next==nullptr && temp2==nullptr)
        || (temp1!=nullptr && temp1->next == nullptr && temp2!=nullptr && temp2->next == nullptr))
        {
            remNode = new NodeL(rem);
        }

        if(sumHead == nullptr){
            sumHead = newNode;
            prev = sumHead;
        }
        else{
            prev->next = newNode;
            prev=newNode;
            if(remNode != nullptr){
                prev->next = remNode;
                prev=remNode;
            }
        }
        if(temp1 != nullptr)
            temp1 = temp1->next;
        if(temp2 != nullptr)
            temp2 = temp2->next;
    } 
    return sumHead;
}
//That became too complicated instead go with below


// - Here clubbed intr addition and temp1,2 traverse
// - rem is checked at the end and initially always equated to inter/10 if inter is single digit then gives 0 otherwise gives second digit
NodeL* add2NosBetC(NodeL* l1, NodeL* l2){
    NodeL* temp1 = l1, *temp2 = l2;
    
    NodeL* sumHead = nullptr, *prev = nullptr;

    int rem = 0;

    while(temp1!=nullptr || temp2!=nullptr){
        int inter = rem;
        if(temp1 != nullptr){
            inter += temp1->data;
            temp1 = temp1->next;
        }
        if(temp2 != nullptr){
            inter += temp2->data;
            temp2 = temp2->next;
        }

        rem = inter/10;
        inter = inter%10;

        NodeL* newNode = new NodeL(inter);
        if(sumHead == nullptr){
            sumHead = newNode;
            prev = newNode;
        }
        else{
            prev->next = newNode;
            prev = newNode;
        }
    }
    if(rem!=0){
        NodeL* remNode = new NodeL(rem);
        prev->next = remNode;
    }
    return sumHead;
}
//TC - O(max(n, m)), SC - O(1) where n - digitLen of l1, m - digitLen of l2   

//Using dummyNode inorder for cleaner implementation

NodeL* add2OptClean(NodeL* l1, NodeL* l2){
    NodeL* t1 = l1;
    NodeL* t2 = l2;
    NodeL* dummyNode = new NodeL(-1);
    NodeL* curr = dummyNode;

    NodeL* newNode;

    int carry = 0;
    while(t1 != nullptr || t2 != nullptr){
        int sum = carry;
        if(t1){
            sum += t1->data;
            t1 = t1->next;
        }
        if(t2){
            sum += t2->data;
            t2 = t2->next;
        }
        newNode = new NodeL(sum%10);
        carry = sum/10;

        curr->next = newNode;
        curr = newNode;
    }
    if(carry){
        newNode = new NodeL(carry);
        curr->next = newNode;
    }
    return dummyNode->next;
}

//-------------------------------------------------------------------------------------------------------------------------------

//Odd and Even LinkedList
// Given a LL u should first club odd indexes node and then club even indexes and return head

// Ex: 1->3->4->2->5->6
// res = 1->4->5->3->2->6

NodeL* oddEven(NodeL* head){
    NodeL* cur = head;

    NodeL* dummyOd = new NodeL(-1);
    NodeL* prevOd = dummyOd;
    NodeL* dummyEv = new NodeL(-1);
    NodeL* prevEv = dummyEv;
    
    int i=1;
    while(cur != nullptr){
        if(i%2==1){
            prevOd->next = cur;
            prevOd = cur;
        }
        else{
            prevEv->next = cur;
            prevEv = cur;
        }
        i++;
        cur = cur->next;
    }

    prevOd->next = dummyEv->next;

    return dummyOd->next;
}
//TC - O(n), SC - O(1) {n for output space} here we are not replacing things in place we are using extra space, the optimal uses no extra space and does changes inplace

//Brut:
NodeL* oddEvenBrut(NodeL* head){
    NodeL* cur = head;
    vector<int> arr;

    while(cur!=nullptr && cur->next!=nullptr){
        arr.push_back(cur->data);
        cur = cur->next->next;
    }
    if(cur) arr.push_back(cur->data);

    cur = head->next;
    while(cur!=nullptr && cur->next != nullptr){
        arr.push_back(cur->data);
        cur = cur->next->next;
    }
    if(cur) arr.push_back(cur->data);

    int i=0;
    cur=head;
    while(cur != nullptr){
        cur->data = arr[i];
        cur = cur->next;
        i++;
    }
    return head;
}
//TC - O(n), SC - O(n)

//For optimal which asks link changes inplace and not using extra space it may be o/p or auxillary space, so we know if we want to do, should do in a single pass, cannot do in 2 passes as once links of odd are updated then input no longer remains original

//So we maintain 2 pointers odd and even odd starts with 1st elem and even starts with 2nd elem, then each time u change curr odd and even next link to point next odd/even nodes until u reach end marked as either odd->next!=nullptr when there exist odd no of elem in LL or even->next!=nullptr when len of LL is even, Once reached links of odd and even chained changed atlast connect odd->next = initially keep track of 2nd node
// Ex: 2 -> 3 -> 1 -> 4 -> 5 -> 6
// odd = 2
// even = 3
// -> odd->next != nullptr && even->next!=nullptr
//     odd->next = odd->next->next {2->1}
//     even->next = even->next->next {3->4}
//     odd->next = odd->next->next {odd = 1}
//     even->next = even->next->next {even = 4}
// -> odd->next != nullptr && even->next!=nullptr
//     odd->next = odd->next->next {1->5}
//     even->next = even->next->next {4->6}
//     odd->next = odd->next->next {odd = 5}
//     even->next = even->next->next {even = 6}
// -> even->next = nullptr break
// odd->next = {5->3}

// return 2->1->5->3->4->6

NodeL* evenOddOpt(NodeL* head){
    NodeL* odd = head;
    NodeL* even = head->next;
    NodeL* comb = head->next;

    while(even!=nullptr && even->next != nullptr){
        odd->next = odd->next->next;
        even->next = even->next->next;

        odd = odd->next;
        even = even->next;
    }
    odd->next = comb;
    return head;
}
//TC - O(n/2 * 2) - O(n), SC - o(1)

//-------------------------------------------------------------------------------------------------------------------------------

//Sort a given LL having 0s, 1s, 2s
// Ex: {0,0,1,1,2,1}
NodeL* sortLL(NodeL* head){
    NodeL* cur = head;
    int cnt0=0, cnt1=0, cnt2=0;
    while(cur!=nullptr){
        if(cur->data == 0) cnt0++;
        else if(cur->data == 1) cnt1++;
        else cnt2++;
        cur=cur->next;
    }
    cur = head;
    while(cur != nullptr){
        if(cnt0 != 0){
            cur->data = 0;
            cnt0--;
        }
        else if(cnt1 != 0){
            cur->data = 1;
            cnt1--;
        }
        else if(cnt2!=0){
            cur->data = 2;
            cnt2--;
        }
        cur = cur->next;
    }
    return head;
}
//TC - O(2*n), SC - O(1)

NodeL* sortLLBet(NodeL* head){
    if(head==nullptr || head->next == nullptr) return head;
    NodeL* prev0=nullptr, *prev1=nullptr, *prev2=nullptr;
    NodeL* cur = head;
    NodeL* st1=nullptr, *st2=nullptr, *st0=nullptr;

    while(cur!=nullptr){
        if(cur->data == 0){
            if(prev0 == nullptr){
                prev0 = cur;
                st0 = cur;
            }
            else{
                prev0->next = cur;
                prev0 = cur;
            }
        }
        else if(cur->data == 1){
            if(prev1 == nullptr){
                prev1 = cur;
                st1 = cur;
            }
            else{
                prev1->next = cur;
                prev1 = cur;
            }
        }
        else{
            if(prev2 == nullptr){
                prev2 = cur;
                st2 = cur;
            }
            else{
                prev2->next = cur;
                prev2 = cur;
            }
        }
        cur = cur->next;
    }
    // NodeL* newHead=nullptr;
    // if(st0 != nullptr && st1 == nullptr && st2 == nullptr){
    //     prev0->next = nullptr;
    //     head = st0;
    // }
    // else if(st0 == nullptr && st1 != nullptr && st2 == nullptr){
    //     prev1->next = nullptr;
    //     head = st2;
    // }
    // else if(st0 == nullptr && st1 == nullptr && st2 != nullptr){
    //     prev2->next = nullptr;
    //     head = st2;
    // }
    // else if(st0 != nullptr && st1 != nullptr && st2 == nullptr){
    //     prev0->next = st1;
    //     prev1->next = nullptr;
    //     head = st0;
    // }
    // else if(st0 == nullptr && st1 != nullptr && st2 != nullptr){
    //     prev1->next = st2;
    //     prev2->next = nullptr;
    //     head = st1;
    // }
    // else if(st0 != nullptr && st1 == nullptr && st2 == nullptr){
    //     prev0->next = st2;
    //     prev2->next = nullptr;
    //     head = st0;
    // }
    // else{
    //     prev0->next = st1;
    //     prev1->next = st2;
    //     prev2->next = nullptr;
    //     head = st0;
    // }

    //The above can be simplified as:
    NodeL* newHead=nullptr;
    NodeL* tail = nullptr;

    if(st0!=nullptr){
        newHead = st0;
        tail=prev0;
    }
    
    if(st1 != nullptr){
        if(newHead == nullptr){
            newHead = st1;
        }
        else{
            tail->next = st1;
        }
        tail = prev1;
    }

    if(st2 != nullptr){
        if(newHead == nullptr){
            newHead = st2;
        }
        else{
            tail->next = st2;
        }
        tail=prev2;
    }
    if(tail!=nullptr){
        tail->next = nullptr;
    }

    return head;
}
//TC - O(n), SC - o(1)

//Clean code with same logic using dummyNode
NodeL* sortLLOptClean(NodeL* head){
    if(head==nullptr || head->next == nullptr){
        return head;
    }
    NodeL* zeroHead = new NodeL(-1), *oneHead = new NodeL(-1), *twoHead = new NodeL(-1);
    NodeL* zero = zeroHead, *one = oneHead, *two = twoHead;

    NodeL* cur = head;
    while(cur!=nullptr){
        if(cur->data == 0){
            zero->next = cur;
            zero = cur;
        }
        else if(cur->data == 1){
            one->next = cur;
            one = cur;
        }
        else{
            two->next = cur;
            two = cur;
        }
        cur = cur->next;
    }
    zero->next = oneHead->next?oneHead->next:twoHead->next;
    one->next = twoHead->next;
    two->next = nullptr;

    NodeL* newHead = zeroHead->next;

    delete zeroHead;
    delete oneHead;
    delete twoHead;

    return newHead;
}
//TC - O(n), SC - O(1)

//-----------------------------------------------------------------------------------------------------------------------------------

//Remove nth Node from LL from the end
// Ex: 1->2->3->4->5, k=2
// res = 1->2->3->5

//Brut: find the len of LL and do len-n and delete that node

int LLlen(NodeL* head){
    NodeL* cur = head;
    int cnt=0;
    while(cur!=nullptr){
        cnt++;
        cur = cur->next;
    }
    return cnt;
}

NodeL* deleteLL(NodeL* head, int n){
    if(head == nullptr) return head;
    if(n==1){
        NodeL* temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    NodeL* cur = head;
    n--;
    while(cur!=nullptr && n>0){
        cur = cur->next;
        n--;
    }
    NodeL* temp = cur->next;
    cur->next = cur->next->next;
    delete temp;
    return head;
}

NodeL* deleteFromLast(NodeL* head, int k){
    int len = LLlen(head);
    int n = len - k;
    head = deleteLL(head, n);
    return head;
}
//TC - o(n + len-n) ~ O(2*n), SC - O(1)

//Optimal: in O(n) use fast and slow pointer, intially keep fast&slow ptr at head, move fast ptr k times and once fast ptr went to kth pos then move fast and slow simultaneously until fast->next != nullptr then u see the slow is at the pos which is previous to delete node

NodeL* deleteFromLastBet(NodeL* head, int k){
    if(!head) return head;
    else if(!head->next){
        NodeL* temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    NodeL* fast = head, *slow = head;
    
    NodeL* temp = head;
    while(temp!=nullptr && fast->next!=nullptr){
        if(k>0){
            fast = fast->next;
            k--;
        }
        else{
            slow = slow->next;
            fast = fast->next;
        }
    }
    temp = slow->next;
    slow->next = slow->next->next;
    delete temp;
    return head;
}
//TC - O(n), SC - O(1)

//---------------------------------------------------------------------------------------------------------------------------------

//Reverse a LL
// Ex: 1->3->2->5
// res = 5->2->3->1

//Brut: Data replacement using external space, using a stack
NodeL* reverseLLBrut(NodeL* head){
    if(!head || !head->next) return head;
    NodeL* temp = head;
    stack<int> st;
    while(temp!=nullptr){
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
//TC - O(2*n), SC - o(n)

//Iterative optimal
NodeL* reverseLL(NodeL* head){
    if(!head || !head->next) return head;
    
    NodeL* cur = head, *prev = nullptr;
    while(cur!=nullptr){
        NodeL* front = cur->next;
        cur->next = prev;
        prev=cur;
        cur=front;
    }
    head = prev;
    return head;
}
//TC - O(n), SC - O(1)

//Recursive Optimal
NodeL* reverseLLRec( NodeL* prev, NodeL* cur){
    if(cur==nullptr) return prev;

    NodeL* front = cur->next;
    cur->next = prev;
    prev = cur;
    cur = front;
    return reverseLLRec( prev, cur);
}

NodeL* reverseLLRecInit(NodeL* head){
    if(!head || !head->next) return head;
    return reverseLLRec(nullptr, head);
}
//TC - O(n), SC - o(n){considering tail recursion optimization - O(n)}

//The above recursion u did is just replacing the loop with recursive calls but actual use of recursion is dividing the problem into smaller subpart and backtracking once solved the basic or smallest version
//So we each time call fnctioin by reducing no of nodes by 1 until we reach with a LL having 1 node, if LL has 1 node then u will send back as is, and then each time u maintain a newHead: head for reversed LL, head: the current head which points at begining, front: head->next : cur heads next element or reversed LL last element , then do front->next=head: which reverses a extra node in current call further, head->next = NULL: that makes the last node to point to NULL completing the reversal of LL in current stack Call

NodeL* reverseRecOpt(NodeL* head){
    if(!head || !head->next) return head;

    NodeL* newHead = reverseRecOpt(head->next);
    NodeL* front = head->next;
    front->next = head;
    head->next = nullptr;

    return newHead;
}
//TC - O(n), SC - O(n){As its not tail recursion its always O(n)}

//---------------------------------------------------------------------------------------------------------------------------------------
//Given a LL check its palindrome or not
// Ex: 1->2->3->2->1
// res = true
// Ex: 1->2->3->2->3
// res = false

//Using 2 ptrs from back and one from front and comparing each until they cross each other
// The above approach not possible as how do u write front ptr less then tail coming ptr as while condition
// And more importantly how do u make tail ptr move backwards No way down!

// Brut: Reverse Given LL and compare reversed and input which takes space as well time

//Or better use stack to store first half and compare one by one with second half

NodeL* speclReverse(NodeL* head){
    if(!head || !head->next) return head;
    stack<int> st;

    NodeL* temp = head;
    while(temp){
        st.push(temp->data);
        temp = temp->next;
    }
    NodeL* dummyNode = new NodeL(-1);
    NodeL* mover = dummyNode;
    while(!st.empty()){
        NodeL* temp1 = new NodeL(st.top());
        st.pop();
        mover->next = temp1;
        mover = temp1;
    }
    NodeL* newHead = dummyNode->next;
    delete dummyNode;
    return newHead;
}

bool palindromeCheckBrut(NodeL* head){
    if(!head || !head->next) return true;

    NodeL* temp1 = head;
    NodeL* newHead = speclReverse(head);
    NodeL *temp2 = newHead;
    
    while(temp1!=nullptr){
        if(temp1->data != temp2->data){
            return false;
        } 
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return true;
}
//U cannot use traditional reversing as it reverses things in original input
//TC - O(2*n + n), Sc - O(n)

bool palindromeCheck(NodeL* head){
    if(!head || !head->next) return true;

    stack<int> st;
    int cnt =0;
    NodeL* temp = head;
    while(temp){
        cnt++;
        temp = temp->next;
    }
    int n = cnt/2;

    temp = head;
    while(n>0){
        st.push(temp->data);
        temp = temp->next;
        n--;
    }
    if(cnt%2 == 1){
        temp = temp->next;
    }
    while(temp){
        if(temp->data != st.top()) return false;
        temp = temp->next;
        st.pop();
    }
    return true;
}
//TC - o(2*n), SC - o(n/2)

//His Brut with less complexity just considering all elems inside stack so when traversed it should strictly match all stack tops
bool palindromeCheckBrutHis(NodeL* head){
    NodeL* temp = head;
    stack<int> st;
    while(temp){
        st.push(temp->data);
        temp = temp->next;
    }
    temp = head;
    while(temp){
        if(temp->data != st.top()){
            return false;
        }
        temp = temp->next;
        st.pop();
    }
    return true;
}
//TC - O(2*n), SC - O(n)

//Optimal:
// Find the middle, to get it use tortoise and haier algo, once got the middle , reverse all the links above it then at end keep tail and front pointer go until middle to check will all traversed elem match if so then true else false

bool palindromeCheckOpt(NodeL* head){
    NodeL* slo = head, *fst = head;

    while(fst->next != nullptr && fst->next->next != nullptr){
        slo = slo->next;
        fst = fst->next->next;
    }
    NodeL* prev = slo, *cur=slo->next;

    while(cur != nullptr){
        NodeL* temp=cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }
    NodeL* tail = prev, *front = head;
    while(front != slo->next){
        if(front->data != tail->data) return false;
        front = front->next;
        tail = tail->next;
    }

    //reversing links to make sure input remains same
    cur = prev;
    prev = nullptr;
    while(cur != slo){
        NodeL* temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }
    return true;
}
//TC - O(n + n/2 + n/2), SC - O(1) 

//His clean using reverse function itself

bool palindromeCheckOptClean(NodeL* head){
    if(!head || !head->next) return true;

    NodeL* fst=head, *slo = head;

    while(fst->next != nullptr && fst->next->next != nullptr){
        slo = slo->next;
        fst = fst->next->next;
    }
    NodeL* newHead = reverseRecOpt(slo->next);
    NodeL* front=head, *tail=newHead;
    if(tail!=nullptr){
        if(front->data != tail->data) return false;
        front = front->next;
        tail = tail->next;
    }
    newHead = reverseRecOpt(newHead);
    return true;
}
//TC - O(2*n), SC - o(1)

//--------------------------------------------------------------------------------------------------------------------------------

//Adding 1 to given LL
// Ex1: 1->5->9 
// res: 1->6->0

// Ex2: 9->9->9->9
// res: 1->0->0->0->0

//May be going to tail and then reversing and adding 1 and maintaining rem atlast add if rem remains add rem as node and reverse again
NodeL* add1LL2(NodeL* head){
    NodeL* newHead = reverseRecOpt(head);
    NodeL* tail = newHead;
    int rem=0;

    while(tail){
        if(tail == newHead){
            int sum = tail->data + 1;
            tail->data = sum%10;
            rem = sum/10;
        }
        else{
            if(rem != 0){
                int sum = rem+tail->data;
                tail->data = sum%10;
                rem=sum/10;
            }
        }
        tail = tail->next;
    }
    if(rem!=0){
        NodeL* remNode = new NodeL(rem);
        head->next = remNode;
    }
    head = reverseRecOpt(newHead);
    return head;
}
//TC - o(3*n), Sc - O(1)

//Optimized; just stop when rem==0 as in above u could see its actually same code for when tail starts and when rem!=0 so initialize rem=1 and break when rem==0
NodeL* add1LL(NodeL* head){
    NodeL* newHead = reverseRecOpt(head);
    NodeL* tail = newHead;
    int rem=1;

    while(tail){
        if(rem != 0){
            int sum = rem+tail->data;
            tail->data = sum%10;
            rem=sum/10;
        }
        else{
            break;
        }
        tail = tail->next;
    }
    if(rem!=0){
        NodeL* remNode = new NodeL(rem);
        head->next = remNode;
        head = remNode;
    }
    head = reverseRecOpt(newHead);
    return head;
}

NodeL* add1LLRec(NodeL* cur, NodeL* head, int& rem){
    if(cur->next == nullptr){
        int sum = cur->data + 1;
        cur->data = sum%10;
        rem = sum/10;
        return cur;
    }
    add1LLRec(cur->next, head, rem);

    if(rem==0) return head;

    int sum = cur->data + rem;
    cur->data = sum%10;
    rem = sum/10;

    if(cur == head && rem!=0){
        NodeL* remNode = new NodeL(rem);
        remNode->next = head;
        head = remNode;
    }
    return head;
}

int helper(NodeL* cur){
    if(cur == nullptr){
        return 1;
    }
    int carry = helper(cur->next);
    cur->data += carry;
    if(cur->data < 10){
        return 0;
    }
    cur->data = 0;
    return 1;
}

NodeL* add1LLRecHis(NodeL* head){
    if(!head) return head;

    int carry = helper(head);
    if(carry == 1){
        NodeL* remNode = new NodeL(1, head);
        head = remNode;
    }
    return head;
}

//--------------------------------------------------------------------------------------------------------------------------------

//Find INtersection Point of given LL
// Given 2 LL need to get point of intersection if not exist return nullptr

// Ex: 
/*
l1 =       3->1
               \
                4->6->2
               /
l2 = 1->2->4->5
res = 4
*/

//Brut; may be go on comparing each nodes of ll until 1 stops if 2 nodes find to be pointing to same memory then it is intersection
NodeL* intersectionOFLL(NodeL* head1, NodeL* head2){
    NodeL* t1=head1, *t2 = head2;
    while(t1){
        t2 = head2;
        while(t2){
            if(t1 == t2) return t1;
            t2 = t2->next;
        }
        t1 = t1->next;
    }
    return nullptr;
}
//TC - O(n^2), SC - O(1)

//Using hashing keeping key as Node address and value say node value(not really requird)
NodeL* findIntersectionHashHis(NodeL* head1, NodeL* head2){
    map<NodeL*, int> hash;
    NodeL* temp = head1;
    while(temp){
        hash[temp] = temp->data;
        temp = temp->next;
    }
    temp = head2;
    while(temp){
        if(hash.find(temp) != hash.end()){
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
//TC - O(nlogn+mlogn), SC - O(n) where n - len of l1, m- len of l2


// Consider 
// l1 =       3->1
//                \
//                 4->6->2
//                /
// l2 = 1->2->4->5

// here if move l2 temp by len(l2)-len(l1) initially and then traverse one by one then can get result

NodeL* collisionPoint(NodeL* head1, NodeL* head2, int d){
    NodeL* t1 = head2;
    while(d){
        t1=t1->next;
        d--;
    }
    NodeL* t2 = head1;
    while(t1 != t2){
        t1 = t1->next;
        t2 = t2->next;
    }
    return t1;
}

NodeL* findIntersecLen(NodeL* head1, NodeL* head2){
    NodeL* temp = head1;
    int n1=0, n2=0;
    while(temp){
        n1++;
        temp = temp->next;
    }
    temp = head2;
    while(temp){
        n2++;
        temp = temp->next;
    }
    if(n1<n2){
        return collisionPoint(head1, head2, n2-n1);
    }
    else{
        return collisionPoint(head2, head1, n1-n2);
    }
    return nullptr;
}
//TC - O(n + m + (n-m) + m) {n>m} ~ O(m + 2*n), SC - O(1)


//Using 2 pointers: 
// the problem: before interection point both pointers may not have same no of nodes so traverse both linkedlist onces and expect an answer 
// instead we make both ptrs traverse equal no of nodes i.e equal distance at each iteration and if found any same address then end the iteration this works because consider there is intersection 
// length of l1 before intersection - a
// len of l2 before intersection - b
// len of at point of intersection to end - c

// total len of l1 - a+c
// total len of l2 - b+c

// Ex1:
// List 1:  1 -> 3 -> 5
//                     \
//                      7 -> 9 -> 11 -> nullptr
//                     /
// List 2:       2 -> 4

// Ex2:
// List 1: 1 -> 3 -> 5 -> nullptr
// List 2: 2 -> 4 -> 6 -> 8 -> nullptr

// When both ptrs point to nulptr then automatically loop ends and it doesnt go infinitely when there is no intersection
// t1 
// - Consider ex2 where there is no intersection 
// ex2: a=3, b=4, c=1
// total distance covered by t1 till becoming nullptr = 3+4+1 = 9 (a+c+b+1)
// total distance covered by t2 till becoming nullptr = 4+3+1 = 9 (b+c+a+1)

// considering ex1: there exist intersection
// a=3, b=2, c=4(considering nullptr)

// total distance covered by t1 till t1=t2: 10 = a+c+b+1
// total distance covered by t2 till t2=t1: 10 = b+c+a+1


NodeL* findIntersectionLL(NodeL* head1, NodeL* head2){
    NodeL* t1 = head1;
    NodeL* t2 = head2;

    while(t1 != t2){
        t1 = (t1 == nullptr)?head2:t1->next;
        t2 = (t2 == nullptr)?head1:t2->next;
    }
    return t1;
}
//TC - O(a+b+c+1), SC - O(1)

NodeL* findIntersecOptHis(NodeL* head1, NodeL* head2){
    NodeL* t1 = head1;
    NodeL* t2=head2;

    while(t1 != t2){
        t1 = t1->next;
        t2 = t2->next;
        if(t1 == t2) return t1;
        
        if(t1 == nullptr) t1 = head2;
        if(t2 == nullptr) t2 = head1;
    }
    return t1;
}
//TC - O(n+m), SC - o(1)

//----------------------------------------------------------------------------------------------------------------------------------

//Find the middle element in LL
// Ex:
// 1->2->3->4->5
// res = 3
// 1->2->3->4->5->6
// res = 3+4/2 = 3.5

//Tortoise Hair algo 
// keep slow and fast pointer
// slow = head->next, fast = head->next->next or slo and fst can start with head too!
// Each iteration move slo by 1 step and fst by 2 steps 
// For even len - fst at last goes to null ptr or fst->next->next == nullptr before moving to NULL
// For odd len - fst at last goes to last node so fst->next = nullptr

double findMiddle(NodeL* head){
    if(!head) return -1;
    NodeL* slo = head;
    NodeL* fst = head;

    if(slo == nullptr){
        return head->data;
    }
    else if(fst == nullptr){
        int x = head->data;
        int y = slo->data;
        return ((double)x + y)/2;
    }

    while(slo && fst){
        if(fst->next == nullptr){
            return slo->data;
        }
        else if(fst->next->next == nullptr){
            int x = slo->data;
            int y = slo->next->data;

            return ((double)x + y)/2;
        }
        slo = slo->next;
        fst = fst->next->next;
    }
    return 0;
}
//TC - O(n/2), SC - O(1)

//Brut: FInd len and then find middle element 
// Actually in ques they didnt ask to find median but middle element, for odd - only 1 middle element but for even take second middle element 
// So take len+1/2 traverse upto that starting from head thats all

int middleElemLL(NodeL* head){
    int n=0;
    NodeL* temp = head;
    while(temp){
        n++;
        temp = temp->next;
    }
    int m = (n+1)/2;
    temp = head;
    while(m>0){
        temp = temp->next;
        m--;
    }
    return temp->data;
}
//TC - O(n + n/2), SC - O(1)

int middleElemOptHis(NodeL* head){
    if(!head) return -1;

    NodeL* slo = head, *fst = head;
    while(fst != nullptr && fst->next != nullptr){ //fst = nullptr then evenLen, fst->next = nullptr then odd len
        slo = slo->next;
        fst = fst->next->next;
    }
    return slo->data;
}
//TC - O(n/2), C - O(1)
//intuition consider 2 cars carA moves with speed 2x and carB moves with speed x then when carA reaches destination then carB will be at half the distance of that path if both move same straight path

//------------------------------------------------------------------------------------------------------------------------------

//Awaited: Detecting cycle/loop in a LL
// Given head of LL retrurn bool i.e tre if LL has loop

// When LL has loop: When there is minimum of 1 node from which if start traversing then its guarantee to meet same node again
// Ex:
/*
    head
      |
      v
      1 ----> 2 ----> 3 ----> 4 ----> 5 --------
                       ^                       |
                       |                       v
                       9 <---- 8 <---- 7 <---- 6
*/

//Brut : use hashing
bool findCycles(NodeL* head){
    if(!head) return false;

    map<NodeL*, int> hash;
    NodeL* temp = head;
    while(temp){
        if(hash.find(temp) != hash.end()){
            return true;
        }
        hash[temp] = 1;
        temp = temp->next;
    }
    return false;
}
//TC - O(nlogn), SC - O(n)

//Optimal: Using Tortoise & Hare algo:
bool findCycleOpt(NodeL* head){
    if(!head) return false;
    NodeL* slo = head, *fst = head;
    while(!fst && !fst->next){
        slo = slo->next;
        fst = fst->next->next;
        if(slo == fst) return true;
    }
    return false;
}
//TC - O(n), SC - o(1)
//TC - do depends on no of nodes on loop 

// Why Tortoise Hare:
// As slo and fst goes to loop the distance between them go on reducing cuz consider a circle if slo completed 1 lap then fst completes 2 laps and at this point they meet since speed of fst is twice of slo

// For x:
/*
    head
      |
      v
      1 ----> 2 ----> 3 ----> 4 ----> 5 --------
                       ^                       |
                       |                       v
                       9 <---- 8 <---- 7 <---- 6
*/
// slo = 1, fst = 1
// -> fst != null & fst->next->next != null
//         slo = 2
//         fst = 3
//         distance-between: 1(count edges)
// -> fst != null & fst->next->next != null
//         slo = 3
//         fst = 5
//         dis: 2 {entered the loop}
// -> fst != null & fst->next != null
//         slo = 4
//         fst = 7
//         dis: 3
// -> fst != null & fst->next->next != null
//         slo = 5
//         fst = 9
//         dis: 4
// -> fst != null & fst->next->next != null
//         slo = 6
//         fst = 4
//         dis: 5
// -> fst != null & fst->next->next != null
//         slo = 7
//         fst = 6
//         dis: 6
// -> fst != null & fst->next->next != null
//         slo = 8
//         fst = 8
//         dis: 0
//Here calculated distance between slo and fst but if u calculate dis bet fst and slo it will decrease as move further in iteration

//--------------------------------------------------------------------------------------------------------------------------------

//Find len of loop in LL

// If LL has a loop then return no of nodes in loop otherwise retun 0
// Ex:
/*
    head
      |
      v
      1 ----> 2 ----> 3 ----> 4 ----> 5 --------
                       ^                       |
                       |                       v
                       9 <---- 8 <---- 7 <---- 6
*/

//Using hashing
int LengthLoopLL(NodeL* head){
    if(!head || !head->next) return 0;

    NodeL* temp = head;
    map<NodeL*, int> hash;
    int cnt=0;

    while(temp){
        cnt++;
        if(hash.find(temp) != hash.end()){
            return (cnt - hash[temp]);
        }
        hash[temp] = cnt;
        temp = temp->next;
    }
    return 0;
}
//TC - o(nlogn), SC - O(n)

//Using TortoiseHare
//We use same thing yet a addition we do say once slo=fst we will move fst 1 step at a time by keeping a count until again fst=slo
int LenLoopLL(NodeL* head){
    if(!head || !head->next) return 0;

    NodeL* slo=head, *fst=head;
    while(fst && fst->next){
        slo = slo->next;
        fst = fst->next->next;
        if(slo == fst){
            int cnt=1;
            fst=fst->next;
            while(fst != slo){
                cnt++;
                fst = fst->next;
            }
            return cnt;
        }
    }
    return 0;
}
//TC - O(n), SC - O(1)

//--------------------------------------------------------------------------------------------------------------------------------

// Find the middle elem of LL
// Ex:
// 1->2->3->4->5
// res = 1->2->4->5

//Brut
// We have to reach the node before middle inorder to delet, find (len/2), traverse len/2-1 starting from head

NodeL* middleDelete(NodeL* head){
    if(!head || !head->next) return nullptr;
    int len = 0;
    NodeL* temp = head;
    while(temp){
        len++;
        temp = temp->next;
    }
    int mid = len/2 - 1;
    temp = head;
    while(mid>0){
        temp = temp->next;
        mid--;
    }
    NodeL* delNode = temp->next;
    temp->next = temp->next->next;
    delete delNode;
    return head;
}
//TC - O(n + n/2), SC - O(1)

// Use tortoise hare algo inorder to delete we need a ptr back of slo i.e middle elem
NodeL* deleteMiddleElem(NodeL* head){
    if(!head || !head->next) return nullptr;
    NodeL* slo = head->next, *fst = head->next->next, *prev = head;
    while(fst && fst->next){
        prev = slo;
        slo = slo->next;
        fst = fst->next->next;
    }
    prev->next = slo->next;
    delete slo;
    return head;
}
//TC - O(n/2), SC - O(1)

//Inorder to make the slo itself pointing to the node before middle will skip the first movement of slo, skipping 1 movement of slo guarantee it to be node before middle when fst reaches null incase of even or last node incase of odd
NodeL* deleteMiddleOptHis(NodeL* head){
    if(!head || !head->next) return nullptr;
    NodeL* slo = head, *fst = head;
    fst = fst->next->next;
    while(fst && fst->next){
        slo = slo->next;
        fst = fst->next->next;
    }
    NodeL* temp = slo->next;
    slo->next = slo->next->next;
    delete temp;
    return head;
}
//TC - O(n/2),SC - O(1)

//--------------------------------------------------------------------------------------------------------------------------------
// Finding starting node in a loop of a LL
// Given LL may have loop or not if has return loops starting node otherwise return nullptr
// Ex:
/*
      head
        |
        v
        1 ----> 2 ----> 3 ----> 15 ----> 4 ----> 13 -----
                                ^                       |
                                |                       v
                                9 <---- 8 <---- 7 <---- 6
*/
//Brut: hashing 
int startNodeL(NodeL* head){
    if(!head || !head->next) return 0;

    map<NodeL*, int> hash;
    NodeL* temp = head;
    while(temp){
        if(hash.find(temp) != hash.end()){
            return temp->data;
        }
        hash[temp]=1;
        temp = temp->next;
    }
    return 0;
}
//TC - o(n*2*logn), SC - o(n)

//Using tortoise hare: 
// When slo and fst meet it means loop exist after that make one of them to start from head and increment both 1 step until they meet, the meeting node is starting node
NodeL* firstNodeLoopOpt(NodeL* head){
    if(!head || !head->next) return nullptr;
    NodeL* slo=head, *fst = head;
    while(fst && fst->next){
        slo = slo->next;
        fst = fst->next->next;
        if(slo == fst){
            slo=head;
            while(slo != fst){
                slo = slo->next;
                fst = fst->next;
            }
            return slo;
        }
    }
    return nullptr;
}
//TC - O(n), SC - o(1)

// Why its correct?
/*
      head
        |
        v
        1 ----> 2 ----> 3 ----> 15 ----> 4 ----> 13 -----
                                ^                       |
                                |                       v
                                9 <---- 8 <---- 7 <---- 6
*/
// Here consider slo is at 15 i.e it has moved 3 steps = L1
// - If slo has moved 3 steps then fst will have moved 2*3=6 steps, So fst is at node 6

// -The distance between fst and sloo has of now (when slo-15, fst-6) is d(4)
// - Each time fst moves towards slo in 2 steps so distance should decrement between fst and slo by 2 i.e d-2, But as slo moves 1 step ahead each time fst moves 2 steps So distance between fst and slo should decrement by 1 step i.e (d-1)
// - So for each iteration the d decrements by 1 Say when fst=6, slo=15, d=4, when fst=8, slo=4, d=3(4-1)
// - So d eventually becomes 0 when fst=7, slo=7

// // [image-comments/image-20261102-044426-zzezrr.png]
// So the loop len = l1+d

// Here inorder to reach the collision point slo would have taken d steps and fst would have taken 2d steps from when fst=6, slo=15
// So the distance between collided point and node15(start node) is len of loop - d = l1+d-d = l1 
// And So the distance from collided point to startnode (7-15) is same as  distance from head to start node(1-15)

//------------------------------------------------------------------------------------------------------------------------------
//Delete all the occurences of a key in doubly Linked List

// Ex; Given head of head of DLL and a key(node data), u need to return head after deleting all keys occurences
           
//        → ┌────┐ →   → ┌────┐ →   → ┌────┐ →   → ┌────┐ →   → ┌────┐ →   → ┌────┐ →
//  X <── ← │ 10 │ ← ─ ← │  4 │ ← ─ ← │ 10 │ ← ─ ← │ 10 │ ← ─ ← │  6 │ ← ─ ← │ 10 │ ← ──> X
//          └────┘       └────┘       └────┘       └────┘       └────┘       └────┘
//           head
// Res:
//        → ┌────┐ →   → ┌────┐ →
//  X <── ← │  4 │ ← ─ ← │  6 │ ← ──> X
//          └────┘       └────┘
//           head


NodeD* deleteAllOcc(NodeD* head, int key){
    NodeD* temp = head;
    bool flag=true;
    while(temp){
        if(temp->data == key){
            NodeD* nx = temp->next;
            if(temp->prev)
                temp->prev->next = temp->next;
            if(temp->next)    
                temp->next->prev = temp->prev;

            NodeD* deNode = temp;
            temp = nx;
            delete deNode;
        }
        else{
            if(flag){
                head = temp;
                flag = false;
            }
            temp = temp->next;
        }
    }
    return head;
}
//TC - o(n), SC - o(1)

//------------------------------------------------------------------------------------------------------------------------------

//Find pairs with given sum in a sorted DLL
// Ex:
//        → ┌────┐ →   → ┌────┐ →   → ┌────┐ →   → ┌────┐ →   → ┌────┐ →
//  X <── ← │  1 │ ← ─ ← │  2 │ ← ─ ← │  3 │ ← ─ ← │  4 │ ← ─ ← │  9 │ ← ──> X
//          └────┘       └────┘       └────┘       └────┘       └────┘
//           head
// Sum =5
// res = {(1,4), (2,3)} return all the pairs

auto twoSumLL(NodeD* head, int target){
    unordered_map<int, int> hash;
    vector<pair<int, int>> res;
    NodeD* temp = head;
    while(temp){
        int sum = target - temp->data;
        if(hash.find(sum) != hash.end()){
            res.push_back({sum, temp->data});
        }
        hash[temp->data] = 1;
        temp = temp->next;
    }
    return res;
}
//TC - O(n), SC - o(n)

//Using 2 pointers
auto twoSumLLOpt(NodeD* head, int target){
    if(!head) return vector<pair<int, int>>{};
    NodeD* i=head, *j=head;
    vector<pair<int, int>> res;
    while(j->next){
        j = j->next;
    }
    while(i != j->next){  //or i->data < j->data as dll is sorted
        int x=i->data, y=j->data;
        if(x+y == target){
            res.push_back({x,y});
            i=i->next;
            j=j->prev;
        }
        else if((x+y)<target){
            i=i->next;
        }
        else{
            j=j->prev;
        }
    }
    return res;
}
//TC - O(2*n), SC - O(1)

//------------------------------------------------------------------------------------------------------------------------------

// Remove duplicates from sorted DLL
// Ex: 
//        → ┌────┐ →   → ┌────┐ →   → ┌────┐ →   → ┌────┐ →   → ┌────┐ →   → ┌────┐ →   → ┌────┐ →
//  X <── ← │  1 │ ← ─ ← │  1 │ ← ─ ← │  1 │ ← ─ ← │  2 │ ← ─ ← │  3 │ ← ─ ← │  3 │ ← ─ ← │  4 │ ← ──> X
//          └────┘       └────┘       └────┘       └────┘       └────┘       └────┘       └────┘
//           head

NodeD* removeDup(NodeD* head){
    if(!head) return head;
    NodeD* i=head, *j=head->next;
    while(i && j){
        if(i->data == j->data){
            NodeD* delNode = j;
            i->next = j->next;
            j->next->prev = i;

            j = i->next;
            delete delNode;
        }
        else{
            i = i->next;
            j=j->next;
        }
    }
    return head;
}
//TC - O(n), SC - o(1)

//His approach go to a node which has val different then current node and make cur next point to newNode and newNodes prev point to current
NodeD* removeDupHis(NodeD* head){
    if(!head) return head;
    NodeD* temp = head;
    while(temp){
        NodeD* newNode = temp->next;
        while(newNode && newNode->data == temp->data){
            NodeD* delNode = newNode;
            newNode = newNode->next;
            delete delNode;
        }
        temp->next = newNode;
        if(newNode) newNode->prev = temp;
        temp = temp->next;
    }
    return head;
}
//TC - O(n), SC - O(1)

//------------------------------------------------------------------------------------------------------------------------------

// Reverse nodes in K-Group
// Given head of LL u need to return head by reversing every kth no of nodes starting from head
// Ex: 1->2->3->4->5->6->7->8->9->10, k=3
// res: 3->2->1->6->5->4->9->8->7->10

NodeL* reverseLLK(NodeL* head, NodeL* start, NodeL* stop){
    NodeL* cur = start->next;
    NodeL* endWall = stop->next;
    NodeL* prev = endWall;

    while(cur != endWall){
        NodeL* nextcur = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nextcur;
    }

    start->next = prev;
    return head;
}

NodeL* reverseK(NodeL* head, int k){
    NodeL* start, *dummyNode = new NodeL(-1);
    dummyNode->next = head;
    start = dummyNode;
    while(start){
        int cnt=k-1;
        NodeL* stop = start->next;
        NodeL* endWall = start->next;
        while(stop && cnt>0){
            stop = stop->next;
            cnt--;
        }
        
        if(cnt == 0 && stop)
            head = reverseLLK(head, start, stop);
        start = endWall;
    }
    return dummyNode->next;
}
// Tc - o(2*n), SC - O(1)

//Above is optimal at same time complicated but still feasible
//His approach:
// Use prevNode pointing to start of ur previous, use nextNode to point as of stop->next, use temp to traverse , use recursive Reverse LL by providing it prevNode->next as head and after making temp->next = nullptr where temp points as of stop
// Dry run:
// Consider: 1->2->3->4->5->6->7->8->9->10, k=3
// temp = head, prevnode = null, nextnode = null, kNode = null

// ->temp != null
//     kNode = 3 (temp+k)
//     if(kNode == null){
//         break;
//     }
//     nextNode = kNode->next = 4
//     kNode->next = null
//     reverse: 3->2->1 (temp still points 1)
//     if(kNode == head)
//         head = kNode
//     else 
//         prevNode->next = kNode
//     prevNode = temp = 1
//     if(nextNode) 
//         temp->next = nextNode = 4
//     temp = nextNode

//     LL: 3->2->1->4->5->6->7->8->9->10
// ->temp !=null
//     kNode = 6
//     nextNode = 7
//     kNode->next = null
//     reverse: 6->5->4 (reverse(temp))
//     kNode != head
//         prevNode->next = kNode 
//     preNode = 4
//     temp->next = nextNode = 7
//     temp = nextNode = 7

//     LL: 3->2->1->6->5->4->7->8->9->10
// ->temp != null
//     kNode = 9
//     nextNode = 10
//     kNode->next = null
//     reverse: 9->8->7->null
//     kNode != head
//         prevNode->next = kNode = 9
//     prevNode = 7
//     if(nextNode) temp->next = nextNode = 10
//     temp = 10

//     LL:3->2->1->6->5->4->9->8->7->10
// -> temp != null
//     kNode = null
//     if(kNode == null){
//         break;
//     }
    
//     LL:3->2->1->6->5->4->9->8->7->10


NodeL* reverseOptRecLL(NodeL* head){
    if(head->next == nullptr){
        return head;
    }
    NodeL* newHead = reverseOptRecLL(head->next);
    NodeL* front = head->next;
    front->next = head;
    head->next = nullptr;

    return newHead;
} 

NodeL* findKNode(NodeL* head, int k){
    NodeL* temp = head;
    k--;

    while(temp && k>0){
        temp = temp->next;
        k--;
    }
    return temp;
}

NodeL* reverseKGrpsHisOpt(NodeL* head, int k){
    if(!head) return head;

    NodeL* nextNode=nullptr, *prevNode = nullptr, *temp = head, *kNode = nullptr;
    while(temp){
        // cout<<temp->data<<endl;
        kNode = findKNode(temp, k);
        if(kNode == nullptr) break;
        nextNode = kNode->next;
        kNode->next = nullptr;

        reverseOptRecLL(temp);
        if(temp == head){
            head = kNode;
        }
        else{
            prevNode->next = kNode;
        }
        prevNode = temp;
        if(nextNode) temp->next = nextNode;
        temp = nextNode;
    }
    return head;
}
//TC - O(2*n), SC - O(1)

//--------------------------------------------------------------------------------------------------------------------------------
//Rotate a LL by k times
// Ex:
// 1->2->3->4->5, k=2
// k=1: 5->1->2->3->4
// k=2: 4->5->1->2->3

NodeL* rotateLLK(NodeL* head, int k){
    if(!head) return head;
    NodeL* tail = head;
    int len = 1;
    while(tail->next){
        tail=tail->next;
        len++;
    }
    int brk = len - (k % len);

    NodeL* brkPoint = head, *prevBrk=head;
    while(brk){
        prevBrk = brkPoint;
        brkPoint = brkPoint->next;
        brk--;
    }

    if(brkPoint && brkPoint != head){
        tail->next = head;
        head = brkPoint;
        prevBrk->next = nullptr;
    }

    return head;
}
//TC - O(n + (n-k%n)), SC - O(1)

//------------------------------------------------------------------------------------------------------------------------------
//Merge 2 sorted LL
//Ex:
// 2->4->8->10->x
// 1->3->3->6->11->14->x

// Res: 1->2->3->3->4->6->8->10->11->14

NodeL* merge2SortedLL(NodeL* head1, NodeL* head2){
    if(head1 && !head2) return head1;
    else if(head2 && !head1) return head2;
    else if(!head1 && !head2) return head1;

    NodeL *t1 = head1, *t2= head2;
    NodeL* newHead=nullptr, *prevNode = nullptr, *temp = nullptr;
    while(t1 && t2){
        if(t1->data < t2->data){
            temp = new NodeL(t1->data);
            t1 = t1->next;
        }
        else{
            temp = new NodeL(t2->data);
            t2 = t2->next;
        }

        if(!newHead){
                newHead = temp;
        }
        else{
            prevNode->next = temp;
        }
        prevNode = temp;
        temp->next = nullptr;
    }
    while(t1){
        temp = new NodeL(t1->data);
        if(!newHead){
                newHead = temp;
        }
        else{
            prevNode->next = temp;
        }
        prevNode = temp;
        temp->next = nullptr;
        t1 = t1->next;
    }
    while(t2){
        temp = new NodeL(t2->data);
        if(!newHead){
                newHead = temp;
        }
        else{
            prevNode->next = temp;
        }
        prevNode = temp;
        temp->next = nullptr;
        t2 = t2->next;
    }
    return newHead;
}
//Tc - o(n+m), SC - O(n+m)

// Without using extra space

NodeL* merge2SortedLLOpt(NodeL* head1, NodeL* head2){
    if(!head1 && !head2) return head1;

    NodeL* t1 = head1, *t2 = head2;
    NodeL* dummyNode = new NodeL(-1);
    NodeL* temp = dummyNode;
    while(t1 && t2){
        if(t1->data < t2->data){
            temp->next = t1;
            temp = t1;
            t1 = t1->next;
        }
        else{
            temp->next = t2;
            temp = t2;
            t2 = t2->next;
        }
    }
    while(t1){
        temp->next = t1;
    }
    while(t2){
        temp->next = t2;
    }

    return dummyNode->next;
}
//TC - O(n+m), SC - o(n)

//------------------------------------------------------------------------------------------------------------------------------

// Flatten a LL
// Here each node can have further child nodes which can be LL on their own
//Note: every child LL will be sorted
//Return by converting it into 1 child sorted LL 
/*
  head
 ┌────┐     ┌────┐     ┌────┐     ┌────┐     ┌────┐
 │  3 │ ──> │  2 │ ──> │  1 │ ──> │  4 │ ──> │  5 │ ──> X
 └────┘     └────┘     └────┘     └────┘     └────┘
   │          │          │          │          │
   ▼          ▼          ▼          ▼          ▼
   X        ┌────┐     ┌────┐     ┌────┐     ┌────┐
            │ 10 │     │  7 │     │  9 │     │  6 │
            └────┘     └────┘     └────┘     └────┘
              │          │          │          │
              ▼          ▼          ▼          ▼
              X        ┌────┐       X        ┌────┐
                       │ 11 │                │  8 │
                       └────┘                └────┘
                         │                     │
                         ▼                     ▼
                       ┌────┐                  X
                       │ 12 │
                       └────┘
                         │
                         ▼
                         X
*/

// Res:
/*
  head
 ┌────┐ ──> X
 │  1 │
 └────┘
   │
   ▼
 ┌────┐ ──> X
 │  2 │
 └────┘
   │
   ▼
 ┌────┐ ──> X
 │  3 │
 └────┘
   │
   ▼
 ┌────┐ ──> X
 │  4 │
 └────┘
   │
   ▼
 ┌────┐ ──> X
 │  5 │
 └────┘
   │
   ▼
 ┌────┐ ──> X
 │  6 │
 └────┘
   │
   ▼
 ┌────┐ ──> X
 │  7 │
 └────┘
   │
   ▼
 ┌────┐ ──> X
 │  8 │
 └────┘
   │
   ▼
 ┌────┐ ──> X
 │  9 │
 └────┘
   │
   ▼
 ┌────┐ ──> X
 │ 10 │
 └────┘
   │
   ▼
 ┌────┐ ──> X
 │ 11 │
 └────┘
   │
   ▼
 ┌────┐ ──> X
 │ 12 │
 └────┘
   │
   ▼
   X
*/

class NodeF{
    public:
    int data;
    NodeF* next;
    NodeF* child;

    NodeF(int data1, NodeF* next1, NodeF* child1){
        data = data1;
        next = next1;
        child = child1;
    }

    NodeF(int data1){
        data = data1;
        next = nullptr;
        child = nullptr;
    }
};

NodeF* convertArrF(vector<int>& arr){
    if(arr.size()==0) return nullptr;

    NodeF* head = new NodeF(arr[0]);
    NodeF* mover = head;
    for(int i=1;i<arr.size();i++){
        NodeF* temp = new NodeF(arr[i]);
        mover->child = temp;
        mover = temp;
    }
    return head;
}

void printF(NodeF* head){
    if(!head) return;
    NodeF* temp = head;
    while(temp){
        NodeF* chlds = temp;
        while(chlds){
            cout<<chlds->data<<" ";
            chlds = chlds->child;
        }
        temp = temp->next;
        cout<<endl;
    }
}

NodeF* flattenLL(NodeF* head){
    if(!head) return head;

    vector<int> res;
    NodeF* temp = head;
    while(temp){
        NodeF* chlds = temp;
        while(chlds){
            res.push_back(chlds->data);
            chlds = chlds->child;
        }
        temp = temp->next;
    }

    sort(res.begin(), res.end());
    return convertArrF(res);
}
//TC - O(n*m + (n*m)log(n*m) + n*m){n-no of nodes, m - no of child for each node}, SC - O(2*(n*m))
//Here we did not make use of sorted order of child nodes

//Optimal: it uses the fact of sorted order of child and makes in place link changes and not creates a new LL for output

NodeF* mergeF(NodeF* head1, NodeF* head2){
    NodeF* t1 = head1;
    NodeF* t2 = head2;

    NodeF* dummyNode = new NodeF(-1);
    NodeF* temp = dummyNode;
    while(t1 && t2){
        if(t1->data < t2->data){
            temp->child = t1;
            temp = t1;
            t1 = t1->child;
        }
        else{
            temp->child = t2;
            temp = t2;
            t2 = t2->child;
        }
        temp->next = nullptr;
    }
    if(t1){
        temp->child = t1;
    }
    else if(t2){
        temp->child = t2;
    }
    return dummyNode->child;
}

NodeF* flattenLLOpt(NodeF* head){
    if(!head || !head->next){
        return head;
    }
    NodeF* newHead = flattenLLOpt(head->next);
    return mergeF(head, newHead);
}
//TC - O(n * 2*m), SC - o(1)

//---------------------------------------------------------------------------------------------------------------------------------------------------

//Merge K sorted List:
// Ex:
// 1->4->6->x
// 1->5->x
// 1->1->3->7->x
// 8->x
// res: 1->1->1->3->4->5->6->7->8->x


//Brut: Store all k LLs data in a arr and then sort it and convert to LL and return 
NodeL* mergeKLL(vector<NodeL*>& arr){
    if(arr.size() == 0) return nullptr;
    vector<int> res;

    for(int i=0;i<arr.size();i++){
        NodeL* temp = arr[i];
        while(temp){
            res.push_back(temp->data);
            temp = temp->next;
        }
    }

    sort(res.begin(), res.end());
    return ConvertArr(res);
}
//TC - O(k*n + k*nlog(k*n) + k*n) {where k is no of list to merge and n-no of elems in each LL considered to be same accross all}, SC - O(2*k*n)

//Better: Pass each of 2 LL to merge using 2 pointers

NodeL* merge(NodeL* head1, NodeL* head2){
    if(!head1 && !head2) return head1;

    NodeL* t1=head1, *t2=head2;
    NodeL* dummyNode = new NodeL(-1);
    NodeL* temp = dummyNode;
    while(t1 && t2){
        if(t1->data < t2->data){
            temp->next = t1;
            temp = t1;
            t1 = t1->next;
        }
        else{
            temp->next = t2;
            temp = t2;
            t2 = t2->next;
        }
    }
    if(t1){
        temp->next = t1;
    }
    else if(t2){
        temp->next = t2;
    }
    NodeL* head = dummyNode->next;
    delete dummyNode;
    return head;
}

NodeL* mergeKLLBet(vector<NodeL*>& arr){
    if(arr.size()==0) return nullptr;

    NodeL* l1 = arr[0];
    for(int i=1;i<arr.size();i++){
        NodeL* temp = merge(l1, arr[i]);
        l1 = temp;
    }
    return l1;
}
//TC - 
// Consider 4 LL with sizes as follows:
// l1 - n1
// l2 - n2
// l3 - n3
// l4 - n4

// For i=1, TC - O(n1+n2)
//     i=2, TC - O(n1+n2+n3)
//     i=3, TC - O(n1+n2+n3+n4)
// Total - O((n1+n2) + (n1+n2+n3) + (n1+n2+n3+n4))
// considering n1=n2=n3=n4
// Total - O(2*n + 3*n + 4*n) - O(2*n + 3*n + ... + k*n)
//                            - O(n * (2 + 3 + ... + k))
//                            - O(n * (k*(k+1)/2)) ~ O(n^3) if (k=n)
// SC - O(1)

//Opt: Using Priority queue, using concept of minHeap
// Start pushing only value heads of all k LL to pq along with their Node
// Each time pop the pq and attach it to dummyNode and then push the poped Nodes next Node to pq 
// Repeat above until pq is empty

NodeL* mergeKLLOpt(vector<NodeL*> arr){
    if(arr.size()==0) return nullptr;

    priority_queue<pair<int, NodeL*>, vector<pair<int, NodeL*>>, greater<pair<int, NodeL*>>> pq;
    for(int i=0;i<arr.size();i++){
        pq.push({arr[i]->data, arr[i]});
    }
    
    NodeL* dummyNode = new NodeL(-1);
    NodeL* temp = dummyNode;
    while(!pq.empty()){
        auto tp = pq.top();
        pq.pop();
        temp->next = tp.second;
        temp = temp->next;
        if(tp.second->next) pq.push({tp.second->next->data, tp.second->next});
    }
    NodeL* head = dummyNode->next;
    delete dummyNode;
    return head;
}
//TC - O(klogk + k*n*3*logk), SC - O(k)

//-------------------------------------------------------------------------------------------------------------------------

//Sort a LL
// Brut: Put it to arr, sort and put data back

NodeL* SortLL(NodeL* head){
    if(!head && !head->next) return head;
    vector<int> res;
    NodeL* temp=head;

    while(temp){
        res.push_back(temp->data);
        temp = temp->next;
    }

    temp = head;
    for(int i=0;i<res.size();i++){
        temp->data = res[i];
        temp = temp->next;
    }
    return head;
}
//TC - O(n + n), SC - O(n)

//Opt: Using merge sort: Find middle elem using Tortoise Hare and for each half recurse until left with 1 elem and then merge left and right LL using merge function(uses 2 pointers)
//Note: Finding the misddle is slightly differs: why? As if LL even len: then get the first middle not second , if odd then only 1 middle no issue:
// To make it return 1st middle if LL is even: Consider: 
// 1 2 3 4 
// initially: slo->1, fst->1
// Loop until fst->next = nullptr (if odd) or fst = nullptr(if even)
// -> slo->2, fst->3
// -> slo->3, fst->null : But slo is 2nd middle not 1st

// Change:
// Initially
// slo->1, fst->2
// -> slo->2, fst->4
// ->fst->next = null So: middle = slo = 3 (1st middle)

// Now merge:
// - [3 4 2 1 5]
// - [3 4]     [2 1 5]
// - [3] [4]   [2 1]   [5]
//             [2] [1]

NodeL* MiddleLLTH(NodeL* head){
    if(!head || !head->next) return head;

    NodeL* slo=head, *fst=head->next;

    while(!fst->next && !fst){
        fst = fst->next->next;
        slo = slo->next;
    }
    return slo;
}

NodeL* SortLLOpt(NodeL* head){
    if(!head || !head->next) return head;

    NodeL* middle = MiddleLLTH(head);
    NodeL* left = head, *right = middle->next;
    middle->next = nullptr; 
    left = SortLLOpt(left);
    right = SortLLOpt(right);

    return merge(left, right);
}
//TC - O((n+(n/2)) * logn), SC - O(logn) {for recursive stack space}

//--------------------------------------------------------------------------------------------------------------------------

//Cloning a LL with next and random pointers

// Consider a LL with next ptr: pointing to next elem and random ptr: pointing to random nodes of the LL

//  ┌───┬───┐       ┌────┬───┐       ┌────┬───┐       ┌────┬───┐       ┌────┬───┐
//  │ 7 │ ──┼─────> │ 13 │ ──┼─────> │ 11 │ ──┼─────> │ 10 │ ──┼─────> │  1 │ ──┼───> X
//  └───┴───┘       └────┴───┘       └────┴───┘       └────┴───┘       └────┴───┘
//    │               │               │               │               │
//    │ [random]      │ [random]      │ [random]      │ [random]      │ [random]
//    ▼               ▼               ▼               ▼               ▼
//    X               Node(7)         Node(1)         Node(11)        Node(7)

// [image-comments/image-20261106-132152-hcc204.png]

// U just need to create another LL with exactly same random ptrs and next ptrs 
// The problem is: U cannot do it in 1 pass: cuz if a node's random ptr can point to a further away node in LL So u cannnot point random ptr to a node thats not created yet while traversing sequentially

// So need to store the details of node in input LL and created node beforehand connecting random and next ptr sequentially, So use hash Map

class NodeR{
    public:
    int data;
    NodeR* next;
    NodeR* random;

    NodeR(int data1){
        data = data1;
        next = nullptr;
        random = nullptr;
    }

    NodeR(int data1, NodeR* next1, NodeR* rand1){
        data = data1;
        next = next1;
        random = rand1;
    }
};

NodeR* convertArrR(vector<int>& arr){
    if(arr.size() == 0) return nullptr;

    NodeR* head = new NodeR(arr[0]);
    NodeR* temp = head;
    for(int i=1;i<arr.size();i++){
        NodeR* newNode = new NodeR(arr[i]);
        temp->next = newNode;
        temp = newNode;
    }   
    temp = head;
    map<int, NodeR*> mpp;
    while(temp){
        mpp[temp->data] = temp;
        temp = temp->next;
    }
    temp = head->next;
    temp->random = mpp[7];

    temp = mpp[11];
    temp->random = mpp[1];

    temp = mpp[10];
    temp->random = mpp[11];

    temp = mpp[1];
    temp->random = mpp[7];

    return head;
}

void printR(NodeR* head){
    NodeR* temp = head;
    while(temp){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    temp = head;
    cout<<endl;
    while(temp){
        if(temp->random) cout<<temp->data<<" random points to: "<<temp->random->data<<endl;
        else cout<<temp->data<<" random points to: nullptr"<<endl;
        temp = temp->next;
    }
    cout<<"======================================="<<endl;
}


NodeR* copyRand(NodeR* head){
    if(!head || !head->next) return head;

    unordered_map<NodeR*, NodeR*> hash;
    NodeR* temp = head;
    while(temp){
        NodeR* newNode = new NodeR(temp->data);
        hash[temp] = newNode;
        temp = temp->next;
    }
    temp = head;
    NodeR* newHead = hash[head];
    NodeR* mover = newHead;
    while(temp){
        mover->next = hash[temp->next];
        mover->random = hash[temp->random];
        temp = temp->next;
        mover = mover->next;
    }
    return newHead;
}
//TC - O(2*n*1 {worst - O(n^2)}), SC - O(n) + O(n)

//Optimal: Without using hash map
NodeR* copyRandOpt(NodeR* head){
    if(!head) return head;

    NodeR* temp = head;
    while(temp){
        NodeR* newNode = new NodeR(temp->data);
        newNode->next = temp->next;
        temp->next = newNode;

        temp = newNode->next;
    }
    temp = head;
    while(temp){
        if(temp->random) 
            temp->next->random = temp->random->next;
        else 
            temp->next->random = nullptr;

        temp = temp->next->next;
    }

    NodeR* newHead = head->next;
    NodeR* mover = head;
    while(mover){
        NodeR *clone = mover->next;

        mover->next = clone->next;

        if(clone->next) 
            clone->next = clone->next->next;

        mover = mover->next;
    }
    return newHead;
}
//TC - O(3*n), SC - O(n)

//-----------------------------------------------------------------------------------------------------------------------------

//Design Browser History:
// with visit, back(n), forward(n)

//Use DLL
class Browser{
    public:
    NodeD* current;

    Browser(){
        NodeD* newNode = new NodeD(0);
        current = newNode;
    }

    void visit(int n){
        NodeD* newNode = new NodeD(n);
        current->next = newNode;
        current = newNode;
    }

    int back(int t){
        while(current->prev && t){
            current = current->prev;
            t--;
        }
        return current->data;
    }

    int forward(int t){
        while(current->next && t){
            current = current->next;
            t--;
        }
        return current->data;
    }
};

//----------------------------------------------------------------------------------------------------------------

int main(){
    // vector<int> arr1 = {2,4,6};
    // vector<int> arr2 = {3,8,7};

    // NodeL* l1 = ConvertArr(arr1);
    // NodeL* l2 = ConvertArr(arr2);

    // print(l1);
    // print(l2);

    // NodeL* sumHead = add2NosBetC(l1, l2);
    // print(sumHead);

    //==================================================

    // vector<int> arr = {1,2,3,4,5};
    // NodeL* head = ConvertArr(arr);
    // print(head);
    // head = reverseRecOpt(head);
    // print(head);

    //==================================================

    // vector<int> arr = {9, 9, 9, 9};
    // NodeL* head =ConvertArr(arr);
    // // print(head);
    // int rem = 0;
    // head = add1LLRecHis(head);
    // print(head);

    //==================================================

    // vector<int> arr1 = {3,1,4,6,2};
    // NodeL* head1 = ConvertArr(arr1);
    
    // vector<int> arr2 = {1,2,4,5};
    // NodeL* head2 = ConvertArr(arr2);
    // NodeL* temp1 = head1;
    // while(temp1 != nullptr){
    //     if(temp1->data == 4) break;
    //     temp1 = temp1->next;
    // }

    // NodeL* temp2 = head2;
    // while(temp2->next){
    //     temp2=temp2->next;
    // }
    // temp2->next = temp1;

    // print(head1);
    // print(head2);

    // NodeL* res = findIntersecOptHis(head1, head2);
    // cout<<res->data;

    //==================================================

    // vector<int> arr = {1,2,3,4,5};
    // NodeL* head = ConvertArr(arr);
    // head = deleteMiddleOptHis(head);
    // print(head);

    //=================================================

    // vector<int> arr = {1,2,3,15,4,13,6,7,8,9};
    // NodeL* head = ConvertArr(arr);
    // NodeL* temp = head, *con;
    // while(temp->next != nullptr){
    //     if(temp->data == 15) con = temp;
    //     temp = temp->next;
    // }
    // temp->next = con;
    // cout<<firstNodeLoopOpt(head)->data;

    // ================================================

    // vector<int> arr1 = {2,4,8,10};
    // vector<int> arr2 = {1,3,3,6,11,14};
    // NodeL* head1 = ConvertArr(arr1);
    // NodeL* head2 = ConvertArr(arr2);

    // NodeL* head = merge2SortedLLOpt(head1, head2);
    // print(head);

    //================================================

    // vector<vector<int>> arr = {{2, 10}, {1,7,11,12}, {4,9}, {5,6,8}};
    // NodeF* head = new NodeF(3);
    // NodeF* mover = head;

    // for(int i=0;i<4;i++){
    //     NodeF* newNode = convertArrF(arr[i]);
    //     mover->next = newNode;
    //     mover = newNode;
    // }
    // printF(head);

    // head = flattenLLOpt(head);
    // cout<<endl;
    // printF(head);

    //===============================================

    // vector<vector<int>> arr = {{2,4,6}, {1,5}, {1,1,3,7}, {8}};
    // vector<NodeL*> Larr;
    // for(int i=0;i<arr.size();i++){
    //     Larr.push_back(ConvertArr(arr[i]));
    // }
    // NodeL* head = mergeKLLOpt(Larr);
    // print(head);

    vector<int> arr = {7, 13, 11, 10, 1};
    NodeR* head = convertArrR(arr);
    printR(head);

    head = copyRandOpt(head);
    printR(head);


    return 0;
}