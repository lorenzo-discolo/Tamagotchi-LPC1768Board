#include "draws.h"
#include "GLCD_advanced/GLCD.h"



void DrawImage(uint8_t Xpos, uint8_t Ypos, Image_Pixel *image)
{
	int LCD_x,LCD_y,i,color;
	int w = image->width;
	int h = image->height;
	
	uint16_t*  RGB565p = (uint16_t*)&(image->pixel_data);
	LCD_x=0;
	LCD_y=0;
	for(i=0;i<w*h;i++){
		uint16_t RGB565 = *RGB565p++;
		uint8_t r = (RGB565 & 0xF800) >> 8;
		uint8_t g = (RGB565 & 0x07E0) >> 3;
		uint8_t b = (RGB565 & 0x001F) << 3;
		if(LCD_y==image->width)
		{
			LCD_x++;
			LCD_y=0;
		}
		color = (uint16_t)( (( r >> 3) << 11 ) | (( g >> 2 ) << 5 ) | ( b >> 3 ));
		LCD_SetPoint(Xpos+LCD_y, Ypos+LCD_x, color);
		LCD_y++;
	}

}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
