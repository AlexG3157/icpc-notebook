#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpi;

int main()
{   
    // Lambda functions
    int a;
    auto f = [](){};        // empty capture: no outer variables, only parameters + globals
    auto f = [=](int x){cout <<a;};  // capture all outer variables by value
    auto f = [&](int x){a=2;};  // capture all outer variables by reference
    
    // Sort using custom function
    vector<pair<int,int>> P = {{1,2},{3,0},{2,5}};
    sort(P.begin(), P.end(), [](auto &a, auto &b){ return a.second < b.second; });
}
