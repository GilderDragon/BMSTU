#ifndef BMSTU_BINARYTREE_H
#define BMSTU_BINARYTREE_H
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <functional>
#include <stdexcept>
#include <algorithm>


template<typename T>
class BinaryTree {
private:
    struct TreeNode {
        T data;
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;

        TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    std::shared_ptr<TreeNode> root;

    std::shared_ptr<TreeNode> insertRecursive(std::shared_ptr<TreeNode> node, const T& value) {
        if (!node) {
            return std::make_shared<TreeNode>(value);
        }

        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        }

        return node;
    }

    bool searchRecursive(std::shared_ptr<TreeNode> node, const T& value) const {
        if (!node) return false;

        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return searchRecursive(node->left, value);
        } else {
            return searchRecursive(node->right, value);
        }
    }

    void inorderRecursive(std::shared_ptr<TreeNode> node,
                         std::function<void(const T&)> visit) const {
        if (!node) return;

        inorderRecursive(node->left, visit);
        visit(node->data);
        inorderRecursive(node->right, visit);
    }

    void preorderRecursive(std::shared_ptr<TreeNode> node,
                          std::function<void(const T&)> visit) const {
        if (!node) return;

        visit(node->data);
        preorderRecursive(node->left, visit);
        preorderRecursive(node->right, visit);
    }

    void postorderRecursive(std::shared_ptr<TreeNode> node,
                           std::function<void(const T&)> visit) const {
        if (!node) return;

        postorderRecursive(node->left, visit);
        postorderRecursive(node->right, visit);
        visit(node->data);
    }

    int heightRecursive(std::shared_ptr<TreeNode> node) const {
        if (!node) return -1;

        int leftHeight = heightRecursive(node->left);
        int rightHeight = heightRecursive(node->right);

        return 1 + std::max(leftHeight, rightHeight);
    }

    int sizeRecursive(std::shared_ptr<TreeNode> node) const {
        if (!node) return 0;

        return 1 + sizeRecursive(node->left) + sizeRecursive(node->right);
    }

    std::shared_ptr<TreeNode> findMin(std::shared_ptr<TreeNode> node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    std::shared_ptr<TreeNode> findMax(std::shared_ptr<TreeNode> node) const {
        while (node && node->right) {
            node = node->right;
        }
        return node;
    }

    std::shared_ptr<TreeNode> removeRecursive(std::shared_ptr<TreeNode> node, const T& value) {
        if (!node) return nullptr;

        if (value < node->data) {
            node->left = removeRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = removeRecursive(node->right, value);
        } else {
            if (!node->left) {
                return node->right;
            } else if (!node->right) {
                return node->left;
            }

            auto minNode = findMin(node->right);
            node->data = minNode->data;
            node->right = removeRecursive(node->right, minNode->data);
        }

        return node;
    }

public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(const T& rootValue) : root(std::make_shared<TreeNode>(rootValue)) {}

    BinaryTree(const BinaryTree& other) {
        std::function<std::shared_ptr<TreeNode>(std::shared_ptr<TreeNode>)> copyTree =
            [&](std::shared_ptr<TreeNode> node) -> std::shared_ptr<TreeNode> {
                if (!node) return nullptr;

                auto newNode = std::make_shared<TreeNode>(node->data);
                newNode->left = copyTree(node->left);
                newNode->right = copyTree(node->right);
                return newNode;
            };

        root = copyTree(other.root);
    }

    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            clear();

            std::function<std::shared_ptr<TreeNode>(std::shared_ptr<TreeNode>)> copyTree =
                [&](std::shared_ptr<TreeNode> node) -> std::shared_ptr<TreeNode> {
                    if (!node) return nullptr;

                    auto newNode = std::make_shared<TreeNode>(node->data);
                    newNode->left = copyTree(node->left);
                    newNode->right = copyTree(node->right);
                    return newNode;
                };

            root = copyTree(other.root);
        }
        return *this;
    }

    void insert(const T& value) {
        root = insertRecursive(root, value);
    }

    bool contains(const T& value) const {
        return searchRecursive(root, value);
    }

    void remove(const T& value) {
        root = removeRecursive(root, value);
    }

    void clear() {
        root = nullptr;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void inorder(std::function<void(const T&)> visit) const {
        inorderRecursive(root, visit);
    }

    void preorder(std::function<void(const T&)> visit) const {
        preorderRecursive(root, visit);
    }

    void postorder(std::function<void(const T&)> visit) const {
        postorderRecursive(root, visit);
    }

    void depthFirst(std::function<void(const T&)> visit) const {
        if (!root) return;

        std::stack<std::shared_ptr<TreeNode>> stack;
        stack.push(root);

        while (!stack.empty()) {
            auto node = stack.top();
            stack.pop();

            visit(node->data);

            if (node->right) stack.push(node->right);
            if (node->left) stack.push(node->left);
        }
    }

    void breadthFirst(std::function<void(const T&)> visit) const {
        if (!root) return;

        std::queue<std::shared_ptr<TreeNode>> queue;
        queue.push(root);

        while (!queue.empty()) {
            auto node = queue.front();
            queue.pop();

            visit(node->data);

            if (node->left) queue.push(node->left);
            if (node->right) queue.push(node->right);
        }
    }

    int height() const {
        return heightRecursive(root);
    }

    int size() const {
        return sizeRecursive(root);
    }

    T getMin() const {
        if (!root) {
            throw std::runtime_error("Дерево пустое");
        }

        auto node = findMin(root);
        return node->data;
    }

    T getMax() const {
        if (!root) {
            throw std::runtime_error("Дерево пустое");
        }

        auto node = findMax(root);
        return node->data;
    }

    T getRoot() const {
        if (!root) {
            throw std::runtime_error("Дерево пустое");
        }
        return root->data;
    }

    void printTree() const {
        if (!root) {
            std::cout << "Дерево пустое" << std::endl;
            return;
        }

        struct NodeInfo {
            std::shared_ptr<TreeNode> node;
            int level;

            NodeInfo(std::shared_ptr<TreeNode> n, int l) : node(n), level(l) {}
        };

        std::queue<NodeInfo> queue;
        queue.push(NodeInfo(root, 0));

        int currentLevel = 0;

        while (!queue.empty()) {
            auto info = queue.front();
            queue.pop();

            if (info.level > currentLevel) {
                std::cout << std::endl;
                currentLevel = info.level;
            }

            int spaces = 40 / (currentLevel + 1);
            for (int i = 0; i < spaces; ++i) {
                std::cout << " ";
            }

            std::cout << info.node->data;

            if (info.node->left) {
                queue.push(NodeInfo(info.node->left, info.level + 1));
            }

            if (info.node->right) {
                queue.push(NodeInfo(info.node->right, info.level + 1));
            }
        }

        std::cout << std::endl;
    }

    void printInorder() const {
        std::cout << "Inorder (ЛКП): ";
        inorder([](const T& value) {
            std::cout << value << " ";
        });
        std::cout << std::endl;
    }

    void printPreorder() const {
        std::cout << "Preorder (КЛП): ";
        preorder([](const T& value) {
            std::cout << value << " ";
        });
        std::cout << std::endl;
    }

    void printPostorder() const {
        std::cout << "Postorder (ЛПК): ";
        postorder([](const T& value) {
            std::cout << value << " ";
        });
        std::cout << std::endl;
    }

    void printBreadthFirst() const {
        std::cout << "Обход в ширину: ";
        breadthFirst([](const T& value) {
            std::cout << value << " ";
        });
        std::cout << std::endl;
    }
};

#endif //BMSTU_BINARYTREE_H