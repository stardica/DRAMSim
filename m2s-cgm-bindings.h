/*
 * m2s-cgm-bindings.h
 *
 *  Created on: Jan 25, 2016
 *      Author: stardica
 */

#ifndef M2S_CGM_BINDINGS_H_
#define M2S_CGM_BINDINGS_H_

void (*read_done_cpp)(unsigned int, long long unsigned, long long unsigned);
void (*write_done_cpp)(unsigned int, long long unsigned, long long unsigned);
void (*power_done_cpp)(double bgpower, double burstpower, double refreshpower, double actprepower);

#endif /*M2S_CGM_BINDINGS_H_*/
