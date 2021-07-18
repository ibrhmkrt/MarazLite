#ifndef __XBEE_H
#define __XBEE_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f1xx_hal.h"

#define hata_var 0
#define hata_yok 1

#define hata_kodu 0
#define hata_kodu_2 2
#define onay_kodu 1


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
extern unsigned int time_out_bitis;
extern unsigned int time_out_baslangic;
extern unsigned char veri_alma_basladimi;

unsigned char veri_alma_baslat_it(void);

unsigned char xbee(void);
unsigned char xbee_gonder(unsigned char* veri,int byte_sayisi);
unsigned char paket_dogrula(void);
unsigned char	xbee_uart_sifirlama(void);
#endif
