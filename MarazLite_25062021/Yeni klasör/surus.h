#ifndef __SURUS_H
#define __SURUS_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "main.h"

#define hata_var 0
#define hata_yok 1

#define hata_kodu 0
#define onay_kodu 1

#define hatali_hiz_max 250
#define hatali_hiz_min 5

#define geri 1
#define ileri 0

#define min_hiz 25
#define max_hiz 200

#define geri_baslangic_degeri 115
#define ileri_baslangic_degeri 140

#define RTC_periyot 0x07 //rpm ölçümü için RTC counter clock sinyal ayari, RTC_CNTR clock =  RTC clokck/(RTC_periyot+1), (0x07+1) için 4096hz
#define RTC_frekans 4096
#define max_rpm 2500
#define BLDC_sensor_tetikleme 10 //BLDC motorun bir turdaki hall sensor tetikleme sayisi
//gecen_zaman = bitis_zamani-baslangic_zamani
//RPM = 60 *( RTC_periyot / (gecen_zaman *  BLDC_sensor_tetikleme )  ) , 60 çarpani dakika için kullaniliyor

extern unsigned int baslangic_zamani;
extern unsigned int bitis_zamani;
extern unsigned int gecen_zaman;
extern unsigned int BLDC_RPM;
extern unsigned char surus_yonu;
extern unsigned int bldc_hiz;

extern unsigned int degisken;

extern unsigned char hiz;
extern unsigned char fren_motor;
extern unsigned char fren_son_durum;

extern unsigned int direksiyon_pozisyonu;


unsigned char surus(unsigned char*);
unsigned char bldc_sur(unsigned char);
unsigned char bldc_motor_calistir(unsigned char);

unsigned char frenleme(unsigned char);

unsigned char direksiyon_cevir(unsigned char);
unsigned int mili_saniye(void);

#endif
