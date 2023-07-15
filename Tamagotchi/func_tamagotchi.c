#include "func_tamagotchi.h"
#include "draws.h"
#include "GLCD_advanced/GLCD.h"
#include "RIT/RIT.h"
#include "timer/timer.h"



uint8_t count_Medikit;
uint8_t count_Chest;
uint8_t restart_time;
uint8_t cuddle;
extern Image_Pixel HORROR00;
extern Image_Pixel HORROR01;
extern Image_Pixel HORROR02;
extern Image_Pixel HORROR03;
extern Image_Pixel Medikit;
extern Image_Pixel Chest;
extern Image_Pixel Heart;
extern Image_Pixel Volume_down;
extern Image_Position HORROR00_position;
extern Image_Position Medikit_position;
extern Image_Position Chest_position;
extern Image_Position volume_bar;
extern uint8_t left;
extern uint8_t right;
extern uint8_t select_joystick;
extern uint8_t volume_old;
extern uint8_t sound;


void start_game(void){
	
	HORROR00_position.Xpos = 83;
	HORROR00_position.Ypos = 175;
	Medikit_position.Xpos = 5;
	Medikit_position.Ypos = 88;
	Chest_position.Xpos = 125; 
	Chest_position.Ypos = 88;
	volume_bar.Xpos = 42;
	volume_bar.Ypos = 10;
	
	static_text();
}

void restart_game(void){
	select_joystick = 0;
	restart_time = 1;
	cuddle = 0;
	left = 1;
	right = 0;
	volume_old = 0;
	reset_RIT();
	reset_timer(0);
	reset_timer(1);
	reset_timer(2);
	reset_timer(3);
	enable_timer(0);
	enable_timer(1);
	enable_timer(2);
	enable_timer(3);
	GUI_Text(95,285, (uint8_t *) "RESTART", Purple, Purple);
	GUI_Text(85,130,(uint8_t *) "GAME OVER",Purple, Purple);
	GUI_Text(60,150,(uint8_t *) "HORROR LEFT YOU!",Purple,Purple);
	start_game();
}


void game_over(void){
	disable_timer(0);
	disable_timer(1);
	disable_RIT();
	select_joystick = 3;
	reset_timer(0);
	enable_timer(0);
	LCD_DrawLine(119, 267, 119, 320, Purple);
	LCD_DrawLine(120, 267, 120, 320, Purple);
	LCD_DrawLine(0, 266, 240, 266, Dark_Red);
	LCD_DrawLine(0, 265, 240, 265, Dark_Red);
	GUI_Text(85,130,(uint8_t *) "GAME OVER",White,Purple);
	GUI_Text(60,150,(uint8_t *) "HORROR LEFT YOU!",White,Purple);
	GUI_Text(50, 285, (uint8_t *) "HP", Purple, Purple);
	GUI_Text(165, 285, (uint8_t *) "AMMO", Purple, Purple);
	GUI_Text(95,285, (uint8_t *) "RESTART", White, Purple);
}

void incremete_time(void){
	static uint8_t time = '0';
	static uint8_t s1;
	static uint8_t s2;
	static uint8_t m1;
	static uint8_t m2;
	static uint8_t h1;
	static uint8_t h2;
	if(restart_time==1)
	{
		s1=1;
		s2=0;
		m1=0;
		m2=0;
		h1=0;
		h2=0;
		restart_time=0;
		PutChar(156,35,time+s1,White,Purple);
	}
	else if(s1<9){
		s1++;
		PutChar(156,35,time+s1,White,Purple);}
	else if(s2<5){
				s2++;
				s1=0;
				PutChar(156,35,time,White,Purple);
				PutChar(148,35,time+s2,White,Purple);}
			 else if(m1<9){
						m1++;
						s2=0;
						PutChar(156,35,time,White,Purple);
						PutChar(148,35,time,White,Purple);
						PutChar(132,35,time+m1,White,Purple);}
						else if(m2<5){
									m2++;
									m1=0;
									PutChar(156,35,time,White,Purple);
									PutChar(148,35,time,White,Purple);
									PutChar(132,35,time,White,Purple);
									PutChar(124,35,time+m2,White,Purple);}
								 else if(h1<9){
											h1++;
											m2=0;
											PutChar(156,35,time,White,Purple);
											PutChar(148,35,time,White,Purple);
											PutChar(132,35,time,White,Purple);
											PutChar(124,35,time,White,Purple);
											PutChar(108,35,time+h1,White,Purple);}
											else if(h2<9){
													 h2++;
													 h1=0;
													 PutChar(156,35,time,White,Purple);
													 PutChar(148,35,time,White,Purple);
													 PutChar(132,35,time,White,Purple);
													 PutChar(124,35,time,White,Purple);
													 PutChar(108,35,time,White,Purple);
													 PutChar(100,35,time+h2,White,Purple);}
													 else 
														GUI_Text(100, 35, (uint8_t *) "YOU WIN THE GAME", White, Purple);
}
void static_text(void){
	uint8_t i;
	DrawImage(20,5,&Volume_down);
	LCD_DrawLine(40,7,213,7,White);
	LCD_DrawLine(40,17,213,17,White);
	LCD_DrawLine(40,8,40,16,White);
	LCD_DrawLine(213,8,213,16,White);
	GUI_Text(72, 35, (uint8_t *) "AGE", White, Purple);
	GUI_Text(95, 35, (uint8_t *) ":", White, Purple);
	GUI_Text(100, 35, (uint8_t *) "00:00:00", White, Purple);
	GUI_Text(20, 65, (uint8_t *) "HAPPINESS", White, Purple);
	GUI_Text(150, 65, (uint8_t *) "SATIETY", White, Purple);
	LCD_DrawLine(0, 266, 120, 266, Dark_Red);
	LCD_DrawLine(0, 265, 120, 265, Dark_Red);
	LCD_DrawLine(119, 266, 240, 266, White);
	LCD_DrawLine(119, 265, 240, 265, White);
	LCD_DrawLine(119, 265, 119, 320, Dark_Red);
	LCD_DrawLine(120, 265, 120, 320, Dark_Red);
	GUI_Text(50, 285, (uint8_t *) "HP", White, Purple);
	GUI_Text(165, 285, (uint8_t *) "AMMO", White, Purple);
		for(i=0;i<5;i++){
		DrawImage(Medikit_position.Xpos,Medikit_position.Ypos,&Medikit);
		Medikit_position.Xpos +=23;
		count_Medikit++;
		DrawImage(Chest_position.Xpos, Chest_position.Ypos,&Chest);
		Chest_position.Xpos +=23;
		count_Chest++;
		}
	DrawImage(HORROR00_position.Xpos,HORROR00_position.Ypos,&HORROR00);
}

void animation_idle(void){
	static uint8_t alternate;
	switch(alternate){
		case 0:
			DrawImage(HORROR00_position.Xpos,HORROR00_position.Ypos,&HORROR00);
			alternate=1;
		break;
		case 1:
			DrawImage(HORROR00_position.Xpos,HORROR00_position.Ypos,&HORROR01);
			alternate=2;
		break;
		case 2:
			DrawImage(HORROR00_position.Xpos,HORROR00_position.Ypos,&HORROR02);
			alternate=3;
		break;
		case 3:
			DrawImage(HORROR00_position.Xpos,HORROR00_position.Ypos,&HORROR03);
			alternate=0;
			incremete_time();
		break;
		default:
		break;
}
}

void animation_cuddle(void){
	static uint8_t animation;
	disable_timer(0);
	switch(animation){
		case 0:
	LCD_DrawRectangle(HORROR00_position.Xpos,HORROR00_position.Ypos,HORROR00.width,HORROR00.height,Purple);
	DrawImage(HORROR00_position.Xpos+20,HORROR00_position.Ypos,&HORROR00);
	animation++;
		break;
		case 1:
	LCD_DrawRectangle(HORROR00_position.Xpos+20,HORROR00_position.Ypos,HORROR00.width,HORROR00.height,Purple);
	DrawImage(HORROR00_position.Xpos-20,HORROR00_position.Ypos,&HORROR00);
	animation++;
	incremete_time();
		break;
		case 2:
	LCD_DrawRectangle(HORROR00_position.Xpos-20,HORROR00_position.Ypos,HORROR00.width,HORROR00.height,Purple);
	DrawImage(HORROR00_position.Xpos,HORROR00_position.Ypos,&HORROR00);
	DrawImage(HORROR00_position.Xpos-20,HORROR00_position.Ypos-10,&Heart);
	DrawImage(HORROR00_position.Xpos+80,HORROR00_position.Ypos-10,&Heart);
	animation++;
		break;
		case 3:
	LCD_DrawRectangle(HORROR00_position.Xpos-20,HORROR00_position.Ypos-10,Heart.width,Heart.height,Purple);
	LCD_DrawRectangle(HORROR00_position.Xpos+80,HORROR00_position.Ypos-10,Heart.width,Heart.height,Purple);
	animation=0;
	incremete_time();
	increase_medikit();
	cuddle=0;
	reset_timer(1);
	init_timer(1,0x07735940);
	enable_timer(1);
	enable_timer(0);
		break;
		default:
		break;
	}
}
void animation_medikit(void){
	static uint8_t timing_HP;
	switch(timing_HP){
		case 0:
					DrawImage(HORROR00_position.Xpos+120,HORROR00_position.Ypos+45,&Medikit);
					LCD_DrawRectangle(HORROR00_position.Xpos,HORROR00_position.Ypos,HORROR00.width,HORROR00.height,Purple);
					DrawImage(HORROR00_position.Xpos+40,HORROR00_position.Ypos,&HORROR00);
					timing_HP++;
					break;
		case 1:
					LCD_DrawRectangle(HORROR00_position.Xpos+40,HORROR00_position.Ypos,HORROR00.width,HORROR00.height,Purple);
					DrawImage(HORROR00_position.Xpos+80,HORROR00_position.Ypos,&HORROR00);
					sound = 2;
					timing_HP++;
					break;
		case 2:
					LCD_DrawRectangle(HORROR00_position.Xpos+80,HORROR00_position.Ypos,HORROR00.width,HORROR00.height,Purple);
					DrawImage(HORROR00_position.Xpos+40,HORROR00_position.Ypos,&HORROR00);
					timing_HP++;
					break;
		case 3:
					timing_HP=0;
					LCD_DrawRectangle(HORROR00_position.Xpos+40,HORROR00_position.Ypos,HORROR00.width,HORROR00.height,Purple);
					DrawImage(HORROR00_position.Xpos,HORROR00_position.Ypos,&HORROR00);
					increase_medikit();
					incremete_time();
					reset_timer(1);
					reset_timer(0);
					select_joystick = 0;
					enable_timer(0);
					enable_timer(1);
					break;
		default:
					break;
		}
}

void animation_chest(void){
	static uint8_t timing_ammo;
	switch(timing_ammo){
		case 0:
			DrawImage(HORROR00_position.Xpos-60,HORROR00_position.Ypos+45,&Chest);
			LCD_DrawRectangle(HORROR00_position.Xpos,HORROR00_position.Ypos,HORROR00.width,HORROR00.height,Purple);
			DrawImage(HORROR00_position.Xpos-40,HORROR00_position.Ypos,&HORROR00);
			timing_ammo++;
			break;
		case 1:
			LCD_DrawRectangle(HORROR00_position.Xpos-40,HORROR00_position.Ypos,HORROR00.width,HORROR00.height,Purple);
			DrawImage(HORROR00_position.Xpos-80,HORROR00_position.Ypos,&HORROR00);
			timing_ammo++;
			sound = 2;
			break;
		case 2:
			LCD_DrawRectangle(HORROR00_position.Xpos-80,HORROR00_position.Ypos,HORROR00.width,HORROR00.height,Purple);
			DrawImage(HORROR00_position.Xpos-40,HORROR00_position.Ypos,&HORROR00);
			timing_ammo++;
			break;
		case 3:
			timing_ammo=0;
			LCD_DrawRectangle(HORROR00_position.Xpos-40,HORROR00_position.Ypos,HORROR00.width,HORROR00.height,Purple);
			DrawImage(HORROR00_position.Xpos,HORROR00_position.Ypos,&HORROR00);
			increase_chest();
			incremete_time();
			reset_timer(1);
			reset_timer(0);
			select_joystick = 0;
			enable_timer(0);
			enable_timer(1);
			break;
		default:
			break;
	}
}

void run_away(void){
	static uint8_t timing_run;
	switch(timing_run){
		case 0:
			LCD_DrawRectangle(HORROR00_position.Xpos,HORROR00_position.Ypos,HORROR00.width,HORROR00.height,Purple);
			DrawImage(HORROR00_position.Xpos+40,HORROR00_position.Ypos,&HORROR00);
			timing_run++;
			break;
		case 1:
			LCD_DrawRectangle(HORROR00_position.Xpos+40,HORROR00_position.Ypos,HORROR00.width,HORROR00.height,Purple);
			DrawImage(HORROR00_position.Xpos+80,HORROR00_position.Ypos,&HORROR00);
			timing_run++;
			break;
		case 2:
			LCD_DrawRectangle(HORROR00_position.Xpos+80,HORROR00_position.Ypos,HORROR00.width,HORROR00.height,Purple);
			timing_run = 0;
			reset_timer(0);
			disable_timer(0);
			reset_RIT();
			enable_RIT();
			break;
		default:
			break;
	}
}
void erase_object(void){
		Medikit_position.Xpos -= 23;
		Chest_position.Xpos -= 23;
		LCD_DrawRectangle(Medikit_position.Xpos,Medikit_position.Ypos, Medikit.width,Medikit.height,Purple);
		LCD_DrawRectangle(Chest_position.Xpos,Chest_position.Ypos,Chest.width,Chest.height,Purple);
		count_Medikit--;
		count_Chest--;
	if((count_Medikit && count_Chest) == 0)
		{
			game_over();
		}
}

void increase_medikit(void){
			if(count_Medikit<5)
				{
				DrawImage(Medikit_position.Xpos,Medikit_position.Ypos,&Medikit);
				Medikit_position.Xpos +=23;
				count_Medikit++;
				}
}
void increase_chest(void){
			if(count_Chest<5)
				{
				DrawImage(Chest_position.Xpos,Chest_position.Ypos,&Chest);
				Chest_position.Xpos +=23;
				count_Chest++;
				}
}
