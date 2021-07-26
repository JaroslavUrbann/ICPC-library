namespace AHU{
H get(int u,int p,const vector<vector<int>>&g){
	vector<H>children;
	for(int v:g[u])if(v!=p)children.push_back(get(v,u,g));
	sort(children.begin(),children.end());
	H res=makeH('(');
	H bs={1,1};
	for(H&hsh:children)res=(bs*=base)*res+hsh;
	return res*bs*base+makeH(')');
}
int findc(int u,int p,vector<int>&c,int n,const vector<vector<int>>&g){
	int mxsz=0,sz=1;
	for(const int&v:g[u])if(v!=p){
		int csz=findc(v,u,c,n,g);
		mxsz=max(mxsz,csz);
		sz+=csz;
	}
	if(max(n-sz,mxsz)<=n/2)c.push_back(u);
	return sz;
}
// non rooted representation (rooted for each centroid)
vector<H>get(const vector<vector<int>>&g){
	vector<int>c;findc(0,0,c,g.size(),g);
	vector<H>res;
	for(auto u:c)res.push_back(get(u,u,g));
	sort(res.begin(),res.end());
	return res;
}
}

