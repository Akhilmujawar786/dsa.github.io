#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Product {
    string name;
    int cost;
    int utility;

    Product(string n, int c, int u) : name(n), cost(c), utility(u) {}
};


int knapsack(int budget, const vector<Product>& products) {
    int n = products.size();
    vector<vector<int>> dp(n + 1, vector<int>(budget + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= budget; ++w) {
            if (products[i - 1].cost > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                dp[i][w] = max(dp[i - 1][w], products[i - 1].utility + dp[i - 1][w - products[i - 1].cost]);
            }
        }
    }

    return dp[n][budget];
}

int main() {
   
    vector<Product> products = {
        {"Detergent A", 5, 60},
        {"Detergent B", 10, 100},
        {"Comfort C", 3, 50},
        {"Other D", 8, 70}
    };

    int budget = 20; 

  
    int max_utility = knapsack(budget, products);


    cout << "Maximum utility within the budget of " << budget << " is " << max_utility << endl;

    return 0;
}
