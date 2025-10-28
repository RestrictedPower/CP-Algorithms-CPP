const int MAXN = 1e6;
const long long MOD = 1e9 + 7;

long long inv[MAXN + 1];

void precompute() {
    inv[1] = 1;
    for (int a = 2; a <= MAXN; ++a)
        inv[a] = MOD - (MOD / a) * inv[MOD % a] % MOD;
}

// To be used separately:
long long inv(long long a) {
    return a <= 1 ? a : MOD - (MOD / a) * inv(MOD % a) % MOD;
}
