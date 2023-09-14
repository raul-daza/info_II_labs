#include <iostream>

using namespace std;

void fun_c(double *a, int n, double *promedio, double *suma);

int main()
{
    cout << endl;
    double suma, promedio;
    double a[5] = {0,1,2,3,4};
    fun_c(a, 5, &promedio, &suma);
    cout << "La suma de los elementos es " << suma << endl;
    cout << "El promedio de los elementos es: " << promedio << endl;
    return 0;
}

void fun_c(double *a, int n, double *promedio, double *suma){
    *suma = 0.0;
    for (int i = 0; i < n; i++)
        *suma += *(a + i);
    *promedio = *suma / n;
}
