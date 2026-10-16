#include<bits/stdc++.h>

using namespace std;

//Set matrix Zeroes
//Given a binary matrix having either 0/1
//U have to go to cell having 0 and make its whole column and row as 0 then return it

auto setMatrixZrs(vector<vector<int>>& mat){

    vector<vector<int>> res=mat;

    for(int i=0;i<mat.size();i++){
        for(int j=0;j<mat[i].size();j++){
            if(mat[i][j] == 0){
                for(int k=0;k<mat.size();k++){
                    res[k][j]=0;
                }
                for(int k=0;k<mat[i].size();k++){
                    res[i][k]=0;
                }
            }
        }
    }
    return res;
}
//TC - o(n^2), Sc - O(1)

//Without using output space
void setMatrixZrsBrut(vector<vector<int>>& mat){
    for(int i=0;i<mat.size();i++){
        for(int j=0;j<mat[i].size();j++){
            if(mat[i][j] == 0){
                for(int k=0;k<mat.size();k++){
                    if(mat[k][j] != 0) mat[k][j] = -1;
                }
                for(int k=0;k<mat[i].size();k++){
                    if(mat[i][k] != 0) mat[i][k] = -1;
                }
            }
        }
    }

    for(int i=0;i<mat.size();i++){
        for(int j=0;j<mat[i].size();j++){
            if(mat[i][j]==-1) mat[i][j]=0;
        }
    }
}
//Tc - o(n*m * (n+m)), Sc - O(1) , TC ~ O(n^3)

//Better maintain a hashArr for row and col those affected by 0's and at last make all those 0s
void setMatrixZrsBet(vector<vector<int>>& mat){
    int n=mat.size();
    int m=mat[0].size();

    vector<int> rowHash(n, 0);
    vector<int> colHash(m, 0);

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mat[i][j] == 0){
                rowHash[i]=1;
                colHash[j]=1;
            }
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(rowHash[i] == 1 || colHash[j] == 1)
                mat[i][j] = 0;
        }
    }
}
//TC - o(n*m + n*m), Sc - O(n + m)

/*
===============================================================================
                 SET MATRIX ZEROES — OPTIMAL APPROACH
===============================================================================

IDEA:
    Instead of using separate row[n] and col[m] arrays, reuse the first
    column and first row of the matrix as markers.

    mat[i][0] -> marks whether row i must be zeroed.
    mat[0][j] -> marks whether column j must be zeroed (for j > 0).

    PROBLEM:
    mat[0][0] belongs to BOTH the first row and the first column.

    SOLUTION:
    Use mat[0][0] to mark the first row, and use a separate variable
    col0 to track whether the first column must be zeroed.

-------------------------------------------------------------------------------
STEP 1: MARK ROWS AND COLUMNS
-------------------------------------------------------------------------------

    Traverse the original matrix.

    Whenever mat[i][j] == 0:

        1. Set mat[i][0] = 0 to mark row i.

        2. If j != 0:
               Set mat[0][j] = 0 to mark column j.

           Otherwise:
               Set col0 = 0 to mark the first column.

    IMPORTANT EXAMPLE:

        If mat[0][2] == 0:

            mat[0][0] = 0;   // Mark the first row.
            mat[0][2] = 0;   // Mark column 2.
            col0 remains unchanged because column 0 has not
            necessarily been marked for zeroing.

        If mat[2][0] == 0:

            mat[2][0] = 0;   // Mark row 2.
            col0 = 0;        // Mark the first column.

        Thus, mat[0][0] and col0 represent DIFFERENT conditions.

-------------------------------------------------------------------------------
STEP 2: ZERO THE INNER MATRIX
-------------------------------------------------------------------------------

    Traverse only the inner cells:

        i = 1 to n - 1
        j = 1 to m - 1

    If either marker is zero:

        mat[i][0] == 0  OR  mat[0][j] == 0

    set:

        mat[i][j] = 0;

    This zeroes cells whose corresponding row or column was marked.

-------------------------------------------------------------------------------
STEP 3: ZERO THE FIRST ROW
-------------------------------------------------------------------------------

    If mat[0][0] == 0:

        Set every element in the first row to zero.

    mat[0][0] is the marker for the first row.

-------------------------------------------------------------------------------
STEP 4: ZERO THE FIRST COLUMN
-------------------------------------------------------------------------------

    If col0 == 0:

        Set every element in the first column to zero.

    col0 is the separate marker for the first column.

-------------------------------------------------------------------------------
WHY THIS ORDER MATTERS
-------------------------------------------------------------------------------

    First, process the inner matrix while the markers are still available.

    Then, process the first row and first column separately.

    This prevents overwriting the markers before they have been used.

===============================================================================
COMPLEXITY:
    Time Complexity  : O(n * m)
    Auxiliary Space  : O(1)
===============================================================================
*/

void setMatrixZrsOpt(vector<vector<int>>& mat){
    int n=mat.size();
    int m=mat[0].size();

    int elem00;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mat[i][j] == 0){
                mat[i][0] = 0;
                if(j!=0)
                    mat[0][j]=0;
                else
                    elem00=0;
            }
        }
    }

    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){
            if(mat[i][j] != 0)
                if(mat[0][j] == 0 || mat[i][0] == 0)
                    mat[i][j]=0;
        }
    }

    if(mat[0][0] == 0){
        for(int j=1;j<m;j++){
            if(mat[0][j]==1) mat[0][j]==0;
        }
    }

    if(elem00 == 0){
        for(int i=0;i<n;i++){
            if(mat[i][0] == 1) mat[i][0]=0;
        }
    }
}
//TC - O(n*m + (n-1)*(m-1) + (m-1) + (m-1)) ~ O(n*m)
//Sc - O(1)

//-----------------------------------------------------------------------------------------------------------------------------------------------

//Rotated Image of a matrix
//Rotate a matrix by 90degrees clockwise
//Input a matrix of size n*n and return a matrix of size n*n
//Ex: 
// Given:
// 1   2  3  4
// 5   6  7  8
// 9  10 11 12
// 13 14 15 16

// Res:
// 13  9 5 1
// 14 10 6 2
// 15 11 7 3
// 16 12 8 4

auto rotateMatrix(vector<vector<int>>& mat){
    int n=mat.size();
    vector<vector<int>> res(n, vector<int>(n));

    for(int j=0;j<n;j++){
        for(int i=n-1;i>=0;i--){
            res[j][(n-1)-i] = mat[i][j];
        }
    }
    return res;
}
//TC - O(n^2), Sc - O(1){auxillary}

//U have complicated the steps wioth correct logic why? u do not need to traverse evry column from last row and then place each element in correct place of res rather u can just traverse the matric rowise as usual and place them right position based on following observation
//    0   1  2  3
// 0: 1   2  3  4
// 1: 5   6  7  8
// 2: 9  10 11 12
// 3: 13 14 15 16

//     0  1 2 3
// 0: 13  9 5 1
// 1: 14 10 6 2
// 2: 15 11 7 3
// 3: 16 12 8 4

// actual -> result
// (0,0)  =  (0,3)
// (0,1)  =  (1,3)
// (0,2)  =  (2,3)
// (0,3)  =  (3,3)

// (1,0)  =  (0,2)
// (1,1)  =  (1,2)
// (1,2)  =  (2,2)
// (1,3)  =  (3,2)

// Here can be seen (i,j) => (j,n-i)

auto rotateMatBrutHis(vector<vector<int>>& mat){
    int n=mat.size();

    vector<vector<int>> res(n, vector<int>(n));

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            res[j][n-1-i] = mat[i][j];
        }
    }
    return res;
}

//Optimal: Need to do changes inplace
//Take transpose and reverse each rows done!

//    0   1  2  3
// 0: 1   2  3  4
// 1: 5   6  7  8
// 2: 9  10 11 12
// 3: 13 14 15 16

// Transpose:
//    0 1  2  3
// 0: 1 5  9 13
// 1: 2 6 10 14
// 2: 3 7 11 15
// 3: 4 8 12 16

//     0  1 2 3
// 0: 13  9 5 1
// 1: 14 10 6 2
// 2: 15 11 7 3
// 3: 16 12 8 4

// To take transpose inplace: need to swap elements along the diagonal So loop through only in upper or lower triangle elems of matrix and swap i,j with j,i 
// How to loop in upper triangular matrix: 
// n=4
// (0,1), (0,2), (0,3), 
// (1,2), (1,3),
// (2,3)
// i starts from 0 to n-1, j starts from i+1 to n-1

void RotatematOpt(vector<vector<int>>& mat){
    int n=mat.size();

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            swap(mat[i][j], mat[j][i]);
        }
    }
    for(int i=0;i<n;i++){
        reverse(mat[i].begin(), mat[i].end());
    }
}
//TC - O(n^2), Sc - O(1)

//-----------------------------------------------------------------------------------
//Spiral Traversal of a matrix:

//     0   1   2   3   4   5
// 0:  1   2   3   4   5   6
// 1: 20  21  22  23  24   7
// 2: 19  32  33  34  25   8
// 3: 18  31  36  35  26   9
// 4: 17  30  29  28  27  10
// 5: 16  15  14  13  12  11


// res: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 


void noobSpiralTraverse(vector<vector<int>>& mat){
    int n=mat.size();
    int cnt=0;
    int i=0, j=0;
    // while(cnt <= n*n){
        while(i==0 && j<n){
            cout<<mat[i][j]<<" ";
            j++;
            cnt++;
        }
        j--;
        i++;
        while(j==(n-1) && i<n){
            cout<<mat[i][j]<<" ";
            i++;
            cnt++;
        }
        i--;
        j--;
        while(i==n-1 && j>=0){
            cout<<mat[i][j]<<" ";
            j--;
            cnt++;
        }
        j++;
        i--;
        while(j==0 && i>0){
            cout<<mat[i][j]<<" ";
            i--;
            cnt++;
        }
        i++;
        j++;
        while(i==1 && j<n-1){
            cout<<mat[i][j]<<" ";
            j++;
            cnt++;
        }
        j--;
        i++;
        while(j==(n-2) && i<(n-1)){
            cout<<mat[i][j]<<" ";
            i++;
            cnt++;
        }
        i--;
        j--;
        while(i==(n-2) && j>0){
            cout<<mat[i][j]<<" ";
            j--;
            cnt++;
        }
        j++;
        i--;
        while(j==1 && i>1){
            cout<<mat[i][j]<<" ";
            i--;
            cnt++;
        }
        i++;
        j++;
        while(i==2 && j<(n-2)){
            cout<<mat[i][j]<<" ";
            j++;
            cnt++;
        }
        j--;
        i++;
        while(j==(n-3) && i<(n-2)){
            cout<<mat[i][j]<<" ";
            i++;
            cnt++;
        }
        i--;
        j--;
        while(i==(n-3) && j>1){
            cout<<mat[i][j]<<" ";
            j--;
            cnt++;
        }
}

// void SpiralTraverseOpt(vector<vector<int>>& mat){
//     int n=mat.size();
//     int cnt=0;

//     int ij_cnt=0;
//     int ij_ival=0;
//     while(cnt<(n+n)){
//         if(cnt%2==0){
//             if(ij_cnt%2==0){
//                 while(i==ij_ival && j<n-ij_ival){
//                     cout<<mat[i][j]<<" ";
//                     j++;
//                 }
//                 ij_ival++;
//             }
//             else{
//                 while(i==n-ij)
//             }
//             ij_cnt++;
//             cnt++;
//         }
//     }
// }



auto spiralTraversal(vector<vector<int>>& mat){
    int n=mat.size();
    int m=mat[0].size();

    int left_col=0, right_col=m-1;
    int top_row=0, bottom_row=n-1;
    vector<int> ans;

    while(top_row <= bottom_row && left_col <= right_col){
        for(int i=left_col;i<=right_col;i++){
            ans.push_back(mat[top_row][i]);
        }
        top_row++;
        for(int i=top_row;i<=bottom_row;i++){
            ans.push_back(mat[i][right_col]);
        }
        right_col--;
        if(top_row <= bottom_row){
            for(int i=right_col;i>=left_col;i--){
                ans.push_back(mat[bottom_row][i]);
            }
            bottom_row--;
        }
        if(left <= right){
            for(int i=bottom_row;i>=top_row;i--){
                ans.push_back(mat[i][left_col]);
            }
            left_col++;
        }
    }
    return ans;
}
//TC - O(n*m), SC - o(n*m)



//-------------------------------------------------------------------------------------------------------------------------------------------
//Count subarray sum equal to k

//Brut
int CntSubSumK(vector<int>& arr, int k){
    int cnt=0, sum;
    for(int i=0;i<arr.size();i++){
        sum=0;
        for(int j=i;j<arr.size();j++){
            sum+=arr[j];
            if(sum==k)
                cnt++;
        }
    }
    return cnt;
}
//TC - O(n^2), SC - O(1)

//The below u tried to apply sliding window to calculating count of subarrs having sum<=k but it went wrong only because for each l and r sum<=k u tried to do cnt++ but actually it was addition of length of subarr as the possible subarr without the already added by previous addition is r-l+1
//But it could be applied only to positive arrs 
int cntSubarrK(vector<int>& arr, int k){
    int l=0, r=0;
    int cnt=0, sum=0;
    while(r<arr.size()){
        sum+=arr[r];
        while(sum>k){
            sum-=arr[l];
            l++;
        }
        if(l<=r)
            cnt+=r-l+1;
        r++;
    }
    return cnt;
}

int cntSubEqK(vector<int>& arr, int k){
    cout<<cntSubarrK(arr, k)<<" "<<cntSubarrK(arr, k-1)<<endl;
    return (cntSubarrK(arr, k) - cntSubarrK(arr, k-1));
}
//TC - O(n + n), SC - O(1)

//For arrs with negative use prefix sum!
int cntSubArrSumK(vector<int>& arr, int k){
    unordered_map<int, int> pHash;
    int sum=0, cnt=0;
    pHash[0]=1;
    for(int i=0;i<arr.size();i++){
        sum+=arr[i];
        auto it = pHash.find(sum-k);
        if(it != pHash.end()){
            cnt += it->second;
        }
        pHash[sum]++;
    }
    return cnt;
}
//TC - O(n) {O(n^2) use map for O(nlogn) average}, SC - O(n){worst n uniq prefix sum}

//-----------------------------------------------------------------------------------------------------------------------------


int main(){
    //1.
    // vector<vector<int>> mat = {
    //     {1, 1, 1, 1},
    //     {1, 0, 0, 1},
    //     {1, 1, 0, 1},
    //     {1, 1, 1, 1}
    // };

    // setMatrixZrsOpt(mat);

    // for(auto v:mat){
    //     for(auto i:v){
    //         cout<<i<<" ";
    //     }
    //     cout<<endl;
    // }
    //---------------------------
    //2.
    // vector<vector<int>> mat = {
    // {1,  2,  3,  4},
    // {5,  6,  7,  8},
    // {9,  10, 11, 12},
    // {13, 14, 15, 16}
    // };
    // RotatematOpt(mat);
    // for(auto v:mat){
    //     for(auto i:v){
    //         cout<<i<<" ";
    //     }
    //     cout<<endl;
    // }
    //---------------------------
    //3.
    // vector<vector<int>> mat = {
    // {1,  2,  3,  4,  5,  6},
    // {20, 21, 22, 23, 24, 7},
    // {19, 32, 33, 34, 25, 8},
    // {18, 31, 36, 35, 26, 9},
    // {17, 30, 29, 28, 27, 10},
    // {16, 15, 14, 13, 12, 11}
    // };

//     vector<vector<int>> mat = {
//     {1,  2,  3,  4,  5},
//     {16, 17, 18, 19, 6},
//     {15, 24, 25, 20, 7},
//     {14, 23, 22, 21, 8},
//     {13, 12, 11, 10, 9}
// };

//     vector<vector<int>> mat = {
//     {1,  2,  3,  4,  5,  6,  7},
//     {24, 25, 26, 27, 28, 29, 8},
//     {23, 40, 41, 42, 43, 30, 9},
//     {22, 39, 48, 49, 44, 31, 10},
//     {21, 38, 47, 46, 45, 32, 11},
//     {20, 37, 36, 35, 34, 33, 12},
//     {19, 18, 17, 16, 15, 14, 13}
// };

    // noobSpiralTraverse(mat);

    //-------------------------------------------------
    //4.
    vector<int> arr={1,2,1,3};
    cout<<cntSubArrSumK(arr, 3);



    return 0;
}