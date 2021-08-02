// https://codeforces.com/blog/entry/61587

mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

// inclusive, inclusive
#define uid(a, b) uniform_int_distribution<int>(a, b)(gen)

// shuffle(a.begin(),a.end(),gen);
