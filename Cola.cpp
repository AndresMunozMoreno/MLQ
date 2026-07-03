//==============================================================
// Proyecto: Simulador MLQ (Multilevel Queue)
// Autor: Andrés Felipe Muñoz Moreno
// Asignatura: Sistemas Operativos
//
// Archivo: Cola.cpp
//
// Descripción:
// Implementa los métodos de la clase Cola.
// Esta clase encapsula las operaciones básicas sobre una cola
// de procesos, permitiendo agregar, eliminar y consultar
// procesos sin exponer directamente la estructura std::queue.
//==============================================================

#include "Cola.h"

//==============================================================
// Constructor
//==============================================================
Cola::Cola(int idCola, int quantum)
    : idCola(idCola),
      quantum(quantum)
{
}

//==============================================================
// Implementación de los métodos de consulta (Getters)
//==============================================================

int Cola::getIdCola() const
{
    return idCola;
}

int Cola::getQuantum() const
{
    return quantum;
}

//==============================================================
// Agrega un proceso al final de la cola.
//==============================================================
void Cola::agregarProceso(const Proceso& proceso)
{
    procesos.push(proceso);
}

//==============================================================
// Elimina el proceso ubicado al frente de la cola.
//==============================================================
void Cola::eliminarProceso()
{
    if (!procesos.empty())
    {
        procesos.pop();
    }
}

//==============================================================
// Retorna el proceso ubicado al frente de la cola.
//==============================================================
Proceso Cola::obtenerFrente() const
{
    return procesos.front();
}

//==============================================================
// Indica si la cola contiene procesos.
//==============================================================
bool Cola::estaVacia() const
{
    return procesos.empty();
}

//==============================================================
// Retorna la cantidad de procesos almacenados.
//==============================================================
int Cola::cantidadProcesos() const
{
    return procesos.size();
}
