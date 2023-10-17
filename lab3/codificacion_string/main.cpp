#include <bitset>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string encoding1(string input, unsigned int n);
string decoding1(string output, unsigned int n);
string encoding2(string input, unsigned int n);
string decoding2(string output, unsigned int n);

int main()
{

    unsigned int n, option;
    cout << "quiere codificar y descodificar con la opcion 1 o 2: ";
    cin >> option;
    cout << "ingrese la semilla: ";
    cin >> n;
    fstream fileinfo;
    fileinfo.open("C:/Users/raulD/OneDrive/Documentos/QT/labs/lab3/archivos_practica3/textoplano.txt", ios::in);
    if (fileinfo.is_open())
    {
        string line;
        string text = "";
        while (getline(fileinfo, line))
        {
            text += line;
            text += '\n';
        }
        cout << text << endl;
        switch (option) {
        case 1:
        {
            text = "1234";
            string output = encoding1(text, n);
            fstream binfile;
            binfile.open("C:/Users/raulD/OneDrive/Documentos/QT/labs/lab3/archivos_practica3/binFileEncoding1.bin", ios::out | ios::binary);
            binfile << output;
            string decoOutput = decoding1(output, n);
            fstream decodefile;
            decodefile.open("C:/Users/raulD/OneDrive/Documentos/QT/labs/lab3/archivos_practica3/binFileDecoding1.txt", ios::out);
            decodefile << decoOutput;
            decodefile.close();
            binfile.close();
            fileinfo.close();
            break;
        }
        case 2:
        {
            string output = encoding2(text, n);
            fstream binfile;
            binfile.open("C:/Users/raulD/OneDrive/Documentos/QT/labs/lab3/archivos_practica3/binFileEncoding2.bin", ios::out | ios::binary);
            binfile << output;
            string decoOutput = decoding2(output, n);
            fstream decodefile;
            decodefile.open("C:/Users/raulD/OneDrive/Documentos/QT/labs/lab3/archivos_practica3/binFileDecoding2.txt", ios::out);
            decodefile << decoOutput;
            decodefile.close();
            binfile.close();
            fileinfo.close();
            break;
        }
        default:
            break;
        }
    }else
    {
        cout << "No open file" << endl;
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
    unsigned int i = 0;
    while (input[i] != 0)
    {
        cout << bitset<8>{(unsigned long long)(input[i])};
        i++;
    }
    cout << endl;

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
    i = 0;
    // para mostrar en binario los caracteres codificados
    while (output[i] != 0)
    {
        cout << bitset<8>{(unsigned long long)(output[i])};
        i++;
    }
    cout << endl << output << endl;
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
    int i = 0;
    // para mostrar en binario los caracteres codificados
    while (deoutput[i] != 0)
    {
        cout << bitset<8>{(unsigned long long)(deoutput[i])};
        i++;
    }
    cout << endl << deoutput << endl;
    return deoutput;
}

string encoding2(string input, unsigned int n)
{
    cout << input << endl;
    string temp; // cadena temporal: almacena la cadena de entrada corrida a la derecha 1 posicion
    string output; // cadena de salida
    unsigned char character; // caracter que se esta analizando en el momento
    int i = 0;
    while (input[i] != 0)
    {
        cout << bitset<8>{(unsigned long long)(input[i])};
        i++;
    }
    cout << endl;
    i = 0;
    bool isOne = false; // si el ultimo bit del caracter es 1
    while (input[i] != 0)
    {
        character = input[i];
        // hace el corriemiento a la derecha y si el ultimo bit del caracter anterior era 1 lo pasa a la primera posicion de este
        if (isOne)
        {
            temp += (character >> 1) | (1 << 7);
        }else
        {
            temp += character >> 1;
        }
        // verifica si el ultimo bit del caracter es 1
        if (character%2 == 1)
        {
            isOne = true;
        }else
        {
            isOne = false;
        }
        cout << bitset<8>{(unsigned long long)(temp[i])};
        i++;
    }
    unsigned int pointerBit1 = (n+7)%8; // punteros a los bits de la cadena de entrada, se le suma 7 para que cuando n=8 o algun multiplo de 8 se ubique
        // en el bit 7 (antes era n%8-1 pero eso era underflow)
    unsigned int pointerBit2 = 0; // puntero de los bits de la cadena temporal
    unsigned int pointerChar1 = (n-1)/8; // puntero a los caracteres de la cadena de entrada, se le resta uno porque apunta al ultimo bit de un bloque
    unsigned int pointerChar2 = 0; // puntero a los caracteres de la cadena de salida
    unsigned char result;
    character = temp[pointerChar2]; // le asigna la variable el primer caracter a modificar
    while(pointerChar2 < temp.length())
    {
        if (pointerChar1 < input.length()){
            result = input[pointerChar1] & (1 << (7 - pointerBit1)); // mira si el ultimo elemento del bloque de bits era 1 o 0
        }// el puntero esta apuntando mas alla del ultimo elemento, asume que el ultimo elemento del bloque es 0
        else
        {
            result = 0;
        }
        //cout << endl <<bitset<8>{(unsigned long long)(result)};
        // si el ultimo elemento del bloque de bits era 0, entonces pon 0 en la posicion inicial del bloque, de lo contrario pon 1
        if (result == 0)
        {
            character = character & ~(1 << (7 - pointerBit2));
        }else
        {
            character = character | (1 << (7 - pointerBit2));
        }
        //cout << endl <<bitset<8>{(unsigned long long)(character)};
        // actualiza los punteros
        pointerBit1 += n;
        pointerBit2 += n;
        // si los punteros apuntan fuera del caracter actual, muevete a otro caracter
        if (pointerBit1 > 7)
        {
            pointerChar1 += pointerBit1/8; // si n es muy grande puede que se mueva varios caracteres adelante
            pointerBit1 = pointerBit1%8; // le asigna al puntero la posicion relativa al nuevo caracter
        }
        if (pointerBit2 > 7)
        {
            output += character; // agrega el caracter modificado a la cadena de salida
            // si hay caracteres en la cadena temporal que no se modifica lo agrega a la cadena de salida
            for (unsigned int i = pointerChar2+1; i < ((pointerChar2 + pointerBit2/8) < temp.length() ? (pointerChar2 + pointerBit2/8) : temp.length()); i++)
            {
                output += temp[i];
            }
            pointerChar2 += pointerBit2/8; // si n es muy grande puede que se mueva varios caracteres adelante
            pointerBit2 = pointerBit2%8; // le asigna al puntero la posicion relativa al nuevo caracter
            character = temp[pointerChar2]; // se mueve al siguiente caracter a modificar
        }
    }
    cout << endl;
    // si la ultima posicion de toda la cadena es 1 y n no es divisible por la longitud de bits del arreglo
    if (input[input.length()-1]%2 == 1 && input.length()*8%n != 0)
    {
        output += (char)255;
    }else
    {
        output += (char)254;
    }
    i = 0;
    while (output[i] != 0)
    {
        cout << bitset<8>{(unsigned long long)(output[i])};
        i++;
    }
    return output;
}

string decoding2(string output, unsigned int n)
{
    bool isFirstOne = (bool)(output[0] >> 7); // si el primer bit del caracter es 1

    int i = output.length()-2;
    bool isOne = false;
    unsigned char character;
    cout << endl << "decodificador" << endl;
    string temp = ""; // reinicia temp
    while (i != -1)
    {
        character = output[i];
        // hace el corriemiento a la izquierda y si el primer bit del caracter siguiente era 1 lo pasa a la ultima posicion de este
        if (isOne)
        {
            temp = (char)((character << 1) | 1) + temp;
        }else
        {
            temp = (char)(character << 1) + temp;
        }
        // verifica si el primer bit del caracter es 1
        if ((character>>7)%2 == 1)
        {
            isOne = true;
        }else
        {
            isOne = false;
        }
        i--;
    }
    i = 0;
    while (temp[i] != 0)
    {
        cout << bitset<8>{(unsigned long long)(temp[i])};
        i++;
    }
    string outputdeco;
    unsigned int pointerBit1 = -1; // puntero1 para bitswap
    unsigned int pointerBit2 = (n+7)%8; // puntero2 para bitswap
    unsigned int pointerChar1 = 0; // puntero al carater donde esta ubicado el puntero1
    unsigned int pointerChar2 = (n-1)/8; // puntero al caracter donde esta ubicado el puntero2
    unsigned char result;
    character = temp[pointerChar2]; // le asigna la variable el primer caracter a modificar
    // algunos caracteres no se modifican los agrega
    for (unsigned int i = pointerChar1; i < pointerChar2; i++)
    {
        outputdeco += temp[i];
    }
    while(true)
    {
        // asigna a result 1 o 0 dependiendo el bit a colocar es 1 o 0
        if (pointerBit1 != (unsigned short)-1){
            result = temp[pointerChar1] & (1 << (7 - pointerBit1)); // mira si el ultimo elemento del bloque de bits era 1 o 0
        }// asigna a result 1 o 0 dependiendo si el primer bit de toda la cadena era 1 o 0
        else
        {
            result = isFirstOne ? 1 : 0;
        }
        //cout << endl <<bitset<8>{(unsigned long long)(result)};
        // si el primer elemento del bloque de bits era 0, entonces pon 0 en la posicion final del bloque, de lo contrario pon 1
        if (result == 0)
        {
            character = character & ~(1 << (7 - pointerBit2));
        }else
        {
            character = character | (1 << (7 - pointerBit2));
        }
        //cout << endl <<bitset<8>{(unsigned long long)(character)};
        // actualiza los punteros
        pointerBit1 += n;
        pointerBit2 += n;
        // si los punteros apuntan fuera del caracter actual, muevete a otro caracter
        if (pointerBit1 > 7)
        {
            pointerChar1 += pointerBit1/8; // si n es muy grande puede que se mueva varios caracteres adelante
            pointerBit1 = pointerBit1%8; // le asigna al puntero la posicion relativa al nuevo caracter
        }
        if (pointerBit2 > 7)
        {
            // agrega el caracter modificado a la cadena de salida solo si el caracter no es el ultimo elemento
            if (pointerChar2 < temp.length()-1) outputdeco += character;
            pointerChar2 += pointerBit2/8; // si n es muy grande puede que se mueva varios caracteres adelante
            // se mueve al siguiente caracter a modificar solo si pointerChar2 apunta a una posicion valida de la cadena temporal
            if (pointerChar2 < temp.length()) character = temp[pointerChar2];
            pointerBit2 = pointerBit2%8; // le asigna al puntero la posicion relativa al nuevo caracter
            // si pointerChar2 apunta a una posicion invalida
            if (pointerChar2 >= temp.length())
            {
                // agrega los caracteres que faltan excepto el ultimo
                for (unsigned int i = pointerChar1+1; i < temp.length() - 1; i++)
                {
                    outputdeco += temp[i];
                }
                // si se estaba apuntando al ultimo caracter en la cadena temporal, entonces guarda en character el ultimo caracter
                if (pointerChar1 < temp.length()-1)
                {
                    character = temp[temp.length()-1];
                }
                break;
            }// si apunta a una direccion valida
            else
            {
                // agrega los caracteres que no fueron modificados
                for (unsigned int i = pointerChar1+1; i < pointerChar2; i++)
                {
                    outputdeco += temp[i];
                }
            }
        }
    }
    // si el ultimo bit del ultimo caracter debe ser 1 asigna el 1 y agrega el caracter, de lo contrario solo agrega el caracter
    if (output[output.length()-1] == (char)255)
    {
        outputdeco += character | 1;
    }else
    {
        outputdeco += character;
    }
    i = 0;
    cout << endl;
    while (outputdeco[i] != 0)
    {
        cout << bitset<8>{(unsigned long long)(outputdeco[i])};
        i++;
    }
    cout << endl << outputdeco << endl;
    return outputdeco;
}
