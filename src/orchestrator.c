#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "orchestrator.h"

/**
 * TODO: Implementar el despliegue del microservicio.
 * * Requisitos:
 * 1. Crear un nuevo proceso.
 * 2. En el proceso HIJO:
 * - Configurar las restricciones de recursos (memoria).
 * - Reemplazar la imagen del proceso por el binario del servicio.
 * 3. En el proceso PADRE:
 * - Registrar el PID y el estado inicial en el dashboard.
 * - Retornar el PID asignado.
 */
int spawn_service(int index) {
    pid_t pid;

    // TODO: Invocar la creación del proceso hijo.

    // Casos a manejar:
    // - Error en la creación del proceso.
    // - Lógica del proceso HIJO (Setup de límites y Ejecución).
    // - Lógica del proceso PADRE (Gestión del dashboard).

    //return 0; // Cambiar por el PID real
    
    pid = fork();

    if (pid == -1)
    {
        perror("No se pudo crear un nuevo proceso");
    }
    else if (pid == 0)
    {
        apply_resource_limits(DEFAULT_MEM_LIMIT);
        execvp(dashboard[index].path, NULL); // //Como último argumento, se usa NULL para indicar el final de los argumentos adicionales (no hay).
        
        //Si execvp falla, se ejecuta el siguiente código:
        perror("Error al ejecutar el servicio");
        exit(EXIT_FAILURE);
    }
    else
    {
        pthread_mutex_lock(&dashboard_mutex); //Bloquear el mutex para actualizar el dashboard de forma segura
        dashboard[index].pid = pid;
        dashboard[index].state = STATE_RUNNING;
        pthread_mutex_unlock(&dashboard_mutex);

        // Como el proceso hijo ya ha sido lanzado, se inicia el hilo monitor desde el proceso padre
        if (pthread_create(&dashboard[index].monitor_thread, NULL, monitor_service, &dashboard[index]) != 0) {
            perror("Error al crear el hilo monitor");
        }
    }
    
    return pid;
}