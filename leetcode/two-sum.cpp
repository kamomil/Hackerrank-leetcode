// https://leetcode.com/problems/two-sum/
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int, int> m{};
       
        for (int i = 0; i < nums.size(); ++i) {
            int s = target - nums[i];
            if (auto search = m.find(s); search != m.end()) {
                return {search->second, i};
            } else {
                m[nums[i]] = i;
            }
        }
        return {0,0};
    }
};
