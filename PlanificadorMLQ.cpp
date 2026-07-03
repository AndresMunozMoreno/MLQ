//==============================================================
// Proyecto: Simulador MLQ (Multilevel Queue)
// Autor: Andrés Felipe Muñoz Moreno
// Asignatura: Sistemas Operativos
//
// Archivo: PlanificadorMLQ.cpp
//
// Descripción:
// Implementa los métodos de la clase PlanificadorMLQ.
//
// La simulación avanza el reloj del sistema (tiempoActual) un
// ciclo (1 unidad de tiempo) a la vez. En cada ciclo:
//   1. Se incorporan a sus colas los procesos que ya llegaron.
//   2. Se verifica si el proceso en ejecución debe ser
//      expropiado, ya sea porque una cola de mayor prioridad
//      tiene procesos listos, o porque (en el caso de STCF)
//      llegó un proceso con menor tiempo restante dentro de la
//      misma cola 3.
//   3. Si el CPU quedó libre, se selecciona el siguiente
//      proceso a ejecutar según la política de la cola elegida.
//   4. Se ejecuta un ciclo de CPU sobre el proceso seleccionado
//      y se revisa si terminó o si debe volver a la cola
//      (por expiración de su quantum, en el caso de RR).
//
// Las colas 1 y 2 siempre se planifican con Round Robin (con el
// quantum que indique el esquema). La cola 3 cambia de política
// según el esquema (SJF, Priority o STCF), tal como lo define
// la guía del parcial.
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
      politicaCola3(POLITICA_SJF),
      procesoEnEjecucion(-1),
      colaEnEjecucion(0),
      quantumConsumido(0),
      promedioWT(0.0),
      promedioCT(0.0),
      promedioRT(0.0),
      promedioTAT(0.0)
{
    configurarColas();
}

//==============================================================
// Configura las colas y la política de la cola 3 según el
// esquema seleccionado.
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
            politicaCola3 = POLITICA_SJF;

            break;

        case 2:

            // RR(3), RR(5), Priority
            cola1 = Cola(1, 3);
            cola2 = Cola(2, 5);
            cola3 = Cola(3, 0);
            politicaCola3 = POLITICA_PRIORITY;

            break;

        case 3:

            // RR(2), RR(3), STCF
            cola1 = Cola(1, 2);
            cola2 = Cola(2, 3);
            cola3 = Cola(3, 0);
            politicaCola3 = POLITICA_STCF;

            break;

        default:

            // Si el esquema no es válido se utilizará el esquema 1
            cola1 = Cola(1, 1);
            cola2 = Cola(2, 3);
            cola3 = Cola(3, 0);
            politicaCola3 = POLITICA_SJF;

            break;
    }
}

//==============================================================
// Recibe los procesos provenientes del lector y reinicia el
// estado interno de la simulación.
//==============================================================

void PlanificadorMLQ::cargarProcesos(const std::vector<Proceso>& procesos)
{
    this->procesos = procesos;

    tiempoActual = 0;
    procesosTerminados = 0;
    procesoEnEjecucion = -1;
    colaEnEjecucion = 0;
    quantumConsumido = 0;

    primeraEjecucion.assign(this->procesos.size(), true);
}

//==============================================================
// Retorna todos los procesos.
//==============================================================

std::vector<Proceso> PlanificadorMLQ::getProcesos() const
{
    return procesos;
}

//==============================================================
// Retorna la referencia a la cola solicitada.
//==============================================================

Cola& PlanificadorMLQ::obtenerCola(int numCola)
{
    switch (numCola)
    {
        case 1:
            return cola1;
        case 2:
            return cola2;
        default:
            return cola3;
    }
}

//==============================================================
// Agrega a sus respectivas colas los procesos cuyo tiempo de
// llegada ya se cumplió.
//==============================================================

void PlanificadorMLQ::agregarProcesosLlegados()
{
    for (int i = 0; i < static_cast<int>(procesos.size()); i++)
    {
        if (!procesos[i].getAgregado() &&
            procesos[i].haLlegado(tiempoActual))
        {
            obtenerCola(procesos[i].getIdCola()).agregarProceso(i);
            procesos[i].setAgregado(true);
        }
    }
}

//==============================================================
// Retorna el número de la cola de mayor prioridad (1 es la más
// alta) que tenga al menos un proceso listo. Retorna 0 si
// ninguna cola tiene procesos.
//==============================================================

int PlanificadorMLQ::colaMasAltaDisponible() const
{
    if (!cola1.estaVacia())
    {
        return 1;
    }

    if (!cola2.estaVacia())
    {
        return 2;
    }

    if (!cola3.estaVacia())
    {
        return 3;
    }

    return 0;
}

//==============================================================
// Retira de la cola indicada y retorna el índice del siguiente
// proceso a ejecutar, respetando la política de dicha cola.
//==============================================================

int PlanificadorMLQ::seleccionarProceso(int numCola)
{
    Cola& cola = obtenerCola(numCola);

    // Colas 1 y 2: Round Robin -> se respeta estrictamente el
    // orden FIFO de llegada / reencolamiento.
    if (numCola == 1 || numCola == 2)
    {
        int indice = cola.obtenerFrente();
        cola.eliminarProceso();

        return indice;
    }

    // Cola 3: la política depende del esquema. Se recorren todos
    // los procesos listos y se elige el mejor candidato según
    // el criterio correspondiente. En caso de empate se respeta
    // el orden FIFO (el primero encontrado se conserva).
    std::vector<int> candidatos = cola.obtenerTodos();
    int mejorIndice = candidatos[0];

    for (int idx : candidatos)
    {
        const Proceso& actual = procesos[idx];
        const Proceso& mejor = procesos[mejorIndice];

        switch (politicaCola3)
        {
            case POLITICA_SJF:

                // Menor ráfaga (burst time) total
                if (actual.getBurstTime() < mejor.getBurstTime())
                {
                    mejorIndice = idx;
                }

                break;

            case POLITICA_PRIORITY:

                // Mayor prioridad (5 es la más alta, 1 la más baja)
                if (actual.getPriority() > mejor.getPriority())
                {
                    mejorIndice = idx;
                }

                break;

            case POLITICA_STCF:

                // Menor tiempo restante de ejecución
                if (actual.getRemainingTime() < mejor.getRemainingTime())
                {
                    mejorIndice = idx;
                }

                break;
        }
    }

    cola.eliminarIndice(mejorIndice);

    return mejorIndice;
}

//==============================================================
// Vuelve a agregar un proceso a la cola indicada (por
// expiración de quantum o por expropiación desde una cola de
// mayor prioridad).
//==============================================================

void PlanificadorMLQ::reencolarProceso(int indiceProceso, int numCola)
{
    obtenerCola(numCola).agregarProceso(indiceProceso);
}

//==============================================================
// Indica si, dentro de la cola 3 con política STCF, existe un
// proceso listo con menor tiempo restante que el proceso que
// se está ejecutando actualmente.
//==============================================================

bool PlanificadorMLQ::debePreemptarPorSTCF() const
{
    std::vector<int> candidatos = cola3.obtenerTodos();

    for (int idx : candidatos)
    {
        if (procesos[idx].getRemainingTime() <
            procesos[procesoEnEjecucion].getRemainingTime())
        {
            return true;
        }
    }

    return false;
}

//==============================================================
// Ejecuta la simulación completa, ciclo a ciclo, hasta que
// todos los procesos hayan finalizado.
//==============================================================

void PlanificadorMLQ::simular()
{
    while (procesosTerminados < static_cast<int>(procesos.size()))
    {
        // 1. Incorporar los procesos que llegan en este instante
        agregarProcesosLlegados();

        // 2. Verificar si el proceso en ejecución debe ser
        //    expropiado
        if (procesoEnEjecucion != -1)
        {
            int colaDisponible = colaMasAltaDisponible();

            if (colaDisponible != 0 && colaDisponible < colaEnEjecucion)
            {
                // Una cola de mayor prioridad tiene procesos
                // listos: se libera el CPU y se reencola el
                // proceso actual al final de su propia cola.
                reencolarProceso(procesoEnEjecucion, colaEnEjecucion);
                procesoEnEjecucion = -1;
            }
            else if (colaEnEjecucion == 3 &&
                     politicaCola3 == POLITICA_STCF &&
                     debePreemptarPorSTCF())
            {
                // Dentro de la cola 3 (STCF) llegó un proceso
                // con menor tiempo restante.
                reencolarProceso(procesoEnEjecucion, colaEnEjecucion);
                procesoEnEjecucion = -1;
            }
        }

        // 3. Si el CPU está libre, seleccionar el siguiente
        //    proceso a ejecutar
        if (procesoEnEjecucion == -1)
        {
            colaEnEjecucion = colaMasAltaDisponible();

            if (colaEnEjecucion != 0)
            {
                procesoEnEjecucion = seleccionarProceso(colaEnEjecucion);
                quantumConsumido = 0;

                if (primeraEjecucion[procesoEnEjecucion])
                {
                    procesos[procesoEnEjecucion].setResponseTime(
                        tiempoActual -
                        procesos[procesoEnEjecucion].getArrivalTime()
                    );

                    primeraEjecucion[procesoEnEjecucion] = false;
                }
            }
        }

        // 4. Ejecutar un ciclo de CPU (si hay un proceso asignado)
        if (procesoEnEjecucion != -1)
        {
            procesos[procesoEnEjecucion].ejecutarUnCiclo();
            quantumConsumido++;

            if (procesos[procesoEnEjecucion].termino())
            {
                // El proceso finalizó en este ciclo
                int tiempoCompletado = tiempoActual + 1;

                procesos[procesoEnEjecucion].setCompletionTime(
                    tiempoCompletado
                );

                procesos[procesoEnEjecucion].setTurnaroundTime(
                    tiempoCompletado -
                    procesos[procesoEnEjecucion].getArrivalTime()
                );

                procesos[procesoEnEjecucion].setWaitingTime(
                    procesos[procesoEnEjecucion].getTurnaroundTime() -
                    procesos[procesoEnEjecucion].getBurstTime()
                );

                procesosTerminados++;
                procesoEnEjecucion = -1;
            }
            else
            {
                bool colaEsRR = (colaEnEjecucion == 1 || colaEnEjecucion == 2);

                if (colaEsRR &&
                    quantumConsumido == obtenerCola(colaEnEjecucion).getQuantum())
                {
                    // El quantum expiró: el proceso vuelve al
                    // final de su cola.
                    reencolarProceso(procesoEnEjecucion, colaEnEjecucion);
                    procesoEnEjecucion = -1;
                }

                // Para SJF y Priority (no expropiativas dentro de
                // su propia cola) el proceso continúa en el CPU
                // hasta terminar o hasta ser expropiado por una
                // cola de mayor prioridad (paso 2). STCF se
                // revisa en cada ciclo también en el paso 2.
            }
        }

        // 5. Avanzar el reloj del sistema (si no hay ningún
        //    proceso disponible, este avance simplemente salta
        //    el tiempo muerto hasta la siguiente llegada)
        tiempoActual++;
    }
}

//==============================================================
// Calcula las métricas finales: promedios de WT, CT, RT y TAT.
//==============================================================

void PlanificadorMLQ::calcularMetricas()
{
    double sumaWT = 0.0;
    double sumaCT = 0.0;
    double sumaRT = 0.0;
    double sumaTAT = 0.0;

    int n = static_cast<int>(procesos.size());

    for (const Proceso& p : procesos)
    {
        sumaWT += p.getWaitingTime();
        sumaCT += p.getCompletionTime();
        sumaRT += p.getResponseTime();
        sumaTAT += p.getTurnaroundTime();
    }

    if (n > 0)
    {
        promedioWT = sumaWT / n;
        promedioCT = sumaCT / n;
        promedioRT = sumaRT / n;
        promedioTAT = sumaTAT / n;
    }
}

//==============================================================
// Getters de las métricas promedio
//==============================================================

double PlanificadorMLQ::getPromedioWT() const
{
    return promedioWT;
}

double PlanificadorMLQ::getPromedioCT() const
{
    return promedioCT;
}

double PlanificadorMLQ::getPromedioRT() const
{
    return promedioRT;
}

double PlanificadorMLQ::getPromedioTAT() const
{
    return promedioTAT;
}
