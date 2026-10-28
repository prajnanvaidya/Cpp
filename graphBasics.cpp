#include<bits/stdc++.h>

using namespace std;


//Graph
// every graph has 2 things:
// - nodes
// - edges

// Note: All trees are also graph: minimal req for a graph: should have nodes and edges

//=================================================================================================================

// Types of graph:
// - Directed graph: has directed edges 
// - Undirected graph: all edges are bidirectional
// Even directed graph can have bidirectional edges
// [image-comments/image-20261022-122201-3lmqv7.png]

//=================================================================================================================

// Cycles in graph:
// cycle: Start from a node and end at the same node
// - Undirected cyclic graph: undirected edges with atleast 1 cycle
// Ex: // [image-comments/image-20261022-122444-1rrvxg.png]
// The above graph has multiple cycles: 1->2->4->5, 2->5->3, 1->2->3->5->4

// - Directed cyclic graph: having directed edges with atleast 1 cycle in it
// // [image-comments/image-20261022-122729-glytp2.png]
// The above is not a directed cyclic graph instead its a directde acyclic graph as there exist no cycles in it!

// Note: DAG - Directed Acyclic graph

//=================================================================================================================

// Path: Contain a lot of nodes/vertices and each of them are reachable
// A node cannot appear twice in a graph
// for ex: // [image-comments/image-20261022-123008-hv1f4f.png]
// in above 1-2-3-5 is a path, 1-2-3-2-1 not a path as 2 appears twice, 1-3-5 is not a path as there is no direct edge from 1-3

//=================================================================================================================

// Degrees in a graph:

// - Undirected graph: 
// Degree of a node: For undirected graph degree is no of eedges attached to that node
// ex: // [image-comments/image-20261022-123402-6kdrnr.png]
// Degree of 3: 3, 4: 2

// Note: Total degree of a undirected graph = 2*total no of edges
// Ex in above 12 = 2*6

// - Directed graph:
// Degree: total no of edges incoming or outgoing from that node
// Classified as:
// - Indigree of a node: incoming edges
// - Outdegree of a node: outgoing edges
// Ex: // [image-comments/image-20261022-123805-x3o0qt.png]

//=================================================================================================================

// Edge Weight: 
// Every edge in any graph holds a weightage if not assigned we consider them as unit weights

//=================================================================================================================

// Representation of a graph in cpp:   
// Initially they sppecify directed or undirected here consider undirected with n nodes and m edges
// input: 
// 1. n(no of nodes), m(no of edges) 
//     5 6
// 2. m lines representing edges they can be in any order
//     2 1
//     1 3
//     2 4
//     3 4
//     2 5
//     4 5

//  1--2 \ 
//  |  |  \
//  |  |   5
//  |  |  /
//  3--4 /

//  is there any upper limit on m: no m can be anything for a raph with n nodes a maximum of n*(n-1) edges are possible 

//  Store:
//  1. using matrix
//  known as adjacency matrix

// Consider a graph with 5 edges check whether it is 0 or 1 based, if 0 based then create matrix as adj[n+1][n+1] - its a matrix of 0 and 1s
// Each position corresponding to i and j asks is there a edge between i and j if yes then the value is 1 otherwise 0 
// // [image-comments/image-20261022-131421-i4gpzd.png]

// Note: adjacency matrix using to store graph is costly

//Undirected un-weighted graph using adj matrix
void inputUndirectedGraph(int& n, int& m, vector<vector<int>>& adj){
    int u,v;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>u>>v;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
}


//Space adjacency matrix uses is O(n^2) where n is no of nodes

// 2. using List

// Its a list of list where index represents a node and each internal list items showcases list of all nodes to which index is connected 
// Total space taken, Undirected: 2*Edges = 2*m, Directed: m (as we only input for edge outgoing node in it)
// Incase of adjacenecy matrix total space was, Directed: n*m, Undirected: m
//So using adjacenecy list is space optimum 

//=================================================================================================================

// For weighted graph:
// 1. Using adjacenecy matrix: store weights itself instead of 1

//Directed weighted graph using adj matrix
void inputDWG(vector<vector<int>>& arr, int& n, int& m){
    cin>>n>>m;
    arr = vector<vector<int>>(n+1, vector<int>(m+1));
    int u,w,v;
    for(int i=0;i<m;i++){
        cin>>u>>w>>v;
        arr[u][v] = w;
        // arr[v][u] = w; for undirected 
    }
}

// 2. Using lists: Store pair as arr elems containing neigbouring nodes with wassociated weights

//Undirected weighted graph using adj lists
void inputUWGL(vector<vector<pair<int, int>>>& arr, int n, int m){
    cin>>n>>m;
    int u, v, w;
    arr = vector<vector<pair<int, int>>>(n+1);
    for(int i=0;i<m;i++){
        cin>>u>>w>>v;
        arr[u].push_back({v, w});
        arr[v].push_back({u, w});
    }
}


//input directed graph un-weihted using list
void inputGraphUDirectedAdL(int& n, int& m, vector<vector<int>>& arr){
    cin>>n>>m;
    int u, v;
    arr = vector<vector<int>>(n+1);
    for(int i=0;i<m;i++){
        cin>>u>>v;
        arr[u].push_back(v);

        arr[v].push_back(u); //for undirected
    }
}

//===============================================================================

// print

//print Undirected or Directed U-weighted Graph which uses adj matrix
void printGraphAdjMatDOrUD(vector<vector<int>>& arr){
    int n = arr.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<arr[i].size();j++){
            if(arr[i][j] > 0){
                cout<<i<<"--->"<<j<<endl;
            }
        }
    }
}

//print Undirected or Directed Weighted which uses adj matrix
void printGraphAdjMatUW(vector<vector<int>>& arr){
    int n=arr.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<arr[i].size();j++){
            if(arr[i][j]>0){
                cout<<i<<"--"<<arr[i][j]<<"-->"<<j<<endl;
            }
        }
    }
}

//Print Undirected/Directed weighted graph uses adj list
void printAdjListUW(vector<vector<pair<int, int>>>& arr){
    int n=arr.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<arr[i].size();j++){
            cout<<i<<"--"<<arr[i][j].second<<"-->"<<arr[i][j].first<<endl;
        }
    }
}

//Print Undirected/Directed un-weighted graph uses adj list
void printAdjListUuW(vector<vector<int>>& arr){
    int n=arr.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<arr[i].size();j++){
            cout<<i<<"---->"<<arr[i][j]<<endl;
        }
    }
}

//===============================================================================================

//Connected Components
// In image both are graph: // [image-comments/image-20261024-173929-qzs8ts.png]
// In image: no of graph is 4(single node can also be treated as graph), // [image-comments/image-20261024-174525-6oasz3.png]

// Can the 4 graphgs in above image can be said a single grph?
// Yes as if a undirected graph with N=10, M=8 now all of them come under a single graph but there exist 4 different components   

// But in traversal algo if u started say from Node1, u cannot reach Node8 so we maintain a arr of bool said as visied arr of size n
// visited[n] where once we start a traversal fom 1 Node we mark all node printed as 1 and go to next 0 having index to traverse\
// for(i = 1->n){
//     if(!vis[i]){
//         traverse[i]
//     }
// }

//===============================================================================================


// BFS(level-wise traversal)
// First prints starting node and goes to all nodes which are equal distance from curr node and prints 1 by 1 in any order and then goes to next 
// Ex: // [image-comments/image-20261024-181059-bvqk7p.png]

// Here if starting node = 1
// BFS:
// 1, 
// 1, 2, 6
// 1, 2, 6, 3, 4
// 1, 2, 6, 3, 4, 7, 8
// 1, 2, 6, 3, 4, 7, 8, 5

// Starting node = 6
// 6,
// 6, 1, 7, 8
// 6, 1, 7, 8, 2, 5
// depth: 0  1  1  1  2  3  3
//        6, 1, 7, 8, 2, 3, 4

// Use queue:
// start = 1
// q: 1
// -> q initially has pushed starting node
// maintain a visited arr of size n+1 (if node follows 1 based numbering), mark start node as visited
//       0 1 2 3 4 5 6 7 8 
// vis - 0 1 0 0 0 0 0 0 0

// -> Each time pop the elem from q and print it and push all its unvisited child nodes and make all pushed nodes to be visited

// 1. 
//     q: 
//     print 1
//     q: 2, 6
//           0 1 2 3 4 5 6 7 8 
//     vis - 0 1 1 0 0 0 1 0 0

// 2.
//     q: 6
//     print 1, 2
//     q: 6, 3, 4
//           0 1 2 3 4 5 6 7 8 
//     vis - 0 1 1 1 1 0 1 0 0

// 3.
//     q: 3, 4
//     print 1, 2, 6
//     q: 3, 4, 7, 8
//           0 1 2 3 4 5 6 7 8 
//     vis - 0 1 1 1 1 0 1 1 1

// 4.
//     q: 4, 7, 8
//     print: 1, 2, 6, 3
//     q: 4, 7, 8
//           0 1 2 3 4 5 6 7 8 
//     vis - 0 1 1 1 1 0 1 1 1

// 5.
//     q: 7, 8
//     print: 1, 2, 6, 3, 4
//     q: 7, 8, 5
//           0 1 2 3 4 5 6 7 8 
//     vis - 0 1 1 1 1 1 1 1 1

// 6.
//     q: 8, 5
//     print: 1, 2, 6, 3, 4, 7
//     q: 8, 5
//           0 1 2 3 4 5 6 7 8 
//     vis - 0 1 1 1 1 1 1 1 1

// 7.
//     q: 5
//     print: 1, 2, 6, 3, 4, 7, 8
//     q: 5
//           0 1 2 3 4 5 6 7 8 
//     vis - 0 1 1 1 1 1 1 1 1

// 8.
//     q:
//     print: 1, 2, 6, 3, 4, 7, 8, 5
//     q:
//           0 1 2 3 4 5 6 7 8 
//     vis - 0 1 1 1 1 1 1 1 1

void bfsTraversal(vector<vector<int>>& adjL, int s){
    int n=adjL.size();
    vector<int> vis(n, 0);
    vis[s]=1;

    queue<int> q;
    q.push(s);

    while(!q.empty()){
        int node = q.front();
        cout<<node<<" ";
        q.pop();

        for(int i=0;i<adjL[node].size();i++){
            int child = adjL[node][i];
            if(!vis[child]){
                q.push(child);
                vis[child] = 1;
            }
        }
    }
}
//TC - O(n + 2*m) cuz each node is printed once so outer while loop runs n times and inner for loop runs for each node its child node no of times i.e its degree and total degree of a undirected graph = 2*edges as edge holds 2 nodes

//====================================================================================

//Depth First Traversal: 
// Go inside full depth once and then retreat for others each time u see a new node complete the full depth of it 

// Ex: // [image-comments/image-20261025-052504-xl9j1y.png]
// starting node: 1
// 1,
// 1,2,6
// 1,2,6,5
// 1,2,6,5,3,4,8
// 1,2,6,5,3,4,8,7

// Using recurion
// Steps: first print the current node and loop through its child nodes and check is it visited if not then pass it in next function call

void dfs(vector<int>& visited, int node, vector<vector<int>>& adjL){
    cout<<node<<" ";
    visited[node] = 1;
    for(int i=0;i<adjL[node].size();i++){
        int cld = adjL[node][i];
        if(!visited[cld]){
            dfs(visited, cld, adjL);
        }
    }
}

void dfsInitialiser(vector<vector<int>>& adjL, int st){
    int n=adjL.size();
    vector<int> vis(n+1, 0);
    dfs(vis, st, adjL);
}
//TC - O(n + 2*m), SC - O(depth) ~ O(n){if graph is skewed} output space{if used a vector to store traversal} - O(n)


int main(){
    int n, m;
    vector<vector<int>> adj;
    inputGraphUDirectedAdL(n, m, adj);
    printAdjListUuW(adj);

    dfsInitialiser(adj, 3);

    return 0;
}