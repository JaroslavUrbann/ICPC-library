// (https://codeforces.com/blog/entry/88669)

/*
Preorder + Data structures
Dynamic Programming on tree
"Re-rooting" tree DP (where you DP twice, once going down and once propagating from top)
2^K Decomposition of tree (and Lowest Common Ancestor)
virtual/auxiliary tree
	- have a set of red nodes on a tree, we want all paths between all pairs.
 - use the fact that lca's of all pairs are the same as lca's of only adjacent pairs
 - get all red nodes and lca's and create a new compressed tree
 - gradually put nodes on stack (smallest pre-order time first)
 - invariant: node on the top of the stack is a child of the node before it in the stack
 - when adding a new node (by dfs time): is the new node a child of the top node?
 -	yes: add it to stack / no: remove top node and add it to tree that is being built
 - calc ans on smaller tree. Must be able to compress the path from node to any lca in log(n)
Centroid Decomposition
 - centroid = node who's removal guarantees that the largest subtree is as small as possible
 - find centroid by calculating sizes and checking n/2<
 - calculate subproblem for all paths going through centroid
 - remove centroid and solve the same problem for all new trees
Set Merging
 - while doing a bottom-up dp, each node gets added to a set which is a union of all sets
 - of its children (eg. merging convex hulls). You can effectively merge them by doing
 - binomial-heap-like merging where you always just keep log(n) sets of sizes 1,2,4,...
*/


// Kruskal Reconstruction Tree (KRT) (IOI Werewolf trick)
// O(N^2) Distribution DP
// UFDS on tree (See: CEOI 2017 Streets)
// Greedy for furthest node (See: RU Code Funny Salesman)
// reachability trees
