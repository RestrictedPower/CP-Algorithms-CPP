const int MAXN = 1e6;
int spf[MAXN + 1];

void sieve_spf() {
    for (int i = 1; i <= MAXN; i++) {
        spf[i] = i;
    }
    for (int i = 2; i * i <= MAXN; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= MAXN; j += i) {
                // If spf[j] hasn't been marked yet, mark it with i
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}

// Returns unique prime factors
std::vector<int> factorize(int x) {
    std::vector<int> factors;
    if (x == 1) return factors;
    while (x > 1) {
        int prime_factor = spf[x];
        while (x % prime_factor == 0) {
            x /= prime_factor;
        }
        factors.push_back(prime_factor);
    }
    return factors;
}

// Returns pairs from prime factor to it's frequency
std::vector<std::pair<int, int>> factorize(int x) {
    std::vector<std::pair<int, int>> factors;
    if (x == 1) return factors;
    while (x > 1) {
        int prime_factor = spf[x];
        int count = 0;
        while (x % prime_factor == 0) {
            x /= prime_factor;
            count++;
        }
        factors.emplace_back(prime_factor, count);
    }
    return factors;
}
