class Solution {
public:
    void rec_perm(vector<int>& nums, vector<vector<int>> &p, std::vector<int> &v) {

        if (nums.size() == 0) {
            p.push_back(v);
            return;
        }

        for (int i = 0 ; i < nums.size(); i++){
            int tmp = nums[i];
            int n = nums.back();
            nums[i] = n;
            nums.pop_back();
            v.push_back(tmp);
            
            rec_perm(nums, p, v);
            v.pop_back();
            nums.push_back(n);
            nums[i] = tmp; 
        }  
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> p;
        std::vector<int> vv = {};
        if (nums.size() == 1) {
            std::vector<int> v = {nums[0]};
            p.push_back(v);
            return p;
        }
        rec_perm(nums, p, vv);
        return p;  
    }
};
