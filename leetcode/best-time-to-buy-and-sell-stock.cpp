//https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0 || prices.size() == 1)
            return 0;

        int min_val = prices[0];
        int max_profit = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] < min_val)
                min_val = prices[i];
            else if (prices[i] - min_val > max_profit)
                max_profit = prices[i] - min_val;
        }
        return max_profit;
    }
};
