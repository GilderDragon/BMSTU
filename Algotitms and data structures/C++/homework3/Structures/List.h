#ifndef BMSTU_LIST_H
#define BMSTU_LIST_H
#include <iostream>
#include <stdexcept>


template<typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;

        explicit Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* firstNode; // первый элемент списка
    Node* backNode; // последний элемент списка
    int listSize; // размер списка
public:
    // Конструктор
    List() : firstNode(nullptr), backNode(nullptr), listSize(0) {}

    // Деструктор
    ~List() {
        clear();
    }

    // Конструктор копирования
    List(const List& other) : firstNode(nullptr), backNode(nullptr), listSize(0) {
        Node* current = other.firstNode;
        while (current != nullptr) {
            append(current->data);
            current = current->next;
        }
    }

    // Конструктор присваивания
    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            Node* current = other.firstNode;
            while (current != nullptr) {
                append(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Добавление в конец списка
    void append(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            firstNode = backNode = newNode;
        } else {
            backNode->next = newNode;
            backNode = newNode;
        }
        listSize++;
    }

    // Удаление элемента по индексу
    T pop(int index = -1) {
        if (isEmpty()) {
            throw std::runtime_error("Cannot pop from empty list");
        }

        if (index < 0) {
            index = listSize + index;
        }

        if (index < 0 || index >= listSize) {
            throw std::out_of_range("List index out of range");
        }

        if (index == 0) {
            Node* nodeToDelete = firstNode;
            T value = firstNode->data;
            firstNode = firstNode->next;
            if (firstNode == nullptr) {
                backNode = nullptr;
            }
            delete nodeToDelete;
            listSize--;
            return value;
        }

        Node* current = firstNode;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }


        Node* nodeToDelete = current->next;
        T value = nodeToDelete->data;
        current->next = nodeToDelete->next;
        if (nodeToDelete == backNode) {
            backNode = current;
        }
        delete nodeToDelete;
        listSize--;
        return value;
    }

    // Получение элемента по индексу
    T& get(int index) {
        if (index < 0) {
            index = listSize + index;
        }
        if (index < 0 || index > listSize) {
            throw std::out_of_range("List index out of range");
        }

        Node* current = firstNode;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    T& operator[](const int index) {
        return get(index);
    }

    // Проверка на пустоту
    [[nodiscard]] bool isEmpty() {
        return firstNode == nullptr;
    }

    // Получение размера
    [[nodiscard]] int size() const {
        return listSize;
    }

    // Очистка списка
    void clear() {
        while (firstNode != nullptr) {
            Node* nodeToDelete = firstNode;
            firstNode = firstNode->next;
            delete nodeToDelete;
        }
        backNode = nullptr;
        listSize = 0;
    }


};


#endif //BMSTU_LIST_H