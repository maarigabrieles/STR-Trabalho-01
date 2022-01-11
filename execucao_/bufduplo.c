/* Monitor buffer duplo, no arquivo bufduplo.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define TAMBUF 100 

static double buffer_0[TAMBUF]; 
static double buffer_1[TAMBUF];

static int emuso = 0; 
static int prox_insercao = 0; 
static int gravar = -1;
static FILE* dados_arq;

static pthread_mutex_t exclusao_buff = PTHREAD_MUTEX_INITIALIZER; 
static pthread_cond_t buffer_cheio = PTHREAD_COND_INITIALIZER;

void bufduplo_insereLeitura( double leitura) {
	pthread_mutex_lock( &exclusao_buff); 
	if( emuso == 0) 
		buffer_0[prox_insercao] = leitura; 
	else 
		buffer_1[prox_insercao] = leitura; 
	++prox_insercao; 
	if( prox_insercao == TAMBUF){ 
		gravar = emuso; 
		emuso = (emuso + 1)% 2; 
		prox_insercao = 0; 
		pthread_cond_signal( &buffer_cheio); 
	} 
	pthread_mutex_unlock( &exclusao_buff);
}

//Função para guardar em arquivo os dados do buffer do tempo de resposta

void bufduplo_guardaTempo_espera(double v_lido){
	
	printf("\nMedicoes de Tempo de Espera do buffer\n\n");
	
	dados_arq = fopen("dados_tempo_resposta_buf.txt", "w");
	if(dados_arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
        exit(1);    
    }
	
	for( int i=0; i< TAMBUF; i++){
		if(emuso == 0){
			//buffer_0[i] = v_lido;
			printf("Tempo de execucao=%4lfus\n", v_lido );
			fprintf(dados_arq, "%4lf\n", v_lido);	
		}else {
			//buffer_1[i] = v_lido;
			printf("Tempo de execucao=%4lfus\n", v_lido);
			fprintf(dados_arq, "%4lf\n", v_lido);	
		}
	}
	fclose(dados_arq);
}
double *bufduplo_esperaBufferCheio( void) {
	double *buffer; 
	pthread_mutex_lock( &exclusao_buff); 
	while( gravar == -1) 
		pthread_cond_wait( &buffer_cheio, &exclusao_buff);
	if(gravar==0) 
		buffer = buffer_0; 
	else 
		buffer = buffer_1; 
	gravar = -1; 
	pthread_mutex_unlock( &exclusao_buff); 
	return buffer; 
}

