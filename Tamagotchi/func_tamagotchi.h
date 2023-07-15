/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           func_tamagotchi.h
** Last modified Date:  2023
** Last Version:        V1.00
** Descriptions:        
** Correlated files:    
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"



void start_game(void);
void restart_game(void);
void game_over(void);
void static_text(void);
void incremete_time(void);
void animation_idle(void);
void animation_cuddle(void);
void erase_object(void);
void animation_medikit(void);
void animation_chest(void);
void increase_medikit(void);
void increase_chest(void);
void run_away(void);

