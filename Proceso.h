#ifndef PROCESO_H
#define PROCESO_H

#include <string>

class Proceso
{
private:

    // Información del archivo de entrada
    std::string etiqueta;
    int burstTime;
    int arrivalTime;
    int idCola;
    int priority;

    // Información utilizada durante la simulación
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int responseTime;
    bool started;

public:

    // Constructor
    Proceso(std::string etiqueta,
             int burstTime,
             int arrivalTime,
             int idCola,
             int priority);

    // Getters
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
    bool getStarted() const;

    // Setters
    void setRemainingTime(int remainingTime);
    void setCompletionTime(int completionTime);
    void setWaitingTime(int waitingTime);
    void setTurnaroundTime(int turnaroundTime);
    void setResponseTime(int responseTime);
    void setStarted(bool started);

    // Métodos de comportamiento
    void ejecutarUnCiclo();
    bool termino() const;
};

#endif
