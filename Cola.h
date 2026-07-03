//==============================================================
// Proyecto: Simulador MLQ (Multilevel Queue)
// Autor: Andrés Felipe Muñoz Moreno
// Asignatura: Sistemas Operativos
//
// Archivo: Cola.h
//
// Descripción:
// Define la clase Cola, encargada de administrar los índices
// de los procesos pertenecientes a una cola de planificación.
//
// Cada objeto Cola almacena únicamente los índices de los
// procesos dentro del vector principal del PlanificadorMLQ.
// De esta forma existe una única instancia de cada proceso
// durante toda la simulación.
//==============================================================

#ifndef COLA_H
#define COLA_H

//==============================================================
// Librerías necesarias
//==============================================================

#include <queue>

//==============================================================
// Clase Cola
//==============================================================

class Cola
{
private:

    // Cola FIFO que almacena los índices de los procesos
    std::queue<int> procesos;

    // Identificador de la cola
    int idCola;

    // Quantum de la cola
    int quantum;

public:

    //==========================================================
    // Constructor
    //==========================================================
    Cola(int idCola, int quantum);

    //==========================================================
    // Getters
    //==========================================================
    int getIdCola() const;

    int getQuantum() const;

    //==========================================================
    // Operaciones sobre la cola
    //==========================================================

    void agregarProceso(int indiceProceso);

    void eliminarProceso();

    int obtenerFrente() const;

    bool estaVacia() const;

    int cantidadProcesos() const;
};

#endif
