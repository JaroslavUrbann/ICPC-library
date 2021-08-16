// https://codeforces.com/blog/entry/75885
// amazing data structure
/*
you have a rooted tree with light and heavy edges,
each node has at most 1 heavy edge going down.
you represent continuous paths on this tree with splay trees:
1) my left children in the splay tree are above me in the LCT, right children below.
2) you can re-root the splay tree in log(n)
3) you can merge 2 splay trees in O(1)

"vir" holds LCT subtree information for a node's subtree except for
the part that is connected with a heavy edge.
"sub" hold the same information for the whole subtree
"self" and "path" hold the same information at the level of a splay tree.

if you have a un-un-doable query (max,min,gcd...), keep a datastructure instead of vir
(multiset / treap for gcd)
*/

struct SplayTree {
  struct Node {
    int ch[2] = {0, 0}, p = 0;
    ll self = 0, path = 0;        // Path aggregates
    ll sub = 0, vir = 0;          // Subtree aggregates
    bool flip = 0;                       // Lazy tags
  };
  vector<Node> T;
 
  SplayTree(int n) : T(n + 1) {}

  // normal lazy push
  void push(int x) {
    if (!x || !T[x].flip) return;
    int l = T[x].ch[0], r = T[x].ch[1];
 
    T[l].flip ^= 1, T[r].flip ^= 1;
    swap(T[x].ch[0], T[x].ch[1]);
    T[x].flip = 0;
  }
  
	// normal pull update
  void pull(int x) {
    int l = T[x].ch[0], r = T[x].ch[1]; push(l); push(r); 
 
    T[x].path = T[l].path + T[x].self + T[r].path;
    T[x].sub = T[x].vir + T[l].sub + T[r].sub + T[x].self;
  }
  
	// d-th child of x is y
  void set(int x, int d, int y) {
    T[x].ch[d] = y; T[y].p = x; pull(x); 
  }
 
	// makes x root
  void splay(int x) { 
    auto dir = [&](int x) { // 0 = left child, 1 = right child
      int p = T[x].p; if (!p) return -1;
      return T[p].ch[0] == x ? 0 : T[p].ch[1] == x ? 1 : -1;
    };
    auto rotate = [&](int x) { // z->y->x
      int y = T[x].p, z = T[y].p, dx = dir(x), dy = dir(y);
      set(y, dx, T[x].ch[!dx]);  // y takes x's children
      set(x, !dx, y); // x becomes parent of y
      if (~dy) set(z, dy, x); 
      T[x].p = z;
    };
    for (push(x); ~dir(x); ) {
      int y = T[x].p, z = T[y].p;
      push(z); push(y); push(x);
      int dx = dir(x), dy = dir(y);
      if (~dy) rotate(dx != dy ? x : y);
      rotate(x);
    }
  }
};
 
struct LinkCut : SplayTree {
  LinkCut(int n) : SplayTree(n) {}
 
	// makes x root of a splay tree that contains exactly the whole path x<->root
  int access(int x) {
    int u = x, v = 0;
    for (; u; v = u, u = T[u].p) {
      splay(u); 
      int& ov = T[u].ch[1];
      T[u].vir += T[ov].sub;
      T[u].vir -= T[v].sub;
      ov = v; pull(u);
    }
    return splay(x), v;
  }
	
	// you can reroot by flipping, since everytime you touch a node, you splay it,
	// and while splaying, you go from splay root and push down the flip update
  void reroot(int x) { 
    access(x); T[x].flip ^= 1; push(x); 
  }
  
	// connects u to v
  void Link(int u, int v) { 
    reroot(u); access(v); 
    T[v].vir += T[u].sub;
    T[u].p = v; pull(v);
  }
  
	// disconnects u and v
  void Cut(int u, int v) {
    reroot(u); access(v);
    T[v].ch[0] = T[u].p = 0; pull(v);
  }
  
  // Rooted tree LCA. Returns 0 if u and v aren't connected.
  int LCA(int u, int v) { 
    if (u == v) return u;
    access(u); int ret = access(v); 
    return T[u].p ? ret : 0;
  }
  
  // Query subtree of u where v is outside the subtree.
  ll Subtree(int u, int v) {
    reroot(v); access(u); return T[u].vir + T[u].self;
  }
  
  // Query path [u..v]
  ll Path(int u, int v) {
    reroot(u); access(v); return T[v].path;
  }
  
  // Update vertex u with value v
  void Update(int u, ll v) {
    access(u); T[u].self = v; pull(u);
  }
};
