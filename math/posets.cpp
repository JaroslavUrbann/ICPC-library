/*
partially ordered sets (posets):
example: points on a plane and (x1,y1)<=(x2,y2) iff x1<=x2 and y1<=y2.
A chain is a set of elements a1...an such that a1<=a2<=...<=an
A partition is a set of chains where each element belongs to exactly one chain
An antichain is a set of elements such that no two elements are comparable.
Dilworth's theorem says that |maximum antichain| == |minimum partition|
The width of a poset is the size of the maximum antichain
The height of a poset is the size of the maximum chain
You can calculate the width by maximum matching:
1) split each node into two (input and output) (becomes bipartite)
2) |unmatched verticies| / 2 == |minimal partition|
3) => nodes not in vertex cover have the same cardinality
   and aren't comparable => that's your maximum antichain

mirsky's theorem:
you can partition a poset into n antichains, where n is the length of the longest chain
(just pop all sources n times)
*/
