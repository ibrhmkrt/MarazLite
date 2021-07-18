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

#define fren_geri 1
#define fren_ileri 0

#define geri 1
#define ileri 0
#define yon_yok 2

#define min_hiz 25
#define max_hiz 120

#define geri_baslangic_degeri 112 //120 //-09.09.2020 yeni kumamda i�in
#define ileri_baslangic_degeri 132 //130 //09.09.2020 yeni kumamda i�in


#define direksiyon_sol_limit 1700 //1650
#define direksiyon_sag_limit 2600 //2550
#define direksiyon_hassasiyet_degeri 10
#define direksiyon_ivmesi 5// %5 ivmelenme hata degeri katina g�re

#define direksiyon_sola 0x4000
#define direksiyon_saga 0x8000
#define direksiyon_yon_sifirlama 0x3FFF

#define pwm_max_yuzde 100
#define pwm_min_yuzde 50
#define pwm_artis_carpani 25

#define BLDC_pwm_max_yuzde 75
#define BLDC_pwm_min_yuzde 25// %30, 3.3volt i�in ~1Volt'tur.
#define BLDC_pwm_artis_carpani 1
#define BLDC_max_rpm 3500
#define BLDC_hiz_cozunurlugu 128// map islemi i�in gelen  byte i�inde hiz i�in min ve max deger farki,120 yaklasik bir deger

#define RTC_periyot 0x07 //rpm �l��m� i�in RTC counter clock sinyal ayari, RTC_CNTR clock =  RTC clokck/(RTC_periyot+1), (0x07+1) i�in 4096hz
#define RTC_frekans 4096
#define max_rpm 2500
#define BLDC_sensor_tetikleme 10 //BLDC motorun bir turdaki hall sensor tetikleme sayisi
//gecen_zaman = bitis_zamani-baslangic_zamani
//RPM = 60 *( RTC_periyot / (gecen_zaman *  BLDC_sensor_tetikleme )  ) , 60 �arpani dakika i�in kullaniliyor

extern unsigned int baslangic_zamani;
extern unsigned int bitis_zamani;
extern unsigned int gecen_zaman;
extern unsigned int BLDC_RPM_sayac;
extern unsigned int BLDC_RPM;
extern unsigned char surus_yonu;
extern unsigned int bldc_hiz;
extern unsigned char istenilen_hiz;//y�zde �zerinden
extern unsigned char BLDC_pwm;
extern unsigned char BLDC_yonu;

extern unsigned int degisken;

extern unsigned char hiz;
extern unsigned char fren_motor;
extern unsigned char fren_son_durum;
extern unsigned char fren_veri[2];
extern unsigned char fren_veri_sayisi;
extern unsigned char fren_istenilen;
extern unsigned char fren_sol_durum;
extern unsigned char fren_sag_durum;
extern unsigned char uart3_kuyruk_ekle;


//28.05.2020 baslangic
extern unsigned int arac_durdurma_sayac;
//28.05.2020 bitis

extern unsigned int direksiyon_pozisyonu;
extern unsigned int direksiyon_istenilen;
//direksiyon i�in lm358 "-" ve "out" pinleri arasina 1Kohm(SON DENEME 220ohm)
//"-" ve "gnd" arasi 3.2kohm(SON DENEME 1Kohm)
//"+" girise PWM ve pull-down 10kohm
//besleme girisi 12V ve �zeri olacak.
//LM358 �ikis max= max_giris(3.3V)* (1+ (1K/3.2K))= 4.4V olacaktir.(220ohm/1kohm olarak g�ncellendi ve pcb �zerinde)

void direksiyon_kur(void);

void fren_durum_kontrol(void);

unsigned char surus(unsigned char*);
unsigned char bldc_sur(unsigned char);
unsigned char bldc_motor_calistir(unsigned char);
unsigned char bldc_motor_durdur(void);

unsigned char frenleme(unsigned char);

unsigned char direksiyon_cevir(unsigned char);
unsigned int mili_saniye(void);

#endif
