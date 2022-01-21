#include <stdio.h>
#include <stdlib.h>

#define ARQUIVO_AMOSTRAS "dados_tempo_resposta_buf.txt"

//Carrega o arquivo de dados_tempo_resposta_buf
int carregar_serie( const char * arq, double * s[], int * n )
{
    FILE * fp = NULL;
    char amostra[ 100 ] = {0};
    double * p = NULL;
    int i = 0;

    fp = fopen( arq, "r" );

    if(!fp)
        return -1;

    while( fgets( amostra, sizeof(amostra), fp ) )
    {
        i++;
        p = (double*) realloc( p, i * sizeof(double));
        sscanf( amostra, "%lf", p + i - 1 );
    }

    fclose(fp);

    *s = p;
    *n = i;

    return 0;
}

//Calcula o valor medio dos dadsos lido
double media( double s[], int n )
{
    double sum = 0.0;
    int i = 0;

    for( i = 0; i < n; i++ )
        sum += s[i];

    return sum / n;
}

//Calcula o valor maximo dos dados lido
double valor_maximo( double s[], int n){
	double max = 0.0;
	int i = 0;
	
	for(i = 0; i < n; i++){
		if(s[i] > max){
			max = s[i];
		}
	}
	return max;
}

//calcula o valor minimo dos dados lido
double valor_minimo( double s[], int n){
	double min = 0.0;
	int i = 0;
	
	for(i = 0; i < n; i++){
		if(s[i] < min){
			min = s[i];
		}
	}
	return min;
}

//executa main
int main( void )
{
    double * serie = NULL;
    int n = 0;

    if( carregar_serie( ARQUIVO_AMOSTRAS, &serie, &n ) < 0 )
    {
        printf("Erro ao abrir arquivo de tempo de resposta para leitura: '%s'\n", ARQUIVO_AMOSTRAS );
        return 1;
    }

    printf( "Media  : %f\n", media( serie, n ) );
    printf( "Valor maximo: %f\n", valor_maximo( serie, n ) );
	printf( "Valor minimo: %f\n", valor_minimo( serie, n ) );

    free(serie);

    return 0;
}
