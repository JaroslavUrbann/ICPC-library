// just like a normal set, but has find_by_order(int) which returns the kth element
// and order_of_key(T), which is tree.lower_bound(T) - tree.begin()
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>
using Tree=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
