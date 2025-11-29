#ifndef BMSTU_BINARYSEARCHTREE_H
#define BMSTU_BINARYSEARCHTREE_H
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <queue>


template<typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        explicit Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int treeSize;

    Node* insert(Node* node, const T& value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data, value) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }

        return node;
    }

    Node* findMin(Node* node) const {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* remove(Node* node, const T& value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            if (node->left == nullptr) {
                Node* rightChild = node->right;
                delete node;
                return rightChild;
            } else if (node->right == nullptr) {
                Node* leftChild = node->left;
                delete node;
                return leftChild;
            } else {
                Node* minNode = findMin(node->right);
                node->data = minNode->data;
                node->right = remove(node->right, minNode->data);
            }
        }
        return node;
    }

    bool contains(Node* node, const T& value) const {
        if (node == nullptr) {
            return false;
        }

        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return contains(node->left, value);
        } else {
            return contains(node->right, value);
        }
    }

    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* copy(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        Node* newNode = new Node(node->data);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    void inOrder(Node* node, std::vector<T>& result) const {
        if (node != nullptr) {
            inOrder(node->left, result);
            result.push_back(node->data);
            inOrder(node->right, result);
        }
    }

    void preOrder(Node* node, std::vector<T>& result) const {
        if (node != nullptr) {
            result.push_back(node->data);
            preOrder(node->left, result);
            preOrder(node->right, result);
        }
    }

    void postOrder(Node* node, std::vector<T>& result) const {
        if (node != nullptr) {
            postOrder(node->left, result);
            postOrder(node->right, result);
            result.push_back(node->data);
        }
    }

    int height(Node* node) const {
        if (node == nullptr) {
            return -1;
        }
        return 1 + std::max(height(node->left), height(node->right));
    }

public:
    BinarySearchTree() : root(nullptr), treeSize(0) {}

    ~BinarySearchTree() {
        clear();
    }

    BinarySearchTree(const BinarySearchTree& other) : root(nullptr), treeSize(0) {
        root = copy(other.root);
        treeSize = other.treeSize;
    }

    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this != &other) {
            clear();
            root = copy(other.root);
            treeSize = other.treeSize;
        }
        return *this;
    }

    void insert(const T& value) {
        if (!contains(value)) {
            root = insert(root, value);
            treeSize++;
        }
    }

    void remove(const T& value) {
        if (contains(value)) {
            root = remove(root, value);
            treeSize--;
        }
    }

    [[nodiscard]] bool contains(const T& value) const {
        return contains(root, value);
    }

    [[nodiscard]] int size() const {
        return treeSize;
    }

    [[nodiscard]] bool isEmpty() const {
        return root == nullptr;
    }

    void clear() {
        clear(root);
        root = nullptr;
        treeSize = 0;
    }

    [[nodiscard]] int height() const {
        return height(root);
    }

    std::vector<T> inOrder() const {
        std::vector<T> result;
        inOrder(root, result);
        return result;
    }

    std::vector<T> preOrder() const {
        std::vector<T> result;
        preOrder(root, result);
        return result;
    }

    std::vector<T> postOrder() const {
        std::vector<T> result;
        postOrder(root, result);
        return result;
    }

    std::vector<T> levelOrder() const {
        std::vector<T> result;
        if (root == nullptr) {
            return result;
        }

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            result.push_back(current->data);

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        return result;
    }

    T& findMin() const {
        if (isEmpty()) {
            throw std::runtime_error("Tree is empty");
        }
        return findMin(root)->data;
    }

    T& findMax() const {
        if (isEmpty()) {
            throw std::runtime_error("Tree is empty");
        }

        Node* current = root;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current->data;
    }
};


#endif //BMSTU_BINARYSEARCHTREE_H