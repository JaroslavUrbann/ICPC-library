// 1 if the pattern starts there
vector<int>kmp(string &t,string &p,vector<int>&pr){
	int n=t.size(),m=p.size();
	int i=0,j=0;
	vector<int>res(n);
	while(i<=n){
		if(i<n&&j<m&&t[i]==p[j]){++i;++j;}
		else if(j){
			if(j==m)res[i-m]=1;
			j=pr[j-1];
		}
		else ++i;
	}
	return res;
}
