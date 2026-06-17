#ifndef GESTIONALUMNOS_HPP
#define GESTIONALUMNOS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX_ALUMNOS = 100;

struct tAlumno {
    int id; 
    string nombre;
    string carrera;
    int anio;
};

typedef tAlumno tArray[MAX_ALUMNOS];

struct tListaAlumnos {
    tArray elementos;
    int contador;
};

// --- SOBRECARGA DE OPERADORES ---
inline bool operator>(tAlumno opIzq, tAlumno opDer) {
    return opIzq.nombre > opDer.nombre;
}

inline bool operator<(tAlumno opIzq, tAlumno opDer) {
    return opIzq.nombre < opDer.nombre;
}

inline bool compararPorCampo(tAlumno a, tAlumno b, int campo, bool ascendente) {
    bool condicion = false;
    if (campo == 1) { 
        condicion = ascendente ? (a.id > b.id) : (a.id < b.id);
    } else if (campo == 2) { 
        condicion = ascendente ? (a.nombre > b.nombre) : (a.nombre < b.nombre);
    } else if (campo == 3) { 
        condicion = ascendente ? (a.carrera > b.carrera) : (a.carrera < b.carrera);
    } else if (campo == 4) { 
        condicion = ascendente ? (a.anio > b.anio) : (a.anio < b.anio);
    }
    return condicion;
}

// --- FUNCIONES DE PERSISTENCIA ---
inline void cargarDesdeArchivo(tListaAlumnos &lista, bool &ok) {
    ifstream archivo;
    lista.contador = 0;
    ok = true;
    
    archivo.open("Alumnos.txt");
    if (!archivo.is_open()) {
        ok = false;
        return;
    }

    tAlumno alumno;
    while ((lista.contador < MAX_ALUMNOS) && (archivo >> alumno.id)) {
        if (alumno.id == -1) break; 
        archivo.ignore(); 
        getline(archivo, alumno.nombre);
        getline(archivo, alumno.carrera);
        archivo >> alumno.anio;
        archivo.ignore(); // Limpiar el fin de línea tras leer el año
        
        lista.elementos[lista.contador] = alumno;
        lista.contador++;
    }
    archivo.close();
}

inline void guardarEnArchivo(const tListaAlumnos &lista) {
    ofstream archivo;
    archivo.open("Alumnos.txt");
    if (archivo.is_open()) {
        for (int i = 0; i < lista.contador; i++) {
            archivo << lista.elementos[i].id << "\n"
                    << lista.elementos[i].nombre << "\n"
                    << lista.elementos[i].carrera << "\n"
                    << lista.elementos[i].anio << "\n";
        }
        archivo.close();
        cout << "Datos guardados correctamente en Alumnos.txt.\n";
    } else {
        cout << "Error al intentar guardar los datos.\n";
    }
}

// --- OPERACIONES COMPLEMENTARIAS ---
inline void mostrarListado(const tListaAlumnos &lista) {
    if (lista.contador == 0) {
        cout << "La lista de alumnos esta vacia.\n";
        return;
    }
    cout << "\n==================== LISTADO DE ALUMNOS ====================\n";
    cout << setw(6) << "ID" << setw(20) << "Nombre" << setw(20) << "Carrera" << setw(8) << "Anio" << endl;
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < lista.contador; i++) {
        cout << setw(6) << lista.elementos[i].id
             << setw(20) << lista.elementos[i].nombre
             << setw(20) << lista.elementos[i].carrera
             << setw(8) << lista.elementos[i].anio << endl;
    }
    cout << "============================================================\n";
}

inline int buscarAlumnoPorId(const tListaAlumnos &lista, int idBuscado) {
    int pos = -1;
    int i = 0;
    while ((i < lista.contador) && (pos == -1)) {
        if (lista.elementos[i].id == idBuscado) {
            pos = i;
        }
        i++;
    }
    return pos;
}

inline void mostrarAlumnoDeterminado(const tListaAlumnos &lista) {
    int idBuscado;
    cout << "Ingrese el ID del alumno a buscar de forma determinada: ";
    cin >> idBuscado;
    cin.ignore(); // Limpiar búfer
    
    int pos = buscarAlumnoPorId(lista, idBuscado);
    if (pos != -1) {
        cout << "\n--- Alumno Encontrado ---\n";
        cout << "ID: " << lista.elementos[pos].id << "\n";
        cout << "Nombre: " << lista.elementos[pos].nombre << "\n";
        cout << "Carrera: " << lista.elementos[pos].carrera << "\n";
        cout << "Anio: " << lista.elementos[pos].anio << "\n";
    } else {
        cout << "Alumno con ID " << idBuscado << " no encontrado.\n";
    }
}

inline void insertarAlumno(tListaAlumnos &lista) {
    if (lista.contador >= MAX_ALUMNOS) {
        cout << "Error: Lista de alumnos llena (maximo 100).\n";
        return;
    }
    
    tAlumno nuevoAlumno;
    cout << "Ingrese ID (Numero entero unico): ";
    cin >> nuevoAlumno.id;
    
    if (buscarAlumnoPorId(lista, nuevoAlumno.id) != -1) {
        cout << "Error: Ya existe un alumno con ese ID.\n";
        cin.ignore();
        return;
    }
    
    cin.ignore(); 
    cout << "Ingrese Nombre Completo: ";
    getline(cin, nuevoAlumno.nombre);
    cout << "Ingrese Carrera: ";
    getline(cin, nuevoAlumno.carrera);
    cout << "Ingrese Anio de cursada: ";
    cin >> nuevoAlumno.anio;
    cin.ignore(); // ¡CRÍTICO! Limpiar el salto de línea residual del año
    
    lista.elementos[lista.contador] = nuevoAlumno;
    lista.contador++;
    cout << "Alumno insertado con exito en memoria.\n";
}

inline void eliminarAlumno(tListaAlumnos &lista) {
    int idEliminar;
    cout << "Ingrese el ID del alumno a eliminar: ";
    cin >> idEliminar;
    cin.ignore(); // Limpiar búfer
    
    int pos = buscarAlumnoPorId(lista, idEliminar);
    if (pos != -1) {
        for (int j = pos; j < lista.contador - 1; j++) {
            lista.elementos[j] = lista.elementos[j + 1];
        }
        lista.contador--;
        cout << "Alumno eliminado con exito de la memoria.\n";
    } else {
        cout << "El alumno con ID " << idEliminar << " no existe.\n";
    }
}

// --- MÉTODO DE LA BURBUJA MEJORADO (Ordenamiento) ---
inline void ordenarBurbuja(tListaAlumnos &lista, int campo, bool ascendente) {
    bool inter = true;
    int i = 0;
    
    while ((i < lista.contador - 1) && inter) {
        inter = false;
        for (int j = lista.contador - 1; j > i; j--) {
            if (compararPorCampo(lista.elementos[j - 1], lista.elementos[j], campo, ascendente)) {
                tAlumno tmp = lista.elementos[j];
                lista.elementos[j] = lista.elementos[j - 1];
                lista.elementos[j - 1] = tmp;
                inter = true;
            }
        }
        if (inter) {
            i++;
        }
    }
    cout << "Lista ordenada exitosamente.\n";
}

#endif