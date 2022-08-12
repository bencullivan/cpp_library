#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template<typename K,typename V>
using imap = __gnu_pbds::tree<
    K, V, std::less<K>,
    __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
template<typename K>
using iset = imap<K, __gnu_pbds::null_type>;