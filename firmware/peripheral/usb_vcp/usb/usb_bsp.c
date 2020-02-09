#include "usb_bsp.h"
#include "usbd_conf.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"

void USB_OTG_BSP_Init(USB_OTG_CORE_HANDLE *pdev)
{
	GPIO_InitTypeDef GPIO_InitStructure;

#ifndef USE_ULPI_PHY 
#ifdef USB_OTG_FS_LOW_PWR_MGMT_SUPPORT
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
#endif  
#endif

#ifdef USE_USB_OTG_FS 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);  

	/* configure sof, vbus, dm dp pins */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_OTG1_FS) ;
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_OTG1_FS) ; 
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_OTG1_FS) ; 
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_OTG1_FS) ;

	/* this for ID line debug */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_OTG1_FS) ;   

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS, ENABLE) ; 
#else //USE_USB_OTG_HS 

#ifdef USE_ULPI_PHY //ulpi
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC |
			       RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOI, ENABLE);    

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3, GPIO_AF_OTG2_HS) ; //d0
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5, GPIO_AF_OTG2_HS) ; //clk
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0, GPIO_AF_OTG2_HS) ; //d1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1, GPIO_AF_OTG2_HS) ; //d2
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5, GPIO_AF_OTG2_HS) ; //d7
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_OTG2_HS) ; //d3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_OTG2_HS) ; //d4
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource12,GPIO_AF_OTG2_HS) ; //d5
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_OTG2_HS) ; //d6
	GPIO_PinAFConfig(GPIOH,GPIO_PinSource4, GPIO_AF_OTG2_HS) ; //nxt
	GPIO_PinAFConfig(GPIOI,GPIO_PinSource11,GPIO_AF_OTG2_HS) ; //dir
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource0, GPIO_AF_OTG2_HS) ; //stp

	//clk
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	//d0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3  ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	//d1 d2 d3 d4 d5 d6 d7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_10 |
				      GPIO_Pin_11| GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
  
	//stp
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOC, &GPIO_InitStructure);  
  
	//nxt
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOH, &GPIO_InitStructure);  

	//dir
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOI, &GPIO_InitStructure);  

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_OTG_HS | RCC_AHB1Periph_OTG_HS_ULPI, ENABLE) ;    
#else
#ifdef USE_I2C_PHY    
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB , ENABLE);  
	/* configure reset intn scl sda phy/i2c pins */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
  
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_OTG2_FS) ; 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_OTG2_FS) ; 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_OTG2_FS) ; 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_OTG2_FS);
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_OTG_HS, ENABLE) ;  
#else
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12  | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
  
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource12, GPIO_AF_OTG2_FS) ; 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_OTG2_FS) ; 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_OTG2_FS) ; 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_OTG2_FS) ;
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_OTG_HS, ENABLE) ;  
#endif  
#endif //USE_ULPI_PHY
  
#endif //USB_OTG_HS

	/* enable the pwr clock */
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);   
  
	/* Configure the key button in exti mode */
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
  
#ifdef USB_OTG_FS_LOW_PWR_MGMT_SUPPORT
	EXTI_ClearITPendingBit(EXTI_Line18);
  
	EXTI_InitStructure.EXTI_Line = EXTI_Line18; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_ClearITPendingBit(EXTI_Line18);   

	NVIC_InitStructure.NVIC_IRQChannel = OTG_FS_WKUP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	EXTI_ClearITPendingBit(EXTI_Line18);    
#endif 
  
#ifdef USB_OTG_HS_LOW_PWR_MGMT_SUPPORT
	EXTI_ClearITPendingBit(EXTI_Line20);
	EXTI_InitStructure.EXTI_Line = EXTI_Line20; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_ClearITPendingBit(EXTI_Line20);   

	NVIC_InitStructure.NVIC_IRQChannel = OTG_HS_WKUP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	EXTI_ClearITPendingBit(EXTI_Line20);    
#endif   

	EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);  
}

void USB_OTG_BSP_EnableInterrupt(USB_OTG_CORE_HANDLE *pdev)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef NVIC_InitStructure; 
#ifdef USE_USB_OTG_HS   
	NVIC_InitStructure.NVIC_IRQChannel = OTG_HS_IRQn;
#else
	NVIC_InitStructure.NVIC_IRQChannel = OTG_FS_IRQn;  
#endif
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  
#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = OTG_HS_EP1_OUT_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  
  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = OTG_HS_EP1_IN_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);   
#endif
}

void USB_OTG_BSP_uDelay(const uint32_t usec)
{
	uint32_t count = 0;
	const uint32_t utime = (120 * usec / 7);
	do {
		if(++count > utime) return;
	}
	while (1);
}

void USB_OTG_BSP_mDelay(const uint32_t msec)
{
	USB_OTG_BSP_uDelay(msec * 1000);   
}
