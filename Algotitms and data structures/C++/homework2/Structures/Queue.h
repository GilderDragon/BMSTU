#ifndef BMSTU_QUEUE_H
#define BMSTU_QUEUE_H
#include <iostream>
#include <stdexcept>

using namespace std;


template<typename T>
class Queue {
private:
    // Узел очереди
    struct Node {
        T data;
        Node* next; // указатель на следующий элемент

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* frontNode; // начало очереди
    Node* backNode; // конец очереди
    int queueSize; // размер очереди

public:
    // Конструктор
    Queue() : frontNode(nullptr), backNode(nullptr), queueSize(0) {}

    // Деструктор
    ~Queue() {
        clear();
    }

    // Конструктор копирования
    Queue(const Queue& other) : frontNode(nullptr), backNode(nullptr), queueSize(0) {
        Node* current = other.frontNode;
        while (current != nullptr) {
            enqueue(current->data);
            current = current->next;
        }
    }

    // Оператор присваивания
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            clear();
            Node* current = other.frontNode;
            while (current != nullptr) {
                enqueue(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Добавление элемента в конец очереди
    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            frontNode = backNode = newNode;
        } else {
            backNode->next = newNode;
            backNode = newNode;
        }
        queueSize++;
    }

    // Удаление и возврат элемента из начала очереди
    T dequeue() {
        if (isEmpty()) {
            throw runtime_error("Cannot dequeue from empty queue");
        }

        Node* nodeToDelete = frontNode;
        T value = frontNode->data;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            backNode = nullptr;
        }

        delete nodeToDelete;
        queueSize--;

        return value;
    }

    // Просмотр первого элемента без удаления
    T& front() {
        if (isEmpty()) {
            throw runtime_error("Cannot get front from empty queue");
        }
        return frontNode->data;
    }

    // просмотр последнего элемента очереди
    T& back() {
        if (isEmpty()) {
            throw runtime_error("Cannot get back from empty queue");
        }
        return backNode->data;
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return frontNode == nullptr;
    }

    // Получение размера стека
    int size() const {
        return queueSize;
    }

    // Очистка стека
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};


#endif //BMSTU_QUEUE_H