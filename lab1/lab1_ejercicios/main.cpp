#include <QCoreApplication>
#include <iostream>

#define PI 3.1416

using namespace std;

int main()
{
    unsigned short option;

    cout << "Ingrese que ejercicio desea ejecutar (impares): ";
    cin >> option;

    switch (option) {
    case 1:
    {
        int a, b;

        cout << "Ingrese un numero A: ";
        cin >> a;
        cout << "Ingrese un numero B: ";
        cin >> b;
        cout << "El residuo de la division A/B es: " << a%b;
        break;
    }
    case 3:
    {
        int a, b;

        cout << "Ingrese un numero A: ";
        cin >> a;
        cout << "Ingrese un numero B: ";
        cin >> b;
        if (a==b) cout << "Los numeros son iguales" << endl;
        else cout << "el numero mayor es: " << ((a > b) ? a : b) << endl;
        break;
    }
    case 5:
    {
        float a, b;

        cout << "Ingrese un numero A: ";
        cin >> a;
        cout << "Ingrese un numero B: ";
        cin >> b;
        cout << (int) (a/b+0.5) << endl;
        break;
    }
    case 7:
    {
        int num, sum = 0;
        cout<< "Ingrese un numero: ";
        cin >> num;
        for (int i = 1; i <= num; i++) sum += i;
        cout << "la sumatoria de 0 hasta " << num << " es: " << sum << endl;
        break;
    }
    case 9:
    {
        int radio;
        cout << "Ingrese un numero: ";
        cin >> radio;
        cout << "Perimetro: " << 2*PI*radio << endl;
        cout << "Area: " << PI*radio*radio << endl;
        break;
    }
    case 11:
    {
        int num;
        cout << "Ingrese un numero: ";
        cin >> num;
        for (int i = 1; i <= 10; i++)
        {
            cout << i << "x" << num << "=" << i*num <<endl;
        }
        break;
    }
    case 13:
    {
        int num;
        cout << "Ingrese un numero: ";
        cin >> num;
        cout << "los divisiores de n son:" << endl;
        for (int i = 1; i <= num; i++)
            if (num%i == 0) cout << i << endl;
        break;
    }
    case 15:
    {
        int num, sum = 0;
        do
        {
            cout << "ingrese un numero ('0' para finalizar): ";
            cin >> num;
            sum += num;
        }while(num != 0);
        cout << "El resultado de la sumatoria es: " << sum << endl;
        break;
    }
    case 17:
    {
        int num, mayor = 0;
        do
        {
            cout << "ingrese un numero ('0' para finalizar): ";
            cin >> num;
            if (num > mayor) mayor = num;
        }while(num != 0);
        cout << "El numero mayor fue: " << mayor << endl;
        break;
    }
    case 19:
    {
        int num;
        bool primo = true;
        cout << "Ingrese un numero: ";
        cin >> num;
        for (int i = 2; i < num; i++)
        {
            if (num%i == 0)
            {
                primo = false;
                break;
            }
        }
        if (primo) cout << num << " es un numero primo" << endl;
        else cout << num << " no es un numero primo" << endl;
        break;
    }
    case 21:
    {
        char c;
        cout << "Ingrese un caracter: ";
        cin >> c;
        cout << "Letra convertida: " << (char)((c < 91) ? (c + 32) : (c - 32)) ;
        break;
    }
    case 23:
    {
        int a, b;
        int mult1 = 1, mult2 = 1;
        int result1, result2;

        cout << "ingrese un numero (A): ";
        cin >> a;
        cout << "ingrese un numero (B): ";
        cin >> b;

        result1 = mult1*a;
        result2 = mult2*b;

        do
        {
            if(result1 > result2)
            {
                mult2++;
                result2 = mult2*b;
            }
            else if(result2 > result1)
            {
                mult1++;
                result1 = mult1*a;
            }
        }while(result1 != result2);

        cout << "el MCM de " << a << " y " << b << " es: " << result1 << endl;

        break;
    }
    case 25:
    {
        int num, temp, count = 0;
        cout << "ingrese un numero: ";
        cin >> num;
        temp = num;
        do{
            count++;
            temp /= 10;
        }while (temp != 0);
        cout << num << " tiene " << count << " digitos" << endl;
        break;
    }
    case 27:
    {
        float a,b;
        char symb;
        cout << "Ingrese el primer operando: ";
        cin >> a;
        cout << "Ingrese el simbolo de la operacion: ";
        cin >> symb;
        cout << "Ingrese el segundo operando: ";
        cin >> b;
        switch (symb)
        {
        case '+':
            cout << a << symb << b << "=" << a+b << endl;
            break;
        case '-':
            cout << a << symb << b << "=" << a-b << endl;
            break;
        case '*':
            cout << a << symb << b << "=" << a*b << endl;
            break;
        case '/':
            cout << a << symb << b << "=" << a/b << endl;
            break;
        default:
            cout << "el simbolo " << symb << " no es valido" << endl;
            break;
        }
        break;
    }
    case 29:
    {
        char symb = 0;
        int upper = 100, lower = 0, tried;
        cout << "Piense en un numero entre 0 y 100" << endl;
        tried = (upper-lower)/2;
        while((symb != '='))
        {

            cout << "su numero es mayor (>), menor (<) o igual (=) a " << tried << ": ";
            cin >> symb;
            switch (symb) {
            case '=':
                cout << "He acerdato, tu numero es: " << tried;
                break;
            case '<':
                upper = tried - 1;
                tried = tried - (upper-lower)/2 - 1;
                break;
            case '>':
                lower = tried + 1;
                tried = tried + (upper-lower)/2 + 1;
                break;
            default:
                cout << "caracter invalido" << endl;
                break;
            }
        }
        break;
    }
    default:
        cout << "El ejercicio ingresado no existe" << endl;
        break;
    }

    return 0;
}
