/*
Mám graf a v něm terminal nodes
jakej je nejmenší počet nodes / nejmenší součet váh hran / ...
který můžu vybrat tak, že vzniklej podgraf je connected?
budu vytvářet stromy se spojenejma terminálníma nodama a spojovat je

dp[root][mask] is the best price for a tree of mask terminals rooted at root
the tree is the best of all trees, even ones with intermediary nodes
the algorithm is correct, because the best tree for each submask is already calculated
when using it as a subtree.

for each mask of terminals:
	for each root:
		for each submask:
			dp[root][mask] min= dp[root][submask]+dp[root][othersubmask]
		// dp[root][mask] is calculated, you can reroot the tree
		// (calculate the cost of using the tree as a subtree of a tree rooted at newroot
		for each newroot:
			dp[newroot][mask] min= dp[root][mask] + dist[root][newroot]
*/
