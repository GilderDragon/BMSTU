#ifndef BMSTU_STACK_H
#define BMSTU_STACK_H
#include <iostream>
#include <stdexcept>

using namespace std;


template<typename T>
class Stack {
private:
    // Узел стека
    struct Node {
        T data;
        Node* prev; // указатель на предыдущий элемент

        Node(const T& value, Node* previous = nullptr)
            : data(value), prev(previous) {}
    };

    Node* topNode; // вершина стека
    int stackSize; // размер стека

public:
    // Конструктор
    Stack() : topNode(nullptr), stackSize(0) {}

    // Деструктор
    ~Stack() {
        clear();
    }

    // Конструктор копирования
    Stack(const Stack& other) : topNode(nullptr), stackSize(0) {
        if (!other.isEmpty()) {
            // Создаем временный стек для сохранения порядка
            Stack temp;
            Node* current = other.topNode;
            while (current != nullptr) {
                temp.push(current->data);
                current = current->prev;
            }

            // Переносим элементы в правильном порядке
            while (!temp.isEmpty()) {
                push(temp.pop());
            }
        }
    }

    // Оператор присваивания
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            clear();
            if (!other.isEmpty()) {
                Stack temp;
                Node* current = other.topNode;
                while (current != nullptr) {
                    temp.push(current->data);
                    current = current->prev;
                }

                while (!temp.isEmpty()) {
                    push(temp.pop());
                }
            }
        }
        return *this;
    }

    // Добавление элемента в стек
    void push(const T& value) {
        Node* newNode = new Node(value, topNode);
        topNode = newNode;
        stackSize++;
    }

    // Удаление и возврат верхнего элемента
    T pop() {
        if (isEmpty()) {
            throw runtime_error("Cannot pop from empty stack");
        }

        Node* nodeToDelete = topNode;
        T value = topNode->data;
        topNode = topNode->prev;
        delete nodeToDelete;
        stackSize--;

        return value;
    }

    // Просмотр верхнего элемента без удаления
    T& front() {
        if (isEmpty()) {
            throw runtime_error("Cannot get top from empty stack");
        }
        return topNode->data;
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return topNode == nullptr;
    }

    // Получение размера стека
    int size() const {
        return stackSize;
    }

    // Очистка стека
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};


#endif //BMSTU_STACK_H