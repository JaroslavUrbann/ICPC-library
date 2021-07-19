// returns indexes of longest strictly increasing subsequence
template<class T>
vector<int>lis(vector<T>&a){
	int n=a.size();
	vector<int>bst,p(n,-1),res;
	for(int i=0;i<n;++i){
		auto it=lower_bound(bst.begin(),bst.end(),i,[&](int x,int y){
			return a[x]<a[y]; // STRICTLY INCREASING BY DEFAULT
		}); 
		if(it!=bst.begin())p[i]=*prev(it);
		if(it==bst.end())bst.push_back(i);
		else *it=i;
	}
	for(int i=bst.back();~i;i=p[i])res.push_back(i);
	reverse(res.begin(),res.end());
	return res;
}
