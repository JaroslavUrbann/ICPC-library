const int N=4010,inf=1e9;
int cost[N][N];
 
vector<int>dp,newdp;

// if dp has form of dp[i][j]=min(dp[i-1][k] + cost[j][k]) for all k<=j
// and if optk(i,j) <= optk(i,j+1) - proving this will be very hard, be ready
// you can use divide and conquer dp:
// you calculate dp[i][n/2] = res and then use res as upperbound and lower bound
// for other dp values. this way you can get n*n*log(n) runtime
// it's not terribly fast, so you probably have to really optimize the
// whole program, use very fast input/output etc...
 
// do inclusive,inclusive and 1-indexing, trust me
// l,r = what I want to solve for newdp, optl,optr = bounds in dp
void solvedp(int l,int r,int optl,int optr){
	if(l>r)return;
	int m=(l+r)/2;
	pair<int,int>bst={inf,0};
	for(int i=optl;i<=min(m,optr);++i){
		bst=min(bst,{cost[m][i]+dp[i-1],i});
	}
	newdp[m]=bst.first;
	solvedp(l,m-1,optl,bst.second);
	solvedp(m+1,r,bst.second,optr);
}
