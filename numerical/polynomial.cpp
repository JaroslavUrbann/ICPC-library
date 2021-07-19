// https://github.com/bqi343/USACO/blob/master/Implementations/content/numerical/Polynomials/Poly.h

using T=mint;using poly=vector<T>;

poly remz(poly p){while(p.size()&&p.back()==0)p.pop_back();return p;}
poly rev(poly p){reverse(p.begin(),p.end());return p;}
poly shift(poly p,int x){
	if(x>=0)p.insert(p.begin(),x,0);
	else assert(p.size()+x>=0),p.erase(p.begin(),p.begin()-x);
	return p;
}
poly rsz(const poly&p,int x){
	if(x<=p.size())return poly(p.begin(),p.begin()+x);
	poly q=p;q.resize(x);return p;
}
T eval(const poly&p,T x){
	T res=0;
	for(int i=(int)p.size()-1;i>=0;--i)res=x*res+p[i];
	return res;
}
poly dif(const poly&p){
	poly res;
	for(int i=1;i<p.size();++i)res.push_back(i*p[i]);
	return res;
}
poly integ(const poly&p){
	static poly invs{0,1};
	for(int i=invs.size();i<=p.size();++i)invs.push_back(-mod/i*invs[mod%i]);
	poly res(p.size()+1);
	for(int i=0;i<p.size();++i)res[i+1]=p[i]*invs[i+1];
	return res;
}

poly&operator+=(poly&l,const poly&r){
	l.resize(max(l.size(),r.size()));
	for(int i=0;i<r.size();++i)l[i]+=r[i];
	return l;
}
poly&operator-=(poly&l,const poly&r){
	l.resize(max(l.size(),r.size()));
	for(int i=0;i<r.size();++i)l[i]-=r[i];
	return l;
}

poly&operator*=(poly&l,const T&r){
	for(auto&v:l)v*=r;
	return l;
}
poly&operator/=(poly&l,const T&r){
	for(auto&v:l)v/=r;
	return l;
}
poly operator*(const poly&l,const poly&r){
	if(l.empty()||r.empty())return{};
	poly x(l.size()+r.size()-1);
	for(int i=0;i<l.size();++i)
		for(int j=0;j<r.size();++j)
			x[i+j]+=l[i]*r[j];
	return x;
}

poly operator+(poly l,const poly&r){return l+=r;}
poly operator-(poly l,const poly&r){return l-=r;}
poly operator-(poly l){for(auto&v:l)l*=-1;return l;}
poly operator*(poly l,const T&r){return l*=r;}
poly operator*(const T&r,const poly&l){return l*r;}
poly operator/(poly l,const T&r){return l/=r;}
poly&operator*=(poly&l,const poly&r){return l=l*r;}

pair<poly,poly>quorem(poly a,poly b){
	remz(a);remz(b);assert(b.size());
	T lst=b.back(),B=1/lst;
	for(auto&t:a)t*=B;
	for(auto&t:b)t*=B;
	poly q(max((int)a.size()-(int)b.size()+1,0));
	for(int dif;(dif=a.size()-b.size())>=0;remz(a)){
		q[dif]=a.back();
		for(int i=0;i<b.size();++i)a[i+dif]-=q[dif]*b[i];
	}
	for(auto&t:a)t*=lst;
	return {q,a}; // quotient, remainder
}
poly operator/(const poly&a,const poly&b){return quorem(a,b).first;}
poly operator%(const poly&a,const poly&b){return quorem(a,b).second;}
poly gcd(poly a,poly b){return b==poly{}?a:gcd(b,a%b);}
