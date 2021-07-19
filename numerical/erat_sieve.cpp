// prime[i] = highest prime factor of i
vector<int>prime;
vector<int>erat(int n){ // exclusive
	prime.resize(n);
	vector<int>res;
	for(int i=2;i<n;++i)if(!prime[i]){
		res.push_back(i);
		for(int j=i;j<n;j+=i)prime[j]=i;
	}
	return res;
}
unordered_map<int,int>factorize(int x){
	unordered_map<int,int>res;
	while(x!=1){
		++res[prime[x]];
		x/=prime[x];
	}
	return res;
}
