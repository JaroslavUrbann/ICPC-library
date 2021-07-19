vector<ll>manacher(string s){
	ll n=2*s.length()+1;
	vector<ll>L(n,0);
	L[1]=1;
	ll C=1,R=2; // center, centerRight
	ll diff=-1;
	for(int i=2;i<n;++i){
		L[i]=0;
		diff=R-i;
		if(diff>0)L[i]=min(L[2*C-i],diff);
		ll l=i-L[i],r=i+L[i];
		while(l>0&&r<n&&(((r+1)%2==0)||(s[(r+1)/2]==s[(l-1)/2]))){
			L[i]++;r++;l--;
		}
		if(r>R){
			C=i;
			R=r;
		}
	}
	// returns lengths of pallindromes, e.g. for aabbaa
	// | a | a | b | b | a | a |
	// 0 1 2 1 0 1 6 1 0 1 2 1 0
	return L;
}

