// https://www.youtube.com/watch?v=ihj4IQGZ2zc

#include <bits/stdc++.h>

class Node {
    public:
        char root;
        Node *left, *right;
        Node(char root) {
            this->root = root;
            this->left = nullptr;
            this->right = nullptr;
        }
};

Node *build_binary_tree(
    const std::string& preorder,
    const std::string& inorder
) {
    if (!preorder.size() or !inorder.size()) return nullptr;

    Node *root = new Node(preorder[0]);
    int inorder_root = inorder.find(preorder[0]);

    root->left = build_binary_tree(
        preorder.substr(1, inorder_root),
        inorder.substr(0, inorder_root)
    );
    root->right = build_binary_tree(
        preorder.substr(inorder_root + 1),
        inorder.substr(inorder_root + 1)
    );

    return root;
}

std::string post_order_traversal(Node *node) {
    if (node == nullptr) return "";

    std::string left = post_order_traversal(node->left);
    std::string right = post_order_traversal(node->right);

    return left + right + node->root;
}

int main() {
    std::vector<std::string> answers;

    int test_cases;
    std::cin >> test_cases;
    while (test_cases--) {
        int nodes;
        std::cin >> nodes;

        std::string preorder, inorder;
        std::cin >> preorder >> inorder;
        
        std::map<char, int> inorder_positions;

        Node *root = build_binary_tree(preorder, inorder);
        answers.push_back(post_order_traversal(root));
    }

    for (const std::string& answer : answers) std::cout << answer << std::endl;

    return 0;
}
