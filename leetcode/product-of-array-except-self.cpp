class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        std::vector<int>* answer = new std::vector<int>(nums.size(), 1);

        if (nums.size() == 2) {
            (*answer)[0] = nums[1];
            (*answer)[1] = nums[0];
            return *answer;
        }
        std::vector<int> pre(nums.size());
        std::vector<int> pst(nums.size());

        pre[0] = nums[0];
        pst[nums.size() - 1] = nums[nums.size() - 1];
        for (int i = 1 ; i < nums.size() - 1; i++) {
            pre[i] = pre[i - 1] * nums[i];
            int k = nums.size() - i - 1;
            pst[k] = pst[k + 1] * nums[k];
            
        }
        pre[nums.size() - 1] = pre[nums.size() - 2] * nums[nums.size() - 1];
        pst[0] = pst[1] * nums[0];

        for (int i = 1 ; i < nums.size() - 1; i++) {
            (*answer)[i] = pre[i - 1] * pst[i + 1];
        }
        (*answer)[0] = pst[1];
        (*answer)[nums.size() - 1] = pre[nums.size() - 2];

        return *answer;

    }
};
