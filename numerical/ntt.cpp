// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/NumberTheoreticTransform.h
// multiply pointwise, divide by n, reverse(s+1,e), ntt again

template<class T>
void ntt(vector<T>&a){
	int n=a.size(),L=31-__builtin_clz(n);
	static vector<T>rt(2,1);
	for(static int k=2,s=2;k<n;k*=2,++s){
		rt.resize(n);
		T z[]={1,pow(T::root(),T::mod()>>s)};
		for(int i=k;i<2*k;++i)rt[i]=rt[i/2]*z[i&1];
	}
	vector<int>rev(n);
	for(int i=0;i<n;++i)rev[i]=(rev[i/2]|(i&1)<<L)/2;
	for(int i=0;i<n;++i)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int k=1;k<n;k*=2)
		for(int i=0;i<n;i+=2*k)
			for(int j=0;j<k;++j){
				T z=rt[j+k]*a[i+j+k],&ai=a[i+j];
				a[i+j+k]=ai-z;
				ai+=z;
			}
}

template<class T>
vector<T>conv(const vector<T>&a,const vector<T>&b){
	if(a.empty()||b.empty())return{};
	int s=a.size()+b.size()-1,B=32-__builtin_clz(s),n=1<<B;
	int inv=1/T(n);
	vector<T>L(a),R(b),out(n);
	L.resize(n),R.resize(n);
	ntt(L),ntt(R);
	for(int i=0;i<n;++i)out[-i&(n-1)]=L[i]*R[i]*inv;
	ntt(out);
	return{out.begin(),out.begin()+s};
}
