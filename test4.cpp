#include<iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

typedef struct /*создаем структуру*/
{
    int * mass;
}Str;

int main(void)
{
    Str strct; /* объявляем ее */
    int size; /* переменная для размера */
    cin >> size;
    strct.mass=(int*)malloc(sizeof(int)*size); /* создаем динамический массив с введенным размером. Просим память у системы */
    if (strct.mass==0) /* Если система не дала памяти под массив, выходим */
    {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        strct.mass[i] = 202220221;
    }

    for (int i = 0; i < size; i++) {
        cout << strct.mass[i] << endl;
    }

    cout << "===========" << endl;

    free(strct.mass); /* после работы с массивом, вернем память системе */

    int newStorageSize = size + 1;
    
    int *newStorage = (int*)malloc(sizeof(int)*newStorageSize); /* создаем динамичесмас */

    for (int i = 0; i < size; i++) {
        newStorage[i] = strct.mass[i];
    }

    delete[] strct.mass;

    strct.mass = newStorage;

    newStorage = NULL;

    size = newStorageSize;

    for (int i = 0; i < newStorageSize; i++) {
        cout << strct.mass[i] << endl;
    }

    return 0; /* не забывайте про return 0! */
}
