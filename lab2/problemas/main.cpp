#include <iostream>

using namespace std;

int main()
{
    unsigned short option;
    cout << "ingrese el numero de un problema: ";
    cin >> option;

    switch (option) {
    case 1:
    {
        unsigned int money, quantity;
        unsigned short denomination[10] = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50};
        cout << "ingrese una cantidad de dinero: ";
        cin >> money;

        cout << "para " << money << ":" << endl;
        for (int i = 0; i < 10; i++)
        {
            quantity = money/denomination[i];
            cout << denomination[i] << " : " << quantity << endl;
            money %= denomination[i];
        }
        cout << "Faltante: " << money << endl;

        break;
    }
    default:
        cout << "El ejercicio ingresado no existe" << endl;
        break;
    }

    return 0;
}
