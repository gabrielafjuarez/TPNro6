#include "unity.h"
#include "reloj.h"

#define TICKS_POR_SEGUNDO 5

reloj_t reloj;
bool estado_alarma;


void SimularSegundos(int segundos){
        for(int index=0; index < segundos * TICKS_POR_SEGUNDO; index++) {
        NuevoTickReloj(reloj);
    }
}

void EventoManejoAlarma(reloj_t reloj, bool estado){//si es true la enciendo,si es false la apago
    estado_alarma = estado;
}

//Creo el reloj y lo pongo en hora
void setUp (void){
    static const uint8_t INICIAL[] = {1, 2, 3, 4};
    reloj = CrearReloj(TICKS_POR_SEGUNDO, EventoManejoAlarma);//inicializo el reloj
    ConfigurarReloj(reloj, INICIAL, sizeof(INICIAL));
    estado_alarma = false;

}

//Configurar libreria, consultar hora, y la hora debe ser invalida
void test_hora_inicial(void){
    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 0};
    uint8_t hora[6];
    uint8_t alarma[4];
    reloj_t reloj = CrearReloj(TICKS_POR_SEGUNDO, EventoManejoAlarma);
    
    TEST_ASSERT_FALSE(TraerHoraReloj(reloj, hora, sizeof(hora)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY (ESPERADO, hora, sizeof(ESPERADO));
    TEST_ASSERT_FALSE(ObtenerAlarmaReloj(reloj,alarma,sizeof(alarma)));//me aseguro que la alarma arranca en falso
}

//Configurar libreria, ajustar hora (con valores correctos), consultar hora y la hora tiene que ser valida
void test_configurar_hora_actual (void){
    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 0};
    uint8_t hora[6];
    TEST_ASSERT_TRUE(TraerHoraReloj(reloj, hora, sizeof(hora)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY (ESPERADO, hora, sizeof(ESPERADO));
}

//Simular el paso de n ciclos de reloj, consultar la hora y verificar que avanza un segundo
void test_pasa_un_segundo(void){
    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 1};
    uint8_t hora[6];
    
    SimularSegundos(1);
    TraerHoraReloj(reloj, hora, sizeof(hora));
    TEST_ASSERT_EQUAL_UINT8_ARRAY (ESPERADO, hora, sizeof(ESPERADO));
}

//Simular el paso de 10*n ciclos de reloj, consultar la hora y verificar que avanza un segundo
void test_pasan_diez_segundos(void){
    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 1, 0};
    uint8_t hora[6];
    
    SimularSegundos(10);
    TraerHoraReloj(reloj, hora, sizeof(hora));
    TEST_ASSERT_EQUAL_UINT8_ARRAY (ESPERADO, hora, sizeof(ESPERADO));
}


//Simular el paso de un minuto de reloj, consultar la hora y verificar que avanza un minuto
void test_pasa_un_minuto(void){
    static const uint8_t ESPERADO[] = {1, 2, 3, 5, 0, 0};
    uint8_t hora[6];
    
    SimularSegundos(60);
    TraerHoraReloj(reloj, hora, sizeof(hora));
    TEST_ASSERT_EQUAL_UINT8_ARRAY (ESPERADO, hora, sizeof(ESPERADO));
}

//Simular el paso de 10 minutos de reloj, consultar la hora y verificar que avanza un minuto
void test_pasan_diez_minutos(void){
    static const uint8_t ESPERADO[] = {1, 2, 4, 4, 0, 0};
    uint8_t hora[6];
    
    SimularSegundos(10*60);//simulate minutos
    TraerHoraReloj(reloj, hora, sizeof(hora));
    TEST_ASSERT_EQUAL_UINT8_ARRAY (ESPERADO, hora, sizeof(ESPERADO));
}

//6-SIMULAR LA ALARMA ---guarda y activa la alarma 6 y 8
void test_configurar_y_obtener_alarma (void){
    static const uint8_t ALARMA[] = {1, 2, 3, 5};
    uint8_t hora[4];

    ConfigurarAlarmaReloj(reloj, ALARMA, sizeof(ALARMA));
    TEST_ASSERT_TRUE(ObtenerAlarmaReloj(reloj, hora, sizeof(ALARMA)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ALARMA, hora, sizeof(ALARMA));
}

//9-deshabilitarR LA ALARMA ---guarda y activa la alarma
void test_configurar_y_deshabilitar_alarma (void){
    static const uint8_t ALARMA[] = {1, 2, 3, 5};
    uint8_t hora[4];

    ConfigurarAlarmaReloj(reloj, ALARMA, sizeof(ALARMA));
    TEST_ASSERT_FALSE(CambiarAlarmaReloj(reloj));

    TEST_ASSERT_FALSE(ObtenerAlarmaReloj(reloj, hora, sizeof(hora)));//cambia la bandera de tru a false y viceversa
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ALARMA, hora, sizeof(ALARMA));
}

void test_configurar_y_disparar_alarma (void){
    static const uint8_t ALARMA[] = {1, 2, 3, 5};
    
    ConfigurarAlarmaReloj(reloj, ALARMA, sizeof(ALARMA));
    SimularSegundos(60);//simulate minutos
    TEST_ASSERT_TRUE(estado_alarma);
}

//  void test_ver_estado_alarma (void){
//      static const uint8_t ALARMA[] = {1, 2, 3, 5};
    
//      ConfigurarAlarmaReloj(reloj, ALARMA, sizeof(ALARMA));
//      TEST_ASSERT_TRUE(estado_alarma); 
//      estado_alarma = false;
//      SimularSegundos(1);//simulate minutos
//      TEST_ASSERT_FALSE(estado_alarma); 
//  }

void test_configurar_y_no_disparar_alarma (void){
    static const uint8_t ALARMA[] = {1, 2, 3, 5};
    
    ConfigurarAlarmaReloj(reloj, ALARMA, sizeof(ALARMA));
    CambiarAlarmaReloj(reloj);

    SimularSegundos(60);//simulate minutos
    TEST_ASSERT_FALSE(estado_alarma);
}