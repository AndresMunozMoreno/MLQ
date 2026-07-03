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
    // Política de planificación de la cola 3. Las colas 1 y 2
    // siempre usan Round Robin (con distinto quantum según el
    // esquema); la cola 3 varía según el esquema seleccionado.
    //==========================================================

    enum PoliticaCola3
    {
        POLITICA_SJF,
        POLITICA_PRIORITY,
        POLITICA_STCF
    };

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

    // Política vigente para la cola 3, derivada del esquema
    PoliticaCola3 politicaCola3;

    // Índice del proceso que actualmente tiene el CPU (-1 si el
    // CPU está inactivo)
    int procesoEnEjecucion;

    // Cola (1, 2 o 3) a la que pertenece el proceso en ejecución
    int colaEnEjecucion;

    // Quantum consumido por el proceso en ejecución dentro de su
    // ráfaga actual en su cola
    int quantumConsumido;

    // Indica, por índice de proceso, si aún no ha tenido su
    // primer ciclo de CPU (para calcular el Response Time)
    std::vector<bool> primeraEjecucion;

    // Métricas promedio de toda la simulación
    double promedioWT;
    double promedioCT;
    double promedioRT;
    double promedioTAT;

    //==========================================================
    // Métodos privados
    //==========================================================

    // Configura las colas y la política de la cola 3 según el
    // esquema seleccionado
    void configurarColas();

    // Agrega a las colas los procesos cuyo tiempo de llegada ya
    // se cumplió
    void agregarProcesosLlegados();

    // Retorna la referencia a la cola 1, 2 o 3 según el número
    // recibido
    Cola& obtenerCola(int numCola);

    // Retorna el número (1, 2 o 3) de la cola de mayor prioridad
    // que tenga al menos un proceso listo; retorna 0 si ninguna
    // tiene procesos
    int colaMasAltaDisponible() const;

    // Retira y retorna el índice del siguiente proceso a
    // ejecutar de la cola indicada, respetando su política
    // (FIFO para las colas 1 y 2; SJF/Priority/STCF para la 3)
    int seleccionarProceso(int numCola);

    // Vuelve a agregar un proceso a la cola indicada (por
    // expiración de quantum o por expropiación)
    void reencolarProceso(int indiceProceso, int numCola);

    // Indica si, dentro de la cola 3 con política STCF, hay un
    // proceso listo con menor tiempo restante que el que se
    // está ejecutando actualmente
    bool debePreemptarPorSTCF() const;

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

    //==========================================================
    // Getters de las métricas promedio (válidos tras llamar a
    // calcularMetricas())
    //==========================================================

    double getPromedioWT() const;

    double getPromedioCT() const;

    double getPromedioRT() const;

    double getPromedioTAT() const;
};

#endif