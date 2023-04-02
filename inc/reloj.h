#include <stdint.h>
#include <stdbool.h>

typedef struct reloj_s * reloj_t;

typedef void (*evento_reloj_t)(reloj_t reloj, bool estado);

reloj_t CrearReloj(uint16_t ticks_por_segundo, evento_reloj_t manejo_evento);

bool TraerHoraReloj(reloj_t reloj, uint8_t * tiempo, uint8_t size);

void ConfigurarReloj(reloj_t reloj, uint8_t const * const tiempo, uint8_t size);

void NuevoTickReloj(reloj_t reloj);

void ConfigurarAlarmaReloj(reloj_t reloj, uint8_t const * const alarma, uint8_t size);

bool ObtenerAlarmaReloj(reloj_t reloj, uint8_t * alarma, uint8_t size);

bool CambiarAlarmaReloj(reloj_t reloj);
