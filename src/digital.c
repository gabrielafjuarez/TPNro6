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

/** @file digital.c
 **
 ** @brief Plantilla de archivos fuente
 **
 ** Plantilla para los archivos de codigo fuente de prácticos de las 
 ** asignaturas Diseño Integrado de Sistemas Emebebidos y Sistemas Embebidos
 ** de Tiempo Real dictadas en de la Especialización en Integración de
 ** Sistemas Informaticos de la Univesidad Nacional de Tucumán
 ** 
 ** | RV | YYYY.MM.DD | Autor       | Descripción de los cambios              |
 ** |----|------------|-------------|-----------------------------------------|
 ** |  1 | 2022.08.27 | evolentini  | Version inicial del archivo             |
 ** 
 ** @defgroup plantilla Plantilals de Archivos
 ** @brief Plantillas de archivos normalizadas
 ** @{ 
 */

/* === Inclusiones de cabeceras ============================================ */
#include "digital.h"
#include "chip.h"

/* === Definicion y Macros privados ======================================== */

#ifndef OUTPUT_INSTANCES
    #define OUTPUT_INSTANCES       4 
#endif

#ifndef INPUT_INSTANCES
    #define INPUT_INSTANCES        6 
#endif
/* === Declaraciones de tipos de datos privados ============================ */

struct digital_output_s{       
    uint8_t gpio;               //!< Puerto GPIO de la salida digital
    uint8_t bit;                //!< Terminal del puerto GPIO de la salida digital
    bool allocated;             //!< Bandera para indicar que el descriptor esta en uso
};
//!Estructura para almacenar el descriptor de una entrada digital
struct digital_input_s{       
    uint8_t port;               //!< Puerto GPIO de la entrada digital
    uint8_t pin;                //!< Terminal del puerto GPIO de la entrada digital
    bool inverted;              //!< La entrada opera con logica invertida
    bool ultimo_estado;         //!< Bandera con el ultimo estado reportado de la entrada
    bool allocated;             //!< Bandera para indicar que el descriptor esta en uso
};

/* === Definiciones de variables privadas ================================== */

/* === Definiciones de variables publicas ================================== */

/* === Declaraciones de funciones privadas ================================= */
static struct digital_output_s instances [OUTPUT_INSTANCES] = {0};
static struct digital_input_s instancesi [INPUT_INSTANCES] = {0};

/*Con el = 0 me garantizo que todas las intancias empiezan en falso
porque llena el arreglo con 0 y las variables logicas allocated empiezan con falso*/

/* === Definiciones de funciones privadas ================================== */
//crea un descriptor o puntero a partir de buscar en el arreglo d einstancias
digital_output_t AsignarSalidaDigital(void) {
    digital_output_t output = NULL;
    for (int index = 0; index < OUTPUT_INSTANCES; index++){
        if (instances[index].allocated == false){
            instances[index].allocated = true;
            output =  &instances[index];
            break;
        }
    }
    return output;
}

digital_input_t AsignarEntradaDigital(void) {
    digital_input_t input = NULL;
    for (int index = 0; index < INPUT_INSTANCES; index++){
        if (instancesi[index].allocated == false){
            instancesi[index].allocated = true;
            input =  &instancesi[index];
            break;
        }
    }
    return input;
}

/* === Definiciones de funciones publicas ================================== */
//SALIDAS
digital_output_t CrearSalidaDigital(uint8_t gpio, uint8_t bit) {
    digital_output_t output = AsignarSalidaDigital();
    if (output) {
        output->gpio = gpio;
        output->bit = bit;    
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->gpio, output->bit, false);
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, output->gpio, output->bit, true);
    }
    return output;
}

void ActivarSalidaDigital(digital_output_t output){
    if(output){
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->gpio, output->bit, true);
    }
}

void DesactivarSalidaDigital(digital_output_t output){
    if(output){
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->gpio, output->bit, false);
    }
}

void CambiarSalidaDigital(digital_output_t output){
    if(output){
        Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, output->gpio, output->bit);
    }
}

//ENTRADAS
//CREAR ENTRADA
digital_input_t CrearEntradaDigital(uint8_t port, uint8_t pin, bool inverted) {
    digital_input_t input = AsignarEntradaDigital();
    if (input) {
        input->port = port;
        input->pin = pin;   
        input->inverted = inverted; 
        //Chip_GPIO_SetPinState(LPC_GPIO_PORT, input->gpio, input->bit, false);
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, input->port, input->pin, false);
    }
    return input;
}

//PROBAR
 bool GetStateEntradaDigital(digital_input_t input){
    return input->inverted ^ Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, input->port, input->pin);
}

//CAMBIAR
bool CambioEntradaDigital (digital_input_t input){
    bool estado = GetStateEntradaDigital(input);
    bool resultado = estado != input->ultimo_estado;
    input->ultimo_estado = estado;
    return resultado;
}

//ENCENDER
bool ActivaEntradaDigital (digital_input_t input){
    bool estado = GetStateEntradaDigital(input);
    bool resultado = estado && !input->ultimo_estado;
    input->ultimo_estado = estado;
    return resultado;
}

//APAGAR
bool DesactivaEntradaDigital (digital_input_t input){
    bool estado = GetStateEntradaDigital(input);
    bool resultado = !estado && !input->ultimo_estado;
    input->ultimo_estado = estado;
    return resultado;
}
/* === Ciere de documentacion ============================================== */

/** @} Final de la definición del modulo para doxygen */

