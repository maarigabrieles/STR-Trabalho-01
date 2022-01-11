#ifndef BUFDUPLO_H
#define BUFDUPLO_H
#include <stdio.h>
#include <stdlib.h>

void bufduplo_insereLeitura( long leitura);
void bufduplo_guardaTempo_espera(double v_lido);
double *bufduplo_esperaBufferCheio( void);

#endif
