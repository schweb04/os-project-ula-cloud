#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include "orchestrator.h"

/**
 * TODO: Implementar la restricción de recursos del sistema.
 * * Requisitos:
 * 1. Definir los límites (soft y hard) para el espacio de direccionamiento virtual.
 * 2. Aplicar el límite utilizando la syscall 'setrlimit'.
 * 3. Garantizar que si la configuración falla, el proceso no continúe su ejecución.
 * * Ayuda: Revisar la constante RLIMIT_AS en la documentación de Linux.
 */
void apply_resource_limits(size_t mem_limit) {
    // TODO: Configurar la estructura rlimit y ejecutar la syscall.
    
    // Casos a considerar:
    // - ¿Qué diferencia hay entre rlim_cur y rlim_max?
    // - ¿Qué sucede si el límite solicitado es menor al tamaño del propio binario?

    struct rlimit *limit;
    limit->rlim_cur = limit->rlim_max = mem_limit; //si la memoria del proceso sobrepasa a rlim_cur, el proceso sigue vivo; mientras que si sobrepasa a rlim_max, se mata al proceso
    int success = setrlimit(RLIMIT_AS, limit); //APH

    if (success == -1)
    {
        perror("La configuración falló");
        exit(EXIT_FAILURE);
    }
}
