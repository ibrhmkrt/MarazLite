/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "surus.h"
#include "xbee.h"
#include "ATS.h" //Kesme fonksiyonuna ATS.h kütüphanesi dahil edildi.
#include "surusLite.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc1;
//extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
/* USER CODE BEGIN EV */

int kesmesayac=0;
int asd=0;
int asd2=0;
int hal_kontrol=0;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
	//28.05.2020 baslangic
	aracLite_durdurma_sayac=RTC->CNTL+4;
	//28.05.2020 bitis
	
	sendDataAts[0]=20; //Atistan sonra slave mod olan ats kartina 20 verisi yollanmak için atama yapildi.
	devAdressControl=devAdressAts; //Callback fonksiyonlarinda hangi slaveden veri geldigini karsilastirmak icin kontrol degiskeni atamasi
	if(HAL_I2C_Master_Transmit_IT(&hi2c1,devAdressAts<<1,sendDataAts,1)) //Ats ile olan i2c haberlesme baslatildi.(20 verisi yollandi)
	{
		if(hal_kontrol==0)
		{
			//i2c_reset
			//I2C1->CR1|=0x0400;
			I2C1->CR1|=0x8000;
			I2C1->CR1&=0xFFFE;
			I2C1->CR1&=0x7FFF;
			
			
			hi2c1.Instance = I2C1;
			hi2c1.Init.ClockSpeed = 100000;
			hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
			hi2c1.Init.OwnAddress1 = 0;
			hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
			hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
			hi2c1.Init.OwnAddress2 = 0;
			hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
			hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
			if (HAL_I2C_Init(&hi2c1) != HAL_OK)
			{
				Error_Handler();
			}
		}
	}
	else
	{
		hal_kontrol=1;
	}
	
  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */

  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line2 interrupt.
  */
void EXTI2_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_IRQn 0 */

  /* USER CODE END EXTI2_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  /* USER CODE BEGIN EXTI2_IRQn 1 */

  /* USER CODE END EXTI2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line3 interrupt.
  */
void EXTI3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI3_IRQn 0 */
	//Fren Sag Ileri Limit
	fren_veri[0]=64;
	if(HAL_UART_Transmit_IT(&huart3,fren_veri,fren_veri_sayisi))
	{
		uart3_kuyruk_ekle=1;
		//__nop();//uart3 mesgul yada hata
	}
	fren_sag_durum=fren_ileri;
	kesmesayac++;
  /* USER CODE END EXTI3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
  /* USER CODE BEGIN EXTI3_IRQn 1 */

  /* USER CODE END EXTI3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */
	//fren sag geri limit
	fren_veri[0]=64;
	if(HAL_UART_Transmit_IT(&huart3,fren_veri,fren_veri_sayisi))
	{
		uart3_kuyruk_ekle=1;
		//__nop();//uart3 mesgul yada hata
	}
	fren_sag_durum=fren_geri;
  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles ADC1 and ADC2 global interrupts.
  */
void ADC1_2_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_2_IRQn 0 */
	//direksiyon tim1 tarafindan 50ms de bir kontrol edilmek üzere ADC1 kesme siyalinde kontrol edilir.
	/*
	ADC1->SR=0x00;//adc regular bayrak temizle
	//HAL_ADC_IRQHandler(&hadc1);//
	direksiyon_pozisyonu=ADC1->DR;//direksiyon pozisyon degeri oku
	if(direksiyon_pozisyonu>direksiyon_istenilen)//direksiyon istenilen pozisyondan sagda ise
	{
		degisken=(direksiyon_pozisyonu-direksiyon_istenilen);//pozisyon ve istenilen pozisyon farki
		asd=degisken;//-
		if(degisken<direksiyon_hassasiyet_degeri)//+-direksiyon hassasiyet degeri kadar fark var ise motor direksiyon sabitlernir
		{
			TIM3->CCR1=0;//direksiyon pwm'ini %0 yap
			//direksiyon_yon_sifirlama
			GPIOB->ODR&=direksiyon_yon_sifirlama;//direksiyon sürücüsüne giden yön pimmlerini "0"'la
		}
		else
		{
			GPIOB->ODR&=direksiyon_yon_sifirlama;//direksiyon sürücü yön pinleri, f103 üzerinde A=PB15 ve B=PB14 pinleridir
			//direksiyon_sola
			GPIOB->ODR|=direksiyon_sola;//direksiyon_sola degeri PB14 "1" ve PB15 "0" için 0x4000
			//degisken=(degisken/direksiyon_hassasiyet_degeri)*direksiyon_ivmesi;//direksiyon istenilen ve mevcut pozisyonunun farkinin hassasiyet degerine orani ile dogru orantili olarak ivmelendirilmek üzere verilen pwm %'si degistirilir
			//
			//degisken=degisken*(pwm_max_yuzde-pwm_min_yuzde)/((direksiyon_sag_limit-direksiyon_sol_limit)/2)+pwm_min_yuzde;
			degisken=(degisken*(pwm_max_yuzde-pwm_min_yuzde))/(direksiyon_sag_limit-direksiyon_sol_limit);
			asd2=degisken;//-
			degisken=(degisken*degisken)*(5/3)+pwm_min_yuzde;
			//
			if(degisken>pwm_max_yuzde)//verilecek pwm % sinir kontrolü
			{
				degisken=pwm_max_yuzde;
			}
			if(degisken<pwm_min_yuzde)//verilecek pwm % sinir kontrolü
			{
				degisken=pwm_min_yuzde;
			}
			TIM3->CCR1=degisken;//pwm % degerinin tim3 1.pwm kanalina yazilmasi
			//ADC1->CR2|=0x01;//adc start
		}
	}
	else//direksiyon istenilen pozisyondan solda ise
	{
		degisken=(direksiyon_istenilen-direksiyon_pozisyonu);
		asd=degisken;//-
		if(degisken<direksiyon_hassasiyet_degeri)
		{
			TIM3->CCR1=0;
			//direksiyon_yon_sifirlama
			GPIOB->ODR&=direksiyon_yon_sifirlama;
		}
		else
		{
			GPIOB->ODR&=direksiyon_yon_sifirlama;
			//direksiyon_saga
			GPIOB->ODR|=direksiyon_saga;
			//degisken=(degisken/direksiyon_hassasiyet_degeri)*direksiyon_ivmesi;	
			//
			//degisken=degisken*(pwm_max_yuzde-pwm_min_yuzde)/((direksiyon_sag_limit-direksiyon_sol_limit)/2)+pwm_min_yuzde;
			degisken=(degisken*(pwm_max_yuzde-pwm_min_yuzde))/(direksiyon_sag_limit-direksiyon_sol_limit);
			asd2=degisken;//-
			degisken=(degisken*degisken)*(5/3)+pwm_min_yuzde;
			//
			if(degisken>pwm_max_yuzde)
			{
				degisken=pwm_max_yuzde;
			}
			if(degisken<pwm_min_yuzde)//verilecek pwm % sinir kontrolü
			{
				degisken=pwm_min_yuzde;
			}
			TIM3->CCR1=degisken;
			//ADC1->CR2|=0x01;//adc start
		}
	}*/
  /* USER CODE END ADC1_2_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc1);
  /* USER CODE BEGIN ADC1_2_IRQn 1 */
	
  /* USER CODE END ADC1_2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */
	//exti_5 fren sol geri limit
	//exti_6 fren sol ileri limit
	if((GPIOA->IDR&0x0040)==0)
	{
		fren_veri[1]=192;
		if(HAL_UART_Transmit_IT(&huart3,fren_veri,fren_veri_sayisi))
		{
			uart3_kuyruk_ekle=1;
			//__nop();//uart3 mesgul yada hata
		}
		fren_sol_durum=fren_ileri;
	}
	if((GPIOC->IDR&0x0020)==0)
	{
		fren_veri[1]=192;
		if(HAL_UART_Transmit_IT(&huart3,fren_veri,fren_veri_sayisi))
		{
			uart3_kuyruk_ekle=1;
			//__nop();//uart3 mesgul yada hata
		}
		fren_sol_durum=fren_geri;
	}
  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt.
  */
void TIM1_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_IRQn 0 */
	ADC1->CR2|=0x01;//adc start
  /* USER CODE END TIM1_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_IRQn 1 */

  /* USER CODE END TIM1_UP_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
	
	//28.05.2020 baslangic
	/*if(arac_durdurma_sayac > RTC->CNTL)
	{
		BLDC_yonu=2;
		istenilen_hiz=0;	
	}	*/
	//28.05.2020 bitis
	//Yeni
	if(aracLite_durdurma_sayac > RTC->CNTL)
	{
		sol_surus_yonu=yon_yok_Lite;
		sag_surus_yonu=yon_yok_Lite;
		istenilen_solTekerHiz=0;
		istenilen_sagTekerHiz=0;
		motorlariDurdur();//Birden fazla açip kapatiyoruz.
	}
		
	//tim2 ARR(auto reload register) 49 degerine ayarlandi 50 ms de bir tasma gerçeklestirecek
	//BLDC motor ivmelenmesi burada yapilacak
	/*bldc_hiz=BLDC_RPM*100/BLDC_max_rpm;//
	if(istenilen_hiz>bldc_hiz)//istenilen hiz mevcut hizdan büyükse 
	{
		if(BLDC_pwm<(BLDC_pwm_max_yuzde-BLDC_pwm_artis_carpani))//bldc pwm %si max pwm %sinden küçükse
		{
			BLDC_pwm+=BLDC_pwm_artis_carpani;//pwm %si artirilir(+ivmelendirme)
		}
		if(BLDC_pwm>istenilen_hiz)//hesaplanan pwm%si istenilen hiz %sinden büyükse, istenilen hiz %sine sabitlenir 
		{
			BLDC_pwm=istenilen_hiz;
		}			
	}
	else
	{
		if(BLDC_pwm>BLDC_pwm_min_yuzde)
		{
			BLDC_pwm-=BLDC_pwm_artis_carpani;//pwm %si azaltilir(-ivmelendirme)
		}
		if(BLDC_pwm<istenilen_hiz)
		{
			BLDC_pwm=istenilen_hiz;
		}
	}*/
	
	/*sol teker ivmelenme ve tekere verilecek pwm*/
	if(istenilen_solTekerHiz>solTekerPwm){
		if(solTekerPwm<(solTeker_pwm_max_yuzde-solTeker_pwm_artis_carpani)){
			solTekerPwm+=solTeker_pwm_artis_carpani;
		}
		if(solTekerPwm>istenilen_solTekerHiz){
			solTekerPwm=istenilen_solTekerHiz;
		}
	}
	else{
		if(solTekerPwm>solTeker_pwm_min_yuzde){
			solTekerPwm-=solTeker_pwm_artis_carpani;
		}
		if(solTekerPwm<istenilen_solTekerHiz){
			solTekerPwm=istenilen_solTekerHiz;
		}
	}
	
	/*sag teker ivmelenme ve tekere verilecek pwm*/
	if(istenilen_sagTekerHiz>sagTekerPwm){
		if(sagTekerPwm<(sagTeker_pwm_max_yuzde-sagTeker_pwm_artis_carpani)){
			sagTekerPwm+=sagTeker_pwm_artis_carpani;
		}
		if(sagTekerPwm>istenilen_sagTekerHiz){
			sagTekerPwm=istenilen_sagTekerHiz;
		}
	}
	else{
		if(sagTekerPwm>sagTeker_pwm_min_yuzde){
			sagTekerPwm-=sagTeker_pwm_artis_carpani;
		}
		if(sagTekerPwm<istenilen_sagTekerHiz){
			sagTekerPwm=istenilen_sagTekerHiz;
		}
	}
	
	
	if(istenilen_sagTekerHiz==0){
		sagTekerPwm=0;
	}
	if(istenilen_solTekerHiz==0){
		solTekerPwm=0;
	}
		
	
	TIM3->CCR1=sagTekerPwm;//pwm % degerinin tim3 1.pwm kanalina yazilmasi
	TIM3->CCR2=solTekerPwm;//pwm % degerinin tim3 2.pwm kanalina yazilmasi
	
	time_out_bitis=RTC->CNTL-time_out_baslangic;
	if(time_out_bitis>=2)//iletisim sorunu
	{
		//GPIOA->ODR|=0x0080;//bldc fren pin 0 yap 
		xbee_uart_sifirlama();
		veri_alma_basladimi=0;
		//ileitsim_durum_led_aç
		GPIOA->ODR|=0x0020;
	}
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
	//YON motor ivmelenmesi burada yapilacak
	
	
  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */
	BLDC_RPM=BLDC_RPM_sayac*33;//rpm hesabi = bldc_rpm_sayac * (1sn/tim4 yenilenme süresi(50ms)) * (60(dakika çarpani)/bldc turdaki tetik sayisi*sensor sayisi(10*3 alindi))
	BLDC_RPM_sayac=0;//exti_15 tetiklenme sayisi sifirlama
  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/**
  * @brief This function handles I2C1 event interrupt.
  */
void I2C1_EV_IRQHandler(void)
{
  /* USER CODE BEGIN I2C1_EV_IRQn 0 */

  /* USER CODE END I2C1_EV_IRQn 0 */
  HAL_I2C_EV_IRQHandler(&hi2c1);
  /* USER CODE BEGIN I2C1_EV_IRQn 1 */

  /* USER CODE END I2C1_EV_IRQn 1 */
}

/**
  * @brief This function handles I2C1 error interrupt.
  */
void I2C1_ER_IRQHandler(void)
{
  /* USER CODE BEGIN I2C1_ER_IRQn 0 */

  /* USER CODE END I2C1_ER_IRQn 0 */
  HAL_I2C_ER_IRQHandler(&hi2c1);
  /* USER CODE BEGIN I2C1_ER_IRQn 1 */

  /* USER CODE END I2C1_ER_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
	if(huart1.RxXferSize==6)
	{
		if(huart1.RxXferCount==0)
		{
			HAL_UART_Transmit_IT(&huart2,xbee_veri_tamponu,xbee_tampon_boyutu);
			//HAL_UART_Receive_IT(&huart1,xbee_veri_tamponu,xbee_tampon_boyutu);
			huart1.RxXferSize=0;//uart_rx_kontrol_sifirlama
			yeni_paket_var=paket_var;
		}
	}
	if(huart1.TxXferSize==xbee_tx_tampon_boyutu)
	{
		if(huart1.TxXferCount==0)
		{
			huart1.TxXferSize=0;//uart_rx_kontrol_sifirlama
			yeni_paket_var=paket_yok;
		}
	}
  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */
	if(huart3.RxXferCount==0)
	{
		if(uart3_kuyruk_ekle==1)
		{
			HAL_UART_Transmit_IT(&huart3,fren_veri,fren_veri_sayisi);
			uart3_kuyruk_ekle=0;
		}
	}
  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */
	BLDC_RPM_sayac++;//exti_15 kesme kanalinin tetiklenme sayisi rpm hesabi için kullanilacak, hesaplandiktan sonra sayac sifirlanacak
  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
