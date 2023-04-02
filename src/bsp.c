/* Copyright 2022, Laboratorio de Microprocesadores 
 * Facultad de Ciencias Exactas y Tecnología 
 * Universidad Nacional de Tucuman
 */


/** \brief Plantilla de archivos de cabecera 
 **
 ** \addtogroup hal HAL
 ** \brief Hardware abstraction layer
 ** @{ 
 */

/* === Inclusiones de cabeceras ============================================ */

#include "bsp.h"
#include "chip.h"
#include "poncho.h"

/* === Definicion y Macros privados ======================================== */

/* === Declaraciones de tipos de datos privados ============================ */

/* === Definiciones de variables privadas ================================== */

static struct board_s board = {0};

/* === Definiciones de variables publicas ================================== */

/* === Declaraciones de funciones privadas ================================= */
static void InicializarDigitos(void);
static void InicializarSegmentos(void);
static void InicializarZumbador(void);
static void InicializarTeclas(void);

//static void DisplayInit(void);
static void ApagarPantalla(void);
static void EscribirNumero(uint8_t segmentos);
static void SeleccionarDigito(uint8_t digito);


/* === Definiciones de funciones privadas ================================== */
void InicializarDigitos(void){
/**** 4 VECES - UNA POR CADA DIGITO  ****/
    Chip_SCU_PinMuxSet(DIGIT_1_PORT, DIGIT_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_1_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, DIGIT_1_GPIO, DIGIT_1_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, DIGIT_1_GPIO, DIGIT_1_BIT, true);

    Chip_SCU_PinMuxSet(DIGIT_2_PORT, DIGIT_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_2_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, DIGIT_2_GPIO, DIGIT_2_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, DIGIT_2_GPIO, DIGIT_2_BIT, true);

    Chip_SCU_PinMuxSet(DIGIT_3_PORT, DIGIT_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_3_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, DIGIT_3_GPIO, DIGIT_3_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, DIGIT_3_GPIO, DIGIT_3_BIT, true);

    Chip_SCU_PinMuxSet(DIGIT_4_PORT, DIGIT_4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_4_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, DIGIT_4_GPIO, DIGIT_4_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, DIGIT_4_GPIO, DIGIT_4_BIT, true);
}


void InicializarSegmentos(void){
/**** 8 VECES - UNA POR CADA SEGMENTO  ****/
    Chip_SCU_PinMuxSet(SEGMENT_A_PORT, SEGMENT_A_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_A_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_A_GPIO, SEGMENT_A_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_A_GPIO, SEGMENT_A_BIT, true);

    Chip_SCU_PinMuxSet(SEGMENT_B_PORT, SEGMENT_B_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_B_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_B_GPIO, SEGMENT_B_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_B_GPIO, SEGMENT_B_BIT, true);

    Chip_SCU_PinMuxSet(SEGMENT_C_PORT, SEGMENT_C_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_C_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, DIGIT_3_GPIO, SEGMENT_C_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_C_GPIO, SEGMENT_C_BIT, true);

    Chip_SCU_PinMuxSet(SEGMENT_D_PORT, SEGMENT_D_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_D_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_D_GPIO, SEGMENT_D_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_D_GPIO, SEGMENT_D_BIT, true);

    Chip_SCU_PinMuxSet(SEGMENT_E_PORT, SEGMENT_E_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_E_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_E_GPIO, SEGMENT_E_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_E_GPIO, SEGMENT_E_BIT, true);

    Chip_SCU_PinMuxSet(SEGMENT_F_PORT, SEGMENT_F_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_F_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_F_GPIO, SEGMENT_F_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_F_GPIO, SEGMENT_F_BIT, true);

    Chip_SCU_PinMuxSet(SEGMENT_G_PORT, SEGMENT_G_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_G_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_G_GPIO, SEGMENT_G_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_G_GPIO, SEGMENT_G_BIT, true);

    Chip_SCU_PinMuxSet(SEGMENT_P_PORT, SEGMENT_P_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_P_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_P_GPIO, SEGMENT_P_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_P_GPIO, SEGMENT_P_BIT, true);


}

void InicializarZumbador(void){
    /**********SALIDAS********/
    Chip_SCU_PinMuxSet(ZUMBADOR_PORT, ZUMBADOR_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | ZUMBADOR_FUNC);
    board.zumbador = CrearSalidaDigital(ZUMBADOR_GPIO, ZUMBADOR_BIT);//
}

void InicializarTeclas(void){
/*********ENTRADAS*********/
    Chip_SCU_PinMuxSet(TIEMPO_PORT, TIEMPO_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TIEMPO_FUNC);
    board.establecer_tiempo = CrearEntradaDigital(TIEMPO_GPIO, TIEMPO_BIT,true);//

    Chip_SCU_PinMuxSet(ALARMA_PORT, ALARMA_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | ALARMA_FUNC);
    board.establecer_alarma = CrearEntradaDigital(ALARMA_GPIO, ALARMA_BIT,true);//

    Chip_SCU_PinMuxSet(ACEPTAR_PORT, ACEPTAR_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | ACEPTAR_FUNC);
    board.aceptar = CrearEntradaDigital(ACEPTAR_GPIO, ACEPTAR_BIT,true);//
        
    Chip_SCU_PinMuxSet(CANCELAR_PORT, CANCELAR_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | CANCELAR_FUNC);
    board.cancelar = CrearEntradaDigital(CANCELAR_GPIO, CANCELAR_BIT,true);//
    
    Chip_SCU_PinMuxSet(INCREMENTAR_PORT, INCREMENTAR_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | INCREMENTAR_FUNC);
    board.incrementar = CrearEntradaDigital(INCREMENTAR_GPIO, INCREMENTAR_BIT,true);//
    
    Chip_SCU_PinMuxSet(DECREMENTAR_PORT, DECREMENTAR_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | DECREMENTAR_FUNC);
    board.decrementar = CrearEntradaDigital(DECREMENTAR_GPIO, DECREMENTAR_BIT,true);//
}


// void DisplayInit(void){
//     static const struct display_driver_s display_driver = {
//         .ScreenTurnOff = ApagarPantalla,
//         .SegmentsTurnOn = EscribirNumero,
//         .DigitTurnOn = SeleccionarDigito,
//     };
//     board.display = CrearPantalla(4, &display_driver);
// }


//apagar pantalla
void ApagarPantalla(void){
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, DIGITS_GPIO, DIGITS_MASK);//pongo en cero los digitos 
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEGMENTS_GPIO, SEGMENTS_MASK);//pongo en cero los segmentos
    Chip_GPIO_SetPinState(LPC_GPIO_PORT,SEGMENT_P_GPIO, SEGMENT_P_BIT, false);
}

void EscribirNumero(uint8_t segmentos){
    Chip_GPIO_SetValue(LPC_GPIO_PORT, SEGMENTS_GPIO, (segmentos) & SEGMENTS_MASK);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT,SEGMENT_P_GPIO, SEGMENT_P_BIT, (segmentos & SEGMENT_P));
}

void SeleccionarDigito(uint8_t digito){
    Chip_GPIO_SetValue(LPC_GPIO_PORT, DIGITS_GPIO, (1 << (3 - digito)) & DIGITS_MASK);// 
}


/* === Definiciones de funciones publicas ================================== */

board_t BoardCreate(void){
    InicializarDigitos();
    InicializarSegmentos();
    InicializarZumbador();
    InicializarTeclas();
//    DisplayInit();    

    board.display = CrearPantalla(4, &(struct display_driver_s){
        .ScreenTurnOff = ApagarPantalla,
        .SegmentsTurnOn = EscribirNumero,
        .DigitTurnOn = SeleccionarDigito,
    });

    return &board;
}

void SisTick_Init(uint16_t ticks){
    __asm volatile("cpsid i");//deshabilita las interrupciones

    /*Activo SysTick*/
    SystemCoreClockUpdate();//obtiene la frecuencia en la que ejecuta el procesador
    SysTick_Config(SystemCoreClock/ticks);//digo que cuente una cantidad (x) de nros

    /*Prioridad de actualizacion de SysTick*/
    NVIC_SetPriority(SysTick_IRQn,(1 <<__NVIC_PRIO_BITS) - 1);

    __asm volatile("cpsie i");//habilita las interrupciones
}


/* === Ciere de documentacion ============================================== */

/** @} Final de la definición del modulo para doxygen */