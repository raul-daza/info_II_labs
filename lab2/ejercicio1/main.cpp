#include <iostream>

using namespace std;

void fun_a(int *px, int *py);
void fun_b(int a[], int tam);

int main()
{
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    fun_b(array, 10);
    return 0;
}
void fun_a(int *px, int *py){
    int tmp = *px;
    *px = *py;
    *py = tmp;
}
void fun_b(int a[], int tam){
    int f, l;
    int *b = a;
    for (f = 0, l = tam -1; f < l; f++, l--) {
        fun_a(&b[f], &b[l]);
    }
}

/*
Cuál es su dirección en memoria? ¿Cuántos bytes se dedican para almacenar cada elemento de array?
    - la direccion en memoria es 0x299bfff6d0, pero esta cambia cada vez que se ejecuta el codigo.
    A cada elemento se le dedican 4 bytes
Cuál es la dirección y el contenido en memoria del elemento array[3] ?
    - el contenido es '3' y la direccion en memoria es 0x299bfff6dc, pero esta cambia cada vez que
    se ejecuta el codigo
Describa el efecto que tiene la función fun_b, sobre el arreglo array.
    - lo que hace la funcion fun_b es intercambiar los valores del arreglo, el primero lo intercambia
    con el ultimo, el penuntimo con el segundo y asi sucesivamente hasta intercambiar todos los elementos
*/
