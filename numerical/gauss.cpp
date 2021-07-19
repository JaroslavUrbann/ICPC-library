// 0 = no solution
// 1 = has solution(s)
// it has inf solutions when you skip column
// to get inf solutions, you'd probably have to solve the
// homogenious set of equations and add them together,
// but there can be a whole basis of solutions, so it's not great
template<class T>
int gauss(vector<vector<T>>a,vector<T>&res){
	const T EPS=1e-7;
	auto eq=[&](T a, T b) { return abs(a-b) <= abs(a+b) * EPS || abs(a-b) < EPS; };
	int n=a.size(),m=a[0].size()-1;
	for(int col=0,row=0;col<m&&row<n;++col,++row){
		int p=row;
		// heuristic to stop float error
		for(int i=row;i<n;++i)
			if(abs(a[p][col])<abs(a[i][col]))
				p=i;
		if(eq(a[p][col],0))continue; // skipping column
		for(int i=0;i<=m;++i)swap(a[row][i],a[p][i]);
		for(int i=0;i<n;++i)
			if(i!=row){
				ld c=a[i][col]/a[row][col];
				for(int j=0;j<=m;++j)a[i][j]-=a[row][j]*c;
			}
	}
	res.resize(m,0);
	for(int i=0;i<m;++i)
		if(!eq(a[i][i],0))
			res[i]=a[i][m]/a[i][i];
	// solution doesn't need to exist (maybe low amount of cols)
	for(int i=0;i<n;++i){
		T sm=0;
		for(int j=0;j<m;++j)sm+=res[j]*a[i][j];
		if(!eq(sm,a[i][m]))return 0;
	}
	return 1;
}
