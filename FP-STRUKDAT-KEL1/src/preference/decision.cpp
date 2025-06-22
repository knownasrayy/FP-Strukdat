#include "../../include/preference/decision.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

DecisionTree::DecisionTree() : root(nullptr) {}

DecisionTree::~DecisionTree() {
    clearTree(root);
}

void DecisionTree::clearTree(TreeNode* node) {
    if (node) {
        for (auto& child : node->children) {
            clearTree(child);
        }
        delete node;
    }
}

std::string DecisionTree::getCriteria() {
    if (!root) {
        throw std::runtime_error("Decision tree not initialized");
    }
    
    TreeNode* current = root;
    while (!current->children.empty()) {
        std::cout << "\n" << current->question << "\n";
        for (size_t i = 0; i < current->children.size(); ++i) {
            std::cout << i+1 << ". " << current->children[i]->answer << "\n";
        }
        
        int choice;
        std::cout << "Pilihan Anda [1-" << current->children.size() << "]: ";
        std::cin >> choice;
        
        if (choice < 1 || choice > static_cast<int>(current->children.size())) {
            throw std::invalid_argument("Pilihan tidak valid");
        }
        
        current = current->children[choice-1];
    }
    
    return current->criteria;
}

void DecisionTree::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open decision tree file: " + filename);
    }

    std::string line;
    std::vector<TreeNode*> nodeStack;
    
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        size_t level = 0;
        while (level < line.size() && line[level] == ' ') level++;
        line = line.substr(level);
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos) continue;

        std::string type = line.substr(0, colonPos);
        std::string content = line.substr(colonPos + 1);
        TreeNode* newNode = new TreeNode;
        if (type == "Q") {
            newNode->question = content;
            newNode->answer = "";
            newNode->criteria = "";
        } else if (type == "A") {
            size_t arrowPos = content.find("->");
            if (arrowPos == std::string::npos) continue;
            newNode->answer = content.substr(0, arrowPos);
            newNode->criteria = content.substr(arrowPos + 2);
            newNode->question = "";
        }
        // Set parent relationship
        if (level == 0) {
            clearTree(root);
            root = newNode;
        } else {
            if (level > nodeStack.size()) {
                throw std::runtime_error("Invalid tree structure in file");
            } else if (level == nodeStack.size()) {
                if (nodeStack.empty()) throw std::runtime_error("Invalid tree structure");
                nodeStack.back()->children.push_back(newNode);
            } else {
                while (level < nodeStack.size()) nodeStack.pop_back();
                if (!nodeStack.empty()) {
                    nodeStack.back()->children.push_back(newNode);
                }
            }
        }
        nodeStack.resize(level);
        nodeStack.push_back(newNode);
    }
}

void DecisionTree::printTree(TreeNode* node, int depth) const {
    if (!node) return;
    
    std::string indent(depth * 2, ' ');
    if (!node->question.empty()) {
        std::cout << indent << "Q: " << node->question << "\n";
    } else {
        std::cout << indent << "A: " << node->answer << " -> " << node->criteria << "\n";
    }
    
    for (const auto& child : node->children) {
        printTree(child, depth + 1);
    }
}