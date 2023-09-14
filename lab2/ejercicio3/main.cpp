#include <iostream>

using namespace std;

int main()
{
    cout << endl;

    unsigned short b[4][2] = {{77, 50}, {5, 2}, {28, 39}, {99, 3}};

    for (int i = 0; i < 4; i++)
    {
        cout << "b[" << i << "] direccion: " << b+i <<endl;
        for (int j = 0; j < 2; j++)
        {
            cout << "   b[" << i << "][" << j << "] direccion: " << *(b+i)+j << endl;
        }
    }
    cout << endl;

    cout << "b: " << b << endl;
    cout << "b+2: " << b+2 << endl;
    cout << "*(b+2): " << *(b+2) << endl;
    cout << "*(b+2)+1: " << *(b+2)+1 << endl;
    cout << "*(*(b+2)+1): " << *(*(b+2)+1) << endl;
    cout << "b[3][1]: " << b[3][1] << endl;
//    cout << "*b++: " << *b++ << endl;

    return 0;
}

/*
 * b[0][0]: 0x0A12
 * b[0][1]: 0x0A14
 * b[1][0]: 0x0A16
 * b[1][1]: 0x0A18
 * b[2][0]: 0x0A1A
 * b[2][1]: 0x0A1C
 * b[3][0]: 0x0A1E
 * b[3][1]: 0x0A20
*/

/*
 * b: 0x0A12
 * b+2: 0x0A1A
 * *(b+2): 0x0A1A
 * *(b+2)+1: 0x0A1C
 * *(*(b+2)+1): 39
 * b[3][1]: 3
 * *b++: 0x0A12
*/
