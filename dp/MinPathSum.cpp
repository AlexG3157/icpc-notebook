#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;

// Given a grid with non negative ints, where you can only move right/down 
// finds the min sum path from top-left to bottom-right.\\
// $O(n \times m)$ Modifies grid.
ll minPathSum(vvi &grid){
    for (int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[0].size(); j++){
            if (i == 0 && j == 0) continue;
            if (i == 0) grid[i][j] += grid[i][j - 1];
            else if (j == 0) grid[i][j] += grid[i - 1][j];
            else grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
        }
    }
    return grid[grid.size() - 1][grid[0].size() - 1];
}