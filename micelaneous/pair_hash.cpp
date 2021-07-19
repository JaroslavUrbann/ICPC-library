// consider using faster kactl hash table from data structures
struct pair_hash {
    int operator()(pair<int,int> x) const { return x.first* 31 + x.second; }
};

// fancy, "safe", same speed, idk why I have it
auto random_address = [] { char *p = new char; delete p; return uint64_t(p); };
 
struct safe_hash {
    static unsigned hash32(unsigned x) {
        x = (x ^ (x >> 16)) * 0x45d9f3b;
        x = (x ^ (x >> 16)) * 0x45d9f3b;
        return x ^ (x >> 16);
    }
 
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    template<typename T>
    uint64_t operator()(T x) const {
        static const uint64_t FIXED_RANDOM = splitmix64(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));
        return sizeof(x) <= 4 ? hash32(unsigned(x ^ FIXED_RANDOM)) : splitmix64(x ^ FIXED_RANDOM);
    }
};

struct safe_pair_hash {
    template<typename T_pair>
    uint64_t operator()(const T_pair &x) const {
        static const uint64_t RANDOM_MULT = safe_hash::splitmix64(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1)) | 1;
        static safe_hash hash_obj;
        return hash_obj(RANDOM_MULT * x.first + x.second);
    }
};

