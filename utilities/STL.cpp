#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpi;

int main()
{   
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    double pi = 3.14159; int x = 12; bool flag = false;
    // Precision / floating point
    cout << fixed << setprecision(2) << pi << '\n';

    // Width / alignment
    cout << setw(5) << x << '\n';       // pad to 5 chars
    cout << left << setw(5) << x;       // left-aligned
    cout << right << setw(5) << x;      // right-aligned

    // Fill character
    cout << setfill('0') << setw(5) << x << '\n';  // 00012

    // Bool as true/false
    cout << boolalpha << flag << '\n';
    cout << noboolalpha << flag << '\n';  // 0 or 1

    // Hex / Oct / Dec
    cout << hex << x << '\n';
    cout << oct << x << '\n';
    cout << dec << x << '\n';

    // Show sign
    cout << showpos << x << '\n';
    cout << noshowpos << x << '\n';
    // Lambda functions
    int a;
    auto f = [](){};        // empty capture: no outer variables, only parameters + globals
    auto f = [=](int x){cout <<a;};  // capture all outer variables by value
    auto f = [&](int x){a=2;};  // capture all outer variables by reference
    // Sort using custom function
    vpi P = {{1,2},{3,0},{2,5}};
    sort(P.begin(), P.end(), [](auto &a, auto &b){ return a.second < b.second; });
    
    vi vec = {1,2,3};
    sort(vec.begin(), vec.end()); // sort ascending
    sort(vec.rbegin(), vec.rend()); // descending

    // Fills v with sequentially increasing values, starting from 0
    vi v(10); iota(v.begin(), v.end(),0);

    // string containing 10 copies of 'a'
    string a(10, 'a');
    // String-int conversion
    int i = stoi("42"); 
    string s = to_string(i);
    
    const char * cstr = s.c_str(); // string to c style string
    
    // transform string to lowercase
    string t = "HOLA";
    transform(t.begin(), t.end(), t.begin(), ::tolower);

    string spaces = "         a a   jdsa";
    // Remove leading spaces
    spaces.erase(spaces.begin(), find_if(spaces.begin(), spaces.end(),
                                [](auto c){ return !isspace(c); }));

    // Remove all spaces 
    spaces.erase(remove(spaces.begin(), spaces.end(), ' '), spaces.end());

    // Remove all tabs, newlines, spaces, etc...
    spaces.erase(remove_if(spaces.begin(), spaces.end(),
                       [](auto c){ return isspace(c); }),
        spaces.end());

    // Split
    vector<string> tok; string tmp;
    stringstream ss(s);
    while (ss >> tmp) tok.push_back(tmp);


    // Pair priority queues using lexicographical order. 
    priority_queue<pii, vpi , greater<pii>> min_pq;
    priority_queue<pii> max_pq;

    // Min max element 
    auto [mn, mx] = minmax_element(v.begin(), v.end());

    // Unique
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    int x = clamp(x, -1, 1);
}
