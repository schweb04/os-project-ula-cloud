#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#include "orchestrator.h"

/**
 * TODO: Implementar la rutina del hilo monitor (Watchdog).
 * * Requisitos:
 * 1. Recuperar la estructura del servicio desde el argumento 'arg'.
 * 2. Utilizar 'waitpid' de forma BLOQUEANTE para esperar al proceso hijo.
 * 3. Analizar el estado de terminación (éxito, error o señal del sistema).
 * 4. Actualizar el Dashboard Global de forma SEGURA (evitar condiciones de carrera).
 */
void* monitor_service(void *arg) {
    // TODO: Castear el argumento al tipo de dato correcto.
    
    // TODO: Implementar la espera del proceso específico.
    // Ayuda: Revisar el uso de waitpid(pid, &status, 0).

    /* * Una vez que waitpid retorna, el proceso hijo ha cambiado de estado.
     * TODO: Analizar el 'status' usando las macros de sys/wait.h:
     * - WIFEXITED: ¿Terminó normalmente?
     * - WEXITSTATUS: ¿Cuál fue su código de retorno?
     * - WIFSIGNALED: ¿Fue terminado por una señal (Segfault, OOM Killer)?
     * - WTERMSIG: ¿Qué señal lo mató?
     */

    /*
     * TODO: Actualizar el dashboard global.
     * ¡CRÍTICO!: El acceso al array 'dashboard' debe estar protegido. 
     * No olvides liberar el mecanismo de sincronización al terminar.
     */

    //return NULL;
    // El hilo monitor se auto-desprende para liberar recursos automáticamente al finalizar
    if (pthread_detach(pthread_self()) != 0) {
        perror("Error al desprender el hilo monitor");
        return NULL;
    }

    service_t *svc = (service_t *)arg;
    int status;
    waitpid(svc->pid, &status, 0); // El argumento options se establece en 0 para indicar que el padre tiene que esperar hasta que el hijo termine

    service_state_t new_state;
    int new_exit_status;
    
    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == 0) {
            new_state = STATE_STOPPED;
        } else {
            new_state = STATE_CRASHED;
        }
        new_exit_status = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        new_state = STATE_KILLED;
        new_exit_status = WTERMSIG(status);
    } else {
        new_state = STATE_CRASHED;
        new_exit_status = status;
    }
    
    pthread_mutex_lock(&dashboard_mutex); // Bloquear el mutex para actualización segura
    svc->state = new_state;
    svc->exit_status = new_exit_status;
    pthread_mutex_unlock(&dashboard_mutex);

    return NULL;
}
