#include <stdio.h>

int binary_search(int list[], int size, int item) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int guess = list[mid];

        if (guess == item) {
            return mid; // item found
        }
        if (guess > item) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

int my_list[] = {1, 1, 3, 5, 8, 12};
int size = sizeof(my_list) / sizeof(my_list[0]);
int item = -1;

int main() {
    int result = binary_search(my_list, size, item);

    printf("%d\n", result);

    return 0;
}