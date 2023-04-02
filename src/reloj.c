#include "reloj.h"
#include <string.h>

#define SIZE_TIEMPO 6
#define SIZE_ALARMA 6
#define VALOR_INICIAL 0
#define UNIDAD_SEGUNDOS 5
#define DECENA_SEGUNDOS 4
#define UNIDAD_MINUTOS 3

#define DECENA_MINUTOS 2
#define UNIDAD_HORA 1
#define DECENA_HORAS 0
#define MAXIMO_VALOR_UNIDADES_HORA  4
#define MAXIMO_VALOR_DECENAS_HORA 2

struct reloj_s{
    bool valida;
    bool activada;
    uint16_t ticks_por_segundo;
    uint16_t cuenta_ticks;
    uint8_t tiempo[SIZE_TIEMPO];
    uint8_t alarma[SIZE_ALARMA];
    evento_reloj_t manejo_evento;
};

static struct reloj_s instancias;

//pongo la hora en cero
reloj_t CrearReloj(uint16_t ticks_por_segundo, evento_reloj_t manejo_evento){
    instancias.valida = false;
    instancias.activada = false;//ya no es necesaria xq lo defino en la creacion del reloj
    instancias.cuenta_ticks = VALOR_INICIAL;
    instancias.manejo_evento = manejo_evento;
    instancias.ticks_por_segundo = ticks_por_segundo;
    memset(instancias.tiempo, VALOR_INICIAL, SIZE_TIEMPO);
    return &instancias;
}

bool TraerHoraReloj(reloj_t reloj, uint8_t * tiempo, uint8_t size){
    memcpy(tiempo, reloj->tiempo, size);
    return reloj->valida;
}

void ConfigurarReloj(reloj_t reloj, uint8_t const * const tiempo, uint8_t size){
    memcpy(reloj->tiempo, tiempo, size);
    reloj->valida = true;
}

void NuevoTickReloj(reloj_t reloj){
    reloj->cuenta_ticks++;
    if(reloj->cuenta_ticks == reloj->ticks_por_segundo){
        reloj->cuenta_ticks = VALOR_INICIAL;
        reloj->tiempo[UNIDAD_SEGUNDOS]++;//los segundos estan en el 5to lugar del arreglo
        if (reloj->tiempo[UNIDAD_SEGUNDOS] == 10){
            reloj->tiempo[UNIDAD_SEGUNDOS] = 0;
            reloj->tiempo[DECENA_SEGUNDOS]++;
            if (reloj->tiempo[DECENA_SEGUNDOS] == 6){
                reloj->tiempo[DECENA_SEGUNDOS] = 0;
                reloj->tiempo[UNIDAD_MINUTOS]++;
                if (reloj->tiempo[UNIDAD_MINUTOS] == 10){
                    reloj->tiempo[UNIDAD_MINUTOS] = 0;
                    reloj->tiempo[DECENA_MINUTOS]++;//FALTAN PARA LOS 24 
                        if (reloj->tiempo[UNIDAD_HORA] == 24){
                            reloj->tiempo[DECENA_HORAS] = 0;
                            reloj->tiempo[UNIDAD_HORA]++;// PARA LOS 24 
                        }
                }
            }
        }
        bool activar = (reloj->tiempo[DECENA_SEGUNDOS] == 0) && (reloj->tiempo[UNIDAD_SEGUNDOS] == 0);
        for (int index = 0; index < SIZE_ALARMA; index++){
            if(reloj->alarma[index]!=reloj->tiempo[index]){
                 activar = false;
                 break;
             }
         }
        if (activar && reloj->activada){
             reloj->manejo_evento(reloj, true);
        }
    }
}

void ConfigurarAlarmaReloj(reloj_t reloj, uint8_t const * const alarma, uint8_t size){
    memcpy(reloj->alarma, alarma, size);
    reloj->activada = true;
}

bool ObtenerAlarmaReloj(reloj_t reloj, uint8_t * alarma, uint8_t size){
    memcpy(alarma, reloj->alarma, size);
    return reloj->activada;
}

bool CambiarAlarmaReloj(reloj_t reloj){
    reloj->activada = !reloj->activada;
    return reloj->activada;
}