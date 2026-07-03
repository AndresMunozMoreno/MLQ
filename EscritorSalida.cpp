//==============================================================
// Proyecto: Simulador MLQ (Multilevel Queue)
// Autor: Andrés Felipe Muñoz Moreno
// Asignatura: Sistemas Operativos
//
// Archivo: EscritorSalida.cpp
//
// Descripción:
// Implementa los métodos de la clase EscritorSalida.
//==============================================================

#include "EscritorSalida.h"

#include <fstream>
#include <iostream>
#include <iomanip>

//==============================================================
// Escribe el archivo de salida con el detalle de cada proceso
// y las métricas promedio de la simulación.
//==============================================================

void EscritorSalida::escribirArchivo(const std::string& nombreArchivo,
                                      const std::vector<Proceso>& procesos,
                                      double promedioWT,
                                      double promedioCT,
                                      double promedioRT,
                                      double promedioTAT)
{
    std::ofstream archivo(nombreArchivo);

    if (!archivo.is_open())
    {
        std::cout << "Error: No fue posible crear el archivo: "
                  << nombreArchivo << std::endl;

        return;
    }

    // Encabezado del archivo
    archivo << "# archivo: " << nombreArchivo << "\n";
    archivo << "# etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT\n";

    // Una línea por cada proceso, en el orden original de entrada
    for (const Proceso& p : procesos)
    {
        archivo << p.getEtiqueta() << ";"
                << p.getBurstTime() << "; "
                << p.getArrivalTime() << "; "
                << p.getIdCola() << "; "
                << p.getPriority() << "; "
                << p.getWaitingTime() << "; "
                << p.getCompletionTime() << "; "
                << p.getResponseTime() << "; "
                << p.getTurnaroundTime() << "\n";
    }

    // Línea final con los promedios de la simulación
    archivo << std::fixed << std::setprecision(2);
    archivo << "# WT=" << promedioWT << "; "
            << "CT=" << promedioCT << "; "
            << "RT=" << promedioRT << "; "
            << "TAT=" << promedioTAT << ";\n";

    archivo.close();
}
