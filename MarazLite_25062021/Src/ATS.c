#include "ATS.h"


uint8_t sendDataAts[2];
uint8_t receiveDataAts[2];
uint16_t devAdressAts;
uint8_t sayac;
uint8_t vurulmaEsigi;
uint8_t birOncekiSayac;
uint8_t sayacResetReceiveSecim;
uint8_t ResetOnayDonus;
uint8_t ResetOnayReturn;


uint8_t sendDataMkn[2];
uint8_t receiveDataMkn[2];
uint16_t devAdressMkn;
uint8_t MankenDurum;

uint16_t devAdressControl;

uint8_t esikSetReceiveSecim;
uint8_t setOnayDonus;
uint8_t setOnayReturn;
//uint8_t receiveDataAtsSet[1];
//uint8_t setOnayDonusDeneme;


/*Masterden Transmit islemi yapildiktan sonra girecegi blok*/
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c1){
		
		if(devAdressControl==devAdressAts){
				HAL_I2C_Master_Receive_IT(hi2c1,devAdressAts<<1,receiveDataAts,2);//Ats'ye transmit yapildiysa girer.(2 byte veri gelecek.Ilk byte sayac,ikinci  byte vurulan esik)
		}
	  else if(devAdressControl==devAdressMkn){
				HAL_I2C_Master_Receive_IT(hi2c1,devAdressMkn<<1,receiveDataMkn,1);//Mkn'ye transmit yapildiysa girer.(Tek byte gelir.95 veya 96.)
		}
		else if(sayacResetReceiveSecim==1){
				HAL_I2C_Master_Receive_IT(hi2c1,devAdressAts<<1,receiveDataAts,1);//Ats'ye reset transmit'i yapildiysa girer.(Tek byte gelir.31 olursa onay dönmüs olur.)
		}
		else if(esikSetReceiveSecim==1){
				HAL_I2C_Master_Receive_IT(hi2c1,devAdressAts<<1,receiveDataAts,1);//Ats'ye set transmit'i yapildiysa girer.(Tek byte gelir.32 olursa onay dönmüs olur.)
		}
					
}
/*Master Receive islemi tapildiktan sonra girecigi blok*/
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c1){
	   
		if(devAdressControl==devAdressAts){ //Ats Receive yapildiktan sonra girer.
						 birOncekiSayac=sayac;
					   sayac=receiveDataAts[0];
					   vurulmaEsigi=receiveDataAts[1];	
						 receiveDataAts[0]=0;
						 receiveDataAts[1]=0;
						 devAdressControl=0;
						 if(birOncekiSayac!=sayac){
								//devAdressControl=devAdressMkn;
							  //sendDataMkn[0]=81;
								//HAL_I2C_Master_Transmit_IT(hi2c1,devAdressMkn<<1,sendDataMkn,1);//Yeni atis oldugu tespit edildi.Mankene tüm senaryon(81) verisi yollaniyor. 
						 }
						 else{
								sayac=birOncekiSayac;
						 }
						 
		 }
		
		else if(devAdressControl==devAdressMkn){//Mkn Receive yapildiktan sonra girer.
				MankenDurum=receiveDataMkn[0];
				receiveDataMkn[0]=0;
				receiveDataMkn[1]=0;
				devAdressControl=0;
		}
		else if(sayacResetReceiveSecim==1){ //Ats'ye reset receive yapildiktan sonra girer.
				sayacResetReceiveSecim=0;
				ResetOnayDonus=receiveDataAts[0];
				receiveDataAts[0]=0;
				receiveDataAts[1]=0;
				if(ResetOnayDonus==31){
					ResetOnayDonus=0;
					sayac=0;
					ResetOnayReturn=1;
				}
				else{
					ResetOnayDonus=0;
					ResetOnayReturn=0;
				}
		}
		else if(esikSetReceiveSecim==1){ //Ats'ye set receive yapildiktan sonra girer.
				esikSetReceiveSecim=0;
				setOnayDonus=receiveDataAts[0];
				receiveDataAts[0]=0;
				receiveDataAts[1]=0;
				/*setOnayDonus=receiveDataAtsSet[0];
				receiveDataAtsSet[0]=0;*/
				//setOnayDonusDeneme=0;
				//setOnayDonusDeneme=setOnayDonus;
				if(setOnayDonus==32){
					setOnayDonus=0;
					setOnayReturn=1;
				}
				else{
					setOnayDonus=0;
					setOnayReturn=0;	
				}	
		}	
}


 uint8_t sayacGet(void){
	return sayac;
}


uint8_t sayacReset(uint8_t ResetVeri){
	if(ResetVeri==1){
		sendDataAts[0]=21;
		sayacResetReceiveSecim=1;//receive'de secim yapabilmek icin kullanilacak.
		HAL_I2C_Master_Transmit_IT(&hi2c1,devAdressAts<<1,sendDataAts,1);//Ats'ye reset verisi transmit ediliyor.(21 verisi.)
		return ResetOnayReturn;
	}
	else{
		return 0;
	}
}


uint8_t esikSetleme(uint8_t esikSetVeri,uint8_t esikSeviye){
	if(esikSetVeri==22){
		sendDataAts[0]=esikSetVeri;
		sendDataAts[1]=esikSeviye;
		esikSetReceiveSecim=1;//receive'de secim yapabilmek icin kullanilacak.
		HAL_I2C_Master_Transmit_IT(&hi2c1,devAdressAts<<1,sendDataAts,2);//Ats'ye set verileri transmit ediliyor.(ilk veri 22, ikinci veri 1-10 arasinda bir sayi)
		return setOnayReturn;
	}
	else{
		return 0;
	}	
}


void AtsMkninit(void)
{ 
devAdressAts=0x01;
sayac=0;
vurulmaEsigi=0;
birOncekiSayac=0;
devAdressMkn=0x02;
MankenDurum=0;
devAdressControl=0;
sayacResetReceiveSecim=0;
ResetOnayDonus=0;
ResetOnayReturn=0;
esikSetReceiveSecim=0;
setOnayDonus=0;
setOnayReturn=0;
//setOnayDonusDeneme=0;
}




