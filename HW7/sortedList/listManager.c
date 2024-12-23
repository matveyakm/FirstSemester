#include <stdlib.h>
#include <stdbool.h>
#include "list/listDeclaration.h"

void addValue(List *sortedList, int value) {
    int left = 0, right = listLength(sortedList) - 1;

    // Бинарный поиск для нахождения индекса вставки
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (peekL(sortedList, mid) < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Вставляем значение в найденную позицию (left)
    addL(sortedList, left, value);
}


bool deleteValue(List *sortedList, int value) {
    int left = 0, right = listLength(sortedList) - 1;

    // Бинарный поиск для нахождения значения
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (peekL(sortedList, mid) == value) {
            // Удаляем значение, если найдено
            popAtL(sortedList, mid);
            return true;
        } else if (peekL(sortedList, mid) < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Если значение не найдено
    return false;
}
