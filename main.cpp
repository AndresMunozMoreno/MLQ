#include <iostream>
#include "Proceso.h"

int main()
{
    Proceso p("P1", 20, 0, 1, 5);

    std::cout << "===== DATOS DEL PROCESO =====\n";

    std::cout << "Etiqueta: " << p.getEtiqueta() << std::endl;
    std::cout << "Burst Time: " << p.getBurstTime() << std::endl;
    std::cout << "Arrival Time: " << p.getArrivalTime() << std::endl;
    std::cout << "ID Cola: " << p.getIdCola() << std::endl;
    std::cout << "Priority: " << p.getPriority() << std::endl;
    std::cout << "Remaining Time: " << p.getRemainingTime() << std::endl;
    std::cout << "Completion Time: " << p.getCompletionTime() << std::endl;
    std::cout << "Waiting Time: " << p.getWaitingTime() << std::endl;
    std::cout << "Turnaround Time: " << p.getTurnaroundTime() << std::endl;
    std::cout << "Response Time: " << p.getResponseTime() << std::endl;
    std::cout << "Started: " << p.getStarted() << std::endl;

    return 0;
}
