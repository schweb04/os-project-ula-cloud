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

    struct rlimit limit;
    limit.rlim_cur = mem_limit;
    limit.rlim_max = mem_limit;
    // rlim_cur es el valor que el kernel impone para el recurso correspondiente.
    // rlim_max actúa como un techo para rlim_cur.
    // rlim_cur puede modificarse a cualquier valor menor o igual a rlim_max. rlim_max puede disminuirse a cualquier valor mayor o igual a rlim_cur. 
    // Solo un proceso con privilegios adecuados puede aumentar rlim_max.
    int success = setrlimit(RLIMIT_AS, &limit); // RLIMIT_AS limita el tamaño total del espacio de direccionamiento virtual del proceso, incluyendo código, datos, pila y memoria compartida.

    if (success == -1)
    {
        perror("La configuración falló");
        exit(EXIT_FAILURE);
    }
}
