#include <inttypes.h>
#include <iostream>
using namespace std;

#define COMPARE_REACT \
    if (cur_len > max_len) { max_len = cur_len; max_len_fch = mass[2]; max_len_lch = i; }


void move_arr(uint32_t* arr, uint32_t a) {
    arr[0] = arr[1];
    arr[1] = a;
} // сдвинет элементы массива

void clear_array(uint32_t* arr) {
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
} // обнулит элементы массива

void clear_array(uint32_t* arr, uint32_t new_el, uint32_t i) {
    arr[0] = new_el;
    arr[1] = 0;
    arr[2] = i + 1;
} // обнулит второй элемент, задаст первый

int main()
{
    uint32_t n = 0;
    cin >> n;
    uint32_t buffer = 0;
    uint32_t max_len = 0;
    uint32_t max_len_fch = 0; // max first child
    uint32_t max_len_lch = 0; // max last child
    uint32_t cur_len = 0;
    uint32_t* mass = new uint32_t[3];
    // формат mass [элемент -2][элемент -1][текущий][начало тек. линии]
    clear_array(mass);
    for (int i = 0; i < n; i++) {
        cin >> buffer;

        if (mass[0] == 0) { // если пустая 1ая ячейка (init)
            clear_array(mass, buffer, i);
            cur_len = 1;
        }
        else if (mass[1] == 0) { // если пустая вторая ячейка
            if (mass[0] != buffer) { // не подряд
                mass[1] = buffer;
                cur_len++;
            }
            else {  // подряд
                COMPARE_REACT; // по сути оставляем таким же
                continue;
            }
        }
        else {
            if (buffer != mass[0] && buffer != mass[1]) { // 1 2 3  --->  [2 3]
                cur_len++;
                move_arr(mass, buffer);
            }
            else if (buffer == mass[0] && buffer != mass[1]) { // 1 2 1  --> [2 1]
                COMPARE_REACT;
                cur_len = 2;
                move_arr(mass, buffer);
            }
            else { // 2 1 1 or 1 1 1  ---> [1 0]
                COMPARE_REACT;
                cur_len = 1;
                clear_array(mass, buffer, i);
            }
        }
    }
    if (cur_len > max_len) { max_len = cur_len; max_len_fch = mass[2]; max_len_lch = n; }
    cout << max_len_fch << " " << max_len_lch << endl;
    free(mass);
    return 0;
}
