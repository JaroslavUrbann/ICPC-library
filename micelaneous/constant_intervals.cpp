// https://github.com/kth-competitive-programming/kactl/blob/main/content/various/ConstantIntervals.h

// splits a monotone function into constant intervals and calls g() for each
// checking (l,r) and looking for the end of p (p starts at i)
// and I don't want to reach q
// modified and not compiled yet
template<class P,class T,class F,class G>
void rec(P l,P r,F&f,G&g,P&i,T&p,T q){
	if(p==q)return;
	if(l+1==r){
		g(i,r,p);
		i=r,p=q;
	}else{
		P m=l+(r-l)/2;
		rec(l,m,f,g,i,p,f(m));
		rec(m,r,f,g,i,p,q);
	}
}

template<class P,class F,class G>
void constantIntervals(P l,P r,F f,G g){
	if(l>=r)return;
	P i=l;auto p=f(l),q=f(r-1);
	rec(l,r,f,g,i,p,q);
	g(i,r,q);
}

