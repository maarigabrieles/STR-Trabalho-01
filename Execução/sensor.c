/* MONITOR SENSORES */ 
#include <math.h>
#include <pthread.h>
#include <string.h>


static pthread_mutex_t exclusao_mutua = PTHREAD_MUTEX_INITIALIZER; 
static pthread_cond_t alarme = PTHREAD_COND_INITIALIZER; 

//Variaveis para os sensores solicitados Ta, T, Ti, No, H
static double sensor_temp_ar = 0;
static double sensor_temp = 0;
static double sensor_temp_in = 0;
static double sensor_saida = 0;
static double sensor_nivel = 0; 

static double limite_atual = HUGE_VAL;

/* Chamado pela thread que le o sensor Ta e disponibiliza aqui o valor lido */
 void sensor_putTa(double v_lido) {
	 pthread_mutex_lock( &exclusao_mutua); 
	 sensor_temp_ar = v_lido;
	 if( sensor_temp_ar >= limite_atual) 
	 	pthread_cond_signal( &alarme); 
	 pthread_mutex_unlock( &exclusao_mutua); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do sensor Ta */ 
 double sensor_getTa(char s[5]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_mutua); 
	 if(strncmp(s,"ta",1)==0){
	 	aux = sensor_temp_ar; 
	 }
	 pthread_mutex_unlock( &exclusao_mutua); 
	 return aux; 
 }
 
 /* Chamado pela thread que le o sensor T e disponibiliza aqui o valor lido */
 void sensor_putT(double v_lido) {
	 pthread_mutex_lock( &exclusao_mutua); 
	 sensor_temp = v_lido;
	 if( sensor_temp >= limite_atual) 
	 	pthread_cond_signal( &alarme); 
	 pthread_mutex_unlock( &exclusao_mutua); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do sensor T */ 
 double sensor_getT(char s[5]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_mutua); 
	 if(strncmp(s,"t",1)==0){
	 	aux = sensor_temp; 
	 }
	 pthread_mutex_unlock( &exclusao_mutua); 
	 return aux; 
 }
 
 /* Chamado pela thread que le o sensor Ti e disponibiliza aqui o valor lido */
 void sensor_putTi(double v_lido) {
	 pthread_mutex_lock( &exclusao_mutua); 
	 sensor_temp_in = v_lido;
	 if( sensor_temp_in >= limite_atual) 
	 	pthread_cond_signal( &alarme); 
	 pthread_mutex_unlock( &exclusao_mutua); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do sensor Ti */ 
 double sensor_getTi(char s[5]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_mutua); 
	 if(strncmp(s,"ti",1)==0){
	 	aux = sensor_temp_in; 
	 }
	 pthread_mutex_unlock( &exclusao_mutua); 
	 return aux; 
 }
 
 /* Chamado pela thread que le o sensor No e disponibiliza aqui o valor lido */
 void sensor_putNo(double v_lido) {
	 pthread_mutex_lock( &exclusao_mutua); 
	 sensor_saida = v_lido;
	 if( sensor_saida >= limite_atual) 
	 	pthread_cond_signal( &alarme); 
	 pthread_mutex_unlock( &exclusao_mutua); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do sensor No */ 
 double sensor_getNo(char s[5]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_mutua); 
	 if(strncmp(s,"no",1)==0){
	 	aux = sensor_saida; 
	 }
	 pthread_mutex_unlock( &exclusao_mutua); 
	 return aux; 
 }

/* Chamado pela thread que le o sensor H e disponibiliza aqui o valor lido */
 void sensor_putH(double v_lido) {
	 pthread_mutex_lock( &exclusao_mutua); 
	 sensor_nivel = v_lido;
	 if( sensor_nivel >= limite_atual) 
	 	pthread_cond_signal( &alarme); 
	 pthread_mutex_unlock( &exclusao_mutua); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do sensor H */ 
 double sensor_getH(char s[5]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_mutua); 
	 if(strncmp(s,"h",1)==0){
	 	aux = sensor_nivel; 
	 }
	 pthread_mutex_unlock( &exclusao_mutua); 
	 return aux; 
 }
/* Thread fica bloqueada até o valor do sensor chegar em limite */ 
void sensor_alarme( double limite) {
	pthread_mutex_lock( &exclusao_mutua); 
	limite_atual = limite; 
	while(sensor_temp < limite_atual)  
		pthread_cond_wait( &alarme, &exclusao_mutua); 
	limite_atual = HUGE_VAL; 
	pthread_mutex_unlock( &exclusao_mutua); 
}

