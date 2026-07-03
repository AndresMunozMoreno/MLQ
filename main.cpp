//==============================================================
// Proyecto: Simulador MLQ (Multilevel Queue)
// Autor: Andrés Felipe Muñoz Moreno
// Asignatura: Sistemas Operativos
//
// Archivo: main.cpp
//
// Descripción:
// Punto de entrada del programa. Recorre todos los archivos de
// entrada ubicados en la carpeta "entradas", ejecuta la
// simulación del algoritmo MLQ para los 3 esquemas de
// planificación definidos en la guía:
//
//   Esquema 1 -> RR(1), RR(3), SJF
//   Esquema 2 -> RR(3), RR(5), Priority
//   Esquema 3 -> RR(2), RR(3), STCF
//
// y guarda el resultado de cada combinación (archivo, esquema)
// en la carpeta "salidas".
//==============================================================

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "Proceso.h"
#include "LectorArchivo.h"
#include "PlanificadorMLQ.h"
#include "EscritorSalida.h"

namespace fs = std::filesystem;

int main()
{
    LectorArchivo lector;
    EscritorSalida escritor;

    const std::string carpetaEntradas = "entradas";
    const std::string carpetaSalidas = "salidas";

    const std::vector<int> esquemas = {1, 2, 3};

    if (!fs::exists(carpetaEntradas))
    {
        std::cout << "Error: no existe la carpeta '" << carpetaEntradas
                  << "'." << std::endl;

        return 1;
    }

    if (!fs::exists(carpetaSalidas))
    {
        fs::create_directory(carpetaSalidas);
    }

    // Se recorren todos los archivos .txt de la carpeta de entradas
    for (const auto& entrada : fs::directory_iterator(carpetaEntradas))
    {
        if (entrada.path().extension() != ".txt")
        {
            continue;
        }

        std::string nombreArchivo = entrada.path().filename().string();
        std::string rutaCompleta = entrada.path().string();
        std::string nombreBase = nombreArchivo.substr(0, nombreArchivo.find(".txt"));

        // Se simula el mismo archivo de entrada con cada uno de
        // los 3 esquemas de planificación
        for (int esquema : esquemas)
        {
            // Se leen los procesos "limpios" en cada simulación,
            // para que ninguna corrida anterior afecte a la
            // siguiente
            std::vector<Proceso> procesos = lector.leerArchivo(rutaCompleta);

            if (procesos.empty())
            {
                continue;
            }

            PlanificadorMLQ planificador(esquema);
            planificador.cargarProcesos(procesos);
            planificador.simular();
            planificador.calcularMetricas();

            std::string nombreSalida = carpetaSalidas + "/" + nombreBase +
                                        "_esquema" + std::to_string(esquema) +
                                        ".txt";

            escritor.escribirArchivo(
                nombreSalida,
                planificador.getProcesos(),
                planificador.getPromedioWT(),
                planificador.getPromedioCT(),
                planificador.getPromedioRT(),
                planificador.getPromedioTAT()
            );

            std::cout << "Generado: " << nombreSalida << std::endl;
        }
    }

    std::cout << "\nSimulacion finalizada." << std::endl;

    return 0;
}
