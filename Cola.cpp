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
// FIFO de índices de procesos.
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
// Getters
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
// Agrega un índice de proceso al final de la cola.
//==============================================================

void Cola::agregarProceso(int indiceProceso)
{
    procesos.push(indiceProceso);
}

//==============================================================
// Elimina el índice ubicado al frente.
//==============================================================

void Cola::eliminarProceso()
{
    if (!procesos.empty())
    {
        procesos.pop();
    }
}

//==============================================================
// Retorna el índice ubicado al frente.
//==============================================================

int Cola::obtenerFrente() const
{
    return procesos.front();
}

//==============================================================
// Indica si la cola está vacía.
//==============================================================

bool Cola::estaVacia() const
{
    return procesos.empty();
}

//==============================================================
// Retorna la cantidad de procesos.
//==============================================================

int Cola::cantidadProcesos() const
{
    return procesos.size();
}

//==============================================================
// Retorna una copia de todos los índices, en orden FIFO, sin
// modificar la cola original.
//==============================================================

std::vector<int> Cola::obtenerTodos() const
{
    std::vector<int> resultado;
    std::queue<int> copia = procesos;

    while (!copia.empty())
    {
        resultado.push_back(copia.front());
        copia.pop();
    }

    return resultado;
}

//==============================================================
// Elimina un índice específico de la cola, sin importar la
// posición en la que se encuentre.
//==============================================================

void Cola::eliminarIndice(int indiceProceso)
{
    std::queue<int> nueva;

    while (!procesos.empty())
    {
        int actual = procesos.front();
        procesos.pop();

        if (actual != indiceProceso)
        {
            nueva.push(actual);
        }
    }

    procesos = nueva;
}
