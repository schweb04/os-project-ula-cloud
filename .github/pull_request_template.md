## 📝 Plantilla de Pull Request: ULA-Cloud

```markdown
## 🚀 Descripción del Proyecto
*¿Qué hace tu implementación de ULA-Cloud y cómo abordaste el reto de la orquestación?*

## 🛠️ Detalles Técnicos
Marca con una `x` las funcionalidades que lograste implementar:
- [ ] **Despliegue Paralelo:** Uso correcto de `fork()` y `execvp()` para los 4 servicios.
- [ ] **Jaula de Memoria:** Implementación de `setrlimit` en el proceso hijo.
- [ ] **Watchdog Multi-hilo:** Un hilo por servicio usando `pthread_create` y `waitpid`.
- [ ] **Sincronización:** Uso de `pthread_mutex_t` para proteger el dashboard global.
- [ ] **Manejo de Señales:** Limpieza de procesos hijos al recibir `SIGINT` (Ctrl+C).

## 🤖 Transparencia en el uso de IA
*¿Utilizaste herramientas de IA (ChatGPT, Claude, Github Copilot, etc.) durante el desarrollo?*
- [ ] No utilicé IA.
- [ ] Sí, utilicé IA para: _________________________________________________
*Nota: Recuerda que durante la consulta técnica deberás ser capaz de explicar cada línea de código, independientemente de su origen.*

## 🧪 Evidencia de Pruebas
*Copia y pega aquí la salida de tu terminal donde se vea al orquestador detectando la muerte del servicio `leak.c` por límite de memoria.*

```text
(Pega aquí tu log de salida)
```

## 🏁 Checklist de Robustez (Autoevaluación)
- [ ] Mi código compila sin warnings con `make all`.
- [ ] No quedan procesos "zombie" tras cerrar el orquestador.
- [ ] Todos los hilos se liberan correctamente.
- [ ] El dashboard muestra el estado real (RUNNING, CRASHED, KILLED) de cada servicio.
- [ ] Estoy preparado para explicar cualquier parte del código en una consulta técnica.
```