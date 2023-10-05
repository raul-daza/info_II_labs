#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string encoding1(string input, unsigned int n);
string decoding1(string output, unsigned int n);

int main()
{
    bool finished = false;
    while (!finished)
    {
        signed short op;
        cout << "-------------------------------------------------------------------" << endl;
        cout << "-------------------Bienvenido al cajero BancUdeA-------------------" << endl;
        cout << "-------------------------------------------------------------------" << endl;
        cout << "Desea ingresar como:" << endl;
        cout << "* Administrador (ingrese 0)" << endl;
        cout << "* Usuario (ingrese 1)" << endl;
        do
        {
            cout << "opcion: ";
            cin >> op;
            for (int i = 0; i < 10; i++) cout << endl;
            try{
                switch (op)
                {
                case 0:
                {
                    string encodedPassword, password;
                    fstream sudo;
                    sudo.open("C:/Users/raulD/OneDrive/Documentos/QT/labs/lab3/archivos_practica4/sudo.bin", ios::in | ios::binary);
                    getline(sudo, encodedPassword);
                    cout << "ingrese la contrasena de administrador: ";
                    cin >> password;
                    if (encodedPassword == encoding1(password,5))
                    {
                        string id, balance, info = "";
                        cout << "Registor de usuarios" << endl;
                        cout << "ingrese la cedula: ";
                        cin >> id;
                        cout << "ingrese la contrasena: ";
                        cin >> password;
                        cout << "ingrese el saldo: ";
                        cin >> balance;
                        info += id + ',' + password + ',' + balance;
                    }else
                    {
                        cout << "contraseña invalida" << endl;
                    }
                    break;
                }
                case 1:
                {
                    unsigned short opUser;
                    cout << "Menu de usuario" << endl;
                    cout << "* Consultar saldo (ingrese 0)" << endl;
                    cout << "* Retirar dinero (ingrese 1)" << endl;
                    do
                    {
                        cout << "opcion: ";
                        cin >> opUser;
                    }while(opUser!= 0 && opUser != 1);
                    break;
                }
                default:
                {
                    throw "Opcion invalida";
                    break;
                }
                }
            }
            catch (const char * error)
            {
                cerr << "Error: " << error << endl;
            }
        }while(op != 0 && op != 1);

    }
    return 0;
}

string encoding1(string input, unsigned int n)
{
    string output; // informacion codificada
    bool finished = false;
    unsigned long long pointerChar1 = 0, pointerChar2 = 0, pointerChar3 = 0; // lleva la cuenta la posicion del caracter que se esta modificando
    unsigned short pointerBit1 = 0, jumps = 0; // apunta al bit que se va a verificar si es 1 o 0 para llevar la cuenta de cantidad de 1s y 0s
        // los saltos que se dan en la inversion de bits
    short pointerBit2 = -1, pointerBit3 = 0; // pointerBit2 apunta al bit a modificar, pointerBit2 apunta al primer bit del bloque de bits
    char character = input[0], character1 = input[0]; // caracter que se esta modificando, caracter1 que se le estan contando los 1s y 0s
    unsigned int ones = 0, zeros = 0; // cantidad de ceros y unos
    // para mostrar en binario la informacion

    while(!finished)
    {
        // define el tamaño de los saltos dependiendo de la cantidad de 1s y 0s
        if (zeros == ones)
        {
            jumps = 1;
        }else if (zeros > ones)
        {
            jumps = 2;
        }else
        {
            jumps = 3;
        }
        // reinicia el conteo
        zeros = 0; ones = 0;
        // cuenta la cantidad de 1s y 0s
        for(unsigned int i = 1; i <= n; i++)
        {
            // si ya no apunta al caracter actual
            if(pointerBit1 > 7)
            {
                pointerChar1++; // se mueve al siguiente caracter de la lista
                // si se alcanzó el final del texto a codificar termina
                if (pointerChar1 == input.length())
                {
                    break;
                }
                character1 = input[pointerChar1]; // se guadar el siguiente caracter
                pointerBit1 = pointerBit1%8; // coloca el puntero el la posicion relativa del siguiete caracter
            }
            // mira si el bit es 0 o 1
            if ((character1 >> (7-pointerBit1))%2 == 0)
            {
                zeros++;
            }else
            {
                ones++;
            }
            // se mueve al siguiete bit
            pointerBit1+=1;
        }
        // se van dando los saltos de bits en el bloque de bits
        for(unsigned int i = jumps; i <= n; i+=jumps)
        {
            // da el salto al bit a modificar
            pointerBit2 += jumps;
            // si ya no apunta al caracter actual
            if(pointerBit2 > 7)
            {
                pointerChar2++; // se mueve al siguiente caracter de la lista
                // si se alcanzó el final del texto a codificar termina
                if (pointerChar2 >= input.length())
                {
                    finished = true;
                    break;
                }
                output += character; // se agrega el caracter codificado a la informacion codificada
                character = input[pointerChar2]; // se guadar el siguiente caracter a codificar
                pointerBit2 = pointerBit2%8; // coloca el puntero en la posicion relativa del siguiete caracter
            }
            character = character ^ (1 << (7-pointerBit2)); // invierte el bit apuntado
        }
        pointerBit3 += n; // se mueve a la primera posicion del siguiente bloque de bits
        // si apunta fuera del caracter actual
        if (pointerBit3 > 7)
        {
            // mueve el puntero del caracter al caracter donde inicia el siguiente bloque de bits
            pointerChar3 += pointerBit3/8;
            // si se alcanzo el final del texto a codificar termina
            if (pointerChar3 >= input.length())
            {
                break;
            }
            pointerBit3 %= 8; // coloca el puntero en la posicion relativa del siguiente caracter
            // si el puntero no apunta al primer bit de un caracter
            if (pointerBit3 > 0)
            {
                // pointerBit2 apunta al bit anterior al inicio del bloque de bits
                pointerBit2 = pointerBit3-1;
                // si no son iguales es porque en el bucle anterior no se guardo el caracter modificado
                if (pointerChar2 != pointerChar3)
                {
                    pointerChar2 = pointerChar3;
                    output += character;
                    character = input[pointerChar2];
                }
            } // si apunta al primer bit de un caracter, entonces pointerBit2 debe apuntar al ultimo bit del caracter anterior
            else
            {
                pointerBit2 = 7;
                pointerChar2 = pointerChar3-1;
            }
        }// actualiza la posicion del puntero que invierte los bits
        else
        {
            pointerBit2 = pointerBit3-1;
        }

    }
    output += character; // agrega el ultimo caracter codificado en el bucle
    return output;
}

string decoding1(string output, unsigned int n)
{
    string deoutput;
    bool finished = false;
    unsigned long pointerChar1 = 0, pointerChar2 = 0, pointerChar3 = 0; // lleva la cuenta la posicion del caracter que se esta modificando
    unsigned short pointerBit1 = 0, jumps = 0; // lleva la cuenta de la posicion del bit que se esta modificando, dice cada cuanto se inverte los bits
    short pointerBit2 = -1, pointerBit3 = 0;
    char character = output[0], character1 = output[0]; // caracter que se esta modificando
    unsigned int ones = 0, zeros = 0; // cantidad de ceros y unos
    // para mostrar en binario la informacion
    while(!finished)
    {
        if (zeros == ones)
        {
            jumps = 1;
        }else if (zeros > ones)
        {
            jumps = 2;
        }else
        {
            jumps = 3;
        }
        zeros = 0; ones = 0;
        for(unsigned int i = 1; i <= n; i++)
        {
            if(pointerBit1 > 7)
            {
                pointerChar1++; // se mueve al siguiente caracter de la lista
                // si se alcanzó el final del texto a codificar termina
                if (pointerChar1 == output.length())
                {
                    break;
                }
                character1 = output[pointerChar1]; // se guadar el siguiente caracter a codificar
                pointerBit1 = pointerBit1%8; // coloca el puntero el la posicion relativa del siguiete caracter
            }
            // inverte los bits desde el mas significativ0
            if ((character1 >> (7-pointerBit1))%2 == 0)
            {
                zeros++;
            }else
            {
                ones++;
            }
            pointerBit1+=1;
            // si ya se acabaron los bits y aun no se cumple la inversion de los n bits entonces para al siguiente caracter
        }
        for(unsigned int i = jumps; i <= n; i+=jumps)
        {
            // inverte los bits desde el mas significativo
            pointerBit2 += jumps;

            if(pointerBit2 > 7)
            {
                pointerChar2++; // se mueve al siguiente caracter de la lista
                // si se alcanzó el final del texto a codificar termina
                if (pointerChar2 >= output.length())
                {
                    finished = true;
                    break;
                }
                deoutput += character; // se agresa el caracter codificado a la informacion codificada
                character = output[pointerChar2]; // se guadar el siguiente caracter a codificar
                pointerBit2 = pointerBit2%8; // coloca el puntero el la posicion relativa del siguiete caracter
            }
            character = character ^ (1 << (7-pointerBit2));
            // como ese bit se invertio, debe restarse en el que sumo y sumarsele al contrario
            if ((character >> (7-pointerBit2))%2 == 0)
            {
                ones--;
                zeros++;
            }else
            {
                zeros--;
                ones++;
            }
            // si ya se acabaron los bits y aun no se cumple la inversion de los n bits entonces para al siguiente caracter
        }
        pointerBit3 += n;
        if (pointerBit3 > 7)
        {
            pointerChar3 += pointerBit3/8;
            if (pointerChar3 >= output.length())
            {
                break;
            }
            pointerBit3 %= 8;
            if (pointerBit3 > 0)
            {
                pointerBit2 = pointerBit3-1;
                if (pointerChar2 != pointerChar3)
                {
                    pointerChar2 = pointerChar3;
                    deoutput += character;
                    character = output[pointerChar2];
                }
            }else
            {
                pointerBit2 = 7;
                pointerChar2 = pointerChar3-1;
            }
        }else
        {
            pointerBit2 = pointerBit3-1;
        }
    }
    deoutput += character; // agrega el ultimo caracter codificado en el bucle
    return deoutput;
}
