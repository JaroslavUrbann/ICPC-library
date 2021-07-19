// inclusive:exclusive
// pr[i] = largest number st: p[0:pr[i]] == p[i+1-pr[i]:i+1]
// aka length of the longest border of p[0:i]
vector<int>pre(string &p){
	int m=p.size();
	vector<int>pr(m);
	int i=0,j=1;
	while(j<m){
		if(p[i]==p[j]){
			pr[j]=i+1;
			++j;++i;
		}else if(i)i=pr[i-1];
		else ++j;
	}
	return pr;
}

/*
visualization:
	a tree with |s|+1 nodes rooted at 0:
		the parent of node i is pr[i]
	the size of a subtree i is how many times s[0:i] appears in s
	smaller strings are at the top, bigger strings are at the bottom
	the path from i to 0 contains all suffixes of s[0:i] that are also prefixes of s
	(in the decreasing order of length)
*/
