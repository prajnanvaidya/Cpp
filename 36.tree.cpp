#include<bits/stdc++.h>

using namespace std;

//Trees
//Intro to Binary Trees:

//Trees: Hierarchial DS 
// For ex: folder structure in file system

//Binary tree: In a hierarchial DS if allowed to have max of 2 nodes then it is binary tree.
// Ex: // [image-comments/image-20261113-132140-kya4qk.png]

// Root: Starting node/top most node of a tree
// Children: Child nodes of a particular node
//Leaf node: node with no child nodes

//Subtree: In a tree if considered a particular node and all its descendents
//Ancestor: Track of parent nodes to root node of a particular node in a tree
//==============================================================================================================

// Types of Binary tree:

// 1. Full Binary Tree:
// Every node has either 2 or 0 child nodes
// Ex of Full binary tree: // [image-comments/image-20261113-132639-okowce.png]
// - Not a full binary tree: cuz 2nd child of root node has only 1 child // [image-comments/image-20261113-132718-frai7u.png]
// ex; Even it is a full binary tree as every node has either 2 or 0 child!
//        O
//       / \
//      O   O
//     / \ 
//    O  O 

// 2. Complete Binary Tree:
// All levels should be competely filled except the last level and last level has all nodes as left as possible
// i.e Even though any node has no 2 child nodes(may have 1 child or 0) then it should be in last level and all other nodes to right of it in last level should be leaf nodes  
// Ex: complete binary tree:
// 1.     O
//       / \
//      O   O
//     / \ / \
//    O  O O  O

// 2.     O
//       / \
//      O   O
//     / \ / 
//    O  O O  

// Not a complete binary tree:
//        O
//       / \
//      O   O
//     / \   \
//    O  O    O

// 3. Perfect Binary Tree:
// All leaf nodes should be at same level:
// Ex: 
//        O
//       / \
//      O   O
//     / \ / \
//    O  O O  O
// So difference between perfect and full binary tree:
//         perfect                     full
// 1.  Every node has 2 children,    Each node can have either 2 or 0 child
//     except leaf node    
// 2.  All leaves are at same        Not necessary all leaves are at same level
//     level
// 3.  Each level is completely      Not necessary each level is filled
//     filled
// 4.  2^(h+1)-1 no of nodes         No fixed formula for no of ndes
// 5.  2^h leaf nodes                No fixed formula

// h - height measured in terms of edges
 
// Note: Aperfect Binary tree is also a full binary tree but vice versa may not be true

// 4. Balanced Binary Tree
// Height should be at max log(N), where N is no of Nodes
// For ex: if N=8, then height can be at max of 3 not greater then that
//        O
//       / \
//      O   O
//     / \ / \
//    O  O O  O
//   /
//  O
// Incorrect:
//         O
//        / 
//       O   
//      / \ 
//     O   O
//    / \
//   O   O
//  / \
// O   O
// Will be discussed more during Binary Search Tree

// 5. Degenerate Tree
// Its a skew tree, where every node has a single children
// Its more likely to be a linkedList than a tree
// Ex:
//         O
//        / 
//       O   
//      /  
//     O   
//    / 
//   O   
//  / 
// O   

//====================================================================

// Representating Binary Tree in cpp:
// U can use struct or class and each node has value, its left and right child ptrs
// Ex:
// [image-comments/image-20261114-033902-sui000.png]

// Code: using struct
// struct Node{
//     public:
//     int data;
//     struct Node* left;
//     struct Node* right;

//     Node(int data){
//         this->data = data;
//         left = right = nullptr;
//     }

//     Node(int data, struct Node* left, struct Node* right){
//         this->data = data;
//         this->left = left;
//         this->right = right;
//     }
// }

//====================================================================================

// Traversal Techniques:
// Mainly we have: BFS, DFS 

// 1. DFS:
// There are 3 types of DFS:
// 1. Inorder Traversal = (left root right)
// 2. Preorder Traversal = (root left right)
// 3. Postorder Traversal = (left right root)

// Consider tree: Ex1:
//        1
//       / \
//      2   3
//     / \ / \
//    4  5 6  7
// 1. Inorder = (left root right) = 4, 2, 5, 1, 6, 3, 7
// 2. Postorder = (left right root) = 4, 5, 2, 6, 7, 3, 1
// 3. Preorder = (root left right) = 1, 2, 4, 5, 3, 6, 7

// Ex2:
//          1
//         / \
//        2   3
//       / \ / \
//      4  5 6  7
//        /    / \
//       8    9  10

// Inorder = 4, 2, 8, 5, 1, 6, 3, 9, 7, 10
// Preorder = 1, 2, 4, 5, 8, 3, 6, 7, 9, 10
// Postorder = 4, 8, 5, 2, 6, 9, 10, 7, 3, 1

// 2. BFS: It goes level wise:
// On ex2:
//          1       -- level0
//         / \ 
//        2   3     -- level1
//       / \ / \
//      4  5 6  7   -- level2
//        /    / \
//       8    9  10 -- level3
// 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

//TC - O(n) n- no of nodes, SC - O(n) { worst case if tree is skew} otherwise height of tree
//=========================================================================

// code solution for traversal techniques

class Node{

    public:
    int data;
    Node* left;
    Node* right;

    Node(int data){
        this->data = data;
        left = right = nullptr;
    }

    Node(int data, Node* left, Node* right){
        this->data = data;
        this->left = left;
        this->right = right;
    } 
};

Node* createBin1(Node* root){
    int val = 2;
    Node* node = root, *node5=nullptr, *node7=nullptr;
    for(int i=0;i<6;i++){
        Node* temp = new Node(val);

        if(val == 5){
            node5 = temp;
        }
        else if(val == 7){
            node7 = temp;
        }

        if(val%2 == 0){
            node->left = temp;
        }
        else{
            node->right = temp;
            if(node == root){
                node = node->left;
            }
            else{
                node = root->right;
            }
        }
        val++;
    }

    node5->left = new Node(8);

    node7->left = new Node(9);
    node7->right = new Node(10); 

    return root;
}

Node* createBin2(Node* root) {
    if (!root) return nullptr;

    // Level 2
    root->left = new Node(2);
    root->right = new Node(3);

    // Level 3
    root->left->left = new Node(4);
    root->left->right = new Node(7);
    root->right->left = new Node(6);
    root->right->right = new Node(8);

    // Level 4
    root->right->right->left = new Node(9);
    root->right->right->right = new Node(10);

    return root;
}

// 1. Preorder Traversal

void preorder(Node* node){
    if(node == nullptr)
        return;

    cout<<node->data<<" ";
    preorder(node->left);
    preorder(node->right);
}
//Ex:
/*
         1
        / \
       2   3
      / \ / \
     4  5 7  8
       /    / \
      6    9  10

-> p(1){
    1,
    -> p(2) 1->left{
            1, 2
        -> p(4): 2->left
            1, 2, 4
        -> p(4->lef)
            return
        -> p(4->right)
            return 
        -> p(5): 2->right
            1, 2, 4, 5
        -> p(6): 5->left
            1, 2, 4, 5, 6
        -> p(5->right)
            return
    }
    ->p(3) 1->right{
        -> p(7): 3->left
            1, 2, 4, 5, 6, 7
        -> p(8): 3->right
            1, 2, 4, 5, 6, 7, 8
        -> p(9): 8->left
            1, 2, 4, 5, 6, 7, 8, 9
        -> p(9->left)
            return 
        -> p(9->right)
            return 
        -> p(10): 8->right
            1, 2, 4, 5, 6, 7, 8, 9, 10
        -> p(10->left)
            return
        -> p(10->right)
            return
    }
}
*/

// 2. Inorder Traversal:

void inorder(Node* node){
    if(node == nullptr)
        return;

    inorder(node->left);
    cout<<node->data<<" ";
    inorder(node->right);
}

// 3. Postorder Traversal

void postorder(Node* node){
    if(node == nullptr)
        return;

    postorder(node->left);
    postorder(node->right);
    cout<<node->data<<" ";
}

//=========================================================================

//Level order traversal or BFS:
// Take a queue, initially put root in queue, 
// Each time take front elem from queue print it and put its left and right children in queue and continue similarly until queue is empty

void BFS(Node* root){
    if(!root){
        return;
    }

    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* frnt = q.front();
        cout<<frnt->data<<" ";
        q.pop();
        if(frnt->left)
            q.push(frnt->left);
        if(frnt->right)
            q.push(frnt->right);
    }
}
//TC - O(n), SC - O(n)

//But inorder to get level wise elements of a tree i.e we store arr of elems of each level in a outer arr 

vector<vector<int>> levelOrder(Node* root){
    if(!root)
        return vector<vector<int>>(0);
    vector<vector<int>> res;

    queue<Node*> q;
    q.push(root);

    while(!q.empty()){
        vector<int> temp;
        int sz = q.size();
        
        for(int i=0;i<sz;i++){
            Node* frnt = q.front();
            temp.push_back(frnt->data);
            q.pop();
            if(frnt->left)
                q.push(frnt->left);
            if(frnt->right)
                q.push(frnt->right);
        }
        res.push_back(temp);
    }
    return res;
}
//Tc - O(n), SC - O(n) 

//=======================================================================================

//Iterative Preorder 
// We use stack
void iterativePreorder(Node* root){
    if(!root)
        return;
    stack<Node*> st;
    st.push(root);

    while(!st.empty()){
        Node* tp = st.top();
        st.pop();
        cout<<tp->data<<" ";
        if(tp->right)
            st.push(tp->right);
        if(tp->left)
            st.push(tp->left);
    }
} 


void iterativeInorder(Node* root){
    stack<Node*> st;
    Node* temp = root;

    while(true){
        if(temp != nullptr){
            st.push(temp);
            temp = temp->left;
        }
        else{
            if(st.empty()) break;
            Node* tp = st.top();
            st.pop();
            cout<<tp->data<<" ";
            temp = tp->right;
        }
    }
}
/*
         1
        / \
       2   3
      / \ / \
     4  5 7  8
       /    / \
      6    9  10

Dry run:
{
    temp = 1
    -> loop:
        if: temp != null
            st = [1
            temp = temp->left = 2
    -> loop:
        if: temp != null
            st = [1, 2
            temp = temp->left = 4
    -> loop:
        if: temp != null
            st = [1, 2, 4 
            temp = temp->left = null
    ->loop:
        else: temp == null
            tp = 4
            st = [1, 2
            print: 4
            temp = null
    ->loop:
        else: temp = null
            tp = 2
            st = [1
            print: 4, 2
            temp = 5
    ->loop:
        if: temp!=null
            st = [1, 5
            temp = temp->left = 6
    ->loop:
        if: temp!=null
            st = [1, 5, 6
            temp = temp->left = null
    ->loop:
        else: temp = null
            tp = 6
            print: 4, 2, 6
            st = [1, 5
            temp = tp->right = null
    ->loop:
        else: temp = null
            tp = 5
            print: 4, 2, 6, 5
            st = [1
            temp = tp->right = null
    ->loop: 
        else: temp = null
            tp = 1
            print: 4, 2, 6, 5, 1
            st = [
            temp = temp->right = 3
    ->loop:
        if: temp != null
            st = [3
            temp = temp->left = 7
    ->loop:
        if: temp != null
            st = [3, 7
            temp = temp->left
    ->loop:
        else: temp = null
            tp = 7
            st = [3
            print: 4, 2, 6, 5, 1, 7
            temp = tp->right = null
    ->loop:
        else: temp = null
            tp = 3
            st = [
            print: 4, 2, 6, 5, 1, 7, 3
            temp = temp->right = 8
    ->loop:
        if: temp != null
            st = [8
            temp = temp->left = 9
    ->loop:
        if: temp != null
            st = [8, 9
            temp = null
    ->loop:
        else: temp = null
            tp = 9
            st = [8
            print: 4, 2, 6, 5, 1, 7, 3, 9
            temp = 9->right = null
    ->loop:
        else: temp = null
            tp = 8
            st = [
            print: 4, 2, 6, 5, 1, 7, 3, 9, 8
            temp = 8->right = 10
    ->loop:
        if: temp != null
        st = [10
        twmp = 10->left = null
    ->loop;
        else: temp = null
        tp = 10
        st = [
        print:  4, 2, 6, 5, 1, 7, 3, 9, 8, 10    
        temp 10->right = null
    ->loop:
        else: temp = null
        st.empty: break
}
*/

// Iterative Postorder

// In inorder:
// We looped infinitely until temp points to null and there is no element in stack
// Initially stack stores nothing but temp points to root
// Each time in infinite loop we check whether temp points to something if so then we put it to stack(i.e root of a subtree) and move temp to left child
// If temp points to null then we print stack top and pop top from stack, and make temp move towards right
// Thats print when there is no left and move to right after printing if has left go down to that storing all left nodes in stack 1 by 1 as they are potential roots also

// For preorder:
// We keep a stack and initially put root to it and we loop until stack is empty
// Each time take top elem from stack and print it and pop stack top
// and if top elems left and right available 1st put right and then left as we need (root left right)

// Now for postorder:
// -Doing to it by using 2 stack
// Step1: st1 with root sa elem and st2 empty
// step2: Each time pop st1 and put it to st2 
// step3: check for left and right elem of st1.top and put it to st1 if present
// Do it until there st1 is empty

void iterativePostorder(Node* root){
    if(!root)
        return;
    stack<Node*> st1;
    stack<Node*> st2;

    st1.push(root);
    while(!st1.empty()){
        Node* tp = st1.top();
        st1.pop();
        st2.push(tp);
        
        if(tp->left){
            st1.push(tp->left);
        }
        if(tp->right){
            st1.push(tp->right);
        }
    }

    while(!st2.empty()){
        cout<<st2.top()<<" ";
        st1.pop();
    }
}
//TC - O(n), SC - O(2*n)

//Postorder: using only 1 stack
// Use a stack and a ptr cur initially pointing to root
// Loop until both cur points to null and st is empty
//     Each time if cur != null then push cur to stack and move it to left
//     If cur = null then take temp = st.top->right 
//         if temp != null then make cur = temp
//         else if temp = null 
//             then make temp = st.top and print it and pop stack
//             Check if st is not empty and temp is right child of st.top(i.e by temp = st.top->right)
//                 if so then print st.top and do temp = st.top and do st.pop and continue until st is not empty and temp = st.top->right

void iterativePostorder1St(Node* root){
    Node* cur = root;
    stack<Node*> st;
    while(cur!=nullptr || !st.empty()){
        if(cur != nullptr){
            st.push(cur);
            cur = cur->left;
        }
        else{
            Node* temp = st.top()->right;
            if(temp == nullptr){
                temp = st.top();
                cout<<temp->data<<" ";
                st.pop();
                while(!st.empty() && temp == st.top()->right){
                    temp = st.top();
                    cout<<temp->data<<" ";
                    st.pop();
                }
            }
            else{
                cur = temp;
            }
        }
    }
}
//TC - O(2*n){worst case when there is only right skew tree}, SC - O(n)

//===========================================================================================================

// Preorder, Inorder, Postorder Traversal in sinle traversal using 1 stack
// Take 3 list:
// 1. Inorder
// 2. Preorder
// 3. Postorder

// Stack each elem stores (node, num)
// Intially stack has (root, 1) where num=1

vector<vector<int>> preInPostIt(Node* root){
    vector<int> preorder;
    vector<int> postorder;
    vector<int> inorder;

    stack<pair<Node*, int>> st;
    st.push({root, 1});

    while(!st.empty()){
        auto pr = st.top();
        st.pop();
        if(pr.second == 1){
            preorder.push_back(pr.first->data);
            pr.second++;
            st.push(pr);
            if(pr.first->left){
                st.push({pr.first->left, 1});
            }
        }
        else if(pr.second == 2){
            inorder.push_back(pr.first->data);
            pr.second++;
            st.push(pr);
            if(pr.first->right){
                st.push({pr.first->right, 1});
            }
        }
        else if(pr.second == 3){
            postorder.push_back(pr.first->data);
        }
    }
    return vector<vector<int>> {inorder, preorder, postorder};
}
//TC - O(3*n), SC - O(n){auxillary}

//------------------------------------  
//Maximum Depth of a binary tree

// We can either do
// 1. Recursive: takes O(n) space wh en tree is skew
// 2. Level order (BFS): takes O(n) every time, he says worst when tree is full binary

// Rec:
int maxDepthBinTree(Node* node){
    if(node == nullptr){
        return 0;
    }
    int left = maxDepthBinTree(node->left);
    int right = maxDepthBinTree(node->right);

    return 1+max(left, right);
}
//TC - O(n), SC - O(n)

//Level wise Traversal:
int maxDepthlevel(Node* root){
    if(root == nullptr){
        return 0;
    }
    queue<Node*> q;
    int cnt = 0;
    q.push(root);
    
    while(!q.empty()){
        int sz = q.size();
        for(int i=0;i<sz;i++){
            Node* frnt = q.front();
            q.pop();

            if(frnt->left){
                q.push(frnt->left);
            }
            if(frnt->right){
                q.push(frnt->right);
            }
        }
        cnt++;
    }
    return cnt;
}
//TC - O(height) {worst=O(n)}, SC - O(n)


//----------------------------------------------------------------------------------------------------------------
//Check for balanced binary tree
// Balanced BT = for every node, (height(left) - height(right)) <= 1

// Brut:
// Recurse, for every node its abs(height(left)-height(right)) <= 1

bool checkBalanced(Node* node){
    if(node == nullptr)
        return true;
    int lft = maxDepthBinTree(node->left);
    int rght = maxDepthBinTree(node->right);

    if(abs(lft - rght) > 1){
        return false;
    }
    bool l = checkBalanced(node->left);
    bool r = checkBalanced(node->right);
    if(!l || !r){
        return false;
    }
    return true;
}
//TC - O(n^2), SC - O(height) {in worst O(n)}

//Optimal:
// Using same maxDepth recursive code with some addition but we are not returning bool instead would be returning -1 incase of unbalanced and depth of tree incase balanced!

int checkBalancedHelper(Node* node){
    if(node == nullptr){
        return 0;
    }
    int left = checkBalanced(node->left);
    if(left == -1){
        return -1;
    }
    int right = checkBalanced(node->right);
    if(right == -1){
        return -1;
    }
    if(abs(left-right) > 1){
        return -1;
    }
    return 1 + max(left, right);
}
//TC - O(n), SC - O(n)

bool checkBalancedOpt(Node* node){
    int n = checkBalancedHelper(node);
    if(n == -1){
        return false;
    }
    else{
        return true;
    }
}

//----------------------------------------------------------------------------------------------------------------


//Diameter of a Binary Tree
/*
Diameter - Longest path between any 2 nodes, it doesnt need to pass through root
Note: Its not max depth 
Ex: 
      1
     / \
    2   3
   / \
  4   5
Diameter = 3 = (4->2->1->3)

2.
    1
   / \
  2   3
     / \
    4   7
    |    \
    5     8
   /       \
  6         9
Diameter = 7 = (6->5->4->3->7->8->9) here t doesnt pass through root

As the max path is for a particular node it is (left height + right height) So we go through each node and find its left+right and compare with maxi var
*/

void diameterBinTree(Node* node, int& maxi){
    if(node == nullptr){
        return;
    }
    int left = maxDepthBinTree(node->left);
    int right = maxDepthBinTree(node->right);

    maxi = max(maxi, left+right);
    diameterBinTree(node->left, maxi);
    diameterBinTree(node->right, maxi);
}
//TC - O(n*(2*n)), SC - O(n)


//Optimal: Use max Depth of Binary Tree code and at every node ask left+right and compare it with maxi
int diameterBinOpt(Node* node, int& maxi){
    if(node == nullptr){
        return 0;
    }
    int left = diameterBinOpt(node->left, maxi);
    int right = diameterBinOpt(node->right, maxi);
    maxi = max(maxi, left+right);
    return 1+max(left, right);
}
//Tc - O(n), Sc - O(1)

//----------------------------------------------------------------------------------------------------------------
// Maximum Path Sum
// Here i dont require the sum of node vals of diameter but i require the max sum of node vals accross any path 
// Ex:
//     -10
//     / \
//    9   20
//       /  \
//      15   7
// the maximum path sum = 42, (15->20->7)

// Brut: Go for each node and find leftSum + rightSum and add it to cur node val and compare with maxi 
// In leftSum choose that path which results in maximum sum

int maxSumBin(Node* node){
    if(node==nullptr){
        return 0;
    }
    int left = maxSumBin(node->left);
    int right = maxSumBin(node->right);
    
    return node->data + max(left, right);
}

void maxPathSum(Node* node, int& maxi){
    if(node == nullptr){
        return;
    }
    int left = maxSumBin(node->left);
    int right = maxSumBin(node->right);

    maxi = max(maxi, left+right+node->data);
}
//TC - O(n^2), SC - O(n)

//Optimal:
int maxPathSumOpt(Node* node, int& maxi){
    if(node == nullptr){
        return 0;
    }
    int left = max(0, maxPathSumOpt(node->left, maxi)); //ignore negative branch as if a branch results negatively we can even ignore it 
    int right = max(0, maxPathSumOpt(node->right, maxi));

    maxi = max(maxi, node->data + left + right);
    return node->data + max(left, right);
}
//TC - O(n), SC - O(n)

//----------------------------------------------------------------------------------------------------------------
 
//Same Tree or Not
// Check 2 trees are same in terms of structure and node value, u are givcen with 2 roots 
// Simple use any traversal method either dfs or bfs

// Using inorder 
bool sameTreeCheck(Node* node1, Node* node2){
    if(!node1 || !node2){
        return (node1 == node2); //this returns true when both are null and false otherwise
    }

    if(!sameTreeCheck(node1->left, node2->left))
        return false;

    if(node1->data != node2->data)
        return false;

    if(!sameTreeCheck(node1->right, node2->right))
        return false;
    return true;
}
//TC - O(max(n, m)), Sc - O(max(n,m))

//Using preorder simplifes code as

bool sameTreePre(Node* node1, Node* node2){
    if(!node1 || !node2){
        return (node1==node2);
    }

    return (node1->data == node2->data) && (sameTreePre(node1->left, node2->left) && (sameTreePre(node1->right, node2->right)));
}

//----------------------------------------------------------------------------------------------------------------

//Zig zag traversal
// Kind of similar to level order traversal but in level order the order in which each level was printed was same but here the order in which next level will be reverse of previous

// Rememeber level order: We used queue and initially fed with root and each time we op front and printde and if present put its left and then right always 
// But we need in even levels first left and then right and in odd levels first right and then left
// So we need a indicatr for even and odd levels, but how do we know a level has completed?
// okay we can use a flag which turns 0 when even and 1 when odd but how do we know when a level completes?
 
// We can know level by considering each loop will be for one level for that we need to add a for loop inside while which will go through all elems inside the current queue and replace those with their childs order as per flag 

vector<vector<int>> zigZagTraversal(Node* root){
    if(!root) return vector<vector<int>>();

    vector<vector<int>> res;
    queue<Node*> q;
    q.push(root);
    bool leftToRight = 1;

    while(!q.empty()){
        int sz = q.size();
        vector<int> temp(sz);
        int index = 0;
        for(int i=0;i<sz;i++){
            Node* frnt = q.front();
            q.pop();

            if(leftToRight){
                index = i;
            }
            else{
                index = sz-1-i;
            }
            temp[index] = frnt->data;
            
            if(frnt->left) q.push(frnt->left);
            if(frnt->right) q.push(frnt->right);
        }

        res.push_back(temp);
        leftToRight = !leftToRight;
    }
    return res;
}
//Remeber u should not try to traverse leftToRight and rightToLeft i.e to add nodes in that order to queu but instead just u should put values in resultant vector in its zig zag order as initially queue has all elems to be in particular level
//Tc - O(n), SC - O(n) {auxillary}

//----------------------------------------------------------------------------------------------------------------

//Boundary Traversal (Anticlockwise)
/*
         1
        / \
       2   7
      /     \
     3       8
      \     /
       4   9
      / \ / \
     5  6 10 11

Boundary Traversal = (1->2->3->4->5->6->10->11->9->8->7)

Approach:
1. Left Boundary excluding leaf nodes
2. Leaf nodesf
3. Right Boundary on the reverse
*/
// 1. Left boundary without leaf
// Use a ds, initially put root  
// And move to left node if no left node only then move to right node and stop if next node is leaf

// 2. Leaf nodes:
// Use inorder traversal and in that only take those which are leaf nodes to res as per original order

// 3. Right Boundary on the reverse
// Use stack, and start with root->right and move right only if no right child then move to left child

void inorderTraversalHelper(Node* node, vector<Node*>& res){
    if(!node){
        return;
    }
    res.push_back(node);
    inorderTraversalHelper(node->left, res);
    inorderTraversalHelper(node->right, res);
}
//TC - O(n), SC - O(n)

vector<int> boundaryTraversal(Node* root){
    vector<int> res;
    if(!root) return res;

    //left boundary
    Node* temp = root;
    while(true){
        if(!temp->left && !temp->right)
            break;
        res.push_back(temp->data);
        if(temp->left)
            temp = temp->left;
        else
            temp = temp->right;
    }

    //leaf nodes
    vector<Node*> inor;
    inorderTraversalHelper(root, inor);
    for(auto v:inor){
        if(!v->left && !v->right){
            res.push_back(v->data);
        }
    }

    //Right Boundary in the reverse
    if(root->right)
        temp = root->right;
    else
        temp = nullptr; //maybe no idea what if root has no right child

    stack<Node*> st;
    while(temp){
        if(!temp->left && !temp->right)
            break;

        st.push(temp);
        if(temp->right)
            temp = temp->right;
        else
            temp = temp->left;
    }

    while(!st.empty()){
        res.push_back(st.top()->data);
        st.pop();
    }
    return res;
}
//TC - O(n + n) {the whole boundary + inorder}, SC - O(n + n) {inorder + stack}

//Covering all edge cases

bool isLeaf(Node* node){
    if(!node) return false;
    if(!node->left && !node->right) return true;

    return false;
}

void addLeftBoundary(Node* node, vector<int>& res){
    Node* temp = node->left;
    while(temp){
        if(!isLeaf(temp)) res.push_back(temp->data);
        if(temp->left) temp = temp->left;
        else temp = temp->right;
    }
}

void addLeafNodes(Node* node, vector<int>& res){
    if(!node){
        return;
    }
    if(isLeaf(node)) res.push_back(node->data);
    addLeafNodes(node->left, res);
    addLeafNodes(node->right, res);
}

void addRightBoundary(Node* node, vector<int>& res){
    Node* temp = node->right;
    stack<int> st;
    while(temp){
        if(!isLeaf(temp)) st.push(temp->data);
        if(temp->right) temp = temp->right;
        else temp = temp->left;
    }

    while(!st.empty()){
        res.push_back(st.top());
        st.pop();
    }
}

vector<int> boundaryTraversalClean(Node* root){
    vector<int> res;
    if(!root) return res;
    
    if(!isLeaf(root)) res.push_back(root->data);
    addLeftBoundary(root, res);
    addLeafNodes(root, res);
    addRightBoundary(root, res);
    return res;
}

//TC - O(n), SC - O(n)

//----------------------------------------------------------------------------------------------------------------

//Vertical Order Traversal

/*
Vertical(x): -2 -1  0  1  2
Level   (y):
0                   1
                  /   \
1                2     3
                / \   / \
2              4  10 9  10
                \
3                5
                  \
4                  6
 
For ex: 
node 1: (0,0)
node 2: (-1,1)
node 3: (1,1)
node 4: (-2,2)
node 10: (0,2)
node 9: (0,2)
node 10: (2,2)
node 5: (-1,3)
node 6: (0,4)

We have to traverse vertical: i.e x axis wise: in each vertical its traversed level wise, if got 2 nodes in same level then put that node with smaller value first
as:
vertical 0: (1, 9, 10, 6)
vertical -1: (2, 5)
vertical -2: (4)
vertical 1: (3)
vertical 2: (10)

We will return a vector<vector<int>> where each dimension1 represents vertical(x axis of node) and dimension2 reps level(y axis of node)

Approach; Use a queue which stores (node data, vertical(x axis), level(y axis)), initially start with root as (root->data, 0, 0)
->until queue is empty loop:
Each time: take front put it to res vector in its exact coordinates and pop it from q and put its left and right child with exact coordinates 
*/
Node* createBin3(Node* root) {
    if (!root) return nullptr;

    // Level 2
    root->left = new Node(2);
    root->right = new Node(3);

    // Level 3
    root->left->left = new Node(4);
    root->left->right = new Node(10);
    root->right->left = new Node(9);
    root->right->right = new Node(10);

    // Level 4 & 5
    root->left->left->right = new Node(5);
    root->left->left->right->right = new Node(6);

    return root;
}


pair<int, int> maxLevel(Node* node){
    if(!node) return {0,0};

    Node* temp = node;
    int resL=0, resR=0;
    while(temp){
        resL++;
        temp =  temp->left;
    }
    temp = node;
    while(temp){
        resR++;
        temp = temp->right;
    }
    return {resL, resL+resR-1};
}

vector<vector<int>> verticalTraversal(Node* root){
    unordered_map<> res;
    if(!root){
        return res;
    }
    res = vector<vector<int>>(verticalWidth, vector<int>(levelHieght, -1));
    queue<tuple<Node*, int, int>> q;
    q.push({root, 0, 0});

    while(!q.empty()){
        auto [node, vert, level] = q.front();
        cout<<node->data<<endl;
        q.pop();
        // if(res[indexOpt + vert][level] != -1){

        // }
        res[indexOpt + vert][level] = node->data;
        if(node->left){
            q.push({node->left, vert-1, level+1});
        }
        if(node->right){
            q.push({node->right, vert+1, level+1});
        }
    }
    return res;
}


int main(){

    // struct Node* root = new Node(1);
    // root->left = new Node(2);
    // root->right = new node(3);
    // root->left->right = new Node(5);

    //produces:
    //   1
    //  / \
    // 2   3
    //  \
    //   5

    //================================
    // Node* root = new Node(1);
    // root = createBin1(root);
    // int maxi = INT_MIN;
    // maxPathSumOpt(root, maxi);
    // cout<<maxi;

    //================================

    // Node* root1 = new Node(1); 
    // root1 = createBin1(root1);

    // Node* root2 = new Node(1);
    // root2 = createBin2(root2);
    
    // cout<<sameTreePre(root1, root2);

    //================================

    // Node* root = new Node(1);
    // root = createBin1(root);
    // auto res = zigZagTraversal(root);
    // for(auto v:res){
    //     for(auto i:v){
    //         cout<<i<<" ";
    //     }
    //     cout<<endl;
    // }

    //================================

    // Node* root = new Node(1);
    // root = createBin1(root);
    // auto res = boundaryTraversalClean(root);
    // for(auto v:res){
    //     cout<<v<<" ";
    // }

    //================================

    Node* root = new Node(1);
    root = createBin3(root);
    auto res = verticalTraversal(root);
    for(auto v:res){
        for(auto i:v){
            cout<<i<<" ";
        }
        cout<<endl;
    }

    return 0;
}