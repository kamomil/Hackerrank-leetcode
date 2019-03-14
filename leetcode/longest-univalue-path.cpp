//Solution to https://leetcode.com/contest/leetcode-weekly-contest-52/problems/longest-univalue-path/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    //return the nember of nodes in longest path, the number of edges will be one less
    void longestUnivaluePathRecurs(TreeNode* root, int* longest,int* as_father, bool ret_as_father) {
        if(!root->left && !root->right){
            if(ret_as_father){
                *as_father = 1;
            }
            *longest = 1;
            return;
        }
        int longest_left = 0;
        int longest_right= 0;
        int as_curr_left = 0;
        int as_curr_right = 0;
        
        if(root->left){
            longestUnivaluePathRecurs(root->left, &longest_left,&as_curr_left, root->val == root->left->val) ;
        }
        
        if(root->right){
            longestUnivaluePathRecurs(root->right, &longest_right,&as_curr_right, root->val == root->right->val) ;
        }
        int as_curr_longer = as_curr_left > as_curr_right ? as_curr_left : as_curr_right;
        
        if(ret_as_father){
            *as_father = as_curr_longer + 1;
        }
        int as_current = as_curr_left + as_curr_right +1;
            
        if(as_current < longest_left){
            *longest = longest_left;
        }
        else{
            *longest = as_current;
        }
        
        if(*longest < longest_right){
            *longest = longest_right;
        }
        
    }
        
    int longestUnivaluePath(TreeNode* root) {
        if(!root)
            return 0;
        int longest = 0;
        int as_curr = 0;
        longestUnivaluePathRecurs(root, &longest,&as_curr, false);
        //printf("%d\n",longest-1);
        
        return longest-1;
    }
};
