//libraries begin
#include<bits/stdc++.h>
#include <iostream>
#include<chrono>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace std::chrono;
using namespace __gnu_pbds;
  
#define ordered_set tree<int32_t, null_type,less<int32_t>, rb_tree_tag,tree_order_statistics_node_update>
typedef tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set_pair;
//libaries end
 
 
//selfddefined macros begin
#define fast_io ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define endl "\n"
#define yes cout<<"YES"<<endl
#define no cout<<"NO"<<endl
#define sz(x) (int)x.size()
#define max(x, y) (y-x >> 31 & (x^y) ^ y)
#define min(x, y) (y-x >> 31 & (x^y) ^ x)
#define iterate cin>>t; while(t--)
#define int long long int 
#define F first
#define S second
#define si set<int>
#define pii pair<int, int>
#define vpi vector<pii>
#define vpp vector<pair<int, pii>>
#define mii map<int, int>
#define mpi map<pii, int>
#define spi set<pii>
#define all(x) x.begin(), x.end()
#define double long double 
#define printArray(a) for(auto x: a) cout<<x<<" "; cout<<endl;
#define printPair(a) for(auto x: a) cout<<x.F<<" "<<x.S<<" "; cout<<endl;
#define printArrayFrom(a, x, y) for(int i = x; i <= y; i++) cout<<a[i]<<" "; cout<<endl;
typedef double lld;
//selfdefined macros end

const int infinity=1e9+7;
int t = 0;

vector<pii> moves = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}}; //use for grid traversal in graphs
 
void findArea(vector<vector<int>> &vis, int x, int y, int n, int m, int &cells)
{
    //using recursion to traverse the grid with U, D, R, L operations adn counting the white cells in each interation
    cells++;
    vis[x][y] = 1;
 
    for(int i = 0; i < sz(moves); i++)
    {
        int dx = x + moves[i].F, dy = y + moves[i].S;
 
        if(dx >= 0 and dx < n and dy >= 0 and dy < m and !vis[dx][dy])
        {
            findArea(vis, dx, dy, n, m, cells);
        }
    }
}
 
    

int32_t main()
{
   
	//fast input output macro
    fast_io;
    int n;
 
    cin>>n;
    n += 2;
 
    vector<vector<char>> a(n + 5, vector<char>(n + 5));
 
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin>>a[i][j];
        }
    }
 
    vector<vector<int>> vis(n + 5, vector<int>(n + 5, 0));  //for marking the cell to be traversed
    
     for(int i = 0; i < n; i++)
        {
        for(int j = 0; j < n; j++)
        
            if(a[i][j] == 'b')
            {
                vis[i][j] = 1;  //marking the black cells as not to be visited
            }
        
        }
 
    int connectedComponents = 0;
    vector<int> cellArea;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(!vis[i][j])
            {
                //traversing to count the number connected componenets and count the number of white cells in the same
                int cells = 0;
                findArea(vis, i, j, n, n, cells);
                cout<<"cells = "<<cells<<endl;
                cellArea.push_back(cells);
                connectedComponents++;
            }
        }
    }
    cout<<"Number of white areas = "<<connectedComponents<<endl;
    for(int i = 0; i < connectedComponents; i++)
    {
        cout<<"Area "<<i<<" has "<<cellArea[i]<<" white cells\n";     //display the output
    }
    
    
   
    return 0;
 
} 