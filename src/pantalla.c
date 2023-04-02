
/** \brief Definiciones de abstraccion de pantalla multiplexada de Siete segmentos
 **
 ** \addtogroup hal HAL
 ** \brief capa de abstraccion de Hardware
 ** @{ */

/* === Inclusiones de cabeceras ============================================ */
#include "pantalla.h"
#include <string.h>

/* === Definicion y Macros privados ======================================== */

#ifndef DISPLAY_MAX_DIGITS
    #define DISPLAY_MAX_DIGITS 8
#endif


/* === Declaraciones de tipos de datos privados ============================ */
struct display_s{
    uint8_t digits;
    uint8_t active_digit;
    uint8_t parpadeo_from;
    uint8_t parpadeo_to;
    uint16_t parpadeo_frecuencia;
    uint16_t parpadeo_cuenta;
    uint8_t memory[DISPLAY_MAX_DIGITS];//tiene que ser igual o menor que la cantidad de digitos
    struct display_driver_s driver[1]; 
};

/* === Definiciones de variables privadas ================================== */

static struct display_s instances [1];

static const uint8_t DIBUJAR [] = {
    SEGMENT_A + SEGMENT_B + SEGMENT_C + SEGMENT_D + SEGMENT_E + SEGMENT_F,              // CERO
    SEGMENT_B + SEGMENT_C,                                                              // UNO
    SEGMENT_A + SEGMENT_B + SEGMENT_G + SEGMENT_E + SEGMENT_D,                          //! < 2
    SEGMENT_A + SEGMENT_B + SEGMENT_C + SEGMENT_D + SEGMENT_G,                          //! < 3
    SEGMENT_F + SEGMENT_B + SEGMENT_G + SEGMENT_C,                                      //! < 4
    SEGMENT_A + SEGMENT_F + SEGMENT_G + SEGMENT_C + SEGMENT_D,                          //! < 5
    SEGMENT_A + SEGMENT_F + SEGMENT_E + SEGMENT_D + SEGMENT_C + SEGMENT_G,              //! < 6
    SEGMENT_A + SEGMENT_B + SEGMENT_C,                                                  //! < 7
    SEGMENT_A + SEGMENT_B + SEGMENT_C + SEGMENT_D + SEGMENT_E + SEGMENT_F+ SEGMENT_G,   //! < 8
    SEGMENT_A + SEGMENT_B + SEGMENT_C + SEGMENT_F + SEGMENT_G,                          //! < 9
};

/* === Definiciones de variables publicas ================================== */

/* === Declaraciones de funciones privadas ================================= */
static display_t DisplayAllocate(void);
/* === Definiciones de funciones privadas ================================== */
display_t DisplayAllocate(void){
    static struct display_s instances[] = {0};

    return &instances[0];
}

/* === Definiciones de funciones publicas ================================== */

display_t CrearPantalla(uint8_t digits, display_driver_t driver){
    display_t display = instances;
   
    display->digits = digits;
    display->active_digit = digits - 1;
    display->parpadeo_cuenta = 0;
    display->parpadeo_from = 0;
    display->parpadeo_to = 0;
    display->parpadeo_frecuencia = 0;

    memcpy(display->driver, driver, sizeof(display->driver));
    memset(display->memory, 0, sizeof(display->memory)); //limpiar la memoria
    display->driver->ScreenTurnOff = driver->ScreenTurnOff;
    display->driver->SegmentsTurnOn = driver->SegmentsTurnOn;
    display->driver->DigitTurnOn = driver->DigitTurnOn;
    
    //ApagarPantalla();
    display->driver->ScreenTurnOff();

    return display;
}


void EscribirPantallaBCD(display_t display, uint8_t * number, uint8_t size){
    memset(display->memory, 0, sizeof(display->memory)); //limpiar la memoria
    for (int index = 0; index < size; index++){
        if(index >= display->digits) break;
        display->memory[index] = DIBUJAR[number[index]];
    }
}


void RefrescarPantalla(display_t display){
    uint8_t segmentos;
    display->driver->ScreenTurnOff();    //ApagarPantalla();
    display->active_digit = (display->active_digit + 1) % display->digits;
    // if (display->active_digit == display->digits - 1) {
    //     display->active_digit = 0;
    // } else {
    //     display->active_digit = display->active_digit + 1;
    // }
    if (display->active_digit == 0) {
        display->parpadeo_cuenta++;
        if (display->parpadeo_cuenta >= display->parpadeo_frecuencia){
            display->parpadeo_cuenta = 0;
        }
    } 

    segmentos = display->memory[display->active_digit];
    if (display->parpadeo_frecuencia > 0){// con esto evito la division por cero de la siguiente linea
        if (display->parpadeo_cuenta >= display->parpadeo_frecuencia / 2){
            if ((display->active_digit >= display->parpadeo_from) && (display->active_digit <= display->parpadeo_to)){
            segmentos = 0;
            }
        }
    }
    display->driver->SegmentsTurnOn(segmentos);
    //display->driver->SegmentsTurnOn(display->memory[display->active_digit]);
    ////EscribirNumero(display->memory[display->active_digit]);
     
    display->driver->DigitTurnOn(display->active_digit);
    //display->driver->DigitTurnOn(display->active_digit);
    ////SeleccionarDigito(display->active_digit);
}



 void MostrarDigitosParpadeando(display_t display, uint8_t from, uint8_t to, uint16_t frecuencia){
    display->parpadeo_cuenta = 0;
    display->parpadeo_from = from;
    display->parpadeo_to = to;
    display->parpadeo_frecuencia = frecuencia;
 }

 void MostrarCambiosPuntos(display_t display, uint8_t from, uint8_t to){
    for (int index = from; index <= to; index++){
        display->memory[index] ^= ( 1 << 7 );
    }
 }


/* === Ciere de documentacion ============================================== */

/** @} Final de la definición del modulo para doxygen */

