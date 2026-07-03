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
#include <algorithm>
#include <cctype>

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
        std::cout << "Error: No fue posible abrir el archivo: "
                  << nombreArchivo << std::endl;

        return procesos;
    }

    std::string linea;

    //==========================================================
    // Leer el archivo línea por línea
    //==========================================================
    while (std::getline(archivo, linea))
    {
        // Eliminar espacios al inicio de la línea
        linea.erase(
            linea.begin(),
            std::find_if(
                linea.begin(),
                linea.end(),
                [](unsigned char c)
                {
                    return !std::isspace(c);
                }
            )
        );

        // Eliminar espacios al final de la línea
        linea.erase(
            std::find_if(
                linea.rbegin(),
                linea.rend(),
                [](unsigned char c)
                {
                    return !std::isspace(c);
                }
            ).base(),
            linea.end()
        );

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

        // Variables para almacenar la información del proceso
        std::string etiqueta;
        int burstTime;
        int arrivalTime;
        int idCola;
        int priority;

        // Flujo para dividir la línea usando ';'
        std::stringstream ss(linea);

        std::string dato;

        // Obtener la etiqueta
        std::getline(ss, etiqueta, ';');

        // Obtener el Burst Time
        std::getline(ss, dato, ';');
        burstTime = std::stoi(dato);

        // Obtener el Arrival Time
        std::getline(ss, dato, ';');
        arrivalTime = std::stoi(dato);

        // Obtener el ID de la Cola
        std::getline(ss, dato, ';');
        idCola = std::stoi(dato);

        // Obtener la prioridad
        std::getline(ss, dato);
        priority = std::stoi(dato);

        // Crear el objeto Proceso y agregarlo al vector
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

    // Retornar el vector con todos los procesos leídos
    return procesos;
}
