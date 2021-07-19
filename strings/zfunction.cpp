// s[i:] and t have common prefix of length res[i]
vector<int>zf(string s, string t){
	int n=s.size(),m=t.size();
	s=t+'#'+s;
	vector<int>z(s.size());
	int l=0,r=1; // s[l:r] == s[0:r-l]
	for(int i=1;i<=n+m;++i){
		if(i<r)z[i]=min(z[i-l],r-i);
		while(i+z[i]<=n+m&&s[i+z[i]]==s[z[i]])++z[i];
		if(i+z[i]>r){l=i;r=i+z[i];}
	}
	vector<int>res(n);
	for(int i=0;i<n;++i)res[i]=z[i+m+1];
	return res;
}

