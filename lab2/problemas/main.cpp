#include <iostream>
#include <string>
#include <math.h>

using namespace std;

bool isSameString(string a, string b);
unsigned short digitsCounter(int num);
void num2chars(int num, char **chars);
void printSeating(bool seating[15][20]);
int starCounter(int light[6][8]);
bool intersection(int *square1, int *square2, int *intersectionSquare);
bool isBothTouching(int min1, int max1, int min2, int max2, int &border, int adding, bool &noIntersection);
bool isTouching(int min, int max, int border);

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
        for (int i = 0; i < (int)in.length(); i++)
        {
            char individual = tolower(in[i]);
            // si el caracter no ha aparecido se agrega a la cadena 'out' y se marcar en el array 'caracter'
            if (!character[(int)individual])
            {
                character[(int)individual] = true;
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
        int sum = 0;

        cout << "ingrese un numero: ";
        cin >> n;
        cin.ignore();
        cout << "ingrese una cadena de caracteres numericos: ";
        getline(cin, a);
        cout << "original: " << a;

        int pos = 1;
        // es una variable auxiliar para iterar el arreglo, pos es el que se encarga de almacenar la posicion inicial que se va a extraer del arreglo
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
    case 11:
    {
        bool seating[15][20] = {};
        char option = 'R';
        while(option == 'R' || option == 'C')
        {
            cout << "el estado actual de la matriz es: " << endl;
            printSeating(seating);
            cout << "desea reservar (R), cancelar (C) un asiento o finalizar el programa (cualquier otra letra): ";
            cin >> option;
            string pos;
            unsigned int row, column;
            switch (option) {
            case 'R':
            {
                cout << "ingrese el lugar que quiere reservar primero la fila y luego la columna. Ej: B12" << endl;
                cin >> pos;
                row = (int)(pos[0]-'A');
                column = stoi(pos.substr(1,pos.length()-1)) - 1;
                if (!seating[row][column])
                    seating[row][column] = true;
                else
                    cout << "el lugar ya estaba ocupado" << endl;
                break;
            }
            case 'C':
            {
                cout << "ingrese el lugar que quiere cancelar primero la fila y luego la columna. Ej: B12" << endl;
                cin >> pos;
                row = (int)(pos[0]-'A');
                column = stoi(pos.substr(1,pos.length()-1)) - 1;
                if (seating[row][column])
                    seating[row][column] = false;
                else
                    cout << "el lugar no estaba ocupado" << endl;
                break;
            }
            default:
                break;
            }
        }
        break;
    }
    case 13:
    {
        int starImage[6][8] = {{0,3,4,0,0,0,6,8},
                               {5,13,6,0,0,0,2,3},
                               {2,6,2,7,3,0,10,0},
                               {0,0,4,15,4,1,6,0},
                               {0,0,7,12,6,9,10,4},
                               {5,0,6,10,6,4,8,0}};
        int counter = starCounter(starImage);
        cout << "la cantidad de estrellas en la imagen es: " << counter << endl;
        break;
    }
    case 15:
    {
        int square1[4], square2[4], intersectionSquare[4];
        cout << "ingrese el primer rectangulo en este orden: x, y, ancho, largo" << endl;
        for (int i = 0; i < 4; i++) cin >> square1[i];
        cout << "ingrese el segundo rectangulo en este orden: x, y, ancho, largo" << endl;
        for (int i = 0; i < 4; i++) cin >> square2[i];
        if (intersection(square1, square2, intersectionSquare))
        {
            cout << "la interseccion es el rectangulo: (" << intersectionSquare[0];
            for (int i = 1; i < 4; i++) cout << ',' << intersectionSquare[i];
            cout << ')' << endl;
        }else
        {
            cout << "no hay interseccion" << endl;
        }
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

void printSeating(bool seating[15][20])
{
    cout << "  ";
    for (int i = 1; i <= 20; i++)
        if (i < 10)
        cout << ' ' << i << ' ';
        else
        cout << i << ' ';
    cout << endl;
    for (int i = 0; i < 15; i++)
    {
        cout << (char)(i + 'A') << ' ';
        for (int j = 0; j < 20; j++)
        {
        if (seating[i][j] == false)
                cout << " - ";
        else
                cout << " + ";

        }
        cout << endl;
    }
}

int starCounter(int light[6][8])
{
    cout << "estellas encontradas en las posiciones: ";
    int counter = 0;
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 7; j++)
        {
            int sum = -(*(*(light+i)+j));
            for (int row = i-1; row <= i+1; row++)
                sum += *(*(light+row)+j);
            for (int col = j-1; col <= j+1; col++)
                sum += *(*(light+i)+col);
            if ((float)sum/5.0f > 6.0f)
            {
                counter += 1;
                cout << '(' << i << ',' << j << "), ";
            }

        }
    }
    cout << endl;
    return counter;
}

bool intersection(int *square1, int *square2, int *intersectionSquare)
{
    bool touchingLeft = false, touchingRight = false, touchingTop = false, touchingBottom = false, noIntersection = false;
    int leftmost = (square1[0] < square2[0]) ? square1[0] : square2[0];
    int rightmost = ((square1[0]+square1[2]) > (square2[0]+square2[2])) ? (square1[0]+square1[2]) : (square2[0]+square2[2]);
    int topmost = (square1[1] > square2[1]) ? square1[1] : square2[1];
    int bottommost = ((square1[1]-square1[3]) < (square2[1]-square2[3])) ? (square1[1]-square1[3]) : (square2[1]-square2[3]);
    while (!touchingLeft || !touchingRight || !touchingTop || !touchingBottom)
    {
        touchingLeft = isBothTouching(square1[0], square1[0]+square1[2], square2[0], square2[0]+square2[2], leftmost, 1, noIntersection);
        touchingRight = isBothTouching(square1[0], square1[0]+square1[2], square2[0], square2[0]+square2[2], rightmost, -1, noIntersection);
        touchingTop = isBothTouching(square1[1]-square1[3], square1[1], square2[1]-square2[3], square2[1], topmost, -1, noIntersection);
        touchingBottom = isBothTouching(square1[1]-square1[3], square1[1], square2[1]-square2[3], square2[1], bottommost, 1, noIntersection);
        if (noIntersection)
        {
            for (int i = 0; i < 4; i++) intersectionSquare[i] = 0;
            return false;
        }
    }
    intersectionSquare[0] = leftmost;
    intersectionSquare[1] = topmost;
    intersectionSquare[2] = rightmost - leftmost;
    intersectionSquare[3] = topmost - bottommost;
    return true;
}

bool isBothTouching(int min1, int max1, int min2, int max2, int &border, int adding, bool &noIntersection)
{
    if (!isTouching(min1, max1, border) && !isTouching(min2, max2, border))
    {
        noIntersection = true;
        return true;
    }else if (!isTouching(min1, max1, border) || !isTouching(min2, max2, border))
    {
        border += adding;
        return false;
    }else
    {
        return true;
    }
}

bool isTouching(int min, int max, int border)
{
    if (min <= border && border <= max)
    {
        return true;
    }
    return false;
}
