//==============================================================
// Proyecto: Simulador MLQ (Multilevel Queue)
// Autor: Andrés Felipe Muñoz Moreno
// Asignatura: Sistemas Operativos
//
// Archivo: LectorArchivo.cpp
//
// Descripción:
// Implementa los métodos de la clase LectorArchivo.
// Se encarga de abrir el archivo de entrada, validar su
// contenido, ignorar comentarios y líneas vacías, convertir
// cada registro en un objeto Proceso y almacenarlo en un
// vector para ser utilizado por el simulador MLQ.
//==============================================================

#include "LectorArchivo.h"

#include <fstream>
#include <sstream>
#include <iostream>

//==============================================================
// Lee un archivo de texto y construye un vector de procesos.
//==============================================================
std::vector<Proceso> LectorArchivo::leerArchivo(std::string nombreArchivo)
{
    // Vector donde se almacenarán todos los procesos
    std::vector<Proceso> procesos;

    // Apertura del archivo
    std::ifstream archivo(nombreArchivo);

    // Verificar que el archivo se abrió correctamente
    if (!archivo.is_open())
    {
        std::cout << "Error: No fue posible abrir el archivo "
                  << nombreArchivo << std::endl;

        return procesos;
    }

    std::string linea;

    //==========================================================
    // Leer el archivo línea por línea
    //==========================================================
    while (std::getline(archivo, linea))
    {
        // Ignorar líneas vacías
        if (linea.empty())
        {
            continue;
        }

        // Ignorar comentarios
        if (linea[0] == '#')
        {
            continue;
        }

        // Variables para almacenar los datos de cada proceso
        std::string etiqueta;
        int burstTime;
        int arrivalTime;
        int idCola;
        int priority;

        // Crear un flujo para dividir la línea
        std::stringstream ss(linea);

        std::string dato;

        //=========================
        // Etiqueta
        //=========================
        std::getline(ss, etiqueta, ';');

        //=========================
        // Burst Time
        //=========================
        std::getline(ss, dato, ';');
        burstTime = std::stoi(dato);

        //=========================
        // Arrival Time
        //=========================
        std::getline(ss, dato, ';');
        arrivalTime = std::stoi(dato);

        //=========================
        // ID de la Cola
        //=========================
        std::getline(ss, dato, ';');
        idCola = std::stoi(dato);

        //=========================
        // Prioridad
        //=========================
        std::getline(ss, dato);
        priority = std::stoi(dato);

        // Crear el proceso y almacenarlo en el vector
        procesos.push_back(
            Proceso(
                etiqueta,
                burstTime,
                arrivalTime,
                idCola,
                priority
            )
        );
    }

    // Cerrar el archivo
    archivo.close();

    // Retornar todos los procesos leídos
    return procesos;
}