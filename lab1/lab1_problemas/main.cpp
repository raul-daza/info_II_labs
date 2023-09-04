#include <QCoreApplication>
#include <iostream>

using namespace std;

int main()
{
    unsigned short option;

    cout << "Ingrese que ejercicio desea ejecutar: ";
    cin >> option;

    switch (option) {
    case 1:
    {
        char vowels[] = "aeiouAEIOU";
        char c;
        bool vowel = false;

        cout << "Ingrese un caracter: ";
        cin >> c;
        if ((c>=65 && c<=90) || (c>=97 && c<=122))
        {
            for (int i = 0; i < 10; i++)
            {
                if (c == vowels[i])
                {
                    vowel = true;
                    break;
                }
            }
            if (vowel)
                cout << c << " es una vocal" << endl;
            else
                cout << c << " es una letra" << endl;
        }else
            cout << "No es una letra" << endl;
        break;
    }
    case 3:
    {
        unsigned short int dias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30 ,31 ,30, 31};
        unsigned short int mes, dia;

        cout << "ingrese el numero de un mes: ";
        cin >> mes;
        cout << "ingrese el numero de un dia en ese mes: ";
        cin >> dia;
        if (mes > 12)
            cout << mes << " es un mes invalido" << endl;
        else
            if (mes == 2 && dia == 29)
                cout << dia << '/' << mes << " es valida en bisiesto" << endl;
            else if (dia > dias[mes-1])
                cout << dia << '/' << mes << " es una fecha invalida" << endl;
            else
                cout << dia << '/' << mes << " es una fecha valida" << endl;
        break;
    }
    case 5:
    {
        int num, spaces, asterisks = 1;
        bool ascent = true;
        do
        {
        cout << "ingrese un numero impar: ";
        cin >> num;
        }while(num%2==0);

        spaces = num/2;

        while (asterisks > 0)
        {
            for(int i = 0; i < spaces; i++)
                cout << ' ';
            for(int i = 0; i < asterisks; i++)
                cout << '*';
            for(int i = 0; i < spaces; i++)
                cout << ' ';
            cout << endl;
            if (asterisks == num)
            {
                ascent = false;
            }
            if (ascent)
            {
                asterisks += 2;
                spaces -= 1;
            }else
            {
                asterisks -= 2;
                spaces += 1;
            }
        }
        break;
    }
    case 7:
    {
        int n, sum = 0, num1 = 1, num2 = 1, aux;
        cout << "ingrese un numero: ";
        cin >> n;
        while (num2 < n )
        {
            if (num2%2==0)
                sum += num2;
            aux = num2;
            num2 = num1 + num2;
            num1 = aux;

        }
        cout << "el resultado de la suma es: " << sum << endl;
        break;
    }
    case 9:
    {
        long long  n, digit, mult = 1, sum = 0;
        cout << "ingrese un numero: ";
        cin >> n;

        do
        {
            digit = n%10;
            n /= 10;
            for (int i = 0; i < digit; i++)
                mult *= digit;
            sum += mult;
            mult = 1;
        } while(n != 0);

        cout << "el resultado de la suma es: " << sum << endl;

        break;
    }
    case 11:
    {
        int MCM, num;
        bool found;
        cout << "ingrese un numero: ";
        cin >> num;
        MCM = num;

        do
        {
            found = true;
            for (int i = 1; i <= num; i++)
                if (MCM%i != 0)
                {
                    found = false;
                    MCM += 1;
                    break;
                }
        }while(!found);

        cout << "el minimo comun multiplo es: " << MCM << endl;
        break;
    }
    case 13:
    {
        int num, sum = 0;
        bool prime;
        cout << "ingrese un numero: ";
        cin >> num;

        for (int i = 2; i < num; i++)
        {
            prime = true;
            for(int j = 2; j < i; j++)
            {
                if (i%j==0)
                {
                    prime = false;
                    break;
                }
            }
            if (prime)
            {
                sum += i;
            }
        }
        cout << "el resultado de la suma es: " << sum << endl;
        break;
    }
    case 15:
    {
        int num, sum = 1;
        cout << "ingrese un numero impar: ";
        cin >> num;

        for(int i = 3; i <= num; i+= 2)
        {
            sum += i*i - i + 1; // izquierda superior
            sum += i*i; // derecha superior
            sum += i*i - 2*i + 2; // izquierda inferior
            sum += i*i - 3*i + 3; // derecha inferior
        }

        cout << "es una espiral de " << num << 'x' << num << ", la suma es: " << sum;

        break;
    }
    case 17:
    {
        int  triangular, k, divisors = 0, n = 1;
        cout << "ingrese un numero: ";
        cin >> k;
        while (divisors <= k)
        {
            divisors = 0;
            triangular = n*(n+1)/2;
            for (int i = 1; i <= triangular; i++)
                if (triangular%i == 0)
                    divisors++;
            n++;
        }
        cout << "el numero es: " << triangular << " que tiene " << divisors << " divisores" << endl;
        break;
    }
    default:
        cout << "El ejercicio ingresado no existe" << endl;
        break;
    }
    return 0;
}
