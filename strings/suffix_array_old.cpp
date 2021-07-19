// 1 indexing only
// suffix_array() goes from 1000ms to 350ms with this
void rs(vector<pair<pair<int,int>,int>>&a){
	int n=max(int(a.size()),256);
	vector<int>cnt2(n),cnt1(n); // count of second/first key
	vector<int>used2(n),used1(n); // number of inserted elements for each bucket
	for(auto u:a)++cnt2[u.first.second];
	for(auto u:a)++cnt1[u.first.first];
	partial_sum(cnt2.begin(),cnt2.end(),cnt2.begin());
	partial_sum(cnt1.begin(),cnt1.end(),cnt1.begin());
	vector<pair<pair<int,int>,int>>by2(a.size());
	for(auto u:a)by2[cnt2[u.first.second-1]+used2[u.first.second]++]=u;
	for(auto u:by2)a[cnt1[u.first.first-1]+used1[u.first.first]++]=u;
}

// if you want 2 words sorted, just add $ between them
// lexicographically i-th suffix starts at s[res[i]]
vector<int>suffix_array(string s){
	s+=char(1); // remove for sorted cyclical shifts (and remove -1 & +1 with res + &&i<21)
	int n=s.size(),cl=0; // current number of classes
	vector<int>c(n); // c[i] = class of suffix starting at i
	for(int i=0;i<n;++i)c[i]=s[i];
	vector<pair<pair<int,int>,int>>a(n); // prev bucket cur bucket, suffix idx
	for(int i=0;cl!=n;++i){
		// gets class of itself and it's successor
		for(int j=0;j<n;++j)a[j]={{c[j],c[(j+(1<<i)/2)%n]},j};
		rs(a); // CONSIDER USING SORT() IF ONSITE
		cl=0;
		for(int j=0;j<n;++j)
			if(j&&a[j-1].first==a[j].first)c[a[j].second]=cl;
			else c[a[j].second]=++cl;
	}
	vector<int>res(n-1); // -1 and +1 because I don't want $ at the beginning
	for(int i=0;i<n-1;++i)res[i]=a[i+1].second;
	return res;
}

// vec[i] = length of the longest common prefix of suffixes at sa[i],sa[i+1]
vector<int>lcp(vector<int>&sa,string &s){
	int n=s.size();assert(sa.size()==n);
	vector<int>rank(n),res(n); // inverted sa
	for(int i=0;i<n;++i)rank[sa[i]]=i;
	int cnt=0;
	for(int i=0;i<n;++i)
		if(rank[i]!=n-1){
			int j=i+cnt,k=sa[rank[i]+1]+cnt;
			while(j<n&&k<n&&s[j]==s[k]){++cnt;++j;++k;}
			res[rank[i]]=cnt;
			if(cnt)--cnt;
		}
	// last idx is 0, but I keep it so everything has lenght n
	return res;
}
