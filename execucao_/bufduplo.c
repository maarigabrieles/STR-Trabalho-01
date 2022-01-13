/* MONITOR BUFFER DUPLOPARA TEMPO DE RESPOSTA*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define TAMBUF 100 

//Criação dos buffes para operação
static double buffer_0[TAMBUF]; 
static double buffer_1[TAMBUF];

//Criação das variaveis usadas
static int emuso = 0; 
static int prox_insercao = 0; 
static int gravar = -1;
static FILE* dados_arq;
static int cont = 0;
static int cont_buffer = 0;

static pthread_mutex_t exclusao_buff = PTHREAD_MUTEX_INITIALIZER; 
static pthread_cond_t buffer_cheio = PTHREAD_COND_INITIALIZER;

//Chamado pela thread insere leitura do tempo de resposta
void bufduplo_insereLeituraTempo_Resposta( double leitura) {
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

//Chamado pela thread para guardar em arquivo os dados do buffer do tempo de resposta

void bufduplo_guardaTempo_Resposta(double v_lido){
	
	dados_arq = fopen("dados_tempo_resposta_buf.txt", "a+");
	if(dados_arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
        exit(1);    
    }
	
   if(cont == 0){
		cont++;
		fprintf(dados_arq, "%4lf\n", v_lido);	
	}else if(cont == 1){
		cont = 0;
		fprintf(dados_arq, "%4lf\n", v_lido);	
	}
	
	fclose(dados_arq);
}

// Chamado pela thread que espera e enche o buffer
double *bufduplo_esperaBufferCheio_temp_resp( void) {
	double *buffer; 
	pthread_t cria_buff_duplo;
	pthread_mutex_lock( &exclusao_buff); 
	while( gravar == -1) 
		pthread_cond_wait( &buffer_cheio, &exclusao_buff);
	if(gravar==0) 
		buffer = buffer_0; 
	else 
		buffer = buffer_1; 
	gravar = -1; 
	pthread_mutex_unlock( &exclusao_buff); 

	while(cont_buffer < TAMBUF){
		bufduplo_guardaTempo_Resposta(buffer[cont_buffer]);
		cont_buffer++;
	}
	cont_buffer = 0;
		
	pthread_create(&cria_buff_duplo, NULL, (void *) bufduplo_esperaBufferCheio_temp_resp, NULL);
	pthread_join(cria_buff_duplo, NULL);
}

