/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {

private:
        /* the longest path and diameter */
        pair<int,int> longestPathAndDiameter(TreeNode *t) {
            pair<int,int> l({0,0});
            pair<int,int> r({0,0});
            int longestPath = 0;
            int diameterThroughCurrent = 0;
            int diameter_l = 0;
            int diameter_r = 0;
            int diameter = 0;
            
            if (t->left) {
                l = longestPathAndDiameter(t->left);
                longestPath = l.first + 1;
                diameterThroughCurrent = l.first + 1;
            }
            if (t->right) {
                r = longestPathAndDiameter(t->right);
                longestPath = max (r.first + 1, longestPath);
                diameterThroughCurrent += r.first + 1;
            }
            cout << diameterThroughCurrent << "\n";
            if (t->left) {
                diameter_l = max (diameterThroughCurrent, l.second);
                
            }
            if (t->right)
                diameter_r = max (diameterThroughCurrent, r.second);
            
            diameter = max (diameter_l, diameter_r);

            return {longestPath, diameter};
        }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        
        return longestPathAndDiameter(root).second;
        
    }
};
