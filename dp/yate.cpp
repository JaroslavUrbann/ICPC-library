/*
https://codeforces.com/blog/entry/45223

F[mask] = sum over all subsets of mask: A[i]

dp[mask][i] = sum of F[submask] for each submask that only differs from mask in bits 0..i
dp[mask][i] = dp[mask][i-1] (leaves bit on, goes to change lower bits) + dp[mask^(1<<i)][i-1] (turns bit off, goes to change lower bits)
if i-th bit of mask is off, then it's just dp[mask][i-1]

for(int mask=0;mask<(1<<mx);++mask){
	dp[mask][-1]=a[mask];
	for(int i=0;i<mx;++i){
		if(mask&(1<<i))dp[mask][i]=dp[mask][i-1]+dp[mask^(1<<i)][i-1];
		else dp[mask][i]=dp[mask][i-1];
	}
	F[mask]=dp[mask][mx-1];
}

*/
