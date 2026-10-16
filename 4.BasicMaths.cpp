#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
                              BASIC MATHS - NOTES
================================================================================

TABLE OF CONTENTS
-----------------
  PART 1  : Extracting digits
  PART 2  : Counting digits (loop method + log10 method)
  PART 3  : Reversing a number (with trailing-zero handling)
  PART 4  : Palindrome check
  PART 5  : Armstrong number check
  PART 6  : Divisors / factors (brute force + optimized sqrt(n))
  PART 7  : Prime number check
  PART 8  : GCD / HCF (multiple approaches, weakest to strongest)
  PART 9  : LCM
  PART 10 : main()

================================================================================
PART 1 : EXTRACTING DIGITS
================================================================================
Given a number, print each digit separately.
Ex: N = 7789 -> 9 8 7 7 (extracted from least significant digit first)
*/

void extract(int n) {
    while (n > 0) {
        cout << n % 10 << " ";
        n /= 10;
    }
    cout << endl;
}
// TC - O(log10(n))   number of digits ~ log10(n)
// SC - O(1)
// EDGE CASE: n = 0 prints nothing (loop never runs, since 0 > 0 is false),
//            even though 0 technically has 1 digit. Handle separately if needed.


/*
================================================================================
PART 2 : COUNTING DIGITS
================================================================================
*/

// Method 1 - loop and divide by 10 until 0
int countDigits(int n) {
    // NOTE: renamed from 'count' to avoid shadowing std::count from <algorithm>
    int cnt = 0;
    while (n > 0) {
        cnt++;
        n /= 10;
    }
    return cnt;
}
// TC - O(log10(n))  -  loop runs once per division by 10.
//      If dividing by 5 instead, it would be O(log5(n)); base of the log is
//      whatever base you're repeatedly dividing by.
// SC - O(1)
// EDGE CASE: n = 0 returns 0, though 0 has 1 digit conventionally. Add a
//            special case (if (n==0) return 1;) if you need that convention.


// Method 2 - using log10 directly, since:
//     number of digits in n = floor(log10(n)) + 1
int countDigitsModified(int n) {
    if (n == 0)
        return 1;              // log10(0) = -infinity / undefined, handle separately
    n = abs(n);                 // log10(negative) = NaN
    int cnt = log10(n) + 1;     // better: floor(log10(n) + 1e-9) + 1

    // FLOATING-POINT PRECISION WARNING (the "999 bug"):
    // std::log10 works on doubles. Binary floating-point representation can
    // introduce tiny rounding errors.
    //   log10(1000) is mathematically exactly 3.
    //   Due to floating-point imprecision, the computed value might be
    //   2.999999999999999 instead of 3.0 exactly.
    //   Casting that to int TRUNCATES down to 2, giving 2+1=3 digits
    //   instead of the correct 4.
    // FIX: add a tiny epsilon before truncating:
    //   int cnt = (int)(log10(n) + 1e-9) + 1;

    return cnt;
}
// TC - O(1)  (a single library call, treated as constant time)
// SC - O(1)


/*
================================================================================
PART 3 : REVERSING A NUMBER (drop leading zeros of the result)
================================================================================
If the input has trailing zeros, the reversed number should NOT show them as
leading zeros. Ex: reverse(40100) = 104, not 00104.
*/

string reversing(int n) {
    string rvs = "";
    int cnt = 0;
    bool prev_zero = false;      // true while we are still in a leading-zero run
    while (n > 0) {
        if (cnt == 0 && n % 10 == 0) {
            prev_zero = true;    // first digit encountered is 0 -> start skipping
        }
        if (!(prev_zero && n % 10 == 0)) {
            rvs += to_string(n % 10);   // or: rvs += char('0' + n % 10);
            prev_zero = false;           // a non-zero digit ends the skip-streak
        }
        n /= 10;
        cnt++;
    }
    return rvs;
}
// TC - O(log10(n)), SC - O(log10(n)) for the output string

// Simpler way to reverse a number WITHOUT tracking units/tens/hundreds
// separately - each step just shifts the accumulated reverse left by one
// decimal place and appends the next digit:
int reverse_digit_simple(int n) {
    int rev = 0;
    while (n > 0) {
        rev = (rev * 10) + n % 10;
        n /= 10;
    }
    return rev;
}
// TC - O(log10(n)), SC - O(1)
// NOTE: this naturally drops trailing zeros of the input as leading zeros of
// the output too, since leading zeros just don't exist in an int's value.


/*
================================================================================
PART 4 : PALINDROME CHECK (for a number)
================================================================================
*/

bool checkPalindrome(int n) {
    int rvs = 0;
    int temp = n;
    while (n > 0) {
        rvs = (rvs * 10) + (n % 10);
        n /= 10;
    }
    return rvs == temp;
}
// TC - O(log10(n)), SC - O(1)


/*
================================================================================
PART 5 : ARMSTRONG NUMBER CHECK
================================================================================
A number equal to the sum of the cubes of its own digits.
Ex: 371 = 3^3 + 7^3 + 1^3 = 27 + 343 + 1 = 371  -> Armstrong number.
*/

bool isArmstrong(int n) {
    int check = 0;                 // FIX: must be initialized to 0, was left
                                    // uninitialized before (undefined behavior)
    int temp = n;
    while (n > 0) {
        int d = n % 10;
        check += d * d * d;        // FIX: plain integer multiply instead of
                                    // pow(d, 3), avoiding unnecessary
                                    // floating-point rounding risk
        n /= 10;
    }
    return check == temp;
}
// TC - O(log10(n)), SC - O(1)


/*
================================================================================
PART 6 : DIVISORS / FACTORS
================================================================================
A divisor of n is any number that divides n with remainder 0 - i.e. a factor.
*/

// Brute force - check every number from 1 to n
vector<int> factorsBrute(int n) {
    vector<int> fact;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0)
            fact.emplace_back(i);
    }
    return fact;
}
// TC - O(n), SC - O(m) where m = number of factors found


// Optimized - factors come in pairs (i, n/i). Once i exceeds sqrt(n), every
// remaining factor has ALREADY been found as the paired n/i of some smaller i.
// So it's enough to loop only up to sqrt(n).
vector<int> factorsOptimized(int n) {
    vector<int> fact;
    for (int i = 1; (long long)i * i <= n; i++) {   // i*i preferred over i<=sqrt(n)
        if (n % i == 0) {                            // to avoid floating point
            fact.emplace_back(i);                     // inaccuracies from sqrt()
            if (i != n / i)
                fact.emplace_back(n / i);
        }
    }
    sort(fact.begin(), fact.end());
    return fact;
}
// TC - O(sqrt(n)) for the loop + O(m log m) for the sort, where m = number of
//      factors found (m is usually much smaller than sqrt(n))
// SC - O(m)


/*
================================================================================
PART 7 : PRIME NUMBER CHECK
================================================================================
A prime number has EXACTLY two factors: 1 and itself.
*/

bool checkPrime(int n) {
    if (n < 2)                 // FIX: 0 and 1 are NOT prime; without this
        return false;           // check, checkPrime(1) incorrectly returned true
    for (int i = 2; (long long)i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}
// TC - O(sqrt(n)), SC - O(1)
// For checking MANY numbers up to some limit, a Sieve of Eratosthenes
// (precompute primality for every number up to N once) is far more efficient
// than calling checkPrime() repeatedly - worth learning next.


/*
================================================================================
PART 8 : GCD / HCF (Greatest Common Divisor / Highest Common Factor)
================================================================================
Multiple approaches shown from weakest to strongest, since seeing WHY each one
is improved on is more useful than only seeing the final efficient version.
*/

// ---- Approach 1: brute force via finding all factors of both numbers ----
vector<int> factorsForGCD(int n) {
    vector<int> fact;
    for (int i = 1; (long long)i * i <= n; i++) {
        if (n % i == 0) {
            fact.emplace_back(i);
            if (i != n / i)
                fact.emplace_back(n / i);
        }
    }
    return fact;
}

int GCDviaFactors(int a, int b) {
    auto facta = factorsForGCD(a);
    auto factb = factorsForGCD(b);
    int best = 1;
    for (auto i : facta)
        for (auto j : factb)
            if (i == j && i > best)
                best = i;
    return best;
}
// TC - O(sqrt(a) + sqrt(b) + |facta|*|factb|)  -  wasteful, mainly educational


// ---- Approach 2: check every number from min(a,b) downward ----
int GCDLinearScan(int a, int b) {
    for (int i = min(a, b); i >= 1; i--) {
        if (a % i == 0 && b % i == 0)
            return i;
    }
    return 1;
}
// TC - O(min(a,b))  -  much simpler, but still slow for large a, b


// ---- Approach 3: Euclidean algorithm via repeated subtraction ----
// Identity: gcd(a,b) = gcd(a-b, b), for a > b
int GCDEuclidSubtractive(int m, int n) {
    m = abs(m);
    n = abs(n);
    if (n == 0) return m;
    if (m == 0) return n;
    if (n > m) return GCDEuclidSubtractive(n, m);   // keep m as the larger one
    return GCDEuclidSubtractive(m - n, n);
}
// TC - O(max(a,b)) worst case (e.g. GCD(10000, 1) subtracts 1, ten thousand
//      times). Average case roughly O(max/min).
// SC - O(max(a,b)) due to recursion depth in the worst case


// ---- Approach 4: Euclidean algorithm via modulo (recursive) - THE STANDARD ----
// Identity: gcd(a,b) = gcd(b, a % b)
// This is a big improvement over Approach 3: instead of subtracting b from a
// one step at a time (which is what a % b effectively "skips ahead" through
// in one operation), a % b jumps straight to the final remainder.
int GCDEuclidRecursive(int a, int b) {
    if (b == 0)
        return a;             // gcd(a, 0) = a, by definition
    return GCDEuclidRecursive(b, a % b);
}
// TC - O(log(min(a,b)))   -  the remainder shrinks by at least half every two
//      steps in the worst case (Fibonacci-like numbers are the true worst
//      case, giving a logarithm base close to the golden ratio, phi).
// SC - O(log(min(a,b)))   -  recursion depth matches the time complexity here

/*
Worked traces:

  GCD(9, 12):
    (9,12) -> b!=0, go to (12, 9%12=9)... wait order matters, see note below.
    Correct call order once b>a naturally resolves itself after one step
    since a%b handles it regardless of which is larger:
    (9,12) -> (12, 9)   [a=9,b=12 -> next call GCDEuclidRecursive(12, 9%12=9)]
    (12,9) -> (9, 3)    [12%9 = 3]
    (9,3)  -> (3, 0)    [9%3 = 0]
    (3,0)  -> returns 3

  GCD(6, 8):
    (6,8) -> (8, 6)     [6%8 = 6]
    (8,6) -> (6, 2)     [8%6 = 2]
    (6,2) -> (2, 0)     [6%2 = 0]
    (2,0) -> returns 2

  GCD(7, 39):
    (7,39) -> (39,7) -> (7,4) -> (4,3) -> (3,1) -> (1,0) -> returns 1
*/


// ---- Approach 5: Euclidean algorithm, iterative (no recursion overhead) ----
int GCDEuclidIterative(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
// TC - O(log(min(a,b))), SC - O(1)  <- best of both worlds: fast AND no
//      recursion stack usage. Preferred in practice for tight loops / large
//      inputs where recursion's stack overhead matters.


/*
================================================================================
PART 9 : LCM (Least Common Multiple)
================================================================================
Relies on the identity:  LCM(a,b) * GCD(a,b) = a * b
So:                       LCM(a,b) = (a * b) / GCD(a,b)
*/

long long LCM(int a, int b) {
    // NOTE: compute a*b as long long FIRST (before dividing) to avoid
    // integer overflow when a and b are both large ints.
    return ((long long)a * b) / GCDEuclidIterative(a, b);
}
// TC - O(log(min(a,b)))  -  dominated by the GCD call
// SC - O(1)


//Some problems:
//---------------------------------------------------------------------------------------------------------------------------

//1. Print all divisors of a number
void divisors(int n){
    if(n==0)
        cout<<"1, 2, 3, ..., infinity"<<endl;

    for(int i=1;i<=n;i++){
        if(n%i==0)
            cout<<i<<" ";
    }
}

void divisorsBet(int n){
    if(n==0)
        cout<<"1, 2, 3, ..., infinity"<<endl;
    else if(n==1)
        cout<<1<<" ";
    else{
        cout<<1<<" ";
        int j=int(sqrt(n))+1;
        for(int i=2;i*i<=n;i++){
            if(n%i==0){
                if(i*i == n)
                    cout<<i<<" ";
                else{
                    cout<<i<<' ';
                    while(j<n){
                        if(n%j==0)
                            cout<<j<<" ";
                        j++;
                    }
                }
            }
        }
        cout<<n<<" ";
    }
        
}
//Tc - O(n), SC - O(1)

void divisorOpt(int n){
    if(n==0)
        cout<<"1, 2, 3, ..., infinity"<<endl;
    else{
        cout<<1<<" ";
        for(int i=2;i*i<n;i++){
            if(n%i==0)
                if(i*i!=n)
                    cout<<i<<" "<<(n/i)<<" ";
                else
                    cout<<i<<" ";
        }
        if(n!=1)
            cout<<n<<" ";
    }
}
//TC - O(sqrt(n)), SC - O(1)

auto divisorOpt_ret(int n){
    vector<int> arr={1, n};
    if(n==0)
        return vector<int>();

    else if(n==1)
        return vector<int>{1};

    else{
        for(int i=2;i*i<=n;i++){
            if(n%i==0){
                arr.push_back(i);
                if(i*i!=n)
                    arr.push_back(n/i);
            }
        }
            
    }
    return arr;
}

//---------------------------------------------------------------------------------------------------------------------------

//2.Check number is prime
bool checkPrime(int n){
    if(n<2)
        return false;

    for(int i=2;i*i<=n;i++){
        if(n%i==0)
            return false;
    }
        
    return true;
}
//TC - O(sqrt(n)), SC - O(1)


//---------------------------------------------------------------------------------------------------------------------------

//3. Return all prime factors of a number
auto pfactors(int n){
    vector<int> arr=divisorOpt_ret(n);
    vector<int> prime_fact;
    for(auto v:arr){
        if(checkPrime(v))
            prime_fact.push_back(v);
    }
    return prime_fact;
}
//Tc - O(m√n), SC - O(m), where m is number of factors of a number


auto pfactorsBet(int n){
    if(n==0)
        return vector<int>{};

    vector<int> prime_fact;
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            if(checkPrime(i))
                prime_fact.push_back(i);

            if(i*i!=n && checkPrime(n/i))
                prime_fact.push_back(n/i);
        }
    }
    return prime_fact;
}
//TC - O(√(n.m)) on average where m is average of all factors, SC - O(k), where k is no of prime factors

//Dividing the n with prime factor until its possible and shrunking it
//Using practical approach of how we solve it 

//  2|780
//  2|390
//  2|195
//  3|65
//  5|13
// 13|1

auto pfactorOpt(int n){
    vector<int> prime_factor;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            prime_factor.push_back(i);
            while(n%i==0)    
                n/=i;
        }
    }
    if(n!=1)
        prime_factor.push_back(n);

    return prime_factor;
}
//TC - O(√n.logn), not exact just on average, SC - o(k), where k is no of prime factors

//Find given exponent of a given no without using pow()
int powerEx(int n, int m){
    int res=1;
    for(int i=m;i>0;i--){
        res*=n;
    }
    return res;
}
//Tc - O(m), Sc - o(1)

int powerExOpt(int n, int m, int res){
    if(m==0)
        return res;
    else if(m%2 != 0){
        res*=n;
        m-=1;
        return powerExOpt(n,m,res);
    }
    else{
        n*=n;
        m/=2;
        return powerExOpt(n,m,res);
    }
}
//TC - O(logm), SC - O(logm)

auto powerExOptL(float n, int m){
    float res=1;
    int k=m;
    m=abs(m);
    while(m!=0){
        if(m%2!=0){
            m-=1;
            res*=n;
        }
        else{
            m/=2;
            n*=n;
        }
    }
    if(k>=0)
        return res;
    else
        return (1.0f/res);
}
//Tc - o(logm), Sc - O(1)

//---------------------------------------------------------------------------------------------------------------------------

//4. Sieve of Erasthonies  
//Given a no n print all prime nos till there
void Sieve(int n){
    for(int i=2;i<=n;i++){
        if(checkPrime(i))
            cout<<i<<" ";
    }
}
//Tc - O(n√n), SC - O(1)

//Using sieve of erathosthenes, a blackbox which checks a no is prime or not in O(1)
void SieveOpt(int n){
    unordered_map<int, int> mpp;
    for(int i=2;i<=n;i++){
        mpp[i];
        if(mpp[i]==0){
            cout<<i<<" ";
            int k=i+i;
            while(k <= n){
                mpp[k]=1;
                k+=i;
            }
        }
    }
}
//TC - O(nloglogn) (may be greater then as k!=i*i), Sc - O(n)
//Why its cvorrect: any composite no will have a prime factor lesser then it, So there cannot be a no composite but not have a factor below it.

// 2 things:
//1. take k=i*i i.e take multiles to mark with 1 to be from ith multiple and not 2 as i*k=m, k<i, has k as factor if its prime then it has already marked, if its composite then that k will have prime factor back and it has been marked it with 1
// 2. loop only till sqrt(n) due to the fact that: all composite_i>sqrt(n) will have a prime factor lesser then sqrt(n) So all composite already marked and left out are prime; i could not do it in hash_map as at end there will no prime>sqrt(n) initialised as key if looped upto sqrt(n).


void SieveOptR(int n){
    vector<bool> arr(n+1, 0);

    int i,j;
    for(i=2;i*i<=n;i++){
        if(arr[i]==0){
            cout<<i<<" ";
            int k=i*i;
            while(k<=n){
                arr[k]=1;
                k+=i;
            }
        }
    }
    for(j=i;j<=n;j++){
        if(arr[j]==0)
            cout<<j<<" ";
    }
}
//Tc - O(nlog(logn)), Sc - O(n)

//---------------------------------------------------------------------------------------------------------------------------

//5. Find the no of primes between L and R
// constraints: (query based problem)
//     Q <= 10^5
//     L <= R <= 10^6 
// example:
//     Q=3
//         L=3, R=10
//         L=8, R=20
//         L=1, R=5

void primeBetLR(int L, int R){
    for(int i=L;i<=R;i++){
        if(checkPrime(i))
            cout<<i<<" ";
    }
    cout<<endl;
}

void Query(){
    int n;
    int L, R;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>L>>R;
        primeBetLR(L, R);
    }
}

//Same just prints prime nos rather then giving a int
int primeBetLR2(int L, int R){
    int res=0;
    for(int i=L;i<=R;i++){
        if(checkPrime(i))
            res+=1;
    }
    return res;
}

void Query2(){
    int n;
    int L, R;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>L>>R;
        cout<<primeBetLR2(L, R)<<endl;
    }
}


//TC -O(n.m.sqrt(R)), where m is R-L+1, n-no of queries, SC - O(1)
// The problem is the vals are multiplying so in worst case when q=10^5, L=1, R=10^6 no time = 10^5.10^6.sqrt(10^6) = 10^11+3 = 10^14, So cpp executes 10^9 statement per sec taking 10^5 secs to execute 10^14 statements.


//Better way is to make the prime check black box by implementing sieve 
auto Getsieve(int n){
    vector<int> pr(n+1, 0);
    pr[0]=1;
    
    if(n>0)
        pr[1]=1;

    vector<int> res;
    int i,j;
    for(i=2;i*i<=n;i++){
        if(pr[i]==0){   
            res.push_back(i);
            int k=i*i;
            while(k<=n){
                pr[k]=1;
                k+=i;
            }
        }
    }
    return pr;
}

void primLRBet(vector<vector<int>> arr){
    int q=arr.size();
    int L, R;
    vector<int> temp;

    int maxR=INT_MIN;
    vector<int> sievRes;

    for(int i=0;i<q;i++){
        for(int j=0;j<2;j++){
            temp=arr[j];
            maxR=max(maxR, temp[1]);
        }
    }

    sievRes = Getsieve(maxR);

    for(int i=0;i<q;i++){
        cout<<endl<<i<<endl;
        int res=0;
        temp=arr[i];
        L=temp[0];
        R=temp[1];

        for(int j=L;j<=R;j++){
            if(sievRes[j]==0){
                res++;
                cout<<j<<" ";
            }
        }
        cout<<endl;
        cout<<"Result: "<<res<<endl;
    }
}
//Tc - O(R.log(log(R)) + qR), Sc - O(R)

// Using prefix sum: that is replacing every val with sum of vals upto that in result of getsieve

auto GetSieveOpt(int n){
    vector<int> pr(n+1, 1);

    if(n>=0){
        pr[0]=0;
        if(n>0)
            pr[1]=0;
    }

    int sum=pr[0];
    for(int i=2;i<=n;i++){
        if(pr[i]==1){
            sum+=pr[i];
            pr[i]=sum;
            
            int k=i*i;
            while(k<=n){
                pr[k]=0;
                k+=i;
            }
        }
        else
            pr[i]=sum;
    }
    
    // int sum=pr[0];
    // for(int i=2;i<=n;i++){
    //     sum+=pr[i];
    //     pr[i]=sum;
    // }
    return pr;
}

void PrimeSumLROpt(vector<vector<int>>& arr){
    int maxR=INT_MIN, ans;
    int q=arr.size();
    vector<int> temp;

    for(int i=0;i<q;i++){
        temp=arr[i];
        maxR = max(maxR, temp[1]);
    }
    vector<int> primeSum = GetSieveOpt(maxR);

    for(int i=0;i<q;i++){
        temp=arr[i];
        if(temp[0]>0){
            ans = (primeSum[temp[1]] - primeSum[temp[0]-1]);
            cout<<"No of Primes between "<<temp[0]<<"-"<<temp[1]<<": "<<ans<<endl;
        }
        else{
            ans = primeSum[temp[1]];
            cout<<"No of Primes between "<<temp[0]<<"-"<<temp[1]<<": "<<ans<<endl;
        }
    }
}
//TC - O(klog(logk) + q), where k is max(R), SC - O(max(R))


//---------------------------------------------------------------------------------------------------------------------------

//6. Prime factorization of a number 
void Primefactorization(vector<int>& arr){
    vector<int> res;
    for(int q=0;q<arr.size();q++){
        res.clear();
        int n=arr[q];
        for(int i=2;i*i<=n;i++){
            if(n%i==0){
                while(n%i==0){
                    res.push_back(i);
                    n/=i;
                }
            }
        }
        if(n!=1)
            res.push_back(n);
        
        for(auto v:res)
            cout<<v<<" ";
        cout<<endl;
    }
}
//Tc - O(q.root(n)), Sc - O(m), where m is no of factors of max(q's elem)


//Trying to reduce Tc and bring it to O(q.log(n)), So has to find the smallest no that prime factor of a index in sieve arr has to abe made in logn time

auto getSieveOptSPF(int n){
    vector<int> spf(n+1);
    for(int i=0;i<=n;i++)
        spf[i] = i;
    // cout<<"Hi";
    for(int i=2;i<=n;i++){
        if(spf[i]==i){
            int k=i*i;
            while(k<=n){
                if(spf[k]==k)
                    spf[k]=i;
                k+=i;
            }
        }
    }
    return spf;
}


void queryOptpfact(vector<int> arr){
    int q = arr.size();
    vector<int> spf;
    int maxN = 0;

    for(int i=0;i<q;i++){
        maxN = max(maxN, arr[i]);
    }

    spf = getSieveOptSPF(maxN);
    // for(auto v:spf)
    //     cout<<v<<" ";
    for(int i=0;i<q;i++){
        int n = arr[i];

        cout<<n<<":"<<endl;
        while(n>1){
            cout<<spf[n]<<" ";
            n/=spf[n];
        }
        cout<<endl;
    }
}
// TC - O(q + mloglogm + q.logm ) cuz in worst case like 16 whose all quotients are divisible by 2 So takes log2(16) steps(others are less then logn and if its prime then happens in 1 step like 17), SC - O(m+1), where m is max(query_elem)

//---------------------------------------------------------------------------------------------------------------------------


/*
================================================================================
PART 10 : main()
================================================================================
*/

int main() {
    int n, m;
    cin >> n >> m;
    cout << "GCD: " << GCDEuclidIterative(n, m) << endl;
    cout << "LCM: " << LCM(n, m) << endl;

        // auto pr = pfactorOpt(427);
    // for(auto v:pr)
    //     cout<<v<<" ";

    // Query();
    // vector<vector<int>> arr;
    // int n;
    // cin>>n;
    // int L, R;

    // for(int i=0;i<n;i++){
    //     cin>>L>>R;
    //     arr.push_back(vector{L, R});
    // }

    // PrimeSumLROpt(arr);

    // int n, elem;
    // cin>>n;
    // vector<int> arr;

    // for(int i=0;i<n;i++){
    //     cin>>elem;
    //     arr.push_back(elem);
    // }
    // queryOptpfact(arr);


    return 0;
}