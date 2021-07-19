// planar graphs:
// graph that can be drawn on a plane in a way that edges intersect in vertices only
// eulers formula: v - e + f = 2 // vertices, edges, faces = number of regions, including the infinite one
// the number of edges in a planar graph is <= 3*|V| - 6
// provable by eulers formula + the fact that each face takes up at least 3 edges, and each edge is a part of at most 2 faces
// => at least one vertex has a degree of <= 5
// graph is planar <=> nemá podgraf s dělením k5 nebo k3,3
// - use hopcroft-tarjan algorithm in O(n)
