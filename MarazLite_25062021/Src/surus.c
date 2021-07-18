#include "surus.h"

unsigned int degisken;
unsigned char surus_yonu;
unsigned char hiz;
unsigned char fren_motor;
unsigned char fren_son_durum=1;
unsigned int direksiyon_pozisyonu;
unsigned int direksiyon_istenilen;

unsigned int bldc_hiz=0;
unsigned int baslangic_zamani=0;
unsigned int bitis_zamani=0;
unsigned int gecen_zaman=0;
unsigned int BLDC_RPM=0;
unsigned char istenilen_hiz=0;
unsigned char BLDC_pwm=0;
unsigned char BLDC_yonu;
unsigned int BLDC_RPM_sayac=0;

unsigned char fren_veri[2];
unsigned char fren_veri_sayisi=0;
unsigned char fren_istenilen=2;
unsigned char fren_sag_durum;
unsigned char fren_sol_durum;
unsigned char uart3_kuyruk_ekle=0;

extern UART_HandleTypeDef huart3;

extern UART_HandleTypeDef huart2;

//28.05.2020 baslangic
unsigned int arac_durdurma_sayac=0;
//28.05.2020 bitis

unsigned char surus(unsigned char* veri)
{
	gecen_zaman=250-veri[1];//
	direksiyon_cevir(gecen_zaman);
	return bldc_sur(veri[0]);//
}

unsigned char bldc_sur(unsigned char gelen_hiz)
{
	if(gelen_hiz>ileri_baslangic_degeri)
	{
		surus_yonu=ileri;
		gelen_hiz=gelen_hiz-127;
		//gelen_hiz+=35;
	}
	else if(gelen_hiz<geri_baslangic_degeri)
	{
		surus_yonu=geri;
		gelen_hiz=127-gelen_hiz;
		//gelen_hiz+=40;
	}
	else if(gelen_hiz>250)
	{
		bldc_motor_durdur();
		return hata_kodu;
	}
	else
	{
		bldc_motor_durdur();
		return hata_kodu;
	}
	return bldc_motor_calistir(gelen_hiz);
}

unsigned char frenleme(unsigned char fren_yonu)
{
	HAL_GPIO_WritePin(BLDC_fren_pin_GPIO_Port,BLDC_fren_pin_Pin,fren_yonu);//
	fren_durum_kontrol();
	/*if(fren_yonu==fren_istenilen)
	{
		__nop();
	}
	else
	{*/
		fren_istenilen=fren_yonu;
		if(fren_yonu==ileri)
		{
			/*fren_veri[0]=50;
			fren_veri[1]=51;*/
			if(fren_sag_durum!=ileri)
			{
				fren_veri[0]=1;//127
			}
			else
			{
				fren_veri[0]=64;
			}
			if(fren_sol_durum!=ileri)
			{
				fren_veri[1]=255;
			}
			else
			{
				fren_veri[1]=192;
			}
		}
		else
		{
			//fren_veri[0]=64;
			if(fren_sag_durum!=geri)
			{
				fren_veri[0]=127;//127
			}
			else
			{
				fren_veri[0]=64;
			}
			if(fren_sol_durum!=geri)
			{
				fren_veri[1]=128;
			}
			else
			{
				fren_veri[1]=192;
			}
		}
		fren_veri_sayisi=2;
		if(HAL_UART_Transmit_IT(&huart3,fren_veri,fren_veri_sayisi))
		{
			uart3_kuyruk_ekle=1;
			//__nop();//uart3 mesgul yada hata
		}
	//}
	return onay_kodu;
}

unsigned char direksiyon_cevir(unsigned char direksiyon_yon)
{
	//direksiyon_istenilen=direksiyon_yon*16;
	if(direksiyon_yon>250)
	{
		direksiyon_yon=250;
	}
	direksiyon_istenilen=direksiyon_yon*(direksiyon_sag_limit-direksiyon_sol_limit)/250+direksiyon_sol_limit;
	ADC1->CR2|=0x01;
	return onay_kodu;
}

unsigned char bldc_motor_calistir(unsigned char surus_hizi)
{
	if(BLDC_RPM==0)
	{
		if(BLDC_pwm==0)
		{
			BLDC_yonu=surus_yonu;
			HAL_GPIO_WritePin(BLDC_yon_pin_GPIO_Port,BLDC_yon_pin_Pin,BLDC_yonu);//
			istenilen_hiz=surus_hizi*(BLDC_pwm_max_yuzde-BLDC_pwm_min_yuzde)/BLDC_hiz_cozunurlugu;
			istenilen_hiz+=BLDC_pwm_min_yuzde;
			BLDC_pwm=BLDC_pwm_min_yuzde;
			TIM2->ARR=49;
			TIM2->CR1|=1;
			return frenleme(fren_geri);
		}
		else
		{
			if(BLDC_yonu==surus_yonu)
			{
				istenilen_hiz=surus_hizi*(BLDC_pwm_max_yuzde-BLDC_pwm_min_yuzde)/BLDC_hiz_cozunurlugu;
				istenilen_hiz+=BLDC_pwm_min_yuzde;
				return frenleme(fren_geri);
				return onay_kodu;
			}
			else
			{
				istenilen_hiz=0;
				BLDC_pwm=0;
				TIM3->CCR2=0;
				TIM2->CR1&=0xFFFE;
				TIM2->ARR=100;
				BLDC_yonu=yon_yok;
				TIM2->CNT=0;
				TIM2->CR1|=1;
				return frenleme(fren_ileri);
			}
		}
	}
	else
	{
		if(BLDC_pwm==0)
		{
			return frenleme(fren_ileri);
		}
		else
		{
			if(BLDC_yonu==surus_yonu)
			{
				istenilen_hiz=surus_hizi*(BLDC_pwm_max_yuzde-BLDC_pwm_min_yuzde)/BLDC_hiz_cozunurlugu;
				istenilen_hiz+=BLDC_pwm_min_yuzde;
				return frenleme(fren_geri);
			}
			else//araç hareket halinde iken ters yone sürme istegi gelmistir.
			{
				istenilen_hiz=0;
				TIM3->CCR2=0;
				BLDC_yonu=yon_yok;
				frenleme(fren_ileri);
				TIM2->CR1&=0xFFFE;
				TIM2->ARR=100;
				TIM2->CNT=0;
				return hata_kodu;
			}
		}		
	}
	return hata_kodu;
}

unsigned int mili_saniye(void)
{
	unsigned int milisaniye=RTC->CNTL;
	return milisaniye;
}

void direksiyon_kur(void)
{
	direksiyon_istenilen=(direksiyon_sol_limit+direksiyon_sag_limit) /2;
	
}

unsigned char bldc_motor_durdur(void)
{
	istenilen_hiz=0;
	BLDC_pwm=0;
	TIM3->CCR2=0;
	BLDC_yonu=yon_yok;
	//fren_istenilen=2;
	//frenleme(fren_ileri);
	if(fren_son_durum==fren_geri)
		frenleme(fren_ileri);
	if(BLDC_RPM>0)
		frenleme(fren_ileri);
	/*
	TIM3->CCR3=32;*/
	/*TIM2->CR1&=0xFFFE;
	TIM2->ARR=100;
	TIM2->CNT=0;
	TIM2->CR1|=1;*/
	return onay_kodu;
}
void fren_durum_kontrol(void)
{
	if((GPIOA->IDR&0x0040)==0)
	{
		fren_sol_durum=0;//0-2905202
	}
	else if((GPIOC->IDR&0x0020)==0)
	{
		fren_sol_durum=1;//1-2905202
	}
	else
	{
		fren_sol_durum=2;
	}
	
	if((GPIOA->IDR&0x0010)==0)
	{
		fren_sag_durum=1;
	}
	else if((GPIOC->IDR&0x0008)==0)
	{
		fren_sag_durum=0;
	}
	else
	{
		fren_sag_durum=2;
	}	
}
