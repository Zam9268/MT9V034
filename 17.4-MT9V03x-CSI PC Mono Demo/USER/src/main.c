/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *+
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.24
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 * @note		
					接线定义：
 					------------------------------------  
						模块管脚         	单片机管脚
						SDA(51的RX)         查看SEEKFREE_MT9V03X_CSI.h文件中的MT9V03X_CSI_COF_UART_TX	宏定义
						SCL(51的TX)         查看SEEKFREE_MT9V03X_CSI.h文件中的MT9V03X_CSI_COF_UART_RX	宏定义
						场中断(VSY)         查看SEEKFREE_MT9V03X_CSI.h文件中的MT9V03X_CSI_VSYNC_PIN		宏定义
						行中断(HREF)	    不需要使用
						像素中断(PCLK)      查看SEEKFREE_MT9V03X_CSI.h文件中的MT9V03X_CSI_PCLK_PIN		宏定义
						数据口(D0-D7)		B31-B24 B31对应摄像头接口D0
						默认分辨率是        188*120
						默认FPS           	50帧
					------------------------------------ 
 ********************************************************************************************************************/


//打开新的工程或者工程移动了位置务必执行以下操作
//第一步 关闭上面所有打开的文件
//第二步 project  clean  等待下方进度条走完


#include "headfile.h"


int main(void)
{
    DisableGlobalIRQ();
    board_init();   //务必保留，本函数用于初始化MPU 时钟 调试串口

	systick_delay_ms(300);	//延时300ms，等待主板其他外设上电成功
	
	
    mt9v03x_csi_init();//初始化摄像头 使用CSI接口
    
    EnableGlobalIRQ(0);
    while(1)
    {
        if(mt9v03x_csi_finish_flag)
        {
			mt9v03x_csi_finish_flag = 0;
            csi_seekfree_sendimg_03x(USART_1,mt9v03x_csi_image[0],MT9V03X_CSI_W,MT9V03X_CSI_H);//串口初始化 由于默认开启了printf功能，因此在board_init已经初始化了串口1 因此本例程不在初始化   
        }
    }
}





