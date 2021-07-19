#include <bits/extc++.h>
__gnu_pbds::gp_hash_table<int,int>real2fake;
vector<int>fake2real;

vector<int>compress(vector<int>a){
	fake2real=a;
	sort(fake2real.begin(),fake2real.end());
	fake2real.erase(unique(fake2real.begin(),fake2real.end()),fake2real.end());
	for(int i=0;i<fake2real.size();++i)real2fake[fake2real[i]]=i;
	vector<int>res;
	for(auto v:a)res.push_back(real2fake[v]);
	return res;
}
