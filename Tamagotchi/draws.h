/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           draws.h
** Last modified Date:  2023
** Last Version:        V1.00
** Descriptions:        
** Correlated files:    
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"


typedef struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
	unsigned char	 pixel_data[70 * 68 * 2 + 1];
}Image_Pixel;

typedef struct {
	uint8_t 	 Xpos;
	uint8_t 	 Ypos;
}Image_Position;


void DrawImage(uint8_t Xpos, uint8_t Ypos, Image_Pixel *image);


