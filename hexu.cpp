#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include <climits>

using namespace std;

long hexu_solve(const std::vector<long>& weights, 
                  const std::vector<long>& profits, 
                  long W) {
    long n = weights.size();
    if (n == 0) return 0;
    
    long w_max = *std::max_element(weights.begin(), weights.end());
    
    std::vector<long> indices(n);
    std::iota(indices.begin(), indices.end(), 0);
    
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    std::shuffle(indices.begin(), indices.end(), rng);
    
    std::vector<std::vector<long long>> f(2, std::vector<long long>(W + 1, 0));
    
    long curr = 1, prev = 0;
    
    for (long i = 1; i <= n; i++) {
        std::swap(curr, prev);
        
        f[curr] = f[prev];
        
        long item_idx = indices[i - 1];
        long wi = weights[item_idx];
        long pi = profits[item_idx];
        
        long long mu_i = (long long)(i * W) / n;
        long long delta_i = (long long)(std::sqrt(i * std::log(n)) * w_max);
        
        long long start_j = std::max(0LL, mu_i - delta_i);
        long long end_j = std::min((long long)W, mu_i + delta_i);
        
        for (long long j = start_j; j <= end_j; j++) {
            if (j >= wi) {
                f[curr][j] = std::max(f[prev][j], f[prev][j - wi] + pi);
            }
        }
    }
    
    long long result = 0;
    for (long j = 0; j <= W; j++) {
        result = std::max(result, f[curr][j]);
    }
    
    return (long)result;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  long n, W;
  cin >> n >> W; 

  vector<long> profits(n), weights(n);

  for (long i = 0; i < n; ++i) {
      cin >> profits[i];
  }

  for (long i = 0; i < n; ++i) {
      cin >> weights[i];
  }

  long result = hexu_solve(weights, profits, W);

  cout << result << endl;

  return 0;
}