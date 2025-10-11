#include <bits/stdc++.h>
using namespace std;
void solve(){
        int n, m, s;
	cin>>n>>m>>s;
	vector<string> grid(n);
	for(int i = 0 ; i <n; i++){
			cin>>grid[i];
	}
	queue<tuple<int, int> > q;
	for(int i = 0 ; i < n; i++) q.push({i,-1}), q.push({i,m});
	for(int j = 0 ; j < m; j++) q.push({-1,j}), q.push({n,j});
	for(int i = 0 ; i < n; i++){
		for(int j = 0 ;j  <m; j++){
			if(grid[i][j] == '#') q.push({i,j});
		}
	}
	vector<tuple<int, int> > directions ={
		{0,-1}, {0,1}, {1,0}, {-1,0}
	};
	unordered_map<int, unordered_map<int, bool>>visited;
	s++;
	while(!q.empty() && s--){
		int _sz = q.size();
		for(int i = 0 ; i< _sz; i++){
			auto [row, col] = q.front(); q.pop();
			if(visited[row][col])continue;
			visited[row][col]=true;
			if(row>=0 && row<n && col>=0 && col<m){
			       	grid[row][col] = '#';
			}
			for(auto [delta_r, delta_c]:directions){
				int next_row = row+delta_r, next_col = col+delta_c;
				if(next_row < 0 || next_row>=n || next_col < 0 || next_col>=m)continue;
				if(visited[next_row][next_col])continue;
				if(grid[next_row][next_col]!='.')continue;
				q.push({next_row, next_col});
			}
		}
	}
	int res = 0;
	for(int i = 0 ;i < n; i++){
		for(int j = 0 ; j < m ;j++){
			if(grid[i][j]!='.')continue;
			queue<tuple<int, int> > q;
			int _sz = 0;
			q.push({i, j});
			while(!q.empty()){
				auto [row, col] = q.front(); q.pop();
				if(grid[row][col]=='#')continue;
				grid[row][col] = '#';
				_sz++;
				for(auto [delta_row, delta_col]:directions){
					int next_row = row+delta_row, next_col = col+delta_col;
					if(next_row < 0 || next_row >=n)continue;
					if(next_col < 0 || next_col >=m)continue;
					if(grid[next_row][next_col]!='.')continue;
					q.push({next_row, next_col});
				}
			}
			res = max(res, _sz);
		}
	}
	cout << res<<endl;
}
int main(){
   int t; cin>>t;
   int i = 1;
   while(t--){
	   cout << "Case #"<<i<<": ";
	   solve();
	   i++;
   }
   return 0;
}
