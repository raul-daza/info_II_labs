#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <string>

#include "network.h"

using namespace std;

void menu(Network &);

int main()
{
    string rootpath = "C:/Users/raulD/OneDrive/Documentos/QT/labs/lab4/networks/";
//    Network network2;
//    network2.loadNetwork("C:/Users/raulD/OneDrive/Documentos/QT/labs/lab4/networks/netwotk1.txt");
//    network2.updateRouters();
//    network2.displayNetwork();
    unsigned int short op;

    cout << "----------------------------------------------" << endl;
    cout << "- Bienvenido al sistema de analisis de redes -" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "opciones:" << endl;
    cout << "0. cargar un archivo con una red" << endl;
    cout << "1. escoger un archivo con una red de forma aleatoria" << endl;
    cout << "2. empezar un a red desde cero" << endl;
    cin >> op;
    switch (op) {
    case 0:
    {
        string path;
        cout << "ingrese la ruta del archivo: ";
        cin.ignore();
        getline(cin, path);
        Network network(rootpath+path);
        menu(network);
        break;
    }
    case 1:
    {
        srand((unsigned) time(NULL));
        int random = rand()%2;
        cout << "la red abierta es la numero " << random << endl;
        Network network(rootpath+"network"+to_string(random)+".txt");
        menu(network);
        break;
    }
    case 2:
    {
        Network network;
        menu(network);
        break;
    }
    default:
        cout << "opcion invalida" << endl;
        break;
    }

    cout << "finished" << endl;
    return 0;
}

void menu(Network &network)
{
    unsigned int op;
    do{
        cout << "opciones:" << endl;
        cout << "agregar(0) o remover enrutadores(1)" << endl;
        cout << "agregar(2) o remover aristas(3)" << endl;
        cout << "calcular camino y costo (4)" << endl;
        cout << "ver la tabla de enrutamiento (5)" << endl;
        cout << "terminar el programa (6)" << endl;
        cin >> op;
        cin.ignore();
        switch (op) {
        case 0:
        {
            bool run;
            do
            {
                string name;
                cout << "ingrese el nombre del enrutador: ";
                getline(cin, name);
                network.addRouter(name);
                cout << "desea a agregar otro enrutador (1) o finalizar de añadir (0): ";
                cin >> run;
                cin.ignore();
            }
            while(run);
            break;
        }
        case 1:
        {
            unsigned int run;
            do
            {
                string name;
                cout << "ingrese el nombre del enrutador: ";
                getline(cin, name);
                network.removeRouter(name);
                cout << "desea eliminar otro enrutador (1) o finalizar de eliminar (0): ";
                cin >> run;
                cin.ignore();
            }
            while(run);
            break;
        }
        case 2:
        {
            unsigned int run;
            do
            {
                string name1, name2;
                unsigned int cost;
                cout << "ingrese el nombre del router1: ";
                getline(cin, name1);
                cout << "ingrese el nombre del router2: ";
                getline(cin, name2);
                cout << "ingrese costo de la arista: ";
                cin >> cost;
                network.addEdge(name1,name2,cost);
                cout << "desea a agregar otra arista (1) o finalizar de añadir (0): ";
                cin >> run;
                cin.ignore();
            }
            while(run);
            network.updateRouters();
            break;
        }
        case 3:
        {
            unsigned int run;
            do
            {
                string name1, name2;
                cout << "ingrese el nombre del router1: ";
                getline(cin, name1);
                cout << "ingrese el nombre del router2: ";
                getline(cin, name2);
                network.removeEdge(name1,name2);
                cout << "desea a eliminar otra arista (1) o finalizar de eliminar (0): ";
                cin >> run;
                cin.ignore();
            }
            while(run);
            network.updateRouters();
            break;
        }
        case 4:
        {
            string name1, name2;
            cout << "ingrese el nombre del router1: ";
            getline(cin, name1);
            cout << "ingrese el nombre del router2: ";
            getline(cin, name2);
            cost_path path_cost = network.pathBetweenRouters(name1, name2);
            cout << "El camino es: " << path_cost.path << ", con un costo de: " << path_cost.cost << endl;
            break;
        }
        case 5:
        {
            network.displayNetwork();
            break;
        }
        default:
            break;
        }
    }while(op!=6);
}

