#include <bits/stdc++.h>
using namespace std;
void solve(){
	int k;
	cin >> k;
	vector<int> A(k), B(k);
	for(int i = 0 ;i < k; i++) cin>>A[i];
	for(int i = 0 ; i  <k; i++) cin>>B[i];
	for(int i = 0 ; i  <k; i++){
		if(B[i] < A[i]){
			cout << -1<<endl;
			return;
		}
	}
	unordered_map<int, int> pos;
	for(int i =0; i < k; i++) pos[A[i]] = i;
	vector<int> indexes(k);
	iota(indexes.begin(), indexes.end(), 0);
	sort(indexes.begin(), indexes.end(), [&](const int i, const int j){
			   return B[i]<B[j];
			});
	vector<pair<int, int> > res;
	for(auto i:indexes){
		if(pos.count(B[i])==0){
			cout << -1 <<endl;
		}else{
			if(A[i]!=B[i]){
				res.push_back({pos[B[i]]+1, i+1});
			}
		}
	}
	cout <<res.size()<<endl;
	for(auto [i,j]:res){
		cout << i<<" "<<j<<endl;
	}
}
int main(){
	int t;
	cin>>t;
	int i = 1;
	while(t--){
		cerr << i <<endl;
		cout << "Case #"<<i<<": ";
		solve();
		i++;
	}
	return 0;
}
/*
   1 2 3 4
   3 4 4 4
   
   0 1 2


 * */
