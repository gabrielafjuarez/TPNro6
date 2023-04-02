#include "inc/reloj.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"






reloj_t reloj;



_Bool 

    estado_alarma;





void SimularSegundos(int segundos){

        for(int index=0; index < segundos * 5; index++) {

        NuevoTickReloj(reloj);

    }

}



void EventoManejoAlarma(reloj_t reloj, 

                                      _Bool 

                                           estado){

    estado_alarma = estado;

}





void setUp (void){

    static const uint8_t INICIAL[] = {1, 2, 3, 4};

    reloj = CrearReloj(5, EventoManejoAlarma);

    ConfigurarReloj(reloj, INICIAL, sizeof(INICIAL));

    estado_alarma = 

                   0

                        ;



}





void test_hora_inicial(void){

    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 0};

    uint8_t hora[6];

    uint8_t alarma[4];

    reloj_t reloj = CrearReloj(5, EventoManejoAlarma);



    do {if (!(TraerHoraReloj(reloj, hora, sizeof(hora)))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(36)));}} while(0);

    UnityAssertEqualIntArray(( const void*)((ESPERADO)), ( const void*)((hora)), (UNITY_UINT32)((sizeof(ESPERADO))), (

   ((void *)0)

   ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

    do {if (!(ObtenerAlarmaReloj(reloj,alarma,sizeof(alarma)))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(38)));}} while(0);

}





void test_configurar_hora_actual (void){

    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 0};

    uint8_t hora[6];

    do {if ((TraerHoraReloj(reloj, hora, sizeof(hora)))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(45)));}} while(0);

    UnityAssertEqualIntArray(( const void*)((ESPERADO)), ( const void*)((hora)), (UNITY_UINT32)((sizeof(ESPERADO))), (

   ((void *)0)

   ), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}





void test_pasa_un_segundo(void){

    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 1};

    uint8_t hora[6];



    SimularSegundos(1);

    TraerHoraReloj(reloj, hora, sizeof(hora));

    UnityAssertEqualIntArray(( const void*)((ESPERADO)), ( const void*)((hora)), (UNITY_UINT32)((sizeof(ESPERADO))), (

   ((void *)0)

   ), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}





void test_pasan_diez_segundos(void){

    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 1, 0};

    uint8_t hora[6];



    SimularSegundos(10);

    TraerHoraReloj(reloj, hora, sizeof(hora));

    UnityAssertEqualIntArray(( const void*)((ESPERADO)), ( const void*)((hora)), (UNITY_UINT32)((sizeof(ESPERADO))), (

   ((void *)0)

   ), (UNITY_UINT)(66), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}







void test_pasa_un_minuto(void){

    static const uint8_t ESPERADO[] = {1, 2, 3, 5, 0, 0};

    uint8_t hora[6];



    SimularSegundos(60);

    TraerHoraReloj(reloj, hora, sizeof(hora));

    UnityAssertEqualIntArray(( const void*)((ESPERADO)), ( const void*)((hora)), (UNITY_UINT32)((sizeof(ESPERADO))), (

   ((void *)0)

   ), (UNITY_UINT)(77), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}





void test_pasan_diez_minutos(void){

    static const uint8_t ESPERADO[] = {1, 2, 4, 4, 0, 0};

    uint8_t hora[6];



    SimularSegundos(10*60);

    TraerHoraReloj(reloj, hora, sizeof(hora));

    UnityAssertEqualIntArray(( const void*)((ESPERADO)), ( const void*)((hora)), (UNITY_UINT32)((sizeof(ESPERADO))), (

   ((void *)0)

   ), (UNITY_UINT)(87), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}





void test_configurar_y_obtener_alarma (void){

    static const uint8_t ALARMA[] = {1, 2, 3, 5};

    uint8_t hora[4];



    ConfigurarAlarmaReloj(reloj, ALARMA, sizeof(ALARMA));

    do {if ((ObtenerAlarmaReloj(reloj, hora, sizeof(ALARMA)))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(96)));}} while(0);

    UnityAssertEqualIntArray(( const void*)((ALARMA)), ( const void*)((hora)), (UNITY_UINT32)((sizeof(ALARMA))), (

   ((void *)0)

   ), (UNITY_UINT)(97), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}





void test_configurar_y_deshabilitar_alarma (void){

    static const uint8_t ALARMA[] = {1, 2, 3, 5};

    uint8_t hora[4];



    ConfigurarAlarmaReloj(reloj, ALARMA, sizeof(ALARMA));

    do {if (!(CambiarAlarmaReloj(reloj))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(106)));}} while(0);



    do {if (!(ObtenerAlarmaReloj(reloj, hora, sizeof(hora)))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(108)));}} while(0);

    UnityAssertEqualIntArray(( const void*)((ALARMA)), ( const void*)((hora)), (UNITY_UINT32)((sizeof(ALARMA))), (

   ((void *)0)

   ), (UNITY_UINT)(109), UNITY_DISPLAY_STYLE_UINT8, UNITY_ARRAY_TO_ARRAY);

}



void test_configurar_y_disparar_alarma (void){

    static const uint8_t ALARMA[] = {1, 2, 3, 5};



    ConfigurarAlarmaReloj(reloj, ALARMA, sizeof(ALARMA));

    SimularSegundos(60);

    do {if ((estado_alarma)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(117)));}} while(0);

}

void test_configurar_y_no_disparar_alarma (void){

    static const uint8_t ALARMA[] = {1, 2, 3, 5};



    ConfigurarAlarmaReloj(reloj, ALARMA, sizeof(ALARMA));

    CambiarAlarmaReloj(reloj);



    SimularSegundos(60);

    do {if (!(estado_alarma)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(137)));}} while(0);

}
