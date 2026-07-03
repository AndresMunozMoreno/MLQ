//==============================================================
// Proyecto: Simulador MLQ (Multilevel Queue)
// Autor: Andrés Felipe Muñoz Moreno
// Asignatura: Sistemas Operativos
//
// Archivo: EscritorSalida.h
//
// Descripción:
// Define la clase EscritorSalida, encargada de generar el
// archivo de texto con los resultados de la simulación, en el
// formato exigido por la guía del parcial:
//
// # archivo: mlq001.txt
// # etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT
// A;6; 0; 1; 5; 3; 9; 0; 9
// ...
// # WT=23.5; CT=35.5; RT=19.5; TAT=35.5;
//==============================================================

#ifndef ESCRITORSALIDA_H
#define ESCRITORSALIDA_H

//==============================================================
// Librerías necesarias
//==============================================================

#include <string>
#include <vector>

#include "Proceso.h"

class EscritorSalida
{
public:

    //==========================================================
    // Escribe en 'nombreArchivo' los procesos ya simulados junto
    // con las métricas promedio de la simulación.
    //==========================================================
    void escribirArchivo(const std::string& nombreArchivo,
                          const std::vector<Proceso>& procesos,
                          double promedioWT,
                          double promedioCT,
                          double promedioRT,
                          double promedioTAT);
};

#endif
