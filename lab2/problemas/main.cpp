#include <iostream>
#include <string>
#include <math.h>

using namespace std;

bool isSameString(string a, string b);
unsigned short digitsCounter(int num);
void num2chars(int num, char **chars);

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
    case 3:
    {
        string a;
        string b;
        cin.ignore();
        cout << "Ingrese una cadena de caracteres: ";
        getline(cin, a);
        cout << "Ingrese otra cadena de caracteres: ";
        getline(cin, b);
        if (isSameString(a,b))
            cout << "las cadenas son iguales" << endl;
        else
            cout << "las cadenas son diferentes" << endl;
        break;
    }
    case 5:
    {
        char *ptr = nullptr;
        char **aux = &ptr;
        int num;
        cout << "ingrese un numero: ";
        cin >> num;
        num2chars(num, aux);
        cout << ptr << endl;
        delete [] ptr;
        break;
    }
    case 7:
    {
        string in;
        string out;
        cin.ignore();
        cout << "ingrese una cadena de caracteres: ";
        getline(cin,in);
        // almacena si el caracter ya existe
        bool character[256] = {};
        for (int i = 0; i < in.length(); i++)
        {
            char individual = tolower(in[i]);
            // si el caracter no ha aparecido se agrega a la cadena 'out' y se marcar en el array 'caracter'
            if (!character[individual])
            {
                character[individual] = true;
                out += individual;
            }
        }
        cout << out<< endl;
        break;
    }
    case 9:
    {
        int n;
        string a;
        cout << "ingrese un numero: ";
        cin >> n;
        cin.ignore();
        cout << "ingrese una cadena de caracteres numericos: ";
        getline(cin, a);
        cout << "original: " << a;
        int sum = 0;
        int pos = 1;
        for (int i = a.length(); pos > 0; i -= n)
        {
            pos = i-n;
            if (pos < 0)
            {
                n += pos;
                pos = 0;
            }
            // si el numero es negativo y solo va a quedar el signo sin iterar, toma el signo también
            if(a[0] == '-' && pos == 1)
            {
                pos = 0;
                sum += stoi(a.substr(pos, n+1));
            }
            else
                sum += stoi(a.substr(pos, n));
        }
        cout << endl << "suma: " << sum << endl;
        break;
    }
    default:
        cout << "El ejercicio ingresado no existe" << endl;
        break;
    }

    return 0;
}

bool isSameString(string a, string b)
{
    if (a.length() != b.length())
        return false;
    if (a == b)
        return true;
    return false;
}

unsigned short digitsCounter(int num)
{
    unsigned short digits = 0;
    do
    {
        num /= 10;
        digits++;
    }while (num != 0);
    return digits;
}

void num2chars(int num, char **chars)
{
    unsigned int digits = digitsCounter(num);
    bool isNegative = false;
    if (num < 0)
    // si el numero es negativo se vuelve positivo y se agrega un digito porque se cuenta el signo '-' para el arreglo
    if (num < 0)
    {
        isNegative = true;
        digits++;
        num *= -1;
    }

    *chars = new char[digits+1];
    (*chars)[digits] = 0;

    if (isNegative)
        (*chars)[0] = '-';
    unsigned short digit;
    int i = digits-1;
    do
    {
        digit = num%10;
        *((*chars)+i) = digit + '0';
        i--;
        num /= 10;
    }while(num != 0);
}
