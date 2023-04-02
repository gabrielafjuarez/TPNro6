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

#ifndef DIGITAL_H   /*! @cond    */
#define DIGITAL_H   /*! @endcond */

/** @file digital.h
 **
 ** @brief Plantilla de archivos de cabecera 
 **
 ** Plantilla para los archivos de cabeceras de las prácticos de las 
 ** asignaturas Diseño Integrado de Sistemas Emebebidos y Sistemas Embebidos
 ** de Tiempo Real dictadas en de la Especialización en Integración de
 ** Sistemas Informaticos de la Univesidad Nacional de Tucumán
 ** 
 ** | RV | YYYY.MM.DD | Autor            | Descripción de los cambios           |
 ** |----|------------|------------------|--------------------------------------|
 ** |  1 | 2022.08.27 | evolentini       | Version inicial del archivo          |
 ** |  1 | 2022.09.17 | gabriela_juarez  | Version modificada del archivo       |
 ** 
 ** @defgroup plantilla Plantilals de Archivos
 ** @brief Plantillas de archivos normalizadas
 ** @{ 
 */

/* === Inclusiones de archivos externos ==================================== */
#include <stdint.h>
#include <stdbool.h>
/* === Cabecera C++ ======================================================== */
#ifdef __cplusplus
extern "C" {
#endif

/* === Definicion y Macros publicos ======================================== */

/* == Declaraciones de tipos de datos publicos ============================= */

//!Referencia para gestionar una entrada digital
typedef struct digital_output_s * digital_output_t;

//!Referencia para gestionar una salida digital
typedef struct digital_input_s * digital_input_t; 

/* === Declaraciones de variables publicas ================================= */

/* === Declaraciones de funciones publicas ================================= */
/**
 * @brief Metodo para crear una salida digital
 * 
 * @param gpio Puerto GPIO que contiene la salida
 * @param bit  Numero de terminal del puerto GPIO asignado a la salida
 * @return digital_output_t 
 */
digital_output_t CrearSalidaDigital(uint8_t gpio, uint8_t bit);

/**
 * @brief Metodo para activar una salida Digital
 * 
 * @param output Puntero al descriptor de la salida
 * 
 */
void ActivarSalidaDigital(digital_output_t output);//me dice si hay cambio de 0 a 1

/**
 * @brief Metodo para desactivar una salida digital
 * 
 * @param output Puntero al descriptor de la salida
 */
void DesactivarSalidaDigital(digital_output_t output);//me dice si hay cambio de 1 a 0

/**
 * @brief Metodo para invertir una salida digital
 * 
 * @param output Puntero al descriptor de la salida
 */
void CambiarSalidaDigital(digital_output_t output);

/**
 * @brief Metodo para crear una entrada digital
 * 
 * @param port                  Puerto GPIO que contiene la entrada
 * @param pin                   Numero de terminal del puerto GPIO asignado a la entrada
 * @param inverted              Bandera que indica que la entrada trabaja con logica invertida
 * @return digital_input_t      Puntero al descriptor de la entrada creada
 */
digital_input_t CrearEntradaDigital(uint8_t port, uint8_t pin, bool inverted);

/**
 * @brief Metodo para consultar el estado de una entrada digital
 * 
 * @param input     Puntero al descriptor de la entrada
 * @return true     La entrada esta activa
 * @return false    La entrada esta inactiva
 */
bool GetStateEntradaDigital(digital_input_t input);

/**
 * @brief Metodo para consultar activaviones de una entrada digital
 * 
 * @param input     Puntero al descriptor de la entrada
 * @return true     La entrada tuvo activaciones desde la ultima llamada
 * @return false    La entrada no tuvo activaciones desde la ultima llmada
 */
bool ActivaEntradaDigital(digital_input_t input);

/**
 * @brief Metodo para consultar
 * 
 * @param input     Puntero al descriptor de la entrada
 * @return true     La entrada tuvo desactivaciones desde la ultima llamada
 * @return false    La entrada no tuvo desactivaciones desde la ultima llamada
 */
bool DesactivaEntradaDigital(digital_input_t input);

/**
 * @brief Metodo para consultar cambios en el estado de una entrada digital
 * 
 * @param input     Puntero al descriptor de la entrada
 * @return true     La entrada tuvo cambios desde la ultima llamada
 * @return false    La entrada no tuvo cambios desde la ultima llamada
 */
bool CambioEntradaDigital(digital_input_t input);

/* === Ciere de documentacion ============================================== */
#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif   /* DIGITAL_H */
