#include <iostream>
#include <vector>
using namespace std;

long DP_solve(vector<long>& weight, vector<long>& value, long W) {
    long N = weight.size();
    vector<long> dp(W + 1, 0);

    for (long i = 0; i < N; ++i) {
        for (long w = W; w >= weight[i]; --w) {
            dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
        }
    }
    return dp[W];
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

  long result = DP_solve(weights, profits, W);

  cout << result << endl;

  return 0;
}