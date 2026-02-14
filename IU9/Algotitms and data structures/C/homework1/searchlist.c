#include "elem.h"

struct Elem *searchlist(struct Elem *list, int k) {
    // Проходим по всем элементам списка
    while (list != NULL) {
        // Проверяем тип текущего элемента
        if (list->tag == INTEGER) {
            // Если это целое число, сравниваем с искомым
            if (list->value.i == k) {
                return list; // Найден нужный элемент
            }
        } else if (list->tag == LIST) {
            // Если это вложенный список, рекурсивно ищем в нем
            struct Elem *found = searchlist(list->value.list, k);
            if (found != NULL) {
                return found; // Найден во вложенном списке
            }
        }
        // Переходим к следующему элементу
        list = list->tail;
    }
    
    // Элемент не найден
    return NULL;
}