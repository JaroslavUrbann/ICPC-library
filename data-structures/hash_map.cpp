// if you want to have values in a map/set and then repeatedly add some values to all of them in O(1)
// unordered map might timelimit for some reason
// not tested
template<typename K,typename V>
struct HashMap{
	map<K,V>mp;
	K delta=0; // insertedkey + delta = newkey
	int count(K key){return mp.count(key-delta);}
	V &operator[](K key){return mp[key-delta];}
	void erase(K key){mp.erase(key-delta);}
	void insert(pair<K,V>item){mp.insert({item.first-delta,item.second});}
	void shift(K d){delta+=d;} // adds d to all keys
};
