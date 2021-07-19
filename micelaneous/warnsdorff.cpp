// knight begins at x,y and has to visit all squares exactly once
// O(N*N)
const int N=8;
int acc[N][N];
int f[N][N];
int x,y;
int dx[8]={1,1,-1,-1,2,2,-2,-2};
int dy[8]={2,-2,2,-2,1,-1,1,-1};

vector<pair<int,int>>moves(int y,int x){
	vector<pair<int,int>>res;
	for(int i=0;i<8;++i){
		int ny=y+dy[i];
		int nx=x+dx[i];
		if(ny>=0&&nx>=0&&ny<N&&nx<N&&f[ny][nx]==-1)res.push_back({ny,nx});
	}
	return res;
}

int dfs(int y,int x,int cnt){
	if((f[y][x]=cnt)==N*N)return 1;
	auto m=moves(y,x);
	if(m.empty()){f[y][x]=-1;return 0;}
	sort(m.begin(),m.end(),[&](auto p,auto q){
		return moves(p.first,p.second).size()<moves(q.first,q.second).size();
	});
	for(auto mov:m)if(dfs(mov.first,mov.second,cnt+1))return 1;
	f[y][x]=-1;
	return 0;
}

signed main(){
	cin.tie(0);cin.sync_with_stdio(0);
	cin>>x>>y;--x;--y;
	memset(f,-1,sizeof(f));
	assert(dfs(y,x,1));
	for(int i=0;i<N;++i,cout<<endl)
		for(int j=0;j<N;++j)
			cout<<f[i][j]<<" ";
}
