#ifndef __OLED_H
#define __OLED_H	

/*
**********************************************************************
*                         头文件包含
**********************************************************************
*/
#include "common.h"


/*
**********************************************************************
*                         本地宏定义
**********************************************************************
*/
#define OLED_CMD  0			// 写命令
#define OLED_DATA 1			// 写数据
#define OLED_MODE 0

#define OLED_CS_Clr()  		OLED_CS=0
#define OLED_CS_Set()  		OLED_CS=1

#define OLED_RST_Clr() 		OLED_RST=0
#define OLED_RST_Set() 		OLED_RST=1

#define OLED_DC_Clr() 		OLED_DC=0
#define OLED_DC_Set() 		OLED_DC=1

#define OLED_SCLK_Clr() 	OLED_SCL=0
#define OLED_SCLK_Set() 	OLED_SCL=1

#define OLED_SDIN_Clr() 	OLED_SDIN=0
#define OLED_SDIN_Set() 	OLED_SDIN=1

//OLED模式设置
//0:4线串行模式
//1:并行8080模式

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	  


/*
**********************************************************************
*                         外部函数原型声明
**********************************************************************
*/
//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLED_Set_Pos(u8 x, u8 y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(u8 x0, u8 y0, u8 x1, u8 y1,u8 BMP[]);
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(u8 IIC_Command);
void Write_IIC_Data(u8 IIC_Data);
void Write_IIC_Byte(u8 IIC_Byte);
void IIC_Wait_Ack();

#endif  
	 



