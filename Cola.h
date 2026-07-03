//==============================================================
// Proyecto: Simulador MLQ (Multilevel Queue)
// Autor: Andrés Felipe Muñoz Moreno
// Asignatura: Sistemas Operativos
//
// Archivo: Cola.h
//
// Descripción:
// Define la clase Cola, encargada de administrar los procesos
// pertenecientes a una cola de planificación.
//
// Cada objeto Cola almacena los procesos asignados a una cola
// específica del algoritmo MLQ y ofrece operaciones básicas
// para agregar, eliminar y consultar procesos.
//
// La política de planificación (RR, SJF, STCF o Priority)
// NO se implementa en esta clase. Esa responsabilidad le
// corresponde al PlanificadorMLQ.
//==============================================================

#ifndef COLA_H
#define COLA_H

//==============================================================
// Librerías necesarias
//==============================================================

#include <queue>

#include "Proceso.h"

//==============================================================
// Clase Cola
//==============================================================

class Cola
{
private:

    // Cola FIFO donde se almacenan los procesos
    std::queue<Proceso> procesos;

    // Identificador de la cola (1, 2 o 3)
    int idCola;

    // Quantum asignado a la cola.
    // Si la cola no utiliza Round Robin este valor será 0.
    int quantum;

public:

    //==========================================================
    // Constructor
    //==========================================================
    Cola(int idCola, int quantum);

    //==========================================================
    // Métodos de consulta (Getters)
    //==========================================================
    int getIdCola() const;

    int getQuantum() const;

    //==========================================================
    // Operaciones sobre la cola
    //==========================================================

    // Agrega un proceso al final de la cola
    void agregarProceso(const Proceso& proceso);

    // Elimina el proceso que se encuentra al frente
    void eliminarProceso();

    // Retorna el proceso ubicado al frente de la cola
    Proceso obtenerFrente() const;

    // Indica si la cola está vacía
    bool estaVacia() const;

    // Retorna la cantidad de procesos almacenados
    int cantidadProcesos() const;
};

#endif
