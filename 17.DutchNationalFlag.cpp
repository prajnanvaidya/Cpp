//Sort an array of 0's, 1's and 2's
#include<bits/stdc++.h>
using namespace std;

//Ex: [0 1 2 0 1 2 1 2 0 0 0 1] -> 0 0 0 0 0 1 1 1 1 2 2 2
//Brute - use any quick or merge sort
//Merge sort
void merge(vector<int> &a, int low, int mid, int high){
    int i=low, j=mid+1, k=0;
    vector<int> temp(high+1);
    while(i<mid+1 && j<high+1){
        if(a[i]<a[j]){
            temp[k++]=a[i];
            i++;
        }
        else{
            temp[k++]=a[j];
            j++;
        }
    }

    while(i<mid+1){
        temp[k++]=a[i];
        i++;
    }
    while(j<high+1){
        temp[k++]=a[j];
        j++;
    }

    for(int m=low;m<high+1;m++){
        a[m]=temp[m-low];
    }
}


void mergeSort(vector<int> &a, int low, int  high){
    if(low>=high)
        return;
    int mid = (low+high)/2;
    mergeSort(a, low, mid);
    mergeSort(a, mid+1, high);
    merge(a, low, mid, high);
}
//TC: O(nlogn) - for any case , SC: O(n) for temp
//Dry run:
// Step1: 
// mergeSort:
//     a - 2 0 1 2
//     low=0, high=3
//     mid=1
//     mergeSort(a, 0, 1)

// Step2: 
// mergeSort:
//     a - 2 0
//     low=0, high=1
//     mid=0
//     mergeSort(a, 0, 0)

// Step3:
// mergeSort:
//     a - 2
//     if: low=high
//     return - contrl to Step2

// Step 2 - continued
// mergeSort:
//     mergeSort(a, 1, 1)

// Step4:
// mergeSort:
//     a-0
//     if: low=high
//     return - control to step2

// Step2 - continued
// mergeSort:
//     merge(a, 0, 0, 1)

// Step5:
// merge:
//     a-2 0
//     low=0, high=1, mid=0
//     i=0, j=1, k=0
//     temp - 0 0
//     loop: i<1 and j<2
//         else: a[0]>a[1]
//             temp[0]=0
//             j=2
//     loop: i<1 and j=2
//     loop: i<1
//         temp[1]=2
//         i++
//     loop: i=1
//     temp - 0 2
//     loop: i=0, i<2
//         a[0]=temp[0]
//         a - 0
//     loop: i=1, i<2
//         a[1]=temp[1]
//         a - 0 2

//quick sort
int partition(vector<int> &a, int low, int high){
    int pivot=a[low];
    int i=low, j=high;
    while(i<j){
        while(i<=high && a[i]<=pivot){
            i++;
        }
        while(j>=low && a[j]>pivot){
            j--;
        }
        if(i<j)
            swap(a[i], a[j]);
    }
    swap(a[low], a[j]);
    return j;
}

void quickSort(vector<int> &a, int low, int high){
    if(low>=high)
        return;
    int pivot=partition(a, low, high);
    quickSort(a, low, pivot-1);
    quickSort(a, pivot+1, high);
}
//TC: O(nlogn) - for best and avg case, for worrst case - O(n^2), SC: O(1)


//better: using hashMap:
void SortHash(vector<int> &a, int n){
    map<int, int> mpp;
    for(int i=0;i<n;i++){
        if(a[i]==0){
            if(mpp.find(a[i])!=mpp.end())
                mpp[a[i]]++;
            else
                mpp[a[i]]=1;
        }
        else if(a[i]==1){
            if(mpp.find(a[i])!=mpp.end())
                mpp[a[i]]++;
            else
                mpp[a[i]]=1;
        }
        else{
            if(mpp.find(a[i])!=mpp.end())
                mpp[a[i]]++;
            else
                mpp[a[i]]=1;
        }
    }
    int k=0, m=0;
    while(k<mpp[0]){
        a[k++]=0;
    }

    while(m<mpp[1]){
        a[k++]=1;
        m++;
    }

    m=0;
    while(m<mpp[2]){
        a[k++]=2;
        m++;
    }
}
//TC: O(nlogn + n), SC: O(n)


//U could also do it using 3 variables rather than map
void SortVar(vector<int> &a, int n){
    int cnt0=0, cnt1=0, cnt2=0;
    for(int i=0;i<n;i++){
        if(a[i]==0){
            cnt0++;
        }
        else if(a[i]==1){
            cnt1++;
        }
        else{
            cnt2++;
        }
    }

    int k=0;
    for(int i=0;i<cnt0;i++)
        a[k++]=0;
    for(int i=0;i<cnt1;i++)
        a[k++]=1;
    for(int i=0;i<cnt2;i++)
        a[k++]=2;
}
//TC:O(n + n), SC:O(1)

//Optimal
//Dutch national flag algorithm
//Uses 3 pointer
//low, mid and high

//3 rules to follow
//1.between 0 to low-1 --> everything is 0
//2.between low to mid-1 --> everything is 1
//3.between mid to high --> has 0 or 1 or 2 unsorted 
//4.between high+1 to n-1 --> everything is 2

// 0 - (low-1)       -> 0
// low - (mid-1)     -> 1
// mid - high        -> unsorted
// (high+1) - (n-1)  -> 2

//Initially arr is unsorted so index(0)=mid and index(n-1)=high, index(0)=low


//diagramatic representation
// 0......(low-1) low......(mid-1) mid.......high (high+1)......(n-1) 
// 0 0 0 0 0 0     1 1 1 1 1 1      unsorted arr       2 2 2 2 2 2


// Ex:
// low
// 0 1 1 0 1 2 1 2 0 0 0
//mid                  high

//If a[mid]=0, 
// swap(a[mid], a[low])
// low++; , mid++;

//if a[mid]=1
// mid++

//if a[mid]=2
// swap(a[mid], a[high])
// high--;

//Dry run based on rule:
// 0 1 1 0 1 2 1 2 0 0 0
//    0 1 2 3 4 5 6 7 8 9 10
// low=0, mid=0, high=10
// Step 1: 
//     a[mid]=0
//     swap(a[mid], a[low]) - 0 1 1 0 1 2 1 2 0 0 0
//     mid++, mid=1
//     low++, low=1
// Step2: 
//     a[mid]=1
//     mid++,mid=2
// Step3: 
//     a[mid]=1
//     mid++, mid=3
// Step4:
//     a[mid]=0
//     swap(a[mid], a[low]) - 0 0 1 1 1 2 1 2 0 0 0
//     mid++, mid=4
//     low++, low=2
// Step5:
//     a[mid]=1
//     mid++, mid=5
// Step6:
//     a[mid]=2
//     swap(a[mid], a[high]) - 0 0 1 1 1 0 1 2 0 0 2
//     high--, high=9
// Step6:
//     a[mid]=0
//     swap(a[mid], a[low]) - 0 0 0 1 1 1 1 2 0 0 2
//     mid++, mid=6
//     low++, low=3
// Step7:
//     a[mid]=1
//     mid++, mid=7
// Step8:
//     a[mid]=2
//     swap(a[mid], a[high]) - 0 0 0 1 1 1 1 0 0 2 2
//     high--, high=8
// Step9: 
//     a[mid]=0
//     swap(a[mid], a[low]) - 0 0 0 0 1 1 1 1 0 2 2 
//     mid++, mid=8
//     low++, low=4
// Step10:
//     a[mid]=0
//     swap(a[mid], a[low]) - 0 0 0 0 0 1 1 1 1 2 2
//     mid++, mid=9
//     low++, low=5
// mid>high - stop
// final - 0 0 0 0 0 1 1 1 1 2 2

void SortDutchOptimal(vector<int> &a, int n){
    int low=0, mid=0, high=(n-1);
    while(mid<=high){
        if(a[mid]==0){
            swap(a[mid], a[low]);
            low++;
            mid++;
        }
        else if(a[mid]==1){
            mid++;
        }
        else{
            swap(a[mid], a[high]);
            high--;
        }
    }
}
//TC: nearly - O(n), SC: O(1) 


//Dry run
// 2 0 1 2
// 0 1 2 3
// mid=0, low=0, high=3
// loop: mid<high
//     a[mid]=2
//     swap(a[mid], a[high]) - 2 0 1 2
//     high--; high=2
// loop: mid<high
//     a[mid]=2
//     swap(a[mid], a[high]) - 1 0 2 2
//     high--, high=1
// loop: mid<high
//     a[mid]=1
//     mid++, mid=1
// loop: mid=high
//     a[mid]=0
//     swap(a[mid], a[low]) - 0 1 2 2 
//     low++, low=1
//     mid++, mid=2
// loop: mid>high - stop
// final - 0 1 2 2 




int main(){
    int n, elem;
    cin>>n;
    vector<int> a;
    for(int i=0;i<n;i++){
        cin>>elem;
        a.push_back(elem);
    }
    SortDutchOptimal(a, n);
    for(auto v:a){
        cout<<v<<" ";
    }
    cout<<endl;
}