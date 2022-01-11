/*	LIVRO FUNDAMENTOS DOS SISTEMAS DE TEMPO REAL
*
*	Ilustra a criacao de threads e uso de mutex
*	Compilar com:	
*	ou
*			gcc -o monitor monitor.c sensor.c bufduplo.c -lpthread
*
*/

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "sensor.h"
#include "socket.h"
#include "bufduplo.h"
#include "tela.h"
#include "atuadores.h"
#include "controles.h"

#define NSEC_PER_SEC    (1000000000) 	// Numero de nanosegundos em um segundo

double usuario_temp = 0;
double usuario_nivel = 0;
double atraso_tempo_temperatura;
double atraso_tempo_nivel;

/*************************************************************************/

/***
*	Thread que mostra status na tela
***/
void thread_mostra_status(void) {
	double ta, t, ti, no, h, ni, q, na, nf;
	while(1){
		//Pega os valores dos sensores
		ta = sensor_getTa("ta");
		t = sensor_getT("t");
		ti = sensor_getTi("ti");
		no = sensor_getNo("no");
		h = sensor_getH("h");
		
		//Pega os valores dos atuadores
		ni = atuador_getNi("ni");
		q = atuador_getQ("q");
		na = atuador_getNa("na");
		nf = atuador_getNf("nf"); 
		
		aloca_tela();
		system("tput reset");
		printf("------------------------------------\n");
		printf("Temperatura do ar (Ta)--> %.2lf\n", ta);
		printf("Temperatura interior (T)--> %.2lf\n", t);
		printf("Temperatura da agua que entra (Ti)--> %.2lf\n", ti);
		printf("Fluxo de agua de saida (No)--> %.2lf\n", no);
		printf("Altura do nivel (H)--> %.2lf\n", h);
		printf("Fluxo de agua de entrada (Ni)--> %.2lf\n", ni);
		printf("Fluxo de calor (Q)--> %.2lf\n", q);
		printf("Fluxo de agua aquecida (Na)--> %.2lf\n", na);
		printf("Fluxo de agua de saida (Nf)--> %.2lf\n", nf); 
		printf("------------------------------------\n");
		libera_tela();
		sleep(1);
		}
}

/***
*	Thread que le sensor
***/
void thread_le_sensor(void) {
	struct timespec t, t_fim;
	long int periodo = 10e6; 	// 50e6ns ou 50ms
	
	//Le a hora atual, coloca em t
	clock_gettime(CLOCK_MONOTONIC ,&t);
	while(1){
		//Espera ate o inicio do proximo periodo
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
		
		//Envia mensagem via canal de comunicaçao para receber valores de sensores
		sensor_putTa(msg_socket("sta0"));
		sensor_putT(msg_socket("st-0"));
		sensor_putTi(msg_socket("sti0"));
		sensor_putNo(msg_socket("sno0"));
		sensor_putH(msg_socket("sh-0"));
			
		// Calcula inicio do proximo periodo
		t.tv_nsec += periodo;
		while (t.tv_nsec >= NSEC_PER_SEC) {
			t.tv_nsec -= NSEC_PER_SEC;
			t.tv_sec++;
		}	
	}
}

//Thread para o Controle de Temperatura
void thread_controle_Temperatura(void){
	struct timespec t, t_fim;
	long int periodo = 50e6; 	// 50ms
	double temp_aux;
	double temperatura_lida = 0;
	
	// Le a hora atual, coloca em t
	clock_gettime(CLOCK_MONOTONIC ,&t);

	// Tarefa periodica iniciará em 1 segundo
	t.tv_sec++;

	while(1) {
		// Espera ateh inicio do proximo periodo
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
		
		
		//VERIFICAR
    	// Inicio da operação    	
    	temp_aux = sensor_getT("t");
    	temperatura_lida = temperatura_getT("t");

    	if (temp_aux<temperatura_lida){ //aumentar temp
    	    //printf("temperatura menor do q a escolhida pelo usuario %.2lf\n",temperatura_desejada);
    		atuador_putQ(msg_socket("ana10.7"));
    		
		}
		else if (temp_aux>temperatura_lida){ //diminuir temp
    		//printf("temperatura maior do q a escolhida pelo usuario %.2lf\n",temperatura_desejada);
	    	atuador_putNi(msg_socket("ani00.0"));
    		
    		atuador_putNa(msg_socket("ana100.0"));
	    	
	    	atuador_putNf(msg_socket("anf50.0"));
		}

		   	
		// Le a hora atual, coloca em t_fim
		clock_gettime(CLOCK_MONOTONIC ,&t_fim);	
			
		// Calcula o tempo de resposta observado em microsegundos
		atraso_tempo_temperatura = 1000000*(t_fim.tv_sec - t.tv_sec)   +   (t_fim.tv_nsec - t.tv_nsec)/1000;
		//bufduplo_insereLeitura_tempo_resposta(atraso_fim_temperatura);
		
		// Calcula inicio do proximo periodo
		t.tv_nsec += periodo;
		while (t.tv_nsec >= NSEC_PER_SEC) {
			t.tv_nsec -= NSEC_PER_SEC;
			t.tv_sec++;
		}
	}
}

//Thread para o Controle de Nivel da água
void thread_controle_Nivel(void){
	struct timespec t, t_fim;
	long int periodo = 70e6; 	// 70ms
	double nivel_aux;
	double nivel_lido = 0;
	
	// Le a hora atual, coloca em t
	clock_gettime(CLOCK_MONOTONIC ,&t);

	// Tarefa periodica iniciará em 1 segundo
	t.tv_sec++;

	while(1) {
		// Espera ateh inicio do proximo periodo
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
		
		
		//VERIFICAR
    	// Inicio da operação    	
    	nivel_aux = sensor_getH("h");
    	nivel_lido = nivelA_getH("h");

    	if (nivel_aux<nivel_lido){ //aumentar temp
    	    //printf("temperatura menor do q a escolhida pelo usuario %.2lf\n",temperatura_desejada);
    		atuador_putNi(msg_socket("ani70.0"));
    		
    		atuador_putNf(msg_socket("anf00.0"));
    		
		}
		else if (nivel_aux>nivel_lido){ //diminuir temp
    		//printf("temperatura maior do q a escolhida pelo usuario %.2lf\n",temperatura_desejada);
	    	atuador_putNi(msg_socket("ani00.0"));
    	    		    	
	    	atuador_putNf(msg_socket("anf70.0"));
		}

		   	
		// Le a hora atual, coloca em t_fim
		clock_gettime(CLOCK_MONOTONIC ,&t_fim);	
			
		// Calcula o tempo de resposta observado em microsegundos
		atraso_tempo_nivel = 1000000*(t_fim.tv_sec - t.tv_sec)   +   (t_fim.tv_nsec - t.tv_nsec)/1000;
		//bufduplo_insereLeitura_tempo_resposta(atraso_fim_temperatura);
		
		// Calcula inicio do proximo periodo
		t.tv_nsec += periodo;
		while (t.tv_nsec >= NSEC_PER_SEC) {
			t.tv_nsec -= NSEC_PER_SEC;
			t.tv_sec++;
		}
	}
}
/***
*	Thread que dispara alarme
***/
void thread_alarme(void) {
	while(1){			
		sensor_alarme(30);		
		aloca_tela();
		printf("=========================\n");
		printf("		ALARME!!!\n");
		printf("==========================\n");
		libera_tela();
		sleep(1);	
	}
}

//Thread para ler do usuario os dados de referência da temperatura e do nivel de agua 
void thread_ler_usuario(void){
	printf("Digite um valor de referencia para a Temperatura:\n");
	scanf("%lf", &usuario_temp);
	temperatura_putT(usuario_temp);
	
	printf("Digite um valor de referencia para o nivel de agua:\n");
	scanf("%lf", &usuario_nivel);
	nivelA_putH(usuario_nivel);
}

//Inicio chamada da operação
int main( int argc, char *argv[]) {
	
	cria_socket(argv[1], atoi(argv[2]));
	
    pthread_t t1, t2, t3, ler_usuario, controle_temp, controle_nivel;
    
    pthread_create(&ler_usuario, NULL, (void *) thread_ler_usuario, NULL);
    pthread_join( ler_usuario, NULL);
    pthread_create(&t1, NULL, (void *) thread_mostra_status, NULL);
    pthread_create(&t2, NULL, (void *) thread_le_sensor, NULL);
    pthread_create(&t3, NULL, (void *) thread_alarme, NULL);
    pthread_create(&controle_temp, NULL, (void *) thread_controle_Temperatura, NULL);
    pthread_create(&controle_nivel, NULL, (void *) thread_controle_Nivel, NULL);
    

	
	pthread_join( t1, NULL);
	pthread_join( t2, NULL);
	pthread_join( t3, NULL);
	pthread_join( controle_temp, NULL);
	pthread_join( controle_nivel, NULL);
}
