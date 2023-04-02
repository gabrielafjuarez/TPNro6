/* Laboratorio de Microprocesadores */

#ifndef BSP_H
#define BSP_H

/** \brief Plantilla de archivos de cabecera 
 **
 ** \addtogroup hal HAL
 ** \brief Hardware abstraction layer
 ** @{ 
 */

/* === Inclusiones de archivos externos ==================================== */

#include "digital.h"
#include "pantalla.h"

/* === Cabecera C++ ======================================================== */
#ifdef __cplusplus
extern "C" {
#endif

/* === Definicion y Macros publicos ======================================== */

/* == Declaraciones de tipos de datos publicos ============================= */

typedef struct board_s {
    digital_output_t zumbador;
    digital_input_t establecer_tiempo;
    digital_input_t establecer_alarma;
    digital_input_t incrementar;
    digital_input_t decrementar;
    digital_input_t aceptar;
    digital_input_t cancelar;
    display_t display;
} const * board_t;

/* === Declaraciones de variables publicas ================================= */

/* === Declaraciones de funciones publicas ================================= */

board_t BoardCreate(void);

/* === Ciere de documentacion ============================================== */

#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif   /* BSP_H */