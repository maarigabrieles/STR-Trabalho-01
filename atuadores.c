//Atuadores para guardar o
#include <math.h>
#include <pthread.h>
#include <string.h>

static pthread_mutex_t exclusao_atuador = PTHREAD_MUTEX_INITIALIZER; 
static pthread_cond_t alarme = PTHREAD_COND_INITIALIZER; 

//Variaveis para os atuadores solicitados Ni, Q, Na e Nf.
static double atuador_Ni = 0;
static double atuador_Q = 0;
static double atuador_Na = 0;
static double atuador_Nf = 0;

static double limite_atual = HUGE_VAL;

/* Chamado pela thread que le o Atuador Ni e disponibiliza aqui o valor lido */
 void atuador_putNi(double v_lido) {
	 pthread_mutex_lock( &exclusao_atuador); 
	 atuador_Ni = v_lido;
	 if( atuador_Ni >= limite_atual) 
	 	pthread_cond_signal( &alarme); 
	 pthread_mutex_unlock( &exclusao_atuador); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do Atuador Ni */ 
 double atuador_getNi(char s[6]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_atuador); 
	 if(strncmp(s,"ani",1)==0){
	 	aux = atuador_Ni; 
	 }
	 pthread_mutex_unlock( &exclusao_atuador); 
	 return aux; 
 }
 
 /* Chamado pela thread que le o Atuador Q e disponibiliza aqui o valor lido */
 void atuador_putQ(double v_lido) {
	 pthread_mutex_lock( &exclusao_atuador); 
	 atuador_Q = v_lido;
	 if( atuador_Q >= limite_atual) 
	 	pthread_cond_signal( &alarme); 
	 pthread_mutex_unlock( &exclusao_atuador); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do Atuador Q */ 
 double atuador_getQ(char s[6]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_atuador); 
	 if(strncmp(s,"aq-",1)==0){
	 	aux = atuador_Q; 
	 }
	 pthread_mutex_unlock( &exclusao_atuador); 
	 return aux; 
 }
 
 /* Chamado pela thread que le o Atuador Na e disponibiliza aqui o valor lido */
 void atuador_putNa(double v_lido) {
	 pthread_mutex_lock( &exclusao_atuador); 
	 atuador_Na = v_lido;
	 if( atuador_Na >= limite_atual) 
	 	pthread_cond_signal( &alarme); 
	 pthread_mutex_unlock( &exclusao_atuador); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do Atuador Na */ 
 double atuador_getNa(char s[6]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_atuador); 
	 if(strncmp(s,"ana",1)==0){
	 	aux = atuador_Na; 
	 }
	 pthread_mutex_unlock( &exclusao_atuador); 
	 return aux; 
 }
 
 /* Chamado pela thread que le o Atuador Nf e disponibiliza aqui o valor lido */
 void atuador_putNf(double v_lido) {
	 pthread_mutex_lock( &exclusao_atuador); 
	 atuador_Nf = v_lido;
	 if( atuador_Nf >= limite_atual) 
	 	pthread_cond_signal( &alarme); 
	 pthread_mutex_unlock( &exclusao_atuador); 
 }
 
 /* Chamado por qualquer thread que precisa do valor lido do Atuador Nf */ 
 double atuador_getNf(char s[6]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_atuador); 
	 if(strncmp(s,"anf",1)==0){
	 	aux = atuador_Nf; 
	 }
	 pthread_mutex_unlock( &exclusao_atuador); 
	 return aux; 
 }
 
