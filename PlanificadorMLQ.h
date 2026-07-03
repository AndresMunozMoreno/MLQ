//==============================================================
// Proyecto: Simulador MLQ (Multilevel Queue)
// Autor: Andrés Felipe Muñoz Moreno
// Asignatura: Sistemas Operativos
//
// Archivo: PlanificadorMLQ.h
//
// Descripción:
// Define la clase PlanificadorMLQ, encargada de ejecutar la
// simulación completa del algoritmo Multilevel Queue (MLQ).
//
// Esta clase administra el reloj del sistema, distribuye los
// procesos entre las diferentes colas de planificación,
// ejecuta los algoritmos correspondientes y calcula las
// métricas finales.
//==============================================================

#ifndef PLANIFICADORMLQ_H
#define PLANIFICADORMLQ_H

//==============================================================
// Librerías necesarias
//==============================================================

#include <vector>

#include "Proceso.h"
#include "Cola.h"

//==============================================================
// Clase PlanificadorMLQ
//==============================================================

class PlanificadorMLQ
{
private:

    //==========================================================
    // Procesos de la simulación
    //==========================================================

    std::vector<Proceso> procesos;

    //==========================================================
    // Colas de planificación
    //==========================================================

    Cola cola1;
    Cola cola2;
    Cola cola3;

    //==========================================================
    // Variables de control de la simulación
    //==========================================================

    // Tiempo global del sistema
    int tiempoActual;

    // Cantidad de procesos que finalizaron
    int procesosTerminados;

    // Esquema seleccionado (1, 2 o 3)
    int esquema;

    // Quantum consumido por el proceso que se está ejecutando
    int quantumActual;

    //==========================================================
    // Métodos privados
    //==========================================================

    // Configura las colas según el esquema seleccionado
    void configurarColas();

    // Agrega a las colas los procesos cuyo tiempo de llegada ya
    // se cumplió
    void agregarProcesosLlegados();

    // Selecciona la cola de mayor prioridad disponible
    void ejecutarColaMayorPrioridad();

    // Ejecutan la política correspondiente a cada cola
    void ejecutarCola1();

    void ejecutarCola2();

    void ejecutarCola3();

public:

    //==========================================================
    // Constructor
    //==========================================================

    PlanificadorMLQ(int esquema);

    //==========================================================
    // Métodos públicos
    //==========================================================

    // Recibe los procesos leídos desde el archivo
    void cargarProcesos(const std::vector<Proceso>& procesos);

    // Ejecuta toda la simulación
    void simular();

    // Calcula WT, CT, RT y TAT
    void calcularMetricas();

    // Retorna el vector de procesos para generar el archivo
    std::vector<Proceso> getProcesos() const;
};

#endif