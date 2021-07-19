// bijection between all permutations of length n and numbers (0,n!-1)
// might be useless, bcs 10^n isn't that much and it even might be better time wise
// since you have O(1) acces to elements. So think about using 10^n maybe with bitset

vector<int>perm(int n,int k){
	vector<int>res(n),elems(n);
	iota(elems.begin(),elems.end(),0);
	for(int i=0;i<n;++i){
		int pos=k%(n-i);
		k/=(n-i);
		res[i]=elems[pos];
		elems[pos]=elems[n-i-1];
	}
	return res;
}

// p is items that I'm taking at each step
// what gets written is the position of the item I'm taking (starting from an identity)
// after taking the item, I fill the empty position with the last item
// each sequence of taken positions is unique and so the number is also
// ELEMENTS HAVE TO START FROM 0, OTHERWISE THE BASE STUFF KINDA DOESN'T WORK
int invp(const vector<int>&p){
	int res=0,b=1,n=p.size();
	vector<int>pos(n),elems(n);
	for(int i=0;i<n;++i)pos[i]=elems[i]=i;
	for(int i=0;i<n-1;++i){
		res+=b*pos[p[i]]; // possible vals are (0,n-1), (0,n-2) ..., they can repeat
		// res will be:
		// 1 * (0,n-1)
		// n * (0,n-2)
		// n*(n-1) * (0,n-3)
		// ... this is brilliant, base gets increased by the max val last iter
		b*=(n-i);
		pos[elems[n-i-1]]=pos[p[i]];
		elems[pos[p[i]]]=elems[n-i-1];
	}
	return res;
}

