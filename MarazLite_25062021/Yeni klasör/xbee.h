#ifndef __XBEE_H
#define __XBEE_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f1xx_hal.h"

#define tampon_dolu 1
#define tampon_bos 0
#define paket_var 1
#define paket_yok 0

#define paket_dogrulama_baslangic 254
#define paket_dogrulama_bitis 255

#define xbee_tampon_boyutu 6 //kumandadan gelen veri miktari simdilik 6 byte
#define xbee_tx_tampon_boyutu 1 //kumandadan gelen veri miktari simdilik 6 byte


extern unsigned char xbee_veri_tamponu[xbee_tampon_boyutu];
extern unsigned char xbee_tx_tamponu[xbee_tx_tampon_boyutu];
extern short int xbee_tampon_index;
extern unsigned char xbee_tampon_durumu;
extern unsigned char yeni_paket_var;

unsigned char veri_alma_baslat_it(void);

unsigned char xbee(void);
unsigned char gonder(unsigned char* veri,int byte_sayisi);
unsigned char paket_dogrula(void);
#endif
