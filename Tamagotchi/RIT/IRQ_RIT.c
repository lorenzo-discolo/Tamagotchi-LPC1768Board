/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD_advanced/GLCD.h"
#include "../func_tamagotchi.h"
#include "../draws.h"
#include "../timer/timer.h"
#include "../TouchPanel/TouchPanel.h"
#include "../music/music.h"
#include "../adc/adc.h"

// beat 1/4 = 1.65/4 seconds
#define RIT_SEMIMINIMA 8
#define RIT_MINIMA 16
#define RIT_INTERA 32

#define UPTICKS 1

extern uint8_t count_Medikit;
extern uint8_t count_Chest;
extern Image_Position HORROR00_position;
extern Image_Position volume_bar;
extern Image_Pixel HORROR00;
extern Image_Pixel Volume_down;
extern Image_Pixel Volume_up;
extern uint8_t cuddle;
extern uint8_t volume;

static int currentNote = 0;
static int ticks = 0;
uint8_t volume_old;
uint8_t right=0;
uint8_t left=1;	
uint8_t select_joystick;
uint8_t sound;

NOTE click[] = 
{
	{c5, time_semicroma},
};

NOTE eating[] = 
{
	{f4, time_croma},
	{d4, time_croma},
	{g4, time_croma},
};

NOTE run[] = 
{
	{g4, time_semicroma},
	{c4, time_semicroma},
	{f4, time_semicroma},
	{c4, time_semicroma},
	{g4, time_semicroma},
};

NOTE cuddles[] = 
{
	{f4, time_semicroma},
	{a4, time_semicroma},
	{g4, time_semicroma},
	{a4, time_semicroma},
	{c4, time_semicroma},
	{e4, time_semicroma},
	{g4, time_semicroma},
	{d4, time_semicroma},
};

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


void RIT_IRQHandler (void)
{	
/******************************start_control_volume***************************/
	if(volume != volume_old)
		{
			if(volume > volume_old)
			{	
			uint8_t i;
			for(i=0;i<(volume - volume_old);i++){
				LCD_DrawRectangle(volume_bar.Xpos,volume_bar.Ypos,15,6,White);
				volume_bar.Xpos += 17;
				}
			DrawImage(20,5, &Volume_up);
			}
			else if(volume < volume_old)
			{
				uint8_t j;
				for(j=0;j<(volume_old - volume);j++){
				volume_bar.Xpos -= 17;
				LCD_DrawRectangle(volume_bar.Xpos,volume_bar.Ypos,15,6,Purple);
				}
					if(volume==0)
					{
						DrawImage(20,5, &Volume_down);
					}
			}
			volume_old = volume;
}
/******************************end_control_volume***************************/	

/******************************start_speaker**********************************/
	switch(sound){
		case 1:
			if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(click[currentNote++]);
				}
			}
			if(currentNote == (sizeof(click) / sizeof(click[0])))
			{
				sound = 0;
				currentNote = 0;
			}
			break;
		case 2:
			if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(eating[currentNote++]);
				}
			}
			if(currentNote == (sizeof(eating) / sizeof(eating[0])))
			{
				sound = 0;
				currentNote = 0;
			}
			break;
		case 3:
			if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(run[currentNote++]);
				}
			}
			if(currentNote == (sizeof(run) / sizeof(run[0])))
			{
				sound = 0;
				currentNote = 0;
			}
			break;
		case 4:
			if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(cuddles[currentNote++]);
				}
			}
			if(currentNote == (sizeof(cuddles) / sizeof(cuddles[0])))
			{
				sound = 0;
				currentNote = 0;
			}
			break;
		default:
			break;
	}	

/******************************end_speaker**********************************/
	
/******************************start_Display********************************/
if((select_joystick==0) && (cuddle==0)){  
	if(getDisplayPoint(&display, Read_Ads7846(), &matrix )){
		if((((display.x > HORROR00_position.Xpos) && (display.x < HORROR00_position.Xpos + HORROR00.width)) && ((display.y > HORROR00_position.Ypos) && (display.y < HORROR00_position.Ypos+HORROR00.height))) )
			{
			cuddle = 1;
			reset_timer(1);
			init_timer(1,0x005F5E10);
			enable_timer(1);
			}
		else{			
		//do nothing if touch returns values out of bounds
		}
	}
}
/******************************end_Display**********************************/
	
/******************************start_Joystick*******************************/
if(select_joystick==0){
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	
		/* Joytick LEFT pressed */
		switch(left){
			case 0:
			LCD_DrawLine(119, 266, 240, 266, White);
			LCD_DrawLine(119, 265, 240, 265, White);
			LCD_DrawLine(0, 266, 120, 266, Dark_Red);
			LCD_DrawLine(0, 265, 120, 265, Dark_Red);
				left = 1;
				right = 0;
				break;
			case 1:
				break;
			default:
				break;
		}
	}
}
if(select_joystick==0){
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	
		/* Joytick RIGHT pressed */
			switch(right){
			case 0:
			LCD_DrawLine(0, 266, 120, 266, White);
			LCD_DrawLine(0, 265, 120, 265, White);
			LCD_DrawLine(119, 266, 240, 266, Dark_Red);
			LCD_DrawLine(119, 265, 240, 265, Dark_Red);
				right = 1;
				left = 0;
				break;
			case 1:
				break;
			default:
				break;
		}
	}
}
if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		/* Joytick SELECT pressed */
			sound = 1;
	if(select_joystick==0)
		{	
			if(left==1)
			{
			disable_timer(1);
			reset_timer(0);
			select_joystick = 1;
			enable_timer(0);
			}
			else if(right==1)
			{
			disable_timer(1);
			reset_timer(0);
			select_joystick = 2;
			enable_timer(0);
			}
	  }
		else if(select_joystick==3)
			{
				restart_game();
			}
		}	
/******************************end_Joystick*******************************/
		
	ADC_start_conversion();	/*ADC_management*/
		
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/*************************************************************************
**                            End Of File
**************************************************************************/
