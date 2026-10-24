#include <vector>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    vector<TreeNode*> buildTrees(int start, int end) {
        // Base case: range is invalid -> exactly 1 tree (nullptr)
        if (start > end)
            return {nullptr};

        vector<TreeNode*> allTrees;

        // Try placing each value 'i' as the root
        for (int i = start; i <= end; i++) {
            // Step 1: Generate all possible left subtrees with values < i
            vector<TreeNode*> leftSubtrees = buildTrees(start, i - 1);

            // Step 2: Generate all possible right subtrees with values > i
            vector<TreeNode*> rightSubtrees = buildTrees(i + 1, end);

            // Step 3: Combine each left and right subtree with the current root
            for (TreeNode* left : leftSubtrees) {
                for (TreeNode* right : rightSubtrees) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    allTrees.push_back(root);
                }
            }
        }

        return allTrees;
    }

public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {};
        return buildTrees(1, n);
    }
};