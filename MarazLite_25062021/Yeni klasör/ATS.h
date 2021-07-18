#ifndef __ATS_H
#define __ATS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
extern I2C_HandleTypeDef hi2c1;//i2c1 deklare edildi. it.c içindeki devre disi birakildi.

extern uint8_t sendDataAts[2];//Ats'ye yollanacak send dizisi
extern uint8_t receiveDataAts[2];//Ats'den alinacak receive dizi
extern uint16_t devAdressAts;//Ats kartimin i2c device adresi
extern uint8_t sayac;//atis sayisini bulunduran degisken
extern uint8_t vurulmaEsigi;//atis verisiyle beraber gelen o andaki vurus seviyesini tutan degisken
extern uint8_t birOncekiSayac;//Yeni atis olup olmadigi karsilastiracagimiz degisken
extern uint8_t sayacResetReceiveSecim;//Callback fonksiyonunda gönderilen transmit dönüs secimi yapabilmek icin degisken 
extern uint8_t ResetOnayDonus;//slave adresten reset isleminden sonra dönecek verinin tutulacagi degisken
extern uint8_t ResetOnayReturn;//mainde reset fonksiyonu cagrildiktan sonra dondurulecek degisken (1 ise reset onaylandi,0 ise reset onaylanmadi)


extern uint8_t sendDataMkn[2];//MKN kartina yollanacak send dizisi
extern uint8_t receiveDataMkn[2];//MKN kartindan alinacak receive dizisi
extern uint16_t devAdressMkn;//MKN kartinin i2c device adresi
extern uint8_t MankenDurum;//Manken kartindan gelecek veriyi sakladigimiz degisken(95 ise Manken hareket basladi,96 ise manken mesgul)

extern uint16_t devAdressControl;//Callback fonksiyonunda hangi karttan veri gelecegini tuttugumuz degisken.


void AtsMkninit(void);//Ats ve Mkn için kullanilacak degiskenlerin ilk degerlerinin atamasinin yapildigi fonksiyon 
uint8_t sayacGet(void);//Mainde kullanilmak için olusturulan ve sayacin degerini alan ve sayacin degerinin döndüren fonksiyon.
uint8_t sayacReset(uint8_t);//Mainden sayaci resetlemek için kullanilan fonksiyon.0 veya 1 donderir.Argüman olarak 1 alirsa reset sinyali geldigi varsayilir.



#ifdef __cplusplus
}
#endif

#endif
