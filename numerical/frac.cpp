struct frac{
	ll n,d;
	frac(ll n_,ll d_):n(n_),d(d_){
		ll g=__gcd(n,d);n/=g,d/=g;
		if(d<0)n*=-1,d*=-1;
	}
	frac(ll n_):frac(n_,1){}
	frac():frac(0){}
	friend frac abs(frac a){return frac(abs(a.n),a.d);}
	friend string to_string(const frac& a){return to_string(a.n)+"/"+to_string(a.d);}
	friend bool operator<(const frac&a,const frac&b){return a.n*b.d<b.n*a.d;}
	friend bool operator==(const frac&a,const frac&b){return a.n==b.n&&a.d==b.d;}
	friend bool operator!=(const frac&a,const frac&b){return a.n!=b.n||a.d!=b.d;}
	frac operator-()const{return frac(-n,d);}
	friend frac operator+(const frac&a,const frac&b){return frac(a.n*b.d+b.n*a.d,a.d*b.d);}
	friend frac operator-(const frac&a,const frac&b){return frac(a.n*b.d-b.n*a.d,a.d*b.d);}
	friend frac operator*(const frac&a,const frac&b){return frac(a.n*b.n,a.d*b.d);}
	friend frac operator*(const frac&a,int b){return a*frac(b,1);}
	friend frac operator*(int b,const frac&a){return a*b;}
	friend frac operator/(const frac&a,const frac&b){return a*frac(b.d,b.n);}
	friend frac operator/(const frac&a,const int&b){return a/frac(b,1);}
	friend frac operator/(const int&a,const frac&b){return frac(a,1)/b;}
	friend frac&operator+=(frac&a,const frac&b){return a=a+b;}
	friend frac&operator-=(frac&a,const frac&b){return a=a-b;}
	template<class T>friend frac&operator*=(frac&a,const T&b){return a=a*b;}
	template<class T>friend frac&operator/=(frac&a,const T&b){return a=a/b;}
};
