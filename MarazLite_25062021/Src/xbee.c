#include "xbee.h"
#include "surus.h"
#include "surusLite.h"
//#include "stm32f1xx_hal_uart.h"
extern UART_HandleTypeDef huart2;

unsigned char xbee_veri_tamponu[xbee_tampon_boyutu];
unsigned char xbee_tx_tamponu[xbee_tx_tampon_boyutu];
short int xbee_tampon_index=0;
unsigned char xbee_tampon_durumu=tampon_bos;
unsigned char yeni_paket_var=paket_yok;
unsigned char veri_alma_basladimi=0;
unsigned int time_out_baslangic=0;
unsigned int time_out_bitis=0;
extern UART_HandleTypeDef huart1;


unsigned char veri_alma_baslat_it(void){
	
	if(!HAL_UART_Receive_IT(&huart1,xbee_veri_tamponu,xbee_tampon_boyutu))
	{
		veri_alma_basladimi=1;
		//if(xbee_veri_tamponu[0]==0)//baslangiç if reddi için 
		if(xbee_veri_tamponu[0]!=254)//baslangiç if reddi için 
		{
			return 0;
		}
		return onay_kodu;
	}
	return hata_kodu;
}

unsigned char xbee_gonder(unsigned char* veri, int byte_sayisi){
	if(!HAL_UART_Transmit_IT(&huart1,veri,byte_sayisi))
	{
		xbee_tampon_durumu=tampon_bos;
		veri_alma_basladimi=0;
		return onay_kodu;
	}
	return 0;
}

unsigned char paket_dogrula(void)
{
	if(xbee_veri_tamponu[0]==paket_dogrulama_baslangic)
	{
		if(xbee_veri_tamponu[5]==paket_dogrulama_bitis)
		{	
			//time_out_baslangic=RTC->CNTL;
			xbee_tampon_durumu=tampon_dolu;
			return 2;
		}
		else
		{
			//bldc durdur, paket hatali
			xbee_tx_tamponu[0]=252;
			xbee_veri_tamponu[1]=128;
			xbee_veri_tamponu[2]=128;
			xbee_gonder(xbee_tx_tamponu,1);
			huart1.RxXferCount=6;
			HAL_GPIO_WritePin(BLDC_fren_pin_GPIO_Port,BLDC_fren_pin_Pin,1);//
			//
			
		}
	}
	else
	{
		//bldc durdur, paket hatali
		xbee_tx_tamponu[0]=252;		
		xbee_veri_tamponu[1]=128;
		xbee_veri_tamponu[2]=128;
		xbee_gonder(xbee_tx_tamponu,1);
		huart1.RxXferCount=6;
		HAL_GPIO_WritePin(BLDC_fren_pin_GPIO_Port,BLDC_fren_pin_Pin,1);//
		//
	}
	xbee_tx_tamponu[0]=4;
	xbee_gonder(xbee_tx_tamponu,1);
	return 0;
}

unsigned char xbee(void)
{	
	if(yeni_paket_var==paket_var)
	{
		return paket_dogrula();
	}
	else
	{
		if(xbee_tampon_durumu==tampon_bos)
		{
			if(!veri_alma_basladimi)
			{
				if(!veri_alma_baslat_it())
					return hata_kodu;
				time_out_baslangic=RTC->CNTL;
				GPIOA->ODR&=0xFFDF;
				return 1;
				//iletisim_durum_led_kapa
			}
			else
			{
				time_out_bitis=RTC->CNTL-time_out_baslangic;
				if(time_out_bitis>2)//iletisim sorunu
				{
					xbee_uart_sifirlama();
					veri_alma_basladimi=0;
					//ileitsim_durum_led_aç
					GPIOA->ODR|=0x0020;
				}
			}
		}
	}
	return 0;
}
	
unsigned char xbee_uart_sifirlama(void)
{
	//HAL_UART_DeInit(&huart1);
	fren_istenilen=2;
	bldc_motor_durdur();
	direksiyon_kur();
	motorlariDurdur();
	return hata_kodu;//
}

