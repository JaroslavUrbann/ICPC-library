// just like a normal set, but has find_by_order(int) which returns the kth element
// and order_of_key(T), which is tree.lower_bound(T) - tree.begin()
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>
using Tree=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;


#define all(x) (x).begin(),(x).end()
// max heap
make_heap(all(x));
push_heap(all(x)); // bubbles up last element
pop_heap(all(x)); // swaps with last and bubbles down, biggest is in last position

partial_sort(f,m,l); // 1,2,..,m, random
nth_element(f,m,l); // smaller..,m,...bigger
inplace_merge(a,b,c); // merge [a,b),[b,c);

partition(all(x),predicate); // elementy splňující predikát na začátku, ostatní dál, returns pointer na první nesplňující element
partition_point(all(x),predicate); // binary search na boundry

rotate(f,m,l); // m,m+1,m+2...
shuffle(all(x));

next_permutation(all(x));
prev_permutation(all(x));
reverse(all(x));

stable_...
is_..._until(all(x)) // returns how far the vector is sorted

count(all(x),val); // how many times does it appear here
accumulate(all(x));

partial_sum(all(x),f); // prefix sum
inner_product(all(x)); // dot product of vector
adjacent_difference(all(x),f); // a1, a2-a1, a3-a2...

all_of(all(x),predicate);
any_of(all(x),predicate);
none_of(all(x),predicate);

equal(all(x),f2); // x1..xn == f2...l2
is_permutation(all(x),f2); // is x permutation of f2..l2
lexicographical_compare(all(x),all(y));
mismatch(all(x),f2); // returns first point where they differ

find(all(x),val); // iterator to first value
adjacent_find(all(x),val); // first pos where 2 vals appear in succession
equal_range(all(x),val); // pair: f, l, range of vals in sorted vector
lower_bound(all(x),val); // first element >=
upper_bound(all(x),val); // first element >
binary_search(all(x),val);

search(all(x),all(y)); // finds first subrange y in array x, (naive)
find_end(all(x),all(y)); // finds last subrange y in array x, (naive)

max_element(all(x));
min_element(all(x));
minmax_element(all(x)); // pair of iterators

set_difference(all(x),all(y),back_inserter(res)); // elements in X, but not in Y
set_symmetric_difference(all(x),all(y),back_inserter(res)); // union\intersection
set_intersection(all(x),all(y),back_inserter(res));
set_union(all(x),all(y),back_inserter(res));
includes(all(x),all(y)); // is y a subset of x?
merge(all(x),all(y));

move(f,l,m); // f..l is moved to m...f-l+m
copy(f,l,m); // f..l is copied to m...f-l+m

fill(all(x),val);
generate(all(x),function); // a_i = f(a_i)
iota(all(x),0);
replace(all(x),val,wantval);
remove(all(x),val); // returns new end
unique(all(x)); // returns new end
