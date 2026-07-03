//==============================================================
// Proyecto: Simulador MLQ (Multilevel Queue)
// Autor: Andrés Felipe Muñoz Moreno
// Asignatura: Sistemas Operativos
//
// Archivo: PlanificadorMLQ.cpp
//
// Descripción:
// Implementa los métodos de la clase PlanificadorMLQ.
//==============================================================

#include "PlanificadorMLQ.h"

//==============================================================
// Constructor
//==============================================================

PlanificadorMLQ::PlanificadorMLQ(int esquema)
    : cola1(1, 0),
      cola2(2, 0),
      cola3(3, 0),
      tiempoActual(0),
      procesosTerminados(0),
      esquema(esquema),
      quantumActual(0)
{
    configurarColas();
}

//==============================================================
// Configura las colas según el esquema seleccionado.
//==============================================================

void PlanificadorMLQ::configurarColas()
{
    switch (esquema)
    {
        case 1:

            // RR(1), RR(3), SJF
            cola1 = Cola(1, 1);
            cola2 = Cola(2, 3);
            cola3 = Cola(3, 0);

            break;

        case 2:

            // RR(3), RR(5), Priority
            cola1 = Cola(1, 3);
            cola2 = Cola(2, 5);
            cola3 = Cola(3, 0);

            break;

        case 3:

            // RR(2), RR(3), STCF
            cola1 = Cola(1, 2);
            cola2 = Cola(2, 3);
            cola3 = Cola(3, 0);

            break;

        default:

            // Si el esquema no es válido se utilizará el esquema 1
            cola1 = Cola(1, 1);
            cola2 = Cola(2, 3);
            cola3 = Cola(3, 0);

            break;
    }
}

//==============================================================
// Recibe los procesos provenientes del lector.
//==============================================================

void PlanificadorMLQ::cargarProcesos(const std::vector<Proceso>& procesos)
{
    this->procesos = procesos;
}

//==============================================================
// Retorna todos los procesos.
//==============================================================

std::vector<Proceso> PlanificadorMLQ::getProcesos() const
{
    return procesos;
}

//==============================================================
// Ejecuta la simulación completa.
//==============================================================

void PlanificadorMLQ::simular()
{

}

//==============================================================
// Calcula las métricas finales.
//==============================================================

void PlanificadorMLQ::calcularMetricas()
{

}

//==============================================================
// Agrega los procesos que ya llegaron.
//==============================================================

void PlanificadorMLQ::agregarProcesosLlegados()
{

}

//==============================================================
// Ejecuta la cola de mayor prioridad disponible.
//==============================================================

void PlanificadorMLQ::ejecutarColaMayorPrioridad()
{

}

//==============================================================
// Ejecuta la Cola 1.
//==============================================================

void PlanificadorMLQ::ejecutarCola1()
{

}

//==============================================================
// Ejecuta la Cola 2.
//==============================================================

void PlanificadorMLQ::ejecutarCola2()
{

}

//==============================================================
// Ejecuta la Cola 3.
//==============================================================

void PlanificadorMLQ::ejecutarCola3()
{

}