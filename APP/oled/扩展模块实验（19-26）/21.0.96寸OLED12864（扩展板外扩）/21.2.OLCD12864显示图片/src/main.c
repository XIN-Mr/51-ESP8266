/*********************************************************************
						巫妖王V3.0开发板例程
			   朱有鹏物联网大讲堂出品(www.zhulaoshi.org)      
		  技术支持和学习讨论请加朱有鹏单片机学习1群 214959925获取
**********************************************************************
实验序列：21.2
实验任务: 驱动OLED12864显示图片		
实现现象：程序执行后OLED12864上面显示一副128*64分辨率的二值位图。
硬件接线：使用巫妖王专用扩展板，将官方配套的0.96寸OLED屏插入专用扩展口，
		  注意别插错排母或者插反，参考 OLED12864插接图.png
注意事项：(1) 本程序使用的0.96寸OLCD12864模块数据手册和各种扩展资源资料
			  在巫妖王开发板光盘资料/7.扩展功能模块/3.0.96寸OLED显示屏
		  (2) 本程序使用51单片机IO口模拟I2C接口与OLED屏的I2C接口通信
		  (3) 我们选用的OLED屏本身不带字库，因此需要程序中提供字库。
版    本：V1.00
作    者：朱有鹏（AstonZhu）
时	  间：2018.10.30											  
**********************************************************************/

/*
**********************************************************************
*                         头文件包含
**********************************************************************
*/
#include "oled.h"
#include "pic.h"

/*
**********************************************************************
*                         本地宏定义
**********************************************************************
*/


/*
**********************************************************************
*                         本地全局变量
**********************************************************************
*/


/*
**********************************************************************
*                         函数原型声明
**********************************************************************
*/


/*********************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 参数列表       : 无
* 函数输出    	 : 无
*********************************************************************/
void main(void)
{
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 
		
	OLED_DrawBMP(0, 0, 128, 8, pic);

	while (1);
}









