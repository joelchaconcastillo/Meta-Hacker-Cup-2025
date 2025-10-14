#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > extract_perm(vector<int> &a){
	vector<vector<int> > res;
	int i = 0;
	while(i<a.size()){
		if(a[i]==1){
			int l = i+1;
			while(l<a.size() && a[l-1] < a[l] && a[l]-a[l-1] == 1)l++;
			vector<int> tmp;
			for(int j = i; j < l; j++)tmp.push_back(a[j]);
			res.push_back(tmp);
			i=l;
		}else{
		       int l = i;
		       while(l<a.size() && a[l]!=1)l++;
		       vector<int> tmp;
		       for(int k = 0; k  < a[l-1]; k++,i++){
			       tmp.push_back(a[i]);
		       }
		       res.push_back(tmp);
		}
	}
	return res;
}
void solve(){
   int N; cin>>N;
   vector<int> A(N);
   for(int i = 0;i  < N; i++){
	   cin >> A[i];
   }
   auto permutations = extract_perm(A);
   /*for(auto i:permutations){
	   vector<int> tmp(i.size());
	   iota(tmp.begin(), tmp.end(), 1);
	   set<int> t1(i.begin(), i.end());
	   set<int> t2(tmp.begin(), tmp.end());
	   if(t1!=t2){
		   for(auto j:i)cerr<< j <<" ";
		   cerr<<endl;
		   cerr<<"NO"<<endl;
	   }
	   //for(auto j:i)cerr<< j << " ";
	   //cerr<<endl;
   }*/
   reverse(permutations.begin(), permutations.end());
   //  1 2 3
   //    2 3 1
   //    3 1 2
   //  3 1 2 | 1 2 3 4
   //   1 2 3 | 2 3 4 1
   //   2 3 1 | 3 4 1 2
   //            2,2
   //            2+4-0-> 6%2=2
   //
   //     4  3  2
   vector<vector<long long> > res;
   long long total_movements = 0;
   for(int i = 0; i < permutations.size(); i++){
	   int m = permutations[i].size();
	   long long current = (permutations[i][0]-1+m-(total_movements%m))%m;
	   for(int j = 0 ; j < current; j++){
		   res.push_back({2});
	   }
	   res.push_back({1, m});
	   total_movements += current; //= lcm(total_movements, current);
   }
   reverse(res.begin(), res.end());
   cout << res.size()<<endl;
   for(auto row:res){
	   for(auto item:row)cout << item<<" ";
	   cout <<endl;
   }
}
int main(){
  int t, i=1;
  cin>>t;
  while(t--){
	  cout << "Case #"<<i<<": ";
	  solve();
	  i++;
  }
  return 0;
}
