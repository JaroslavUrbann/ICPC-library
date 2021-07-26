#include <bits/extc++.h>
__gnu_pbds::gp_hash_table<int,int>real2fake;
vector<int>fake2real;

// not tested
// other == inits real2fake
void compress(vector<int>&a,bool other=false){
	int n=a.size();
	vector<pair<int,int>>vals(n);
	for(int i=0;i<n;++i)vals[i]={a[i],i};
	sort(vals.begin(),vals.end());
	int pri=-1,prv=-1;
	for(auto[v,i]:vals){
		if(v!=prv){
			prv=v,++pri;
			fake2real.push_back(v);
			if(other)real2fake[v]=pri;
		}
		a[i]=pri;
	}
}
