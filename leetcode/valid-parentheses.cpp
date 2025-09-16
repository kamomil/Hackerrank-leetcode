// https://leetcode.com/problems/valid-parentheses/
class Solution {
public:
    bool match(char c, char a){
        if (c == '(' && a == ')')
            return true;
        else if (c == '[' && a == ']')
            return true;
        else if (c == '{' && a == '}')
            return true;
        return false;
    }
    bool isValid(string s) {
        std::stack<char> mystack;

        for (char c : s) {
            if (c == '[' || c == '{' || c == '(') {
                mystack.push(c);
            } else {
                if (mystack.empty())
                    return false;
                char a = mystack.top();
                mystack.pop();
                if (!match(a, c))
                    return false;
            }
        }
        if (!mystack.empty())
            return false;
        return true;
    }
};
