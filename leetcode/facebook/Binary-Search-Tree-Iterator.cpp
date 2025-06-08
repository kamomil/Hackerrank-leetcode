#include <stack>
#include <iostream>
/**
 * Definition for a binary tree node.
 **/
 struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode() : val(0), left(nullptr), right(nullptr) {}
   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 
class BSTIterator {
private:
    struct TreeNode *it;
    std::stack<TreeNode *> st;
    void goLeft()
    {
        while (it->left) {
            st.push(it);
            it = it->left;
        }
    }
public:
    BSTIterator(TreeNode* root) {
        it = root;
        goLeft();
    }

    int next() {
        int val = it->val;
        if (it->right) {
            it = it->right;
            goLeft();
        } else if (!st.empty()){
            it = st.top();
            st.pop();
        } else {

        }
        return val; 
    }

    bool hasNext() {
        return (it != NULL);
    }
};

int main ()
{
  TreeNode *t7 = new TreeNode(7);
  TreeNode *t3 = new TreeNode(3);
  TreeNode *t9 = new TreeNode(9);
  TreeNode *t15 = new TreeNode(15);
  TreeNode *t20 = new TreeNode(20);
  t7->left = t3;
  t7->right = t15;
  t15->left = t9;
  t15->right = t20;
  class BSTIterator it(t7);
  std::cout << (it.next()) << "\n";
  std::cout << (it.next()) << "\n";
  std::cout << (it.next()) << "\n";
  std::cout << (it.next()) << "\n";
  std::cout << (it.next()) << "\n";
  return 0;
}
