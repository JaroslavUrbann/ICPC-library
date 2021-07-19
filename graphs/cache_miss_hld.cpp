#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

// solving tree path queries in n^2
// little over 3s with n=100100
// if you have a nice dumb looking for loop, use pragmas
// tu[u] maps vertices to new value 0,1,... which is equivalent to the index of all
// needed values of that vertex (k[u],b[u],comp[u],tin[u],tout[u],p[u])
// if two vertices are part of the same comp, the path between them is just u,u+1,u+2,..,v

const int N=100100;
vector<int>g[N];
int sz[N],tu[N],tim,cnu=-1;
int p[N],tin[N],tout[N],comp[N];
ll tmpk[N],tmpb[N];
ll k[N],b[N];

int dfsz(int u,int par){
	if(u)g[u].erase(find(g[u].begin(),g[u].end(),par));
	sz[u]=1;
	for(int v:g[u])sz[u]+=dfsz(v,u);
	sort(g[u].begin(),g[u].end(),[&](int a,int b){
		return sz[a]>sz[b];
	});
	return sz[u];
}

void dfs(int u,int par){
	int &nu=tu[u]=++cnu;
	p[nu]=par;
	k[nu]=tmpk[u];
	b[nu]=tmpb[u];
	tin[nu]=tim++;
	for(int i=0;i<g[u].size();++i)
		if(i)dfs(g[u][i],nu);
		else{
			comp[cnu+1]=comp[nu];
			dfs(g[u][i],par);
		}
	tout[nu]=tim++;
}

int ispar(int u,int v){return tin[u]<=tin[v]&&tout[u]>=tout[v];}

template<class O>
void go(int l,int r,O op){
	for(int i=l;i<=r;++i)op(i);
}

template<class O>
void walk(int u,int v,O op){
	for(int it=0;it<2;++it,swap(u,v))
		while(!ispar(comp[u],v)){
			go(comp[u],u,op);
			u=p[u];
		}
	go(min(u,v),max(u,v),op);
}

void ProGamerMove(){
	int n,q;cin>>n>>q;
	for(int i=0;i<n;++i)cin>>tmpk[i];
	for(int i=0;i<n;++i)cin>>tmpb[i];
	for(int i=0;i<n-1;++i){
		int u,v;cin>>u>>v;--u;--v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	iota(comp,comp+n,0);
	dfsz(0,0);
	dfs(0,-1);
	while(q--){
		int t,u,v;cin>>t>>u>>v;--u;--v;u=tu[u];v=tu[v];
		if(t==1){
			int x,y;cin>>x>>y;
			walk(u,v,[&](int u){k[u]+=x;b[u]+=y;});
		}else{
			int z;cin>>z;
			ll res=LLONG_MIN;
			walk(u,v,[&](int u){res=max(res,k[u]*z+b[u]);});
			cout<<res<<"\n";
		}
	}
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int tc=1;
	//cin>>tc;
	while(tc--)ProGamerMove();
}

