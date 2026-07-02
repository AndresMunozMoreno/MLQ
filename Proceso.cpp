//==============================================================
// Proyecto: Simulador MLQ (Multilevel Queue)
// Autor: Andrés Felipe Muñoz Moreno
// Asignatura: Sistemas Operativos
//
// Archivo: Proceso.cpp
// Descripción:
// Implementa los métodos de la clase Proceso.
//==============================================================
#include "Proceso.h"

Proceso::Proceso(std::string etiqueta,
                 int burstTime,
                 int arrivalTime,
                 int idCola,
                 int priority)
    : etiqueta(etiqueta),
      burstTime(burstTime),
      arrivalTime(arrivalTime),
      idCola(idCola),
      priority(priority),
      remainingTime(burstTime),
      completionTime(0),
      waitingTime(0),
      turnaroundTime(0),
      responseTime(0),
      started(false)
{
}

//==============================================================
// Implementación de los métodos de consulta (Getters)
//==============================================================

std::string Proceso::getEtiqueta() const
{
    return etiqueta;
}

int Proceso::getBurstTime() const
{
    return burstTime;
}

int Proceso::getArrivalTime() const
{
    return arrivalTime;
}

int Proceso::getIdCola() const
{
    return idCola;
}

int Proceso::getPriority() const
{
    return priority;
}

int Proceso::getRemainingTime() const
{
    return remainingTime;
}

int Proceso::getCompletionTime() const
{
    return completionTime;
}

int Proceso::getWaitingTime() const
{
    return waitingTime;
}

int Proceso::getTurnaroundTime() const
{
    return turnaroundTime;
}

int Proceso::getResponseTime() const
{
    return responseTime;
}

bool Proceso::getStarted() const
{
    return started;
}

//==========================
// Setters
//==========================

void Proceso::setRemainingTime(int remainingTime)
{
    this->remainingTime = remainingTime;
}

void Proceso::setCompletionTime(int completionTime)
{
    this->completionTime = completionTime;
}

void Proceso::setWaitingTime(int waitingTime)
{
    this->waitingTime = waitingTime;
}

void Proceso::setTurnaroundTime(int turnaroundTime)
{
    this->turnaroundTime = turnaroundTime;
}

void Proceso::setResponseTime(int responseTime)
{
    this->responseTime = responseTime;
}

void Proceso::setStarted(bool started)
{
    this->started = started;
}

//==========================
// Métodos de comportamiento
//==========================

void Proceso::ejecutarUnCiclo()
{
    if (remainingTime > 0)
    {
        remainingTime--;
    }
}

bool Proceso::termino() const
{
    return remainingTime == 0;
}
