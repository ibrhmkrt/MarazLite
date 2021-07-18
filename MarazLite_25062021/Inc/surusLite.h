#ifndef __SURUSLITE_H
#define __SURUSLITE_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "main.h"
#include <math.h>
#include <stdlib.h>


#define hata_kodu_Lite 0
#define onay_kodu_Lite 1

/*Kullancidan gelen tanimsiz bolge sinirlari*/
#define Lite_ileri_baslangic_degeri 140 
#define Lite_geri_baslangic_degeri 110

#define sagDonus_baslangic_degeri 140 
#define solDonus_baslangic_degeri 110


/*Driver yön pinleri ve sifirlamalari*/
#define sagTekerileri 0x4000
#define sagTekergeri 0x8000
#define sagYonSifirlama 0x3FFF

#define solTekerileri 0x0080
#define solTekergeri 0x0200
#define solYonSifirlama 0xFD7F

/*sag ve sol teker ileri, geri ,yon yok degerleri*/
#define ileri_Lite 1
#define geri_Lite 0
#define yon_yok_Lite 2




/*Tekerleri verilecek pwm sinirlari ve ivme degerleri*/
#define sagTeker_pwm_max_yuzde 100
#define sagTeker_pwm_min_yuzde 5
#define sagTeker_pwm_artis_carpani 2
#define sagTeker_hiz_cozunurlugu 125

#define solTeker_pwm_max_yuzde 100
#define solTeker_pwm_min_yuzde 5
#define solTeker_pwm_artis_carpani 2
#define solTeker_hiz_cozunurlugu 125


extern int gelenHiz;//Joystick hiz degeri atanacak degisken
extern int gelenYon;//Joystick yon degeri atanacak degisken


extern int solTekerHiz;//islem yapildiktan sonra elde edilen veri
extern int sagTekerHiz;//islem yapildiktan sonra elde edilen veri

extern unsigned char sag_surus_yonu;//islemden cikan sonuca göre - veya + sina göre yon degiskeni
extern unsigned char sol_surus_yonu;//islemden cikan sonuca göre - veya + sina göre yon degiskeni

extern unsigned char istenilen_solTekerHiz;//pwm icin islemden çikan degeri mapleyip atacagimiz degisken
extern unsigned char istenilen_sagTekerHiz;//pwm icin islemden çikan degeri mapleyip atacagimiz degisken

extern unsigned char solTekerPwm;//motora verilecek pwm
extern unsigned char sagTekerPwm;//motora verilecek pwm

extern unsigned int aracLite_durdurma_sayac;//atis geldiginde araç durdurulacak.

unsigned char surusLite(unsigned char*);//mainden adres baslangiciyla cagrilan fonk. (Hiz verisi tanimli bolge kontrol yapilip -125 yapilacak.)
unsigned char motorlariSur(int,int);
unsigned char motorlariDurdur(void);


#endif