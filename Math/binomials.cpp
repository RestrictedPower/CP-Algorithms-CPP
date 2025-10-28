const int MAXN = 1e6;
const long long MOD = 1e9 + 7;

long long fac[MAXN + 1];
long long fac_inv[MAXN + 1];

long long nCr(long long n, long long r) {
    return fac[n] * fac_inv[r] % MOD * fac_inv[n - r] % MOD;
}

void precompute() {
    auto exp = [](long long x, long long n) {
        x %= MOD;
        long long res = 1;
        while (n > 0) {
            if (n % 2 == 1) { res = res * x % MOD; }
            x = x * x % MOD;
            n /= 2;
        }
        return res;
    };
    // Precompute factorials
    fac[0] = 1;
    for (int i = 1; i <= MAXN; i++) { fac[i] = fac[i - 1] * i % MOD; }
    // Precompute factorial inverses
    fac_inv[MAXN] = exp(fac[MAXN], MOD - 2);
    for (int i = MAXN; i >= 1; i--) { fac_inv[i - 1] = fac_inv[i] * i % MOD; }
}
