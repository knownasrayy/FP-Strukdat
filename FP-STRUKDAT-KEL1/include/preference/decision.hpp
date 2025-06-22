#pragma once
#include <string>
#include <vector>

struct TreeNode {
    std::string question;
    std::string answer;
    std::string criteria;
    std::vector<TreeNode*> children;
};

class DecisionTree {
public:
    DecisionTree();
    ~DecisionTree();
    void clearTree(TreeNode* node);
    std::string getCriteria();
    void loadFromFile(const std::string& filename);
    void printTree(TreeNode* node, int depth = 0) const;
    TreeNode* getRoot() const { return root; }
private:
    TreeNode* root;
};
