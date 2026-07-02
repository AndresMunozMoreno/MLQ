#include <iostream>
#include "Proceso.h"

int main()
{
    Proceso p("P1", 20, 0, 1, 5);

    std::cout << "Remaining Time inicial: "
              << p.getRemainingTime() << std::endl;

    p.ejecutarUnCiclo();

    std::cout << "Despues de un ciclo: "
              << p.getRemainingTime() << std::endl;

    p.ejecutarUnCiclo();

    std::cout << "Despues de dos ciclos: "
              << p.getRemainingTime() << std::endl;

    return 0;
}