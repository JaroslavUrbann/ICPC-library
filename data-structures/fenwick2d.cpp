// not tested
template<class T>
struct BIT{
	int n,m;
	vector<vector<T>>bit;
	BIT(int n,int m):n(n),m(m),bit(n,vector<T>(m)){}
	T update(int x,int y,T d){
		for(;x<n;x+=x&-x)
			for(int j=y;j<m;j+=j&-j)
				bit[x][j]+=d;
	}
	T query(int x,int y){
		T r=0;
		for(;x;x-=x&-x)
			for(int j=y;j;j-=j&-j)
				r+=bit[x][j];
		return r;
	}
	T query(int x1,int y1,int x2,int y2){
		return query(x2,y2)-query(x1,y2)-query(x2,y1)+query(x1,y1);
	}
};

