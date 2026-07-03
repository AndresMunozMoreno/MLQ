#include <iostream>
#include <vector>

#include "Proceso.h"
#include "LectorArchivo.h"

int main()
{
    LectorArchivo lector;

    std::vector<Proceso> procesos =
        lector.leerArchivo("entradas/mlq001.txt");

    for (const Proceso& proceso : procesos)
    {
        std::cout << proceso.getEtiqueta() << " | "
                  << proceso.getBurstTime() << " | "
                  << proceso.getArrivalTime() << " | "
                  << proceso.getIdCola() << " | "
                  << proceso.getPriority() << std::endl;
    }

    return 0;
}