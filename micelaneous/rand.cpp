mt19937_64 gen(std::random_device{}());

#define uid(a, b) uniform_int_distribution<int>(a, b)(gen)
mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

// https://codeforces.com/blog/entry/61587
int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<int> permutation(N);

    for (int i = 0; i < N; i++)
        permutation[i] = i;

    shuffle(permutation.begin(), permutation.end(), rng);
    cout << average_distance(permutation) << '\n';

    for (int i = 0; i < N; i++)
        permutation[i] = i;

    for (int i = 1; i < N; i++)
        swap(permutation[i], permutation[uniform_int_distribution<int>(0, i)(rng)]);
}
