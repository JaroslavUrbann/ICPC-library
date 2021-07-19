ll pm(ll a,ll b){return b?(b&1?a:1)*pm(a*a%mod,b/2)%mod:1;}

// works only if mod is prime, use extended euclid otherwise
// (can't use pm(x,phi(mod)-1), since euler's only theorem works for gcd(a,m)==1)
ll inv (ll x) {
    return pm(x, mod-2);
}

ll mul(ll x, ll y){
    return (x * y) % mod;
}

ll divide(ll x, ll y){
    return mul(x, inv(y));
}

ll add(ll x, ll y){
    x = (x + y) % mod;
    while (x < 0) x += mod;
    return x;
}

ll choose(ll n, ll k){
	return F[n]*inv(F[k])%mod*inv(F[n-k])%mod;
}

const int N=505;
mint dpchoose[N][N];
bool donechoose[N][N];
mint F[N];

void calcF(){
	F[0]=1;
	for(int i=1;i<N;++i)F[i]=i*F[i-1];
}

mint choose(int n,int k){
	if(n<k||k<0)return 0;
	if(n==k)return 1;
	if(donechoose[n][k])return dpchoose[n][k];
	donechoose[n][k]=true;
	return dpchoose[n][k]=choose(n-1,k)+choose(n-1,k-1);
}

