/* Copyright 2022, Laboratorio de Microprocesadores 
 * Facultad de Ciencias Exactas y Tecnología 
 * Universidad Nacional de Tucuman
 */

#ifndef PANTALLA_H
#define PANTALLA_H

/** \brief Definiciones de abstraccion de pantalla multiplexada de Siete segmentos
 **
 ** \addtogroup hal HAL
 ** \brief capa de abstraccion de Hardware
 ** @{ */

/* === Inclusiones de archivos externos ==================================== */
#include <stdint.h>

/* === Cabecera C++ ======================================================== */
#ifdef __cplusplus
extern "C" {
#endif

/* === Definicion y Macros publicos ======================================== */

//DEFINICION DE BITS ASOCIADOS A CADA SEGMENTO PARA CONSTRUIR DIGITOS
//defino los segmentos
#define SEGMENT_A (1 << 0)
#define SEGMENT_B (1 << 1)    
#define SEGMENT_C (1 << 2)
#define SEGMENT_D (1 << 3)
#define SEGMENT_E (1 << 4)
#define SEGMENT_F (1 << 5)
#define SEGMENT_G (1 << 6)
#define SEGMENT_P (1 << 7)

/* == Declaraciones de tipos de datos publicos ============================= */

//!Referencia a un descriptor para gestionar una pantalla de siete segmentos multiplexada
typedef struct display_s * display_t;

typedef void (*display_screen_off_t)(void);//puntero a una funcion con un determinado prototipo

typedef void(*display_segments_on_t)(uint8_t segments);

typedef void(*display_digit_on_t)(uint8_t digit);

typedef struct display_driver_s{
   display_screen_off_t ScreenTurnOff;
   display_segments_on_t SegmentsTurnOn;
   display_digit_on_t DigitTurnOn;
} const * display_driver_t;

/* === Declaraciones de variables publicas ================================= */

/**
 * @brief Metodo para crear una pantalla multiplexada de siete segmentos
 * 
 * @param digit       Cantidad de digitos que forma la pantalla multiplexada
 * @param driver        Puntero a la estructura con las funciones de bajo nivel
 * @return display_t    Puntero al descriptor de la pantalla creada
 */

display_t CrearPantalla(uint8_t digits, display_driver_t driver);
//display_t CrearPantalla(uint8_t digit);

/**
 * @brief Funcion para escribir un numero BCD en la pantalla de siete segmentos
 * 
 * @param display       Puntero al descriptor de la pantalla en la que se escribe
 * @param number        Puntero al primer elemento de numero BCD a escribir
 * @param size          Cantidad de elementos en el vector que contiene el numero BCD
 */
void EscribirPantallaBCD(display_t display, uint8_t * number, uint8_t size);


/**
 * @brief Funcion para refrescar pantalla
 * 
 * @param display       Puntero al descriptor de la pantalla en la que se debe refrescar
 */
void RefrescarPantalla(display_t display);

/**
 * @brief Funcion para hacer parpadear algunos digitos de la pantalla
 * 
 * @param display       Puntero al descriptor de la pantalla con la que se quiere trabajar
 * @param from          Posicion del primer digito que se quiere hacer parpadear
 * @param to            Posicion del ultimo digito que se quiere hacer parpadear
 * @param frecuencia    Factod de division de la frecuencia de refresco para el parpadeo
 */
void MostrarDigitosParpadeando(display_t display, uint8_t from, uint8_t to, uint16_t frecuencia);

/**
 * @brief Funcion para cambiar el estado d elos puntos de los digitos en la pantalla
 * 
 * @param display       Puntero al descriptor de la pantalla con la que se quiere trabajar
 * @param from          Posicion del primer digito que se quiere cambiar el punto
 * @param to            Posicion del ultimo digito que se quiere cambiar el punto
 */
void MostrarCambiosPuntos(display_t display, uint8_t from, uint8_t to);

/* === Declaraciones de funciones publicas ================================= */

/* === Ciere de documentacion ============================================== */
#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif   /* PANTALLA_H */