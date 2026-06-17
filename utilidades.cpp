#include <iostream>
#include <cstdlib>
#include <limits>
#include "utilidades.hpp"

using namespace std;

void pauseConsole()
{
    cout << "\nPresione Enter para continuar...";
    // Si el búfer está limpio, cin.peek() evita que ignore() bloquee la pantalla innecesariamente
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    cin.get();
}

void clearConsole()
{
    #ifdef __unix__
        system("clear");
    #elif __APPLE__
        system("clear");
    #elif defined(_WIN32) || defined(WIN32) || defined(WIN64)
        system("cls");
    #endif 
}