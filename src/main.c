/* Copyright 2022, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2022, Esteban Volentini <evolentini@herrera.unt.edu.ar>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \brief Simple sample of use LPC HAL gpio functions
 **
 ** \addtogroup samples Sample projects
 ** \brief Sample projects to use as a starting point
 ** @{ */

/* === Headers files inclusions =============================================================== */
#include "bsp.h"
#include <stdbool.h>
#include "pantalla.h"
#include "poncho.h"
#include "chip.h"
#include "reloj.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

typedef enum {
    HORA_SIN_AJUSTAR,
    MOSTRANDO_HORA,
    AJUSTANDO_MINUTOS_ACTUAL,
    AJUSTANDO_HORAS_ACTUAL,
    AJUSTANDO_MINUTOS_ALARMA,
    AJUSTANDO_HORAS_ALARMA,

} modo_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

static board_t board;

static modo_t modo;

static reloj_t reloj;

/* === Private variable definitions ============================================================ */

void CambiarModo(modo_t valor){
    modo = valor;
    switch (modo)
    {
    case HORA_SIN_AJUSTAR:
        MostrarDigitosParpadeando(board->display, 0, 3, 250);
        break;
    case MOSTRANDO_HORA:
        MostrarDigitosParpadeando(board->display, 0, 0, 0);
        break;
    case AJUSTANDO_MINUTOS_ACTUAL:
        MostrarDigitosParpadeando(board->display, 2, 3, 250);
        break;
    case AJUSTANDO_HORAS_ACTUAL:
        MostrarDigitosParpadeando(board->display, 0, 1, 250);
        break;
    case AJUSTANDO_MINUTOS_ALARMA:
        MostrarDigitosParpadeando(board->display, 2, 3, 250);
        break;
    case AJUSTANDO_HORAS_ALARMA:
        MostrarDigitosParpadeando(board->display, 0, 1, 250); 
        break;
    
    default:
        break;
    }
}

//void SonalAlarma(reloj_t){
//tengo que definir de que manera suena o enciende el led
//}
/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================= */

int main(void) { 
    board = BoardCreate();
    //reloj = CrearReloj(1000, SonalAlarma);
    uint8_t numero[4] = {1,2,3,4};

    SisTick_Init(1000);
    CambiarModo(HORA_SIN_AJUSTAR);
//    MostrarDigitosParpadeando(board->display,0, 1, 250);
   
    while (true) {
        //RefrescarPantalla(board->display);
        //genero interrupcion cada X segundos y evito refrescar la pantalla aqui

        if (ActivaEntradaDigital(board->aceptar)){
            EscribirPantallaBCD(board->display, numero, sizeof(numero));
            //EscribirPantallaBCD(board->display, (uint8_t[]){1, 2, 3, 4}, 4);
            MostrarCambiosPuntos(board->display, 1, 2);
        }

        if (ActivaEntradaDigital(board->cancelar)){
            EscribirPantallaBCD(board->display, NULL, 0);
        }

        if (ActivaEntradaDigital(board->establecer_tiempo)){
        }

        if (ActivaEntradaDigital(board->establecer_alarma)){    
        }

        if (ActivaEntradaDigital(board->decrementar)){
        }

        if (ActivaEntradaDigital(board->incrementar)){          
        }

        for (int index = 0; index < 100; index++) {
            for (int delay = 0; delay < 2500; delay++) {
                __asm("NOP");
            }
        }
    }
}

void SysTick_Handler(void){
    RefrescarPantalla(board->display);
    NuevoTickReloj(reloj);
}
/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
