#ifndef BUFDUPLO_H
#define BUFDUPLO_H
#include <stdio.h>
#include <stdlib.h>

void bufduplo_insereLeituraTempo_Resposta( double leitura);

void bufduplo_guardaTempo_Resposta(double v_lido);

double *bufduplo_esperaBufferCheio_temp_resp( void);

#endif
