// https://leetcode.com/problems/permutations/

class Solution {
public:

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> p;
        if (nums.size() == 1) {
            std::vector<int> v = {nums[0]};
            p.push_back(v);
            return p;
        }
        
        for (int i = 0 ; i < nums.size(); i++) {
            int n = nums[i];  
            nums.erase(nums.begin() + i);
            auto vv = permute(nums);
            for (auto v : vv) {
                v.push_back(n);
                p.push_back(v);
                    
            }
            nums.insert(nums.begin() + i, n);
                
        }     
        return p;  
    }
};
