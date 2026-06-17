#ifndef MENUPRINCIPAL_HPP
#define MENUPRINCIPAL_HPP

#include <iostream>
#include "GestionAlumnos.hpp"
#include "utilidades.hpp"

using namespace std;

inline void ejecutarMenu() {
    tListaAlumnos lista;
    bool archivoOk;
    
    cargarDesdeArchivo(lista, archivoOk);
    if (!archivoOk) {
        cout << "Aviso: No se encontro un archivo previo. Se creara uno nuevo al guardar.\n";
    } else {
        cout << "Cargados " << lista.contador << " alumnos desde el archivo.\n";
    }
    pauseConsole();

    int opcion;
    do {
        clearConsole(); 
        cout << "================ MENU DE GESTION =================\n";
        cout << "1. Mostrar listado de alumnos\n";
        cout << "2. Mostrar un alumno determinado (Buscar e imprimir)\n";
        cout << "3. Insertar un alumno\n";
        cout << "4. Eliminar un alumno\n";
        cout << "5. Buscar posicion de un alumno (Por ID)\n";
        cout << "6. Ordenar y mostrar alumnos\n";
        cout << "7. Guardar cambios en archivo\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opcion (1-8): ";
        cin >> opcion;
        cin.ignore(); // ¡CRÍTICO! Limpiar el salto de línea de la opción elegida

        switch (opcion) {
            case 1:
                mostrarListado(lista);
                pauseConsole(); 
                break;
            case 2:
                mostrarAlumnoDeterminado(lista);
                pauseConsole();
                break;
            case 3:
                insertarAlumno(lista);
                pauseConsole();
                break;
            case 4:
                eliminarAlumno(lista);
                pauseConsole();
                break;
            case 5: {
                int idBuscado;
                cout << "Ingrese el ID a buscar: ";
                cin >> idBuscado;
                cin.ignore();
                int pos = buscarAlumnoPorId(lista, idBuscado);
                if (pos != -1) cout << "Encontrado en el indice de arreglo: " << pos << "\n";
                else cout << "No encontrado.\n";
                pauseConsole();
                break;
            }
            case 6: {
                int campo, sentido;
                cout << "\n--- Seleccione el Campo de Ordenamiento ---\n";
                cout << "1. ID\n2. Nombre\n3. Carrera\n4. Anio\n";
                cout << "Seleccione (1-4): ";
                cin >> campo;
                
                cout << "Seleccione el Sentido:\n1. Ascendente\n2. Descendente\n";
                cout << "Seleccione (1-2): ";
                cin >> sentido;
                cin.ignore();
                
                bool ascendente = (sentido == 1);
                ordenarBurbuja(lista, campo, ascendente);
                mostrarListado(lista); 
                pauseConsole();
                break;
            }
            case 7:
                guardarEnArchivo(lista);
                pauseConsole();
                break;
            case 8:
                cout << "Guardando datos automaticamente antes de cerrar...\n";
                guardarEnArchivo(lista);
                cout << "Programa finalizado. ¡Hasta luego!\n";
                pauseConsole();
                break;
            default:
                cout << "Opcion incorrecta. Intente nuevamente.\n";
                pauseConsole();
        }
    } while (opcion != 8);
}

#endif