#include "surusLite.h"
#include <math.h>
#include <stdlib.h>

int gelenHiz;//Joystick hiz degeri atanacak degisken
int gelenYon;//Joystick yon degeri atanacak degisken

int solTekerHiz;//yüzde üzerinden pwm gonderilecek veri
int sagTekerHiz;;//yüzde üzerinden pwm gonderilecek veri

unsigned char sag_surus_yonu;//islemden cikan sonuca göre - veya + sina göre yon degiskeni
unsigned char sol_surus_yonu;//islemden cikan sonuca göre - veya + sina göre yon degiskeni

unsigned char istenilen_solTekerHiz;//pwm icin islemden çikan degeri mapleyip atacagimiz degisken
unsigned char istenilen_sagTekerHiz;//pwm icin islemden çikan degeri mapleyip atacagimiz degisken

unsigned int aracLite_durdurma_sayac=0;

unsigned char solTekerPwm=0;//motora verilecek pwm
unsigned char sagTekerPwm=0;//motora verilecek pwm

unsigned char surusLite(unsigned char* veri)
{
	if(veri[0]<Lite_geri_baslangic_degeri || veri[0]>Lite_ileri_baslangic_degeri){//Hiz joystick degeri tanimli alanda
		gelenHiz=veri[0]-125;
		/*if(veri[1]<solDonus_baslangic_degeri || veri[1]>sagDonus_baslangic_degeri){//Yon joystick degeri tanimli alanda
			veri[1]=veri[1]-125;
		}
		else{//yon joystick degeri tanimsiz alanda
			veri[1]=0;
		}*/
		gelenYon=veri[1]-125;
		return motorlariSur(gelenHiz,gelenYon);
	}
	else{//Hiz joystick degeri tanimsiz alanda
		
		/*Yon verisi Tanimli alan*/
		/*if(veri[1]<solDonus_baslangic_degeri || veri[1]>sagDonus_baslangic_degeri){	
		}
		else{	
		}*/
		motorlariDurdur();
		return hata_kodu_Lite;
	}
		
}



unsigned char motorlariSur(int gelen_hiz,int gelen_yon){
	solTekerHiz=gelen_hiz * cos(((gelen_yon - abs(gelen_yon))/2)/(gelen_hiz + (375.0/gelen_hiz)));
	sagTekerHiz=gelen_hiz * cos(((abs(gelen_yon) + gelen_yon)/2)/(gelen_hiz + (375.0/gelen_hiz)));
	
	if(solTekerHiz > 0){
		sol_surus_yonu=ileri_Lite;
		GPIOA->ODR&=solYonSifirlama;	
		GPIOA->ODR|=solTekerileri;	
		
	}
	else if(solTekerHiz < 0){
		sol_surus_yonu = geri_Lite;
		solTekerHiz=abs(solTekerHiz);
		GPIOA->ODR&=solYonSifirlama;	
		GPIOA->ODR|=solTekergeri;	
	}
	/*else{
		sol_surus_yonu = yon_yok_Lite;
	}*/
	
	
	if(sagTekerHiz > 0){
		sag_surus_yonu=ileri_Lite;
		GPIOB->ODR&=sagYonSifirlama;
		GPIOB->ODR|=sagTekerileri;		
	}
	else if(sagTekerHiz < 0){
		sag_surus_yonu = geri_Lite;
		sagTekerHiz=abs(sagTekerHiz);
		GPIOB->ODR&=sagYonSifirlama;
		GPIOB->ODR|=sagTekergeri;	
	}
	/*else{
		sag_surus_yonu = yon_yok_Lite;
	}*/
	
	istenilen_solTekerHiz=(solTekerHiz*(solTeker_pwm_max_yuzde-solTeker_pwm_min_yuzde)/solTeker_hiz_cozunurlugu) + solTeker_pwm_min_yuzde;
	istenilen_sagTekerHiz=(sagTekerHiz*(sagTeker_pwm_max_yuzde-sagTeker_pwm_min_yuzde)/sagTeker_hiz_cozunurlugu) + sagTeker_pwm_min_yuzde;
	
	
	if(solTekerPwm==0){
			solTekerPwm=solTeker_pwm_min_yuzde;
	}
	
	
	if(sagTekerPwm==0){
			sagTekerPwm=sagTeker_pwm_min_yuzde;
	}
	
	TIM2->ARR=49;
	TIM2->CR1|=1;
	HAL_GPIO_WritePin(FREN_AKTIF_GPIO_Port,FREN_AKTIF_Pin,1);
	
}


unsigned char motorlariDurdur(void){
	solTekerHiz=0;
	sagTekerHiz=0;
	gelenHiz=0;
	gelenYon=0;
	istenilen_solTekerHiz=0;
	istenilen_sagTekerHiz=0;
	sol_surus_yonu=yon_yok_Lite;
	sag_surus_yonu=yon_yok_Lite;
	HAL_GPIO_WritePin(FREN_AKTIF_GPIO_Port,FREN_AKTIF_Pin,0);
	TIM3->CCR1=0;
	TIM3->CCR2=0;
	
	return onay_kodu_Lite;
}


