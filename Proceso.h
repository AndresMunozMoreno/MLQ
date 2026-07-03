//==============================================================
// Proyecto: Simulador MLQ (Multilevel Queue)
// Autor: Andrés Felipe Muñoz Moreno
// Asignatura: Sistemas Operativos
//
// Archivo: Proceso.h
//
// Descripción:
// Define la clase Proceso, encargada de representar un proceso
// dentro de la simulación del algoritmo MLQ.
//==============================================================

#ifndef PROCESO_H
#define PROCESO_H

//==============================================================
// Librerías necesarias
//==============================================================

#include <string>

//==============================================================
// Clase Proceso
//==============================================================

class Proceso
{
private:

    //==========================================================
    // Información proveniente del archivo de entrada
    //==========================================================

    std::string etiqueta;
    int burstTime;
    int arrivalTime;
    int idCola;
    int priority;

    //==========================================================
    // Información utilizada durante la simulación
    //==========================================================

    int remainingTime;

    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int responseTime;

    // Indica si el proceso ya fue agregado a una cola
    bool agregado;

public:

    //==========================================================
    // Constructor
    //==========================================================

    Proceso(std::string etiqueta,
            int burstTime,
            int arrivalTime,
            int idCola,
            int priority);

    //==========================================================
    // Métodos de consulta (Getters)
    //==========================================================

    std::string getEtiqueta() const;

    int getBurstTime() const;

    int getArrivalTime() const;

    int getIdCola() const;

    int getPriority() const;

    int getRemainingTime() const;

    int getCompletionTime() const;

    int getWaitingTime() const;

    int getTurnaroundTime() const;

    int getResponseTime() const;

    bool getAgregado() const;

    //==========================================================
    // Métodos modificadores (Setters)
    //==========================================================

    void setRemainingTime(int remainingTime);

    void setCompletionTime(int completionTime);

    void setWaitingTime(int waitingTime);

    void setTurnaroundTime(int turnaroundTime);

    void setResponseTime(int responseTime);

    void setAgregado(bool agregado);

    //==========================================================
    // Métodos de comportamiento
    //==========================================================

    void ejecutarUnCiclo();

    bool termino() const;

    bool haLlegado(int tiempoActual) const;
};

#endif