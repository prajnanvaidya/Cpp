#include<bits/stdc++.h>

using namespace std;

//Binary Search
// A searching algo in limited search space - taking O(logn) time to search any key in an arr
// Real life example: A dictionary: find word giraffe, one way is to go page by page until u find the word(Linear), smarter way: as dict is sorted based on Chars can trim down the serach space if random page opened is starting with F then only next part can have Giraffe not previous

//Iterative
void binarySearch(vector<int>& arr, int key){
    if(arr.size() == 0){
        cout<<"Empty Arr"<<endl;
        return;
    }
    int low = 0;
    int high = arr.size()-1;
    int mid;
    while(low <= high){
        mid = low + (high-low)/2;
        if(arr[mid] == key){
            cout<<"Eureka at index: "<<mid<<endl;
            break;
        }
        else if(key < arr[mid]){
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
}

//Recursive:
void binarySearchRecVoid(vector<int>& arr, int key, int low, int high){
    if(low>high){
        cout<<-1;
        return;
    }

    int mid = low + (high-low)/2;

    if(arr[mid] == key){
        cout<<mid;
        return;
    }
    else if(key < arr[mid]){
        binarySearchRecVoid(arr, key, low, mid-1);
    }
    else{
        binarySearchRecVoid(arr, key, mid+1, high);
    }
}

int binarySearchRec(vector<int>& arr, int key, int low, int high){
    if(low>high)
        return -1;

    int mid = low + (high-low)/2;

    if(arr[mid] == key){
        return mid;
    }
    else if(key < arr[mid]){
        return binarySearchRec(arr, key, low, mid-1);
    }
    else{
        return binarySearchRec(arr, key, mid+1, high);
    }
}
//Tc - o(logn), Sc - O(logn)

//Overflow case: A arr can have max of 10^7 not more but imagine we have to apply binary search to some other object say dictionary or even if the arr has INT_MAX number of elements and the search space trims down to only last elem then (low+high)/2 will lead integer overflow so the result will wrap up to negative in that case and mid will be negative so gives arr out of bound error
// So inorder to avoid it use
// mid = low + (high-low)/2; here high - low will not exceed and in our case this comes down to 0 so no problem

//Lower Bound: smallest index such that arr[index]>=x
//[3, 5, 8, 15, 19], n=9
//res = 3
int lowerBound(vector<int>& arr, int n){
    for(int i=0;i<arr.size();i++){
        if(arr[i]>=n){
            return i;
        }
    }
    return -1;
}
//Tc - O(n), Sc - O(1)

int lowerBoundOpt(vector<int>& arr, int n){
    int low=0, high = arr.size()-1;
    int mid, temp=INT_MAX;
    while(low<=high){
        mid = low + (high-low)/2;
        if(arr[mid] == n){
            return mid;
        }
        else if(arr[mid]>n){
            temp = arr[mid];
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    if(temp == INT_MAX)
        return -1;
    return temp;
}
//Tc - o(n)


int lowerBoundOptHis(vector<int>& arr, int x){
    int low=0, high=arr.size()-1;
    int ans=arr.size(), mid;
    while(low<=high){
        mid = low + (high-low)/2;
        if(arr[mid]>=x){
            ans=mid;
            high=mid-1;
        }
        else{
            low = mid+1;
        }
    }
    return ans;
}
//Tc - O(logn), Sc - O(1)

//In cpp we have direct method named lower_bound(arr.begin(), arr.end(), x) it results the iterator to that location, to find index subtract it with arr.begin()

//-------------------------------------------------------------------------------------------------
//Upper bound: The smallest index such that arr[index]>x

int upperBoundOpt(vector<int>& arr, int x){
    int low=0, high=arr.size()-1;
    int mid;
    int ans = arr.size(); //If no upper bound then result len of arr
    while(low<=high){
        mid=low+ (high-low)/2;
        if(arr[mid]>x){
            ans = mid;
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    return ans;
}
//--------------------------------------------------------------

//Search index of elem to insert
// You are given a sorted array arr of distinct values and a target value m. 
// You need to search for the index of the target value in the array.

// If the value is present in the array, then return its index.
// If the value is not present, determine the index where it would be inserted in the array while maintaining the sorted order.

// Ex: [1, 2, 4, 7], m=6, res=3

//Same as lower bound 

//---------------------------------------

//Floor and ciel in sorted arr
// Floor - Largest no in arr <= x, Ciel - smallest no in arr >= x

// Floor - upper_result - 1, Ciel - lower Bound 

int floorOpt(vector<int>& arr, int m){
    int low = 0, high = arr.size()-1;
    int mid;
    int ans = -1;
    while(low<=high){
        mid = low + (high-low)/2;
        if(arr[mid] <= m){
            ans = arr[mid];
            low = mid+1;
        }
        else{
            high = mid-1;
        }
    }
    return ans;
}

//----------------------------------------------------------------------------------------------------------------------

//First and Last occurences of x
//arr = [2, 4, 6, 8, 8, 8, 11, 13], x=8
// res = {3,5}

auto FirstLastOcc(vector<int>& arr, int x){
    int f=-1, l=-1;
    for(int i=0;i<arr.size();i++){
        if(arr[i] == x && f==-1){
            f=i;
            l=i;
        }
        else if(arr[i]==x){
            l=i;
        }
    }
    return make_pair(f, l);
}
//Tc - O(n), Sc - o(1)

auto FirstLastOccOpt(vector<int>& arr, int x){
    int low = 0, high = arr.size();
    int mid;
    int f=-1, l=-1;
    while(low<=high){
        mid = low + (high-low)/2;
        if(arr[mid] == x){
            f=mid;
            high = mid-1;
        }
        else if(arr[mid] < x){
            low = mid+1;
        }
        else{
            high = mid-1;
        }
    }

    if(f!=-1){
        low = 0, high = arr.size();
        while(low<=high){
            mid = low + (high-low)/2;
            if(arr[mid]==x){
                l=mid;
                low = mid+1;
            }
            else if(arr[mid] > x){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
    }
    
    return make_pair(f, l);
}
//O(2logn), Sc - o(1)

//Using Lower Bound and upper bound
//lower bound - smallest index>=x, upper bound - smallest index>x
// So first occurence = lower bound, last occurence = upper bound-1

auto FirstLastOccOptHis(vector<int>& arr, int x){
    int f = lowerBoundOptHis(arr, x);
    int l = upperBoundOpt(arr, x)-1;

    if(f==arr.size() || arr[f]!=x){
        f=-1;
    }
    if(l==arr.size() || arr[l]!=x){
        l=-1;
    }
    return make_pair(f, l);
}

//-----------------------------------------------------------------------------------------------

//Count occurences of a no in a sorted arr with duplicates
//Ex: arr - [1, 1, 1, 2, 2, 3, 3], x=3
// res = 2

int CountOcc(vector<int>& arr, int x){
    int cnt=0;
    for(int i=0;i<arr.size();i++){
        if(arr[i] == x)
            cnt++;
    }
    return cnt;
}
//Tc - O(n), Sc - O(1)

//Using Binary search
int CountOccBinary(vector<int>& arr, int x){
    int low=0, high=arr.size()-1;
    int f=-1, l=-1;
    int mid;
    while(low<=high){
        mid = low + (high-low)/2;
        if(arr[mid] == x){
            f=mid;
            high=mid-1;
        }
        else if(arr[mid]<x){
            low = mid+1;
        }
        else{
            high=mid-1;
        }
    }

    if(f != -1){
        low=0, high=arr.size()-1;
        while(low<=high){
            mid = low+(high-low)/2;
            if(arr[mid] == x){
                l=mid;
                low=mid+1;
            }
            else if(arr[mid]>x){
                high = mid-1;
            }
            else{
                low=mid+1;
            }
        }
        return l-f+1;
    }
    else{
        return 0;
    }
}
//Tc - o(2logn), Sc - O(1)

//-----------------------------------------------------------------------------------------------

//Search in rotated sorted arr - 1 {arr ill have unique elements}

// Rotated sorted arr - consider a sorted arr as [1,2,3,4,5] now rotating it at element 4 will result in - [4,5,1,2,3]

//Ex: [7,8,9,1,2,3,4,5,6] target=1, res=3
//Brute - use linear search taking O(n) time

int SearchRotSortArr(vector<int>& arr, int target){
    int l, f;
    int i=1;
    while(i<arr.size()){
        if(arr[i-1]>arr[i]){
            f = i;
            l=i-1;
            break;
        }
        i++;
    }
    int low = 0, high=arr.size()-1, mid;
    while(low<=high){
        mid = low + (high-low)/2;

        cout<<"low: "<<low<<", "<<"high: "<<high<<" mid: "<<mid<<endl;
        if(arr[mid] == target){
            return mid;
        }
        else if(target < arr[mid]){
            if(mid >= f){
                if(arr[f] <= target){
                    high = mid-1;
                }
                else{
                    break;
                }
            }
            else if(mid <= l){
                if(arr[0]<=target)
                    high = mid-1;
                else
                    low=mid+1;
            }
        }
        else{
            if(mid >= f){
                if(target <= arr[arr.size()-1]){
                    low = mid+1;
                }
                else{
                    high = mid-1;
                }
            }
            else if(mid <= l){
                if(arr[l]>=target){
                    low=mid+1;
                }
                else{
                    break;
                }
            }
        }
    }
    return -1;
}
//Too much complex
//Tc - O(n + logn)

int SearchRotSortArrOpt(vector<int>& arr, int target){
    int low=0, high=arr.size()-1;
    int mid;
    while(low<=high){
        mid = low + (high-low)/2;
        if(arr[mid] == target) return mid;

        //We check for ascendingly sorted half inorder to check whether target lies there or not if a part is not sorted then we cannot check whether target lies or not 
        else if(arr[low] <= arr[mid]){ //Checking wheteher left half is sorted in ascending order
            if(arr[low] <= target && arr[mid]>target){ //If left sorted checking if target lies in left half
                high = mid-1;
            } 
            else{
                low = mid+1;
            }
        }
        else{   //Means right half is sorted in ascending order
            if(arr[mid] < target && arr[high] >= target){ //Means target lies in that right half of sorted stuff
                low = mid+1;
            }
            else{            //if target doesnt lies
                high = mid-1;
            }
        }
    }
    return -1;
}
//Tc - O(logn), Sc - O(1)

//-----------------------------------------------------------------------------------------------
//Search in rotated sorted arr - 2
//Here arr may also contain duplicates
// Return bool 0/1 as returning index is not possible with binary search for that use linear search itself

//So only condition where problem arises is in ex:
// 0 1 2 3 4 5
// 3,1,2,3,3,3

// So when arr[low]=arr[mid]=arr[high] condition satisfies then it means we cannot figure out whether the left portion or right portion is sorted which can eventually lead choosing of wrong half
// Inorder to avoid it before checking which half is sorted we need to check for this condition if it satisfies trim the search space that is to do low++ and high--

bool SearchRotSortArrOpt2(vector<int>& arr, int target){
    if(arr.size() == 0){
        return false;
    }
    int low = 0, high = arr.size()-1, mid;
    while(low<=high){
        mid = low + (high-low)/2;
        if(arr[mid] == target){
            return true;
        }
        else if(arr[mid] == arr[low] && arr[mid] == arr[high]){
            low++;
            high--;
            continue;
        }
        else if(arr[mid]>=arr[low]){
            if(target<arr[mid] && target>=arr[low]){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        else{
            if(target>arr[mid] && target<=arr[high]){
                low = mid+1;
            }
            else{
                high = mid-1;
            }
        }
    }
    return false;
}
//Tc - O(logn) - average, in worst case - O(n/2) for ex: [3, 3, 1, 3, 3, 3, 3] here when low=0, high=6, 1st call: low=0, high=6; 2nd call: low=1, high=5; 3rd call: low=2, high=4, 4th call: actual trimming half happens, So it takes n/2 rather then logn+1

//-----------------------------------------------------------------------------------------------
//Minimum in Rotated sorted arr
//Given a rotated sorted arr find which has only unique elems, find index


// ex: 4 5 6 0 1 2 
// The normal way of doing binary search on rotated arr questions how to or where to go once sorted half found as we are not searching anything we need to find something that fills this gap about choosing what half to drop
// And the answer lies in the ability to find minimum directly from 1 half and it is sorted half for sure as we know if left half is sorted then the first elem is minimum and if the right half is sorted then the current elem is minimum
// So we now know which half to discard and that is sorted half for sure once updating the minimum
// 0 1 2 3 4 5
// 4 5 6 0 1 2
// -> low=0, high=5, min=Int_max
//    mid= 2, left half sorted as arr[low]<=arr[mid] and arr[mid]>arr[high]
//    So min = arr[low] = 4, low = mid+1 = 3

// ->  low=3, high = 5
//     mid=4, arr[mid]>arr[low], we consider left half sorted as its checked first, 
//     So min=arr[low]=0, low=5

// ->  low=5, high=5, min=0
//     mid = 5, left half as arr[low]<=arr[mid]
//     So mid = arr[low] = 2 but min=0, low=6

int MInimumRotArr(vector<int>& arr){
    int low=0, high = arr.size()-1;
    int mid, mini=INT_MAX;

    while(low <= high){
        mid=low+(high-low)/2;
        if(arr[low]<=arr[mid]){
            mini = min(mini, arr[low]);
            low=mid+1;
        }
        else{
            mini = min(mini, arr[mid]);
            high=mid-1;
        }
    }
    return mini;
}
//TC - O(logn), Sc - O(1)

//A small optimization - if we come accross the low and high where both left and right half were sorted then it means the rotated stuff has completely finished and we are remaining with only unbrotated stuff that means the minimum left out is only arr[low] to compare


int MinimumRotArr(vector<int>& arr){
    int low=0, high = arr.size()-1;
    int mid, mini=INT_MAX;

    while(low <= high){
        mid=low+(high-low)/2;
        if(arr[low]<=arr[high]){
            mini = min(mini, arr[low]);
            break;
        }
        if(arr[low]<=arr[mid]){
            mini = min(mini, arr[low]);
            low=mid+1;
        }
        else{
            mini = min(mini, arr[mid]);
            high=mid-1;
        }
    }
    return mini;
}


//-----------------------------------------------------------------------------------------------
//Find minimum in rotated sorted arr containing duplicates
int MinimumRotSortDup(vector<int>& arr){
    int low=0, high=arr.size()-1;
    int mid, mini=INT_MAX;

    while(low<=high){
        mid = low + (high-low)/2;

        if(arr[mid] == arr[low] && arr[mid] == arr[high]){
            low++;
            high--;
            continue;
        }
        else if(arr[mid] >= arr[low]){
            mini = min(mini, arr[low]);
            low=mid+1;
        }
        else{
            mini = min(mini, arr[mid]);
            high=mid-1;
        }
    }
    return mini;
}
//TC - O(n/2) in worst case on average - O(logn), Sc - O(1)

//-----------------------------------------------------------------------------------------------

//Count the number of times a arr is rotated which will have unique elements
//Ex: [3, 4, 5, 1, 2]
// res=3

//Brut - check until arr[i-1]>arr[i] and each time condition false do cnt++ and once true break
int CountNoRot(vector<int>& arr){
    int cnt=1;
    for(int i=1;i<arr.size();i++){
        if(arr[i-1]<=arr[i]) cnt++;
        else{
            break;
        }
    }
    if(cnt == arr.size()) return 0;

    return cnt;
}
//TC - O(n), Sc - O(1)

//Using binary search
//apparently track the minimum elements index and that would be the answer for no of rotation
int CountNoRotBin(vector<int>& arr){
    int min_id=0;
    int low=0, high=arr.size()-1;
    int mid;

    while(low<=high){
        mid = low + (high-low)/2;
        if(arr[low]<=arr[high]){
            if(arr[min_id]>=arr[low])
                min_id = low;
            break;
        }
        else if(arr[mid]>=arr[low]){
            if(arr[min_id]>=arr[low])
                min_id = low;
            low=mid+1;
        }
        else{
            if(arr[min_id]>=arr[mid])
                min_id=mid;
            high = mid-1;
        }
    }
    return min_id;
}

//-----------------------------------------------------------------------------------------------

//Count no of rotation in a arr with duplicates
//Anywhere comes duplicate and rotated sorted arr think its talking about the condition that makes unable to select which half is sorted is it left or right? in rotated sorted arr the only solution is to trim the left and right half by 1 each time it occurs, But also in normal sorted arr this occurs all time as u go so that takes n/2 time to loop and finally come out with nothing in hand
int CountNoRotDup(vector<int>& arr){
    if(arr.size()==0) return 0;

    int min_index=0;
    int low=0, high=arr.size()-1;
    int mid;
    while(low<=high){
        mid = low + (high-low)/2;
        if(arr[low]==arr[mid] && arr[mid]==arr[high]){
            low++;
            high--;
            continue;
        }
        else if(arr[low] <= arr[high]){
            if(arr[min_index] >= arr[low]) min_index=low;
            break;
        }
        else if(arr[mid]>=arr[low]){
            if(arr[min_index] > arr[low])
                min_index=low;
            low=mid+1;
        }
        else{
            if(arr[min_index] > arr[mid])
                min_index = mid;
            high=mid-1;
        }
    }
    return min_index;
}
//TC - O(n/2)-worst, O(logn)-average, Sc - O(1)

//-----------------------------------------------------------------------------------------------

//Finding single element in a sorted arr
// Given an arr all nos will appear twice except 1 number 

//Ex: [1,1,2,2,3,3,4,5,5,6,6], res=4

// Brut: Loop through arr start from id 1 and check if previous and current are same if not return that elem thats all
int SingleElemArr(vector<int>& arr){
    for(int i=1;i<arr.size();i+=2){
        if(arr[i-1] == arr[i]){
            continue;
        } 
        else{
            return arr[i-1];
        }
    }
    return -1;
}
//Tc - O(n), Sc - O(1)

//His brut is simpler as he naively check both sides of a index for repeatation if not found considers that as the answer
int SingleElemSortedArrBrutHis(vector<int>& arr){
    for(int i=0;i<arr.size();i++){
        if(i==0){
            if(arr[i] != arr[i+1]) return arr[i];
        }
        else if(i==arr.size()-1)
            if(arr[i] != arr[i-1]) return arr[i];
        else{
            if(arr[i] != arr[i-1] && arr[i] != arr[i+1]) return arr[i];
        }
    }
    return -1;

}



// Optimal stands on the fact that any elems first occurenbce comes on even index and second occurence comes on odd index until a elements duplicate is chopped and those pairs appearing on its right side will have opposite that is first occurence on odd index and second occurence on even index
//By making use of this fact every time i check mid is on odd or even index if on even index then check is it first or second occurence and if its first occurence then drop the left half otherwise drop right half, and if mid is on odd index then check if its 2nd occurence then drop left half otherwise drop right half

int SingleElemSortedArrOpt(vector<int>& arr){
    if(arr.size()==0)
        return -1;
    int low=0, high=arr.size()-1;
    int mid;
    while(low<=high){
        mid = low+(high-low)/2;
        if(mid%2 == 0){
            if( (mid+1)<arr.size() && arr[mid]==arr[mid+1]){
                low=mid+2;
            }
            else if( (mid-1)>0 && arr[mid-1] == arr[mid]){
                high=mid-2;
            }
            else{
                return arr[mid];
            }
        }
        else{
            if( (mid-1)>=0 && arr[mid] == arr[mid-1]){
                low = mid+1;
            }
            else if( (mid+1)<arr.size() && arr[mid] == arr[mid+1]){
                high = mid-1;
            }
            else{
                return arr[mid];
            }
        }
    }
    return -1;
}
//Tc - O(logn), Sc - o(1)


//Same logic but cleaner code
int SingleElemSortedArrOptHis(vector<int>& arr){
    int low=1, high=arr.size()-2;
    int mid;
    
    if(arr.size()==0) return -1;
    else if(arr.size()==1) return arr[1];

    else if(arr[0] != arr[1]) return arr[0];

    else if(arr[arr.size()-1] != arr[arr.size()-2]) return arr[arr.size()-1];

    while(low<=high){
        mid = low + (high-low)/2;

        if(arr[mid] != arr[mid-1] && arr[mid] != arr[mid+1]){
            return arr[mid];
        }
        else if( (mid%2 == 0 && arr[mid]==arr[mid+1]) || (mid%2 == 1 && arr[mid]==arr[mid-1]) )
            low = mid+1;
        else
            high = mid-1;
    }
    return -1;
}
//-----------------------------------------------------------------------------------------------

//Find Peak element in an arr: arr[i-1] < arr[i] > arr[i+1]
// 1 2 3 4 5 6 7 8 5 1, res=8
// 1 2 1 3 5 6 4, res=2
// 1 2 3 4 5, res != -1 here at ends to make elems check for Peak/not we should assume that behind first elem there exist -infinity and after last elem there exist -infinity, based on that assumption
//So res=5
// 5 4 2 3 1, res=3

//Brut loop through and if condition satisfied return
int findPeak(vector<int>& arr){
    for(int i=0;i<arr.size();i++){
        if(i==0){
            if(arr[i]>arr[i+1])
                return arr[i];
        }
        
        else if(i==(arr.size()-1)){
            if(arr[i]>arr[i-1])
                return arr[i];
        }
        
        else if(arr[i] > arr[i-1] && arr[i] > arr[i+1]){
            return arr[i];
        }
    }
    return -1;
}
//TC - O(n), Sc - O(1)

int findPeakBrutHis(vector<int>& arr){
    for(int i=0;i<arr.size();i++){
        if( (i==0 || arr[i]>arr[i-1]) && (i==arr.size()-1 || arr[i]>arr[i+1]) ){
            return arr[i];
        }
    }
    return -1;
}


//Using binary search
//Observation is crucial 

//First we code considering that there exist only 1 peak
// See the graph of elems in arr, all arrs having 1 peak shows they follow a mountain shape

/*
|
|       /\
|      /  \
|     /    \
|    /      \
|   /        \
|  /          \
| /            \
|_________________
*/
//Based on this u can devise when to drop which part, So when mid is on increasing slope then go on right and if its on decreasing slope then go on left
// To check slope:
// increasing - arr[mid]<arr[mid+1]
// decreasing - arr[mid]>arr[mid+1]

// Now u can come up with example as below to counter:
// [1, 10, 13, 12, 14, 15, 16, 17, 18, 19]
// Here u see first slope increases and once peak came a one elem decrease and again go on increase, But for ur disgrace i tell u this example has 2 peaks 
// Man where: 1 at 13 as u know, other at 19 cuz of condition the beforehand and afterhand of arr there exist -infinity 
// So currently we are not solving it

int find1PeakOpt(vector<int>& arr){
    if(arr.size()==0){
        return -1;
    }

    else if(arr.size()==1 ) return arr[0];

    else if(arr[(arr.size()-1)]>arr[arr.size()-2]) return arr[arr.size()-1];

    else if(arr[0] > arr[1]) return arr[0];

    int low=1, high=arr.size()-2, mid;
    while(low<=high){
        mid = low + (high-low)/2;
        if(arr[mid]>arr[mid-1] && arr[mid]>arr[mid+1]) return arr[mid];

        else if(arr[mid]<arr[mid+1]) low=mid+1;

        else if(arr[mid]<arr[mid-1]) high=mid-1;
    }
    return -1;
}
//TC - O(logn), Sc - o(1)

//Multiple peaks 
//the above code also works but returns any of the peak of all

//One edge case where it fails, falls to infinite loop when low and high both points to peak elems for example
// 1 5 1 2 1
// low=1, high=3, arr[2]<arr[low], arr[2]<arr[high] so not peak, not falls on decreasing as arr[mid] < arr[mid+1], not on increasing arr[mid] < arr[mid-1]

int findMultiplePeak(vector<int>& arr){
    if(arr.size()==0) return 0;

    else if(arr.size()==1) return arr[0];

    int low=1, high=arr.size()-2;
    int mid;
    while(low<=high){
        mid = low + (high-low)/2;

        if(arr[mid]>arr[mid+1] && arr[mid]>arr[mid-1]) return arr[mid];

        else if(arr[mid] > arr[mid-1]){
            low=mid+1;
        }
        else if(arr[mid] > arr[mid+1]){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return -1;
}
//-----------------------------------------------------------------------------------------------

//Find the sqrt of an integer
// Ex: 25 - 5
// 30 - 5
// 35 -5
// 36 -6

int findSQRT(int x){
    int n;
    for(int i=0;i<=x;i++){
        if(i*i <= x) n=i;
        else if(i*i > x) break;
    }
    return n;
}
// O(sqrt(n)), Sc- O(1)

//Binary Search
long long findSqrtBin(long long x){
    if(x<0) return -1;
    
    else if(x==0) return 0;

    long long res=-1;
    long long low=1, high=x, mid;
    while(low<=high){
        mid = low + (high-low)/2;

        if(mid * mid == x) return mid;
        else if(mid*mid < x){
            res = mid;
            low=mid+1;
        } 
        else if(mid*mid > x){
            high=mid-1;
        } 
    }
    return res;
}
//O(logn), Sc - O(1)


//In any Binary Search problem the reality u do not need to maintain a ans or res variable to store intermediate results as if ur wish is to get the final answers then either high or low will be pointing to it at the end and in this case high will be pointing to square root
//Becausehigh starts with most not possible answer that is x and low starts with most possible answer and after binary search at the end, low is pointing to first not possible answer and high points last possible answer

//The same problem can be stated as find Largest integer which on squaring results <= x

//-----------------------------------------------------------------------------------------------

//Find the nth root of given integer m
// Ex: N=3, M=27, res=3
// N=4, M=69, res=-1 as nearest i 2^4 = 16, 3^4=81, so no 69


int NRootM(int n, int m){
    if(m==0) return 0;
    int inter;
    for(int i=1;i<=m;i++){
        inter=1;
        for(int j=0;j<n;j++){
            inter*=i;
        }
        cout<<i<<":"<<inter<<endl;
        if(inter == m)
            return i;
        else if(inter > m)
            break;
    }
    return -1;
}
//Tc - O(nroot(m)), Sc - o(1)

//Using Binary
int NRootMBin(int n, int m){
    if(m==0) return 0;
    int low=1, high=m, mid, inter;
    while(low<=high){
        mid = low+(high-low)/2;
        inter=1;
        for(int i=0;i<n;i++){
            inter*=mid;
        }
        if(inter==m) return mid;

        else if(inter < m) low=mid+1;

        else high=mid-1;
    }
    return -1;
}
//Tc - O(nlogm), Sc - O(1)
//The above fails in some test cases ex: when m=10^9 and n=10, now in first loop: low=1, high=10^9, mid ~ (10^9/2), So now inter=10^90 which is out of bound for sure, so tweak it to not go greater then 10^9

int func(int mid, int n, int m){
    long long ans=1;
    for(int i=0;i<n;i++){
        ans=ans*mid;
        if(ans > m) return 2;
    }
    if(ans < m) return 0;
    else if(ans == m) return 1;
    return -1;
}

//Using exponention to bring down time from O(n) to O(logn)

int funcExp(int mid, int n, int m){
    int ans=1;
    while(n>0){
        if(n%2==1){
            ans=ans*mid;
            n=n-1;
            if(ans>m) return 2;
        }
        else{
            mid = mid*mid;
            n/=2;
        }
    }
    if(ans < m) return 0;
    else if(ans == m) return 1;
    return -1;
}
//TC - O(logn)

int NRootMBinOpt(int n, int m){
    if(m==0) return 0;
    int low=1, high=m, interim, mid;
    while(low<=high){
        mid = low + (high-low)/2;
        interim = func(mid, n, m);
        if(interim == 1) return mid;
        else if(interim == 0) low=mid+1;
        else if(interim == 2) high=mid-1; 
    }
    return -1;
}
//Tc - O(logn * logm), Sc - O(1)
//-----------------------------------------------------------------------------------------------------------------------------

//Most awaited: Koko Eating Banana!!
// Koko is an indidual trying to eat Banana, we should help him to eat as much in less time

// Return the min integer k such that Koko can eat all bananas within h hours
// Given a arr of piles each elem represents the no of bananas to eat that pile has and h:the total hour Koko has
// Koko has at max of h hours u have to return k that is no of bananas eaten by Koko in a hour, So u should return minimum no of Bananas eaten by Koko in a hour given that it can complete all in h hours limit

//Ex: piles[] = {3, 6, 7, 11}, h=8

// Considering K=2, that is 2 bananas/hr
// 0:3 takes 2hrs {ciel value}
// 1:6 takes 3hrs
// 2:7 takes 4hrs
// 3:11 takes 6hrs
// total - 15 hrs which is greater then limit 8, So k greater then 2 for sure

// making k=4
// 0:3 takes 1hrs {ciel value}
// 1:6 takes 2hrs
// 2:7 takes 2hrs
// 3:11 takes 3hrs
// total - 8 hrs 


//Brut:Ok linear where end: Notice: the h should be minimum of size of the arr so at max the K should be max_element(arr) So we loop until max_element(arr) and each time check for time taken and comparing with h and the time when it comes out <=h break as we search for minimum, We start from 1

int timeTaken(vector<int>& arr, int k){
    int total=0;
    float inter;
    for(int i=0;i<arr.size();i++){
        inter = (float)arr[i]/k;
        if(inter > int(inter)){
          total += int(inter+1);  
        } 
        else{
            total += int(inter);
        } 
    }
    return total;
}

int KokoBanana(vector<int>& arr, int h){
    if(h<arr.size()) return -1;
    int maxi = *(max_element(arr.begin(), arr.end()));
    for(int i=1;i<=maxi;i++){
        if(timeTaken(arr, i)<=h) return i; 
    }
    return -1; //that means Koko cannot eat Bananas in h hours
}
//TC - O(n + max_elem * n) ~ O(max(arr)*n), Sc - O(1)

//Using Binary
//For sure low=1, high=max_elem(arr), if mid takes time<=h then return mid otherwise if mid takes time>h then low=mid+1;, time<h then store the mid and go high = mid-1
///Are u sure if a particular k takes time<h then all k less then that too takes time<h - YES

int KokoBananaBin(vector<int>& arr, int h){
    if(h < arr.size()) return -1;
    int low=1, high = *(max_element(arr.begin(), arr.end())), mid;
    int mini=high;
    int time;
    while(low<=high){
        mid = low+(high-low)/2;
        time = timeTaken(arr, mid); 
        if(time <= h){
            mini = min(mini, mid);
            high=mid-1;
        }
        else if(time > h) low=mid+1;
    }
    return mini;
}
//Ur intuition: u thought that 1 to max_elem(arr) shows a decreasing grph interms of time taken, as initially time taken is highest and then it decreases but yet less then h limit but after a point where time taken = h later k's the time taken go on decreases itself all lies below h, least time taken being = max_element(arr)

//Why Binary search works theres a pattern i.e:
// 3 6 7 11
// 1  2  3  4  5  6  7  8  9  10  11
// no no no s  s  s  s  s  s   s   s
// After the least k all comes s

int cielVal(int n, int m){
    float res = (float)n/m;
    if(res == (n/m)){
        return (n/m);
    }
    else if(res > (n/m)) return (n/m)+1;
    return -1;
}

int KokuaBananaKayega(vector<int>& arr, int hr){
    if(arr.size() == 0) return 0;
    else if(arr.size() == 1) return arr[0];

    if(hr < arr.size()) return -1;
    else if(hr == arr.size()) return *(max_element(arr.begin(), arr.end()));

    int l=1, h=*(max_element(arr.begin(), arr.end()));
    int min_bananas_per_hr=1;
    while(l<=h){
        int m=l+(h-l)/2;
        int tot_hrs = 0;
        for(int i=0;i<arr.size();i++){
            tot_hrs += cielVal(arr[i], m);
        }
        if(tot_hrs <= hr){
            min_bananas_per_hr = m;
            h=m-1;
        }
        else{
            l=m+1;
        }
    }
    return min_bananas_per_hr;
}

// Note: No need to maintain separate mini to return as low at the end points to the minimum k, why? - initially low points to 1 which is mostly not possible and high points to max_element(arr) which is most likely possible So after loop they end up being in opposite of what they are initially: low-least k, high-highest impossible k

//-----------------------------------------------------------------------------------------------------------------------------

//Minimum no of days to make M bouquets
// Given an arr where each element represents a flower and the value reps on which day it blooms
// For ex:  0  1  2  3   4   5   6  7
//         {7, 7, 7, 7, 13, 11, 12, 7} means the 3rd index flower blooms on day 7

// Also given with M - no of bouquets, K - adjacent fowers required{the no of contigous flower required to make a bouquet}

// -> So u need to find M: K contigous elems which all blooms within res no of days, u need to return minimum res

// For ex: 0  1  2  3   4   5   6  7
//         {7, 7, 7, 7, 13, 11, 12, 7}, M=2, K=3
//         if taken: deadline = 13 all flowers will be bloomed
//         0  1  2  3   4   5   6  7
//         {b, b, b, b, b, b, b, b} - then take any 3 consecutive elems twice: satisfies

//         if taken: deadline = 7
//         0  1  2  3   4   5   6  7
//         {b, b, b, b, 13, 11, 12, b} (0,1,2) but no other 3 consecutive to make 2nd bouquet as M=2: unsatisfied

//         if taken: deadline = 11
//         0  1  2  3   4   5   6  7
//         {b, b, b, b, 13, b, 12, b} (0, 1, 2) no other: unsatisfied

//         if taken deadline = 12
//         0  1  2  3   4   5   6  7
//         {b, b, b, b, 13, b, b, b} (0,1,2), (5,6,7) Now u have 2(M) bouquets each with 3(K) conseq flowers: satisfied

//         The possible deadlines: 13, 12
//         Min = 12 = result

auto removeDups(vector<int> arr){
    int n = arr.size();
    sort(arr.begin(), arr.end());
    int i=0, j=0;
    while(j<n){
        if(arr[j] != arr[i]){
            i++;
            arr[i] = arr[j];
        }
        j++;
    }
    arr.resize(i+1);
    return arr;
}

bool checkDeadline(int dead, vector<int>& arr, int m, int k){
    int cntFlower=0;
    int bouqComplete = 0, cntBouq=0;

    for(int i=0;i<arr.size();i++){
        if(arr[i] <= dead){
            cntFlower++;
            if(cntFlower == k){
                cntBouq++;
                cntFlower=0;
            }
        }
        else{
            cntFlower=0;
        }
    }
    if(cntBouq >= m){
        return true;
    }
    return false;
}

int minDaysBouquet(vector<int>& arr, int m, int k){
    if(arr.size() < k*m) return -1;
    int n=arr.size();

    vector<int> deads = removeDups(arr);
    int mini = *(max_element(arr.begin(), arr.end()));

    for(int i=0;i<deads.size();i++){
        if(checkDeadline(deads[i], arr, m, k)){
            mini = min(mini, deads[i]);
        }
    }
    return mini;
}
//TC - O(nlogn + n + n + m*n) {sort + loopToRem + resize + mUniqDeadline check} ~ O(nlogn + m*n), SC - O(m) m-uniq elems

//BrutHis
bool possible(int dead, vector<int>& arr, int m, int k){
    int n=arr.size();
    int cntBouq = 0, cntFlower=0;
    for(int i=0;i<n;i++){
        if(arr[i] <= dead){
            cntFlower++;
        }
        else{
            cntBouq += (cntFlower/k);
            cntFlower = 0;
        }
    }
    cntBouq += (cntFlower/k);
    if(cntBouq >= m) return true;
    return false; 
}

int minDaysBrutHis(vector<int>& arr, int m, int k){
    if(arr.size() < (long)k*m) return -1;
    int n=arr.size();
    int mini = *(min_element(arr.begin(), arr.end()));
    int maxi = *(max_element(arr.begin(), arr.end()));

    for(int i=mini;i<=maxi;i++){
        if(possible(i, arr, m, k)){
            return i;
        }
    }
    return -1;
}

//Binary search using

int minDaysBin(vector<int>& arr, int m, int k){
    if(arr.size() < k*m) return -1;

    int n=arr.size();
    int low = *(min_element(arr.begin(), arr.end()));
    int high = *(max_element(arr.begin(), arr.end()));

    while(low <= high){
        int mid = low + (high-low)/2;
        if(possible(mid, arr, m, k)){
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    return low;
}
//low points to result i.e minimum days in which the whole m bouquet with k flower will bloom cuz initially low points to least possible that is minimum of all arr elems and high opoints to most possible i.e max of all arr elems and at the end the low points to possible answer whereas high points to not possible answer i.e max days until which m bouquet with k flower will not bloom

//TC - O(log(max-min+1) * n), SC - O(1)

//-----------------------------------------------------------------------------------------------------------------------------

//Find the smallest divisor given a threshold value

// Given an arr and a threshold:
// Return min divisor that gives ciel vals with arr elemes total less then threshold
// Ex: {1,2,5,9} thr = 6
// consider divisor = 4, total = (1/4) + (2/4) + (5/4) + (9/4) =  1 + 1 + 2 + 3 {take ciel vals} = 7 > thr: not possible
// div = 5, (1/5) + (2/5) + (5/5) + (9/5) = 1 + 1 + 1 + 2 = 5 < thr: possible
// div = 6, (1/6) + (2/6) + (5/6) + (9/6) = 1 + 1 + 1 + 2 = 5<thr: possible

// Result: 5
// See:
// div = 1(min_elem) = 1+2+5+9 = 17 = maximum threshold
// div = 9(max_elem) = 1+1+1+1 = 4 = min threshold = arr.size()

// So possible result lies between 1 and max_elem

bool belowThr(int div, vector<int>& arr, int thr){
    int tot=0;
    for(int i=0;i<arr.size();i++){
        tot += ceil((float)arr[i]/div);
    }
    if(tot <= thr) return true;
    return false;
}

//Using binary:
int findThrteshold(vector<int>& arr, int thr){
    if(thr < arr.size()) return -1;
    else if(thr == arr.size()) return *(max_element(arr.begin(), arr.end()));

    int low = 1, high = *(max_element(arr.begin(), arr.end()));
    int sml = 1;
    while(low <= high){
        int mid = low + (high - low)/2;
        if(belowThr(mid, arr, thr)){
            sml = mid;
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    return sml;
}
//TC - O(n * log(max(arr))), SC - O(1)

//Here too low points to answer as initially it pointed to 1 i.e most not possible abnswer even thugh it depends on threshold given

//-----------------------------------------------------------------------------------------------------------------------------

//Least capacity to ship packages within D days 

//U have a ship that runs once per day 
// Given a array each index represents different type of products and the value represents weight of each type of item to transport
// Also given with day limit under which u have to transport all products 
// Return the minimum capacity the ship can hold so it will be able to transport all products within d days
// Ex: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, d = 5

// if taken cap = 100, all products can be transported within 1 day as sum of arr = 55
// but we need min capacity
// cap = 50 day_req = 1+2+3+4+5+6+7+8+9 - day1, 10n - day2 = 2<5
// cap = 25 day_req = 1+2+3+4+5+6 - day1, 7+8+9 - day2, 10 - day3 = 3<5
// cap = 20 day_req = 1+2+3+4+5 - day1, 6+7 - day2, 8+9 - day3, 10 - day4 = 4<5
// cap = 15 d_r = 1+2+3+4+5 - day1, 6+7 - day2, 8 - day3, 9 - day4, 10 - day5 = 5=5
// cap = 10 d_r = 1+2+3+4 - day1, 4+5 - day2, 6 - day3, 7 - day4, 8 - day5, 9 - day6, 10 - day7 = 7>5

// result = 15

// So ans lies between = (max(arr) to sum(arr)) low is max(arr) as if its less then that then we cannot ship a product type at once we cannot divide a particular product type/arr elem to ship in parts like first half in day1 and second half in day2 - we cannot do so
// edge:
// if: d >= sum(arr)
//     res = 1

bool canBeShipped(int cap, vector<int>& arr, int d){
    int n=arr.size();
    int days = 0, inter=0;
    for(int i=0;i<n;i++){
        if(inter+arr[i] < cap){
            inter += arr[i];
        }
        else if(inter+arr[i] == cap){
            days++;
            inter = 0;
        }
        else{
            days++;
            inter = arr[i];
        }
    }
    if(inter < cap) days++;

    if(days <= d) return true;
    return false;
}
bool canBeShipedHis(int cap, vector<int>& arr, int d){
    int n=arr.size();
    int days = 1, loads = 0;
    for(int i=0;i<n;i++){
        if(loads + arr[i] > cap){
            days++;
            loads = arr[i];
        }
        else{
            loads += arr[i];
        }
    }
    if(days <= d) return true;
    return false;
}

int minCapacityShip(vector<int>& arr, int d){
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if(d >= sum) return 1;
    int low = *(max_element(arr.begin(), arr.end())), high = sum;
    int ans;

    while(low <= high){
        int mid = low + (high-low)/2;
        if(canBeShipedHis(mid, arr, d)){
            ans = mid;
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    return ans;
}
//TC - O(n + n*log(sum(arr)+1) - max(arr)), SC - O(1)

//-----------------------------------------------------------------------------------------------------------------------------

//Find Kth missing number
// Arr given is sorted
// Ex: {2, 3, 4, 7, 11}, k=5
// 1 2 3 4 5 6 7 8 9 10 11
// 0 1 1 1 0 0 1 0 0  0  1
// 1       2 3   4 5  6  

// Result = 9

int KMisNo(vector<int>& arr, int k){
    int maxi = *(max_element(arr.begin(), arr.end()));
    int cnt=0;
    int n=arr.size();
    vector<int> hash(maxi+1, 0);
    hash[0]=1;

    for(int i=0;i<n;i++){
        hash[arr[i]] = 1;
    }

    for(int i=0;i<=maxi;i++){
        if(hash[i] == 0){
            cnt++;
            if(cnt == k) return i;
        }
    }
    return -1;
}
//TC - O(n + max(arr)), SC - O(max(arr))

int KMisNoHisBrut(vector<int>& arr, int k){
    int n=arr.size();
    for(int i=0;i<n;i++){
        if(arr[i] <= k) k++;
        else break;
    }
    return k;
}
//TC - O(n), SC - O(1)

// Important assumption: The array must contain distinct positive integers in sorted ascending order

// Intuition for using binary search:
// U will start from first missing no thats k -> low, and at max can go to arr[n-1]+k -> max
// range = (k) to (arr[n-1]+k)

// how to check whether mid is the kth missing?

// The whole range based intuition is wrong here!

// The real intuition:
// Ex: {2, 3, 4, 7, 11}, k=5
//      1  2  3  4   5
// (cur_elem - actual_serial_elem_toBePresent) = no of elem missing till that elem
// ex: (2-1) = 1 missing elem i.e 1
//     (4-3) = 1 missing i.e 1
//     (7-4) = 3 missing i.e 1,5,6

// This gives the elems between the kth missing elem is present
//         {2, 3, 4, 7, 11}
//          0  1  2  3   4
//          1  2  3  4   5
// missing: 1  1  1  3   6

// go through each and check whether missing is >= k if so then resut = arr[i-1]+(k-arr[i-1]-(i))
// here at index 4, arr[4] = 11, missing = 11-5 = 6>k(5), arr[i-1] = 7, k-arr[i-1]-(i) = 5-7-4 = 2
// result = 7+2 = 9

// How to apply binary search?
// low = 0, high = arr[n-1]
// for each mid calculate no of missing if no_mis<k then move right and if no_mis>=k then return arr[low] + (k-(arr[low]-(low+1)))

//Dry run:
// id:      0  1  2  3   4
//         {2, 3, 4, 7, 11}
// actual:  1  2  3  4   5
// missing: 1  1  1  3   6

// n=5, low = 0, high = 4
// -> 0<=4
//     m=2
//     miss = 4-3 = 1<5
//     low = 3
// -> 3<=4
//     m=3
//     miss=7-4 = 3<5
//     low = 4
// -> 4<=4
//     m=4
//     miss=11-5 = 6>5
//     high = mid-1 = 3
    // high = 3, low = 4
    // return 7+(5-(7-4)) = 7+2 = 9

// Here high initial - arr[n-1] most not possible answer
//      low initil - arr[0] most possible answer 
//      end up in pposite polarity, high being pointing to the start of the missing elem position in arr

// result  = arr[high] + (k - (arr[high] - (high + 1))) 
//         = arr[high] + k - arr[high] + high + 1
//         = high + 1 + k
//         = low + k

int KMisBin(vector<int>& arr, int k){
    int n=arr.size();
    int low = 0, high = n-1;
    while(low<=high){
        int mid = low + (high-low)/2;
        int missing = arr[mid]-(mid+1); 
        if(missing >= k){
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    // if(high>0 && high<n)
    //     return arr[high]+(k-(arr[high] - (high+1)));   //when simplified low + k
    // return k; 
    return low+k;
}
//TC - O(logn), SC-O(1)

//--------------------------------------------------------------------------------------------------------------------------------------
//Pattern 3: BS on answers - min(max) or max(min)

//Pattern: max(min)

//Aggressive Cows
// Find (minimum distance between 2 cows) which is maximum 
// Given a arr whee index represents stalls and the value represents the distance from starting stall and no of cows is given as c
// U need to place the cows such that the minimum distance between any 2 cows should be maximum out of all placements

// Ex: {0, 3, 4, 7, 10, 9}, c=4, first sort the arr
// id:     0 1 2 3 4  5
//         0 3 4 7 9 10
// cows:   1 2 3 4,    here dist b/w c1 and c2 = 3, c1&c3 = 4, c2&c3=1, c2&c4=2, min:c2&c3  Note: So min dist b/w 2 cows is always consecutive distance
// cows:   1   2   3  4, min_dist: cow3&4 = 10-9 = 1
// cows:   1   2 3    4, min dist: cow2&3 = 7-4 = 3
// cows:   1          3, this not possible as u should accomodate every cow

//intuition:
// Can u keep i as the minimum and all others to be atleast i or greater then it
// We start placing cow from index0
// The next cow will be i distance ahead of index0 and each successive cow will be >=i distances ahead of previous if the len of arr passes and u have not completed c cows placing then i-1 is the result, why? cuz for i-1 we already saw its possible for maintaining all consecutive distances between cows as i-1 so its the max min distances between any 2 cow 

// Now the range of min distance 1 to max_possible distance: couyld be 10^9 or more optimized: max(arr)-min(arr) = largest distance possible
// i - (1, max(arr)-min(arr))

// id:     0 1 2 3 4  5
//         0 3 4 7 9 10
// i = 1   1 2 3 4, min-d: cow2&3 = 4-3 = 1
// i = 2   1 2   2 3  4, min-d: cow3&4 = 9-7=2
// i = 3   1 2   3    4, min-d: cow1&2 = 3-0=3
// i = 4   1   2   3   , not possible since return: 3

bool canMaintain(int dis, vector<int>& arr, int c){
    int n=arr.size();

    int cows_placed = 1; // since we assume all cows start from 0 index to make caluclation easier
    int last = arr[0];
    for(int i=1;i<n;i++){
        if(arr[i]-last >= dis){
            cows_placed++;
            last = arr[i];
        }
    }
    if(cows_placed >= c) return true;
    return false;
}


int aggressiveCows(vector<int>& arr, int c){
    int n=arr.size();
    if(c > n) return -1;
    else if(c == n) return *(min_element(arr.begin(), arr.end()));

    sort(arr.begin(), arr.end());

    int maxi = arr[n-1]-arr[0];
    for(int i=1;i<=maxi;i++){
        if(!canMaintain(i, arr, c)){
            return (i-1);
        }
    }
    return -1;
}
//TC - O(nlogn + max-min*n), SC - O(1)

//Using binary
// low = 1, high = max, if mid cannot be maintained then go on left otherwise go to right to find maximum cuz pattern is:
// for ex: {0, 3, 4, 7, 10, 9}
// i =         1 2 3 4 5 6 7 8 9 10
// possible:   1 1 1 0 0 0 0 0 0  0

int aggressiveCowsOpt(vector<int>& arr, int c){
    int n=arr.size();
    sort(arr.begin(), arr.end());
    int low = 0, high = arr[n-1]-arr[0];
    while(low<=high){
        int mid = low + (high-low)/2;
        if(canMaintain(mid, arr, c)){
            low = mid+1;
        }
        else{
            high = mid-1;
        }
    }
    return high;
}
//TC - O(nlogn + log(max-min)*n), SC - O(1)

//Can be optimized: low can be made min of all consecutive distances

//--------------------------------------------------------------------------------------------------------------------------------------
// Allocate Books:
// Given arr where index reps books, val reps total pages in ith book
// Given no of students = s
// U need to find maximum no of pages assigned to student is minimum
/*
    Problem: Allocate Minimum Number of Pages

    Given an array arr of integer numbers, arr[i] represents the
    number of pages in the i-th book.

    There are m students, and the task is to allocate all the books
    to the students.

    Allocate books in such a way that:
    1. Each student gets at least one book.
    2. Each book should be allocated to only one student.
    3. Book allocation should be in a contiguous manner.

    You have to allocate the books to m students such that the
    maximum number of pages assigned to a student is minimized.

    If the allocation of books is not possible, return -1.
*/

// Ex: {25, 46, 28, 49, 24}, s=4
// studs:      s1,     s2,    s3,   s4 
// allocation: 25,     46,    28,   49+24=73 : max=73
//             25,     46, 28+49,   24       : max=77
//             25,  46+28,    49,   24       : max=74
//          25+46,     28,    49,   24       : max=71
// result = 71

int maxAllocation(int stud_max, int max_b, vector<int>& arr, int s){
    int maxi = INT_MIN;
    int j=0;
    for(int i=0;i<s;i++){
        int inter = 0;
        if(i == stud_max){
            int k=0;
            while(k<max_b){
                inter += arr[k];
                k++;
            }
            j+=max_b;
        }
        else{
            inter = arr[j];
            j++;
        }
        maxi = max(maxi, inter);
    }
    return maxi;
}

int bookAllocation(vector<int>& arr, int s){
    int n=arr.size();

    if(n < s) return -1;
    else if(n == s) return *(max_element(arr.begin(), arr.end()));

    int minOfMax = INT_MAX;
    int max_books = n-s+1;
    for(int i=0;i<s;i++){
        int intermediate_max = maxAllocation(i, max_books, arr, s);
        minOfMax = min(minOfMax, intermediate_max);
    }
    return minOfMax;
}
//TC - O(s*n), SC - O(1)

//Actual intuition:
// U would pass the number of max pages to maintain so no student get more then that numbr of pages book allocated , maintain that how much students u can allocate the book for?
// When u get the students allocated = s then return that as minimum of max book pages allocated to a student 
// To start with we will consider the pages such that smallest i i.e to get so many stuednts t=get the book 
// such i is max(arr), for max(arr) as maximum no of pages for a student to maintain if considered then total students getting book = arr.size() 
// And i go on incrementng until sum(arr) as that would allocate total students of 1

// So, i = max(arr) to sum

// For each i write a function that finds no of students get allocated books satisfying:
// - All books are distributed
// - Each books is given to exactly 1 student
// - Books are allocated contigously

int studentAllocated(int max_maintain, vector<int>& arr){
    int n=arr.size();

    int stud_got = 1, pages_allocated=0;
    for(int i=0;i<n;i++){
        if(pages_allocated + arr[i] <= max_maintain){
            pages_allocated += arr[i];
        } 
        else{
            stud_got++;
            pages_allocated = arr[i];
        }
    }
    return stud_got;
}

int bookAllocationLin(vector<int>& arr, int s){
    int n=arr.size();
    if(n < s) return -1;
    if(n == s) return *(max_element(arr.begin(), arr.end()));

    int maxi = *(max_element(arr.begin(), arr.end()));
    int sum = accumulate(arr.begin(), arr.end(), 0);
    for(int i=maxi;i<sum;i++){
        if(studentAllocated(i, arr) == s){
            return i;
        }
    }
    return -1;
}
//TC - O((maxi-sum+1)*n), SC - O(1)


int bookAllocationBin(vector<int>& arr, int s){
    int n=arr.size();
    if(n<s) return -1;
    else if(n==s) return *(max_element(arr.begin(), arr.end()));
    
    int low = *(max_element(arr.begin(), arr.end()));
    int high = accumulate(arr.begin(), arr.end(), 0);
    
    while(low <= high){
        int mid = low+(high-low)/2;
        if(studentAllocated(mid, arr) <= s){
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    return low;
}
//TC - O(n * log(max-sum)), SC - O(1)

//--------------------------------------------------------------------------------------------------------------------------------------

//Painters Partition
// Given a arr and no of painters
// Arr index reps: paint jobs, val reps: unit of painting to be done
// Note: 1 unit of painting requires 1 unit of time

// Allocate paint jobs to k painters such that
// - All jobs should be allocated 
// - Each job should be allocated to exactly 1 painter 
// - Job should be allocated contigously

// Return minimum time required to finish the job by k painters

// Ex: {10, 20, 30, 40}, k=2
//       1             2  
//     (10), (20, 30, 40)  - total_time: p1=10, p2=90, overall_time = 90{as all painters work in parallel}
//     (10,20), (30,40)    - total_time: p1=30, p2=70, overall: 70
//     (10,20,30), (40)    - total_time: p1=60, p2=30, overall: 60

// Minimum time required to finish all job by 2 painters is 60 when partitioned as: (10, 20, 30), (40)

// -> This is same as book allocation why: finding min(max) where no of students: s = no of painters: k, arr representation had book pages here has paint job units
// the range is: (max to sum) if considered max(arr) as max unit to allocate to every painter then total no of painters allocated = arr.size()
// if considered max unit to allocate as sum(arr) then total no of painters allocated is 1 need to for which i the allocation is k

//--------------------------------------------------------------------------------------------------------------------------------------

//Split arr largest sum
// Split the arr into k subarr such that the max subarr sum is minimum

// Note: Its same as book allocation, painters partition i.e max(min) 
// Given arr and k that reps no of subarrs to create 
// Return the minimum of maximum subarr sum out of k, out of every possible k subarr from arr

// Ex: {10, 20, 30, 40}, k=2
// possible 2 subarrs:
// (10), (20, 30, 40) - maxSubarr - 10, 90 = 90
// (10, 20), (30, 40) - maxSubarr - 30, 40 = 70
// (10, 20, 30), (40) - maxSubarr - 10, 20, 30 = 60

//---------------------------------------------------------------------------------------------------------------------------------------------

//Pattern: min(max)
//Minimize the maximum distance to gas stations

// Given with arr that represents coordinates where gas stations are placed, and k which represents the number of gas stations u have to insert in already existing arr
// Have to return the no minimum outy of max consecutive distance between any 2 gas station in arrangement
// Note: Given arr will be in  sorted oredr

// Ex: {1, 2, 3, 4, 5}, k=4
// U need to place k new gas stations anywhere at any coordiate even decimal coordinate such that maximum consec dis should be minimum

// placement1: {1,2,3,4,5,6,7,8,9} all 4 placed, max dis: 1
// placement2: {1, 1.25, 1.5, 1.75, 2, 3, 4.5, 4}, diff: 0.25, 0.25, 0.25, 0.25, 1, 0.5, 0.5, max-dis: 1
// placement3: {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5}, diff: 0.5 for every conseq pair, max-dis: 0.5

// So min max dis: 0.5

// Note: The ques having to deal with decimals, then need to return lonbg double or just double

// -> Whenever u have to return long double, double or float the ques will have line:
// Note: Answers within 10^-6 of the actual answer will be accepted 
// This means consider ur answer is 0.6873421309123 but the actual Test Case answer in server is only upoto 7 decimal places so it compares only till 7 decimal places ur ans with Test case, So if u spend a lot of time to find the exact answer then it might give TLE(Time Limit Exceeded) error so trim it down and only give until they said it accepts

// -> Understanding Higher Intuition:
// Ex: arr = {1, 7}, k=2
//     place: {1, 7, 8, 9} max-dis: 6
//     - So not much eduction in max-dis by placing newer gas station outside the existing as max dis remains same
//     - So have to place in-between existing gas station
//     place: {1, 2, 4, 7} - diff: 1, 2, 3 - max-dis: 3
//     - inorder to minimize split it into 3 equals of distance between
//     (7-1)/3 = 2 - 1+2=3, 3+2=5, 5+2=7
//     place: (1, 3, 5, 7), max-dis=2

// Ex: {1, 13, 17, 23}, k=5
// So based on previous observation, i cannot place stations befpore arr starts or after arr ends we saw it makes no changes in max-dis

// Inorder to keep track of station placed in each section {section is a place in beteen 2 existing station} keep a hash arr whose elems says how many gas station placed in ith section
// Total section for arr with n elems: n-1 

// hash: 0, 0, 0
// -> k=1, where to place 1st gas station - place each stations in section where max-dis is maximum
// max-dis = section_length/station_already_placed+1
//     for sec1: 13-1/0+1 = 12
//         sec2: 17-13/0+1 = 4
//         sec3: 23-17/0+1 = 6
//     place it in sec1 - hash[0]++ = 1,0,0
// -> k=2
//     sec1: 13-1/1+1 = 12/2 = 6
//     sec2: 17-13/0+1=4
//     sec3: 23-17/0+1=6
//     place in sec3 - hash[2]++ = 1,0,1
// -> k=3
//     sec1: 13-1/1+1 = 12/2 = 6
//     sec2: 17-13/0+1 = 4
//     sec3: 23-17/1+1 = 6/2 = 3
//     place in sec1 - hash[0]++ = 2,0,1
// -> k=4
//     sec1: 13-1/3 = 4
//     sec2: 17-13/1 = 4
//     sec3: 23-17/2 = 3
//     place in sec2 - hash[1]++ = 2,1,1
// -> k=5
//     sec1: 13-1/3 = 4
//     sec2: 17-13/2 = 2
//     sec3: 23-17/2 = 3
//     place in sec1 - hash[0]++ = 3,1,1

// Now to find minimised max consec distance
// loop hash arr:
//     sec1: 13-1/4 = 3
//     sec2: 17-13/2 = 2
//     sec3: 23-17/2 = 3
// So result = 3

int MaxDisGasStation(vector<int>& arr, int k){
    int n=arr.size();

    vector<int> hash(n-1, 0);
    for(int i=0;i<k;i++){
        long double maxSubDis = -1;
        int sec;
        for(int j=0;j<n-1;j++){
            long double inter_sub = (arr[i+1]-arr[i])/(hash[i]+1);
            if( inter_sub > maxSubDis ){
                maxSubDis = inter_sub;
                sec=i;
            }
        }
        hash[sec]++;
    }

    int minMax = 0;
    for(int i=0;i<(n-1);i++){
        int inter_consecDis = (arr[i+1]-arr[i])/(hash[i]+1);
        minMax = max(minMax, inter_consecDis);
    }
    return minMax;
}
//TC - O(k*n + n), SC - o(n)

// Inorder to optimize we need to reduce k*n to k*logn using priority queue
// The above gives TLE error as k*n acts as quadratic
// priority queue: normal queue but whenever pushed elems places them in a increasing fashion thats always highest out of all pushed is present at top, for push or pop takes logn time internally maintains a max-heap(binary tree)

// Using priority q: store pair of section lenght and index in q
// Ex: 
// id:  0, 1, 2, 3, 4
//     {1, 13, 17, 23}, k=5
// q: (12, 0), (6, 2), (4, 1) {maintains based on increasing order of 1st elem of pair if that equals then based on 2nd elem of pair}

// Same process: put gas stations 1 by 1 each time in between the section having max distance, maintaining a hash arr about no of stations in each distance
// hash - {0, 0, 0}
// -> k=1
//     q.top = (12, 0), q.pop
//     hash[0]++, {1, 0, 0}
//     12/hash[0]+1 = 12/2 = 6
//     q.push((6, 0)) - {(6,2), (6,0), (4,1)}
// -> k=2
//     q.top = (6, 2), q.pop()
//     hash[2]++, {1, 0, 1}
//     6/hash[2]+1 = 6/2 = 3
//     q.push((3, 2)) - {(6,0), (4,1), (3,2)}
// -> k=3
//     q.top = (6, 0), q.pop()
//     hash[0]++, {2, 0, 1}
//     12/hash[0]+1 = 12/3 = 4
//     q.push((4,0)) - {(4,1), (4,0), (3,2)}
// -> k=4
//     q.top = (4,1), q.pop()
//     hash[1]++, {2,1,1}
//     4/hash[1]+1 = 4/2 = 2
//     q.push((2,1)) - {(4,0), (3,2), (2,1)}
// -> k = 5
//     q.top = (4,0), q.pop()
//     hash[0]++, {3,1,1}
//     12/hash[0]+1, 12/4 = 3
//     q.push((3,0)) - {(3,2), (3,0), (2,1)}

// To find max consec distance: thats q.pop.first = 3

//Better: Using priotiy queue
long double GasStationBet(vector<int>& arr, int k){
    int n=arr.size();
    priority_queue<pair<long double, int>> qu;
    vector<int> hash(n-1, 0);

    for(int i=0;i<(n-1);i++){
        long double section_length = (arr[i+1]-arr[i]);
        qu.push({section_length, i});
    }

    for(int i=0;i<k;i++){
        auto tp = qu.top();
        qu.pop();

        int max_sec = tp.second;
        long double sec_len = arr[max_sec+1]-arr[max_sec];
        hash[max_sec]++;

        long double updated_secLen = sec_len/(hash[max_sec]+1);
        qu.push({updated_secLen, max_sec});
    }

    return qu.top().first;
}
//Tc - O(nlogn + k*logn) as priority queue push, pop takes logn time as p_q has (n-1) elems in it
// SC - O(2*(n-1))

//Moving to optimal where Sc is bought down
//Note: In generic binary serach is designed to accomodate int not double So while(low<=high){ low=mid+1, high=mid-1} all dont work here as we need to return long double

// -> As ques asks the answer should match upto 10^-6

// Note; Conditions for binary search which handles decimals or float or long double where ques needs to give the limit until which input is matched with tes case

// while(low-high < 10^-6){
//     low = mid;
//     high = mid; 
// }
// //We wont decrement or increment mid keep as is while trimming spaces

// //Binay search:
// find ranges of answer: 
// {0, } why start from 0? - as the problem doesnt restrict from placing all stations in same index, what if arr: {1, 1, 1, 1} here if k=2 say again 2 stations are placed in same cords as: {1, 1, 1, 1, 1, 1} now conseq-max-dis = 0
// Now upto where range goes - i.e max_conseq_dis in input arr
// For ex: {1, 2, 3, 4, 5}, k=4
// range - (0, 1) as 1 is the max-conseq-dis why? as i need to reduce max-conseq distance i will not place a station outside the arr making the max-consec-dis even more then what existed in input!

// Now we know low = 0, high = max_consec-dis for binary serach
// But how linear search: for(int i=low;i<=high;i+=10^-6) supposed to increment each time by match limit given in ques i.e 10^-6

// As usual we go on finding the number of gas station that can accomodte by maintaining the max-consec-dis to be i, and once found gas stations that can be accomodated by maintaining the max-consec-dis i to be k then return i

// Say ranges as:
// 0 , 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1
// For 0 there is infinite k possible
// 0.1 - >4
// 0.2 - >4
// .
// .
// 0.5 - =4
// 0.6 - <=4
// .
// .
//             0 , 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1
// possible:   0   0    0    0    0    1    1    1    1    1    1

// Ok how to identify no of k that can be placed?
// Ex: i=0.4 {1,2,3,4,5}, k=4
//     we know: 1, 1.4, 1.8, 2, 2.4, 2.8, 3
//     So between 1&2 = 2 = (2-1)/0.4 = 2.5

//     But when i=0.5
//     we know: 1, 1.5, 2, 2.5, 3
//     So between 1&2 = 1 = (2-1)/0.5 = 2 {but its wrong}
// So we consider only when thereexist some decimal then trim down decimal and thats val of stations top be placed with i range between a section
// But if its perfect division as if in (2-1)/.5 = 2.0 at the time need to take res-1 as stations to be placed with i range

int cntGasAcc(long double minDis, vector<int>& arr){
    int n = arr.size();
    int cnt=0;
    for(int i=0;i<n-1;i++){
        int statBet = (arr[i+1]-arr[i])/minDis;
        if((arr[i+1]-arr[i]) == (statBet*minDis)){
            statBet--;
        }
        cnt+=statBet;
    }
    return cnt;
}

long double gasStationBinOpt(vector<int>& arr, int k){
    int n=arr.size();

    long double low=0;
    long double high=0;
    for(int i=0;i<n-1;i++){
        high = max(high, (long double) arr[i+1]-arr[i]);
    }

    long double ans;
    long double limit = 1e-6;
    while(high-low > limit){
        long double mid = low +(high - low)/2;

        int cnt = cntGasAcc(mid, arr);
        if(cnt > k){
            low = mid;
        }
        else{
            ans=mid;
            high = mid;
        }
    }
    return high; //return ans;
}
//TC - O(n + log(maxConDis)*n), SC - O(1)

//---------------------------------------------------------------------------------------------------------------------------------------------

//Median of 2 sorted arrs
// Note: 2 arrs can also be of different size
// Given 2 arrs merge them maintaining sorted order and then find the median

// Ex: {1, 3, 4, 7, 10, 12}, {2, 3, 6, 15}
// 1, 2, 3, 3, 4, 6, 7, 10, 12, 15
// res = {n=10, median = 5th + 6th/2} = 4+6/2 = 5

// Ex; {2, 3, 4}, {1, 3}
// 1, 2, 3, 3, 4
// res = {n=5, med=3} = 3

// First merge sorted arrs and then based on length find median

//TC - O(n+m), SC - O(n+m)

float medianSorted(vector<int>& arr1, vector<int>& arr2){
    int n=arr1.size();
    int m=arr2.size();

    int i=0, j=0;
    vector<int> res;
    while(i<n && j<m){
        if(arr1[i]<arr2[j]){
            res.push_back(arr1[i]);
            i++;
        }
        else{
            res.push_back(arr2[j]);
            j++;
        }
    }
    while(i<n){
        res.push_back(arr1[i]);
        i++;
    }
    while(j<m){
        res.push_back(arr2[j]);
        j++;
    } 

    if((n+m)%2 == 0){
        float fst = res[((n+m)/2)-1];
        float scd = res[((n+m)/2)];
        return (fst+scd)/2;
    }
    else{
        float mid = res[((n+m+1)/2)-1];
        return mid;
    }
}
//TC - O(n+m), SC - O(n+m)

//With SC - O(1)
float medianSortBet(vector<int>& arr1, vector<int>& arr2){
    int n=arr1.size();
    int m=arr2.size();

    int id1=-1, id2=-1;
    float mid1, mid2;
    if((n+m)%2 == 0){
        id1 = ((n+m)/2)-1;
        id2 = ((n+m)/2); 
    }
    else{
        id1 = ((n+m+1)/2)-1;
    }

    int i=0, j=0, cnt=-1;
    while(i<n && j<m){
        if(arr1[i]<arr2[j]){
            cnt++;
            if(cnt==id1){
                mid1 = arr1[i];
            }
            else if(cnt==id2){
                mid2 = arr1[i];
            }
            i++;
        }
        else{
            cnt++;
            if(cnt==id1){
                mid1 = arr2[i];
            }
            else if(cnt==id2){
                mid2 = arr2[i];
            }
            j++;
        }
    }
    while(i<n){
        cnt++;
        if(cnt==id1){
            mid1 = arr1[i];
        }
        else if(cnt==id2){
            mid2 = arr1[i];
        }
        i++;
    }
    while(j<m){
        cnt++;
        if(cnt==id1){
            mid1 = arr2[i];
        }
        else if(cnt==id2){
            mid2 = arr2[i];
        }
        j++;
    }

    if(id2 == -1) return mid1;
    else{
        return (mid1+mid2)/2;
    } 
}
//TC - O(n+m), SC - O(1)
//The above solution gives TLE error

//Optimal: TC for it may be a sqrt() or log(), its likely to be log due to sorted mentioning in ques

// For even:
// arr1 - {1, 3, 4, 7, 10, 12}
// arr2 - {2, 3, 6, 15}
// n = 10

// median = 5th + 6th

// -> Trying to draw a symmetrical line accross median
// _ _ _ _ _ | _ _ _ _ _
// left - 5elems and right - 5elems

// ->Out of 5 elems on left how many come from arr1 and from arr2?
// In actual soted - 1 2 3 3 4 | 6 7 10 12 15 here 3elems from arr1 and 2elms from arr2

// ->We will try to formulate the correct left half - i.e to find the no of elems from arr1 ad arr2 on left  i.e 3elems from arr1 and 2elems from arr2


// - Start from picking no/0 elem from arr1 if so then we should pbe picking 5 elems from arr2 but arr2 has only 4elems in total so picking0 not possible

// - Picking 1elem from arr1
//     1    | 3 4 7 10 12
// 2 3 6 15 | 
// valid? No as: 1 2 3 6 15 | 3 4 7 10 12, 15>3

// - Picking 2elem
//     1 3 | 4 7 10 12
//   2 3 6 | 15
// valid? No as: 1 2 3 3 6 | 4 7 10 12 15, 6>4

// - Picking 3elem
//   1 3 4 | 7 10 12
//   2 3   | 6 15
// valid? Yes as: 1 2 3 3 4 | 6 7 10 12 15, 4<6

// - Picking 4elem
// 1 3 4 7 | 10 12
// 2       | 3 6 15
// valid? No as: 1 2 3 4 7 | 3 6 10 12 15, 7>3

// - Picking 5elem
// 1 3 4 7 10 | 12
//            | 2 3 6 15
// valid? No as: 1 3 4 7 10 | 2 3 6 12 15

// So picking from arr1 - 0 1 2 3 4 5
// valid?                 0 0 0 1 0 0
// Note: Here we wont see a binary search pattern, does that mean we cannot apply binSearch? no we can

// -> How to check for validity?
// Rule for valid symmetry: l1 < r2, l2 < r1, where l1 and l2 are end elems of arr1 & arr2 selected elems from left half, r1 and r2 are start elems of arr1 & arr2 selected elems from right half

// How to get median: max(l1, l2) + min(r1, r2) / 2

// - Picking 4elem from arr1:
//     1 3 4 7 | 10 12
//     2       | 3 6 15
// Here l1=7, l2=2, r1=10, r2=3, l1>r2, l2<r1

// - Picking 3elem from arr1:
//   1 3 4 | 7 10 12
//   2 3   | 6 15
// Here l1=4, l2=3, r1=7, r2=6, l1<r2, l2<r1, So valid
// Median: max(l1, l2) = 4, min(r1, r2) = 6, (4+6)/2 = 5 

// - Picking 2elem from arr1:
//     1 3 | 4 7 10 12
//   2 3 6 | 15
// Here l1=3, l2=6, r1=4, r2=15, l1<r1 & l2>r1

// -> the pattern was not as of binary search right 
// So we need to determine whether should i go right and eleiminate left or should i go left and eliminate right! for choosing the no of elems from arr1 as getting to know how many from arr1 {i} will automatically say us how many from arr2 i.e {arr.size()-i}
// i can be:
// 0 1 2 3 4 5 6, as arr1.size()=6
// ->         <-
// go          go left 
// right       elemRight
// elimLeft
// -> Rule:IF l1>r2 then high = mid-1, if l2>r1 then low=mid+1 
// Ex:
// - Picking 4elem from arr1:
//     1 3 4 7 | 10 12
//     2       | 3 6 15
// Here l1=7, l2=2, r1=10, r2=3, l1>r2, l2<r1 So high=mid-1

// - Picking 3elem from arr1:
//   1 3 4 | 7 10 12
//   2 3   | 6 15
// Here l1=4, l2=3, r1=7, r2=6, l1<r2, l2<r1, So valid
// Median: max(l1, l2) = 4, min(r1, r2) = 6, (4+6)/2 = 5 

// - Picking 2elem from arr1:
//     1 3 | 4 7 10 12
//   2 3 6 | 15
// Here l1=3, l2=6, r1=4, r2=15, l1<r1 & l2>r1 So low=mid+1

// So now time complexiy becomes: log(choosen arr to pick)
// So inorder to further reduce TC always do Binary Search on shorter arr

// Dry run
// arr1 = {7, 12, 14, 15}
// arr2 = {1, 2, 3, 4, 9, 11}

// n=10, split = 10/2 = 5
// low = 0, high = arr1.size() = 4
// -> 0<=4 
//     mid1 = 2 //means pick 2 elems from arr1
//     mid2 = 5-2 = 3 //means pick 3 from arr2
//          7 12 | 14 15
//         1 2 3 | 4 9 11
//     l1 = mid1-1, l2 = mid2-1, r1=mid1, r2=mid2
//     arr1[mid1-1]>arr2[mid2], arr2[mid2]<arr1[mid1]
//     As l1>r2, high = mid1-1 = 1 
// -> 0<=1
//     mid1 = 0
//     mid2 = 5-0 = 5
//               | 7 12 14 15
//     1 2 3 4 9 | 11
//     l1 = mid1-1, l2 = mid2-1, r1 = mid1, r2=mid2
//     l1 = -1, l2 = 4, r1=0, r2=5
//     arr2[l2](9)>arr1[r1](7), low=mid+1
//     low = 1
// ->1=1
//     mid1 = 1
//     mid2 = 4
//             7 | 12 14 15
//       1 2 3 4 | 9 11
//     l1 = mid1-1, l2 = mid2-1, r1=mid1, r2=mid2
//     l1 = 0, l2 = 3, r1 = 1, r2 = 4
//     arr1[l1] (7) < arr2[r2] (9), arr2[l2](4) < arr1[r1](12)
//         So midian = max(arr1[l1], arr2[l2])+min(arr1[r1], arr2[r2])/2 = 7+9/2 = 16/2 = 8

// For Odd elements:
// Ex: arr1 - {2, 4}, arr2 - {1, 3, 4}
// The split for odd otal: n+m+1 / 2, here 6/2=3
// Note: for both odd and even this formula is valid: (n+m+1)/2 = odd = 5, (5+1)/2 = 3, even=6, (6+1)/2 = 3
// For odd total,  median = max(l1, l2)

double medianSortedOpt(vector<int>& arr1, vector<int>& arr2){
    int n1 = arr1.size();
    int n2 = arr2.size();
    if(n1>n2){
        return medianSortedOpt(arr2, arr1);
    }

    int n = n1+n2;
    int split = (n+1)/2;
    int low = 0, high = n1;
    int l1, l2, r1, r2;
    while(low<=high){
        int mid1 = low + (high-low)/2;
        int mid2 = split - mid1;
        l1 = mid1-1;
        l2 = mid2-1;
        r1 = mid1;
        r2 = mid2;
        if(l1>=0 && arr1[l1] > arr2[r2]){
            high = mid1-1;
        }
        else if(l2>=0 && arr2[l2]>arr1[r1]){
            low = mid1+1;
        }
        else {
            if(n%2 == 0){
                double a,b;
                if(l1>=0 && l2>=0)
                    a = max(arr1[l1], arr2[l2]);
                else if(l1>=0)
                    a=arr1[l1];
                else
                    a=arr2[l2];
                b = min(arr1[r1], arr2[r2]);

                return ((double)a+b)/2;
            }
            else{
                int a;
                if(l1>=0 && l2>=0)
                    a = max(arr1[l1], arr2[l2]);
                else if(l1>=0)
                    a=arr1[l1];
                else
                    a=arr2[l2];
                return (double)a;
            }
        }
    }
    return 0;
}
//Here u did not consder what if r1 and r2 go out of bound as mid1 and mid2 are no of elems and not indices

double medianSortOptHis(vector<int>& a, vector<int>& b){
    int n1 = a.size();
    int n2 = b.size();
    if(n1>n2) return medianSortOptHis(b, a);
    int low = 0, high = n1;
    int split = (n1+n2+1)/2;
    int n = n1+n2;
    while(low <= high){
        int mid1 = (low+high)>>1;
        int mid2 = split - mid1;

        int l1 = INT_MIN, l2 = INT_MIN;
        int r1 = INT_MAX, r2 = INT_MAX;

        if(mid1 < n1) r1 = a[mid1];
        if(mid2 < n2) r2 = b[mid2];
        if(mid1 - 1 >= 0) l1 = a[mid1-1];
        if(mid2 - 1 >= 0) l2 = b[mid2-1];

        if(l1 <= r2 && l2 <= r1){
            if(n%2 == 1) return max(l1, l2);
            else (double)(max(l1, l2) + min(r1, 2))/2.0;
        }
        else if(l1 > r2) high = mid1-1;
        else low = mid1+1;
    }
    return 0;
}
//TC - O(log(min(n, m))) where n - arr1.size(), m - arr2.size()
//SC - o(1)

//---------------------------------------------------------------------------------------------------------------------------------------------------

//Find kth element of 2 sorted arrs
// Given 2 sorted arrs find kth position elem in merged sorted arr

// Optimal: Use binary search similar to previous where u split by k and not based n1+n2+1/2, no need to check for tot len even or odd just split by k and when satisfies l1<r2 and l2<r1 then return max(l1, l2) thats the kth element

//Ex: a - {2,3,6,7,9}, b - {1,4,8,10}, k=4
// res - 1,2,3,4,6,7,8,9,10 = 4

// - Why high = n1 i.e at last to pick all elems of smaller arr and to have remaining from arr2 to make split complete inorder to see does that make valid match
// But in this case it would result in wrong ans why?
// Ex; arr1 - 6elems, k=2 now he asks does it make sense to pick 6 elems from arr1? So indeed atmax u can pick 2 elems right! So high = min(k, n1)

// Again, low=0 is it 0 always?
// Ex: arr1 = 6elems, arr2 = 5elems, int tot=11elems, and if k=2, so taking low=0 make sense here as first picking 0 elems from arr1 and picking 2 elems from arr2 can make a valid match
// But what if k=7, i.e when k>n1 here taking low = 0 means taking 0 elems from arr1 and taking 5 elems from arr2 that doesnt make 7 elems on left So leads to wrong ans, So low = max(0, k-n2) So in this ex: low = max(0, 7-5) = 2, So the first possible case is that take 2elems from arr1 and take 5elems from arr2!


double kElement(vector<int>& a, vector<int>& b, int k){
    int n1 = a.size();
    int n2 = b.size();

    if(n2<n1){
        return kElement(b, a, k);
    }

    int low = max(0, k-n2), high = min(k,n1);
    while(low <= high){
        int mid1 = (low+high)>>1;
        int mid2 = k-mid1;

        int l1=INT_MIN, l2=INT_MIN, r1=INT_MAX, r2=INT_MAX;

        if((mid1-1) >= 0) l1 = a[mid1-1];
        if((mid2-1) >= 0) l2 = b[mid2-1];
        if(mid1 < n1) r1 = a[mid1];
        if(mid2 < n2) r2 = b[mid2];

        if(l1<r2 && l2<r1){
            return max(l1, l2);
        }
        else if(l1>r2) high = mid1-1;
        else low = mid1+1;
    }
    return 0;
    
}
//TC - O(log(min(n,m))), SC - o(1)

//-------------------------------------------------------------------------------------------------------------------------------------------------------

//Row with maximum 1s
// Given matrix of 0's and 1's, where each row is sorted u needb to find the row with maximum no of 1s
// Ex:
// 0 0 1 1 1 - 3
// 0 0 0 0 0 - 0
// 0 1 1 1 1 - 4
// 0 0 0 0 0 - 0
// 0 1 1 1 1 - 4
// res = 4

//Brute:
int maxOnes(vector<vector<int>>& mat){
    int n=mat.size();
    int m=mat[0].size();

    int sum, maxSum = 0, res;
    for(int i=0;i<n;i++){
        sum=0;
        for(int j=0;j<m;j++){
            if(mat[i][j] > 0) sum += mat[i][j];
        }
        if(maxSum < sum){
            maxSum = sum;
            res = i;
        }
    }
    return res;
}
//TC - O(n*m), SC - O(1)

//Optimal: Here we can optimize the each row traversal i.e inner for loop 
//Each row if u know first occurence of 1 then (row_len - id_at_which_1occur_first)
// U can find 1st occurenbce of 1 as:
// - lowerBound(1)
// - upperBound(0)
// - FirstOccurence(1)

//Constraint of problem: if there is no row with atleast one 1 i.e all rows are full of zeros then it says do not return 0 index that is first row instead return -1: inorder to make it possible keep maxSum = 0 and not maxSum = -1 int his case even if m-low came out to be 0  it doesnt go inside if condition as maxSum = 0 
// If 2 rows has same no of 1s then return first row out of them 

int maxOnesOpt(vector<vector<int>>& mat){
    int n = mat.size();
    int m = mat[0].size();

    int res=-1, maxSum=0;
    for(int i=0;i<n;i++){
        int low = 0, high = m-1;
        while(low<=high){
            int mid = low + (high-low)/2;
            if(mat[i][mid] == 1) high = mid-1;
            else low = mid+1;
        }
        if(maxSum < m-low){
            maxSum = m-low;
            res = i;
        }
    }
    return res;
}
//Tc - O(nlog(m)), Sc - O(1)

//-------------------------------------------------------------------------------------------------------------------------------------------------------

//Search in 2D matrix
// Given sorted 2D matrix need to say is target present or not

// Ex: 
// 3   4  7  9
// 12 13 16 18
// 20 21 23 29
// target = 23, res = true

// brut: traverse using nested loop as sorted order matches the straightforward pattern and each time check for target, O(n*m)

// Better: check the boundary of each row to find out should u need to traverse that row or not if in that then use binary search

bool Search2D(vector<vector<int>>& arr, int target){
    int n = arr.size();
    int m = arr[0].size();

    for(int i=0;i<n;i++){
        if(target>=arr[i][0] && target<=arr[i][m-1]){
            int low = 0, high = m-1;
            while(low<=high){
                int mid = (low+high)>>1;
                if(target == arr[i][mid]){
                    return true;
                }
                else if(target > arr[i][mid]){
                    low = mid+1;
                }
                else{
                    high = mid-1;
                }
            }
        }
    }
    return false;
}
//TC - O(n + log(m)), SC - O(1)

//Can optimize as if from O(n + logm) to O(log(n*m)) if we hypopthetically thing the whole matrix to serial and apply S on it

// Ex:
// 3  4  7  9
// 12 13 16 18
// 20 21 23 24

// Here on indexing

// 00{0} 01{1} 02{2}  03{3}
// 10{4} 11{5} 12{6}  13{7}
// 20{8} 21{9} 22{10} 23{11}

// Here we need to convert 1D index to 2D index
// Observe:
// - 1D index in a column is multiple of m=4 - 0, 4, 8 So (1D-index/m) will give i i.e row number 
// For ex: 6: i=6/4 = 1, 11: i=11/4 = 2
// - 1D index in a row shows pattern of remainder to m so j=(1DIndex % m)
// Ex: 6: j=6%4 = 2, 11: j=11%4 = 3

bool Search2DOpt(vector<vector<int>>& arr, int target){
    int n = arr.size();
    int m = arr[0].size();

    int low = 0, high = (n*m)-1;
    while(low <= high){
        int mid = low+(high-low)/2;
        int i = mid % m;
        int j = mid / m;
        if(target == arr[i][j]){
            return true;
        } 
        else if(target > arr[i][j]){
            low = mid+1;
        }
        else high = mid-1;
    }
    return false;
}
//TC - O(log(n*m)), SC - O(1)

//-------------------------------------------------------------------------------------------------------------------------------------------------------

//Searching in 2D matrix - 2

// Given a 2D matrix and a target u need to return the coordinate at which target is presnt if not return (-1, -1)
// But the catch - its not normal matrix
// - In inpt every row is sorted left to right and every column is sorted top to bottom

// Ex;
// 1  4   7 11 15
// 2  5   8 12 19
// 3  6   9 16 22
// 10 13 14 17 24

// target = 14

//Brut: O(n*m) traverse all and condition lineary 

//Better go to each row and do a bs on it to find target

pair<int, int> search2D2(vector<vector<int>>& arr, int target){
    int n=arr.size();
    int m=arr[0].size();

    for(int i=0;i<n;i++){
        if(target >= arr[i][0] && target <= arr[i][m-1]){
            int low =0, high = m-1;
            while(low<=high){
                int mid = low + (high-low)/2;
                if(arr[i][mid] == target){
                    return {i, mid};
                }
                else if(arr[i][mid] < target){
                    low = mid+1;
                }
                else high = mid-1;
            }
        }
    }
    return {-1, -1};
}

//Optimal; start either from (0, m-1) or (n-1, 0) and each time check whether target greter then it or less if greater then, then move 1 step down when u stand at (0, m-1) or 1 step right when stood at (n-1, 0) and if its lesser then , move 1 step left when stood at (0, m-1) or 1 step up when stood at (n-1,0) and if equal then return

pair<int, int> Search2D2Opt(vector<vector<int>>& arr, int target){
    int n = arr.size();
    int m = arr[0].size();

    int i=0, j=m-1;
    while(i<n && j>=0){
        if(target == arr[i][j]){
            return {i, j};
        }
        else if(target > arr[i][j]){
            i++;
        }
        else{
            j--;
        }
    }
    return {-1, -1};
}
//TC - O(n+m), Sc - O(1)

//-------------------------------------------------------------------------------------------------------------------------------------------------------

//Find peak element part-2
// Given 2D matrix , find peak element i.e curr element should be greater then all of its neighboring elems
// Note: Given 2 adjacents cells are not same means 
// not possible to find something like in matrix:  
//     2
//  2  2  2
//     2
// - peak elem: a element which is greater then its top, right, bottom, left neighbor
// Note: Any neighboring counterpart is not present then its considered to be -1 {previously -infinity}
// - If multiple return any 1 of them
// - Return (row, col) of peak elem

// Ex:
// 4 2 5 1 4 5
// 2 9 3 2 3 2
// 1 7 6 0 1 3
// 3 6 2 3 7 2
// res = (1,1) or (3,4)

//Brut
pair<int, int> peakElem2D(vector<vector<int>>& arr){
    int n=arr.size();
    int m = arr[0].size();

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if( (i-1<0 || arr[i][j]>arr[i-1][j]) && (i+1 >= n || arr[i][j]>arr[i+1][j]) && (j-1<0 || arr[i][j]>arr[i][j-1]) && (j+1>=m || arr[i][j]>arr[i][j+1])){
                return {i, j};
            }
        }
    }
    return {-1,-1};
}
//TC - O(n*m*4), Sc - O(1)

//Optimal: Same intuition as 1D peak element 
//   /\ 
//  /  \ 
// /    \
i.e if a element is less then its previous elem then it means is on decreasing side and u should eleiminate right half
// If arr[i]>rr[i-1] then its on increasing ghalf and u should eliminate left half

// But in 2D u also have upper and lower for that we go through each col and take max elem in whole col and consider its leftElem as prev and right elem as next and compare and eliminate
// - Taking of max guarantees correct answer as if prev elem is greter then current then it do means all elem of curr col are also less then prev elem and the possibility is that the max elem of prev column which is greter then the prev elem which is indeed greater then the all elems in current column

//Note: U can also traverse each rows and take max and compare its top and bottom for eleimination it do works
pair<int, int> SearchPeak2DOpt(vector<vector<int>>& arr){
    int n = arr.size();
    int m = arr[0].size();

    int low = 0, high = m-1;
    while(low<=high){
        int mid = low + (high-low)/2;
        int row=0, maxi=INT_MIN;
        for(int i=0;i<n;i++){
            if(maxi<arr[i][mid]){
                maxi = arr[i][mid];
                row=i;
            }
        }
        if(mid-1 >=0 && arr[row][mid] < arr[row][mid-1]){
            high = mid-1;
        }
        else if(mid+1<m && arr[row][mid] < arr[row][mid+1]){
            low = mid+1;
        }
        else{
            return {row, mid};
        }
    }
    return {-1,-1};
}
//TC - O(n*log(m)), Sc - O(1)


//-------------------------------------------------------------------------------------------------------------------------------------------------------

//Finding the median of row wise sorted matrix
// Given 2D matrix which are only sorted row wise need to return its median for its sorted 1D arr
// Ex:
// 1  5  7  9 11
// 2  3  4  5 10
// 9 10 12 14 16
// n*m = 3*5 = 15
// med = 7
// 0 1 2 3 4 5 6 7 8 9  10 11 12 13 14
// 1 2 3 4 5 5 7 9 9 10 10 11 12 14 15

//Note: its given in ques that n and m are always odd

//Brut:
int median2Dmat(vector<vector<int>>& arr){
    int n=arr.size();
    int m=arr[0].size();

    vector<int> inter;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            inter.push_back(arr[i][j]);
        }
    }
    sort(inter.begin(), inter.end());
    int med = (n*m + 1)/2;   //Since 2 odds always result a odd
    return inter[med];
}
//TC - o(n*m + (n*m)log(n*m)), SC - O(n*m)

//Optimal approach
// Optimal should be less then O(n*m) TC, as it says sorted median kind of stuff go for BS

// 1D sorted version:  
// // 1 2 3 4 5 5 7 9 9 10 10 11 12 14 15
// here on left of median = 7elems, on right of median = 7elems(as ques states n&m are podd so n*m is odd)

// Search space:
// min(arr) -> max(arr)

// Note: No need to traverse O(n*m) for min and max search 1st col for min and last col for max thats all cuz input is sorted row wise so any min should be 1st col and any max should be in last col

// - Now inorder to eliminate search space we use kind of special built arr that has for each elem no of elems <= (n*m)/2 i.e index of median traditionally, this arr has <=(n*m)/2 for each unique elems
// - Why <= and not simply < since in ex:// 1 2 3 4 5 5 7 9 9 10 10 11 12 14 15 we see i cannot guarantee that everything left of median(9) < 9 and everything right on median 9 is >9 So we consider <=
// For ex:
// // 0 1 2 3 4 5 6 7 8 9  10 11 12 13 14
// // 1 2 3 4 5 5 7 9 9 10 10 11 12 14 15
// consider for elem 9 the no of elems <= (n*m)/2 {7} is 9 (0-6 and 2 9's)
// for elem 10 it is 11
// So for median the no of elem <= (n*m)/2 should be greater then (n*m)/2

// So u should find the first elem that has <=(n*m)/2 to be greater then (n*m)/2 and that is ur median
// For ex:
// // 0 1 2 3 4 5 6 7 8 9  10 11 12 13 14
// // 1 2 3 4 5 5 7 9 9 10 10 11 12 14 15

// <= arr:
// Note: In this arr u should put every no between min(arr) and max(arr)
// uniq-elem:  1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
// <=(n*m1)/2: 2 3 4 6 6 7 7 7 9 11 12 13 13 14 15

// low = 1, high = 16
// mid = 8, blackBox(8) = 7, which is <7 so low = mid+1
// low = 9

// low = 9, high =16
// mid = 12, BB(12) = 14, >7 So high = mid-1;
// high = 11

// low = 9, high =11
// mid = 10, BB(10)=12, >7 So high = mid-1
// high = 9

// low = 9, high = 9
// mid = 9, BB(9)=11, >7 high = mid-1
// high = 8

// low>high return low = 9 i.e median

int blackBox(int mid, vector<vector<int>>& arr){
    int n = arr.size();
    int m = arr[0].size();
    int res=0;

    for(int i=0;i<n;i++){
        int cnt=0;
        int l=0, h=m-1;
        while(l<=h){
            int m = l+(h-l)/2;
            if(arr[i][m] <= mid){
                cnt = m+1;
                l = m+1;
            }
            else{
                h = m-1;
            }
        }
        res+=cnt;
    }
    return res;
}

int median2DMat(vector<vector<int>>& arr){
    int n=arr.size();
    int m = arr[0].size();
    int low=INT_MAX, high=INT_MIN;

    for(int i=0;i<n;i++){
        low = min(low, arr[i][0]);
        high = max(high, arr[i][m-1]);
    }
    int limit = (n*m)/2;

    while(low<=high){
        int mid = low + (high-low)/2;
        int noLessEq = blackBox(mid, arr);
        if(noLessEq > limit){
            high = mid-1;
        }
        else if(noLessEq <= limit){
            low = mid+1;
        }
    }
    return low;
}
//Tc - O(log(max(arr)) * nlog(m))

//-------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------


int main(){
    // vector<int> arr = {3, 6, 7, 11};
    // binarySearchRecVoid(arr, 50, 0, arr.size()-1);

    // cout<<upperBoundOpt(arr, 50)<<endl;
    // cout<<(lower_bound(arr.begin()+1, arr.begin()+4, 23) - (arr.begin()+1));
    // cout<<(upper_bound(arr.begin(), arr.end(), 50) - arr.begin());

    // auto p = FirstLastOccOptHis(arr, 11);
    // cout<<p.first<<" "<<p.second<<endl; 

    // cout<<SearchRotSortArrOpt2(arr, 10);

    // cout<<findMultiplePeak(arr);

    // cout<<NRootMBin(4, 81);

    // cout<<KokoBananaBin(arr, 8);

    //=================================================================================

    // vector<int> arr = {1,2,3,4,5};
    // cout<<gasStationBinOpt(arr, 4);

    //=================================================================================

    // vector<int> arr1 = {1,4,8,10};
    // vector<int> arr2 = {2,3,6,7,9};
    // cout<<kElement(arr1, arr2, 6);

    //==============================================================================

    // vector<vector<int>> arr = {{3, 4, 7, 9},
    // {12, 13, 16, 18},
    // {20, 21, 23, 29}};
    // cout<<Search2DOpt(arr, 23);

    //==========================================================================

    // vector<vector<int>> arr = {{4, 2, 5, 1, 4, 5},
    // {2, 9, 3, 2, 3, 2},
    // {1, 7, 6, 0, 1, 3},
    // {3, 6, 2, 3, 7, 2}};
    // auto pr = SearchPeak2DOpt(arr);
    // cout<<pr.first<<","<<pr.second<<endl;

    //===========================================================================

    vector<vector<int>> arr = { {1,  5,  7,  9, 11},
    {2,  3,  4,  5, 10},
    {9, 10, 12, 14, 16}};
    cout<<median2DMat(arr);


    return 0;
}