#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

//not A multiset
//find_by_order(k) -> itr of k-th(0-based) element
//order_of_key(k) -> index of lower_bound(k)
using ordered_set=tree<
long long,
null_type,
less<long long>,
rb_tree_tag,
tree_order_statistics_node_update>;