#ifndef BMSTU_SET_H
#define BMSTU_SET_H
#include <iostream>
#include <vector>
#include <functional>


template<typename T>
class Set {
private:
    struct Node {
        T data;
        Node* next;

        explicit Node(const T& value) : data(value), next(nullptr) {}
    };

    std::vector<Node*> buckets;
    int itemCount;
    double loadFactorThreshold;

    size_t hash(const T& value) const {
        return std::hash<T>{}(value) % buckets.size();
    }

    void rehash() {
        std::vector<Node*> oldBuckets = buckets;
        buckets.clear();
        buckets.resize(oldBuckets.size() * 2, nullptr);
        itemCount = 0;

        for (Node* head : oldBuckets) {
            Node* current = head;
            while (current != nullptr) {
                insert(current->data);
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
public:
    explicit Set(int initialSize = 16, double loadFactor = 0.75)
    : buckets(initialSize, nullptr), itemCount(0), loadFactorThreshold(loadFactor) {}

    ~Set() {
        clear();
    }

    Set(const Set& other)
        : buckets(other.buckets.size(), nullptr), itemCount(0), loadFactorThreshold(other.loadFactorThreshold){
        for (Node* head : other.buckets) {
            Node* current = head;
            while (current != nullptr) {
                insert(current->data);
                current = current->next;
            }
        }
    }

    Set& operator=(const Set& other) {
        if (this != &other) {
            clear();
            buckets.resize(other.buckets.size(), nullptr);
            loadFactorThreshold = other.loadFactorThreshold;
            for (Node* head : other.buckets) {
                Node* current = head;
                while (current != nullptr) {
                    insert(current->data);
                    current = current->next;
                }
            }
        }
        return *this;
    }

    void insert(const T& value) {
        if (static_cast<double>(itemCount) / buckets.size() > loadFactorThreshold) {
            rehash();
        }

        size_t index = hash(value);
        Node* current = buckets[index];

        while (current != nullptr) {
            if (current->data == value) {
                return;
            }
            current = current->next;
        }

        Node* newNode = new Node(value);
        newNode->next = buckets[index];
        buckets[index] = newNode;
        itemCount++;
    }

    bool remove(const T& value) {
        size_t index = hash(value);
        Node* current = buckets[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->data == value) {
                if (prev == nullptr) {
                    buckets[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                itemCount--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    bool contains(const T& value) const {
        size_t index = hash(value);
        Node* current = buckets[index];

        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    [[nodiscard]] int size() const {
        return itemCount;
    }

    [[nodiscard]] bool isEmpty() const {
        return itemCount == 0;
    }

    void clear() {
        for (size_t i = 0; i < buckets.size(); i++) {
            Node* current = buckets[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            buckets[i] = nullptr;
        }
        itemCount = 0;
    }

    Set unionWith(const Set& other) const {
        Set result(*this);
        for (Node* head : other.buckets) {
            Node* current = head;
            while (current != nullptr) {
                result.insert(current->data);
                current = current->next;
            }
        }
        return result;
    }

    Set intersectionWith(const Set& other) const {
        Set result;
        for (Node* head : buckets) {
            Node* current = head;
            while (current != nullptr) {
                if (other.contains(current->data)) {
                    result.insert(current->data);
                }
                current = current->next;
            }
        }
        return result;
    }

    Set differenceWith(const Set& other) const {
        Set result;
        for (Node* head : buckets) {
            Node* current = head;
            while (current != nullptr) {
                if (!other.contains(current->data)) {
                    result.insert(current->data);
                }
                current = current->next;
            }
        }
        return result;
    }

    bool isSubsetOf(const Set& other) const {
        for (Node* head : buckets) {
            Node* current = head;
            while (current != nullptr) {
                if (!other.contains(current->data)) {
                    return false;
                }
                current = current->next;
            }
        }
        return true;
    }

    std::vector<T> toVector() const {
        std::vector<T> result;
        for (Node* head : buckets) {
            Node* current = head;
            while (current != nullptr) {
                result.push_back(current->data);
                current = current->next;
            }
        }
        return result;
    }

    class Iterator {
    private:
        const Set* set;
        size_t bucketIndex;
        Node* current;

        void findNext() {
            while (current == nullptr && bucketIndex < set->buckets.size() - 1) {
                bucketIndex++;
                current  = set->buckets[bucketIndex];
            }
        }
    public:
        Iterator(const Set* s, size_t index, Node* node)
            : set(s), bucketIndex(index), current(node) {
            findNext();
        }

        T& operator*() {return current->data;}

        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
                findNext();
            }
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return current != other.current;
        }
    };

    Iterator begin() const {
        return Iterator(this, 0, buckets[0]);
    }

    Iterator end() const {
        return Iterator(this, buckets.size() - 1, nullptr);
    }
};


#endif //BMSTU_SET_H