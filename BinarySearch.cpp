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
        if(mid == key){
            cout<<"Eureka at index: "<<mid<<endl;
            break;
        }
        else if(key < mid){
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
        else if(arr[mid]>n && arr[mid]<temp){
            temp = mid;
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
// If the value is not present, determine the index where it would be inserted in the array while maintaining the sorted order.\

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
            mini = min(mini, arr[mid]);
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

    else if(arr.size()==1 || arr[0] > arr[1]) return arr[0];

    else if(arr[(arr.size()-1)]>arr[arr.size()-2]) return arr[arr.size()-1];

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
// low=1, high=3, arr[2]<arr[low], arr[2]<arr[high] so not peak, not falls on decreasing as arr[mid] < arr[mid+1], not on increasing arr[mid] !> arr[mid+1]

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
    int ans=1;
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
            mid/=2;
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
//-----------------------------------------------------------------------------------------------

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
//For sure low=1, high=max_elem(arr), if mid takes time<=h then return mid otherwise if mid takes time>h then high=mid-1, time<h then low=mid+1
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

// Note: No need to maintain separate mini to return as low at the end points to the minimum k, why? - initially low points to 1 which is mostly not possible and high points to max_element(arr) which is most likely possible So after loop they end up being in opposite of what they are initially: low-least k, high-highest impossible k


itn main(){
    vector<int> arr = {3, 6, 7, 11};
    // binarySearchRecVoid(arr, 50, 0, arr.size()-1);

    // cout<<upperBoundOpt(arr, 50)<<endl;
    // cout<<(lower_bound(arr.begin()+1, arr.begin()+4, 23) - (arr.begin()+1));
    // cout<<(upper_bound(arr.begin(), arr.end(), 50) - arr.begin());

    // auto p = FirstLastOccOptHis(arr, 11);
    // cout<<p.first<<" "<<p.second<<endl; 

    // cout<<SearchRotSortArrOpt2(arr, 10);

    // cout<<findMultiplePeak(arr);

    // cout<<NRootMBin(4, 81);

    cout<<KokoBananaBin(arr, 8);

    return 0;
}