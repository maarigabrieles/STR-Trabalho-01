#ifndef SENSOR_H
#define SENSOR_H

void sensor_putTa( double v_lido);
double sensor_getTa(char s[5]);

void sensor_putT( double v_lido);
double sensor_getT(char s[5]);

void sensor_putTi( double v_lido);
double sensor_getTi(char s[5]);

void sensor_putNo( double v_lido);
double sensor_getNo(char s[5]);

void sensor_putH( double v_lido);
double sensor_getH(char s[5]);

void sensor_alarme( double limite);

#endif



