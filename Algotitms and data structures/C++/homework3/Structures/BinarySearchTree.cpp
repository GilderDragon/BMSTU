#include <iostream>
#include "BinarySearchTree.h"

int main() {
    BinarySearchTree<int> bst;

    // Вставка элементов
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    std::cout << "Size: " << bst.size() << std::endl;
    std::cout << "Height: " << bst.height() << std::endl;
    std::cout << "Min: " << bst.findMin() << std::endl;
    std::cout << "Max: " << bst.findMax() << std::endl;

    // Проверка наличия элементов
    std::cout << "Contains 40: " << bst.contains(40) << std::endl;
    std::cout << "Contains 100: " << bst.contains(100) << std::endl;

    // Удаление элемента
    bst.remove(30);

    // Копирование
    BinarySearchTree<int> bstCopy = bst;

    return 0;
}