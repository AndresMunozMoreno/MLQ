//==============================================================
// Proyecto: Simulador MLQ (Multilevel Queue)
// Autor: Andrés Felipe Muñoz Moreno
// Asignatura: Sistemas Operativos
//
// Archivo: LectorArchivo.h
//
// Descripción:
// Define la clase LectorArchivo, encargada de leer los archivos
// de entrada (.txt) que contienen la información de los procesos.
// La clase procesa cada línea válida del archivo y construye un
// vector de objetos Proceso que será utilizado por el
// PlanificadorMLQ para realizar la simulación.
//
// Formato esperado:
//
// etiqueta; burstTime; arrivalTime; idCola; priority
//
// Ejemplo:
// P1;20;0;1;5
//==============================================================
#ifndef LECTORARCHIVO_H
#define LECTORARCHIVO_H

//==============================================================
// Librerías necesarias
//==============================================================

#include <vector>
#include <string>

#include "Proceso.h"

class LectorArchivo
{
public:

    //==========================================================
    // Lee el archivo indicado y retorna un vector con todos
    // los procesos encontrados.
    //==========================================================
    std::vector<Proceso> leerArchivo(std::string nombreArchivo);

};

#endif