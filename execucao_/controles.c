//MONITOR PARA CONTROLE DE TEMPERATURA E NIVEL DA ÁGUA

#include <math.h>
#include <pthread.h>
#include <string.h>


static pthread_mutex_t exclusao_controls = PTHREAD_MUTEX_INITIALIZER; 
static pthread_cond_t alarme = PTHREAD_COND_INITIALIZER; 

//Variaveis globais para guardar valores lidos
static double temperatura_lida = 0; 
static double nivel_lido = 0; 

static double limite_atual = HUGE_VAL;

//-------------------------------------------------
/* MONITOR DA TEMPERATURA SOLICITADA */
//-------------------------------------------------
/* Chamado pela thread que le o valor da temperatura e atualizar o valor do monitor referente ao valor lido */
 void temperatura_putT( double v_lido) {
	 pthread_mutex_lock(&exclusao_controls); 
	 temperatura_lida = v_lido; 
	 if( temperatura_lida >= limite_atual) 
	 	pthread_cond_signal( &alarme); 
	 pthread_mutex_unlock(&exclusao_controls); 
 }
 
 /* Ler o valor do monitor referente a temperatura */ 
 double temperatura_getT(char s[5]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_controls); 
	 if(strncmp(s,"t",1)==0){
	 	aux = temperatura_lida; 
	 }
	 pthread_mutex_unlock( &exclusao_controls); 
	 return aux; 
 }
  //--------------------------------------------------
 /* MONITOR DO NIVEL DE AGUA SOLICITADO */
 //---------------------------------------------------
/* Chamado pela thread que le o nivelda agua e atualizar o valor do monitor referente ao valor lido */
  void nivelA_putH( double v_lido) {
	 pthread_mutex_lock(&exclusao_controls); 
	 nivel_lido = v_lido; 
	 if( nivel_lido >= limite_atual) 
	 	pthread_cond_signal( &alarme); 
	 pthread_mutex_unlock(&exclusao_controls); 
 }
 
 /* Ler o valor do monitor referente ao nivel da agua */ 
 double nivelA_getH(char s[5]) {
	 double aux; 
	 pthread_mutex_lock( &exclusao_controls); 
	 if(strncmp(s,"h",1)==0){
	 	aux = nivel_lido; 
	 }
	 pthread_mutex_unlock( &exclusao_controls); 
	 return aux; 
 }
