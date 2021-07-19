// O(V^3)
// does dp where k is "you can use nodes that are <=k"
// finds better paths going i->k k->j instead of i->j
// can find negative cycles by running the algo again
// NOT TESTED
const ll inf=LLONG_MAX;
const int N=100;
ll dp[N][N],g[N][N];
int nxt[N][N];
int n;

// graph contains negative cycles if dp[i][j] is -inf
void floydwarshall(){
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			dp[i][j]=inf;
	for(int i=0;i<n;++i)dp[i][i]=0,nxt[i][i]=i;
	for(int k=0;k<n;++k)
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j){
				dp[i][j]=max(-inf,min(dp[i][j],dp[i][k]+dp[k][j]));
				nxt[i][j]=nxt[i][k];
			}
	for(int k=0;k<n;++k)
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				if(dp[i][j]>dp[i][k]+dp[k][j]){
					dp[i][j]=-inf;
					nxt[i][j]=-1;
				}
}	
