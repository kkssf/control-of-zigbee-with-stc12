 #include <command.h>
#include <reg52.h>
#include<neirong.h>

sbit LCD_RS=P2^6;//定义引脚
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7;
sbit PSB =P3^4;		//PSB脚为12864-12系列的串、并通讯功能切换，我们使用8位并行接口，PSB=1
#define LCD_Data P0
#define Busy    0x80 //用于检测LCD状态字中的Busy标识

//写数据
void WriteDataLCD(unsigned char WDLCD)
{
 ReadStatusLCD(); //检测忙 
 LCD_RS = 1;
 LCD_RW = 0;
 LCD_Data = WDLCD;
 LCD_E = 1;
 LCD_E = 1;
 LCD_E = 1;
 LCD_E = 0;
}

//写指令
void WriteCommandLCD(unsigned char WCLCD,BuysC) //BuysC为0时忽略忙检测
{
 if (BuysC) ReadStatusLCD(); //根据需要检测忙 
 LCD_RS = 0;
 LCD_RW = 0; 
 LCD_Data = WCLCD;
 LCD_E = 1; 
 LCD_E = 1;
 LCD_E = 1;
 LCD_E = 0;  
}

//读数据
unsigned char ReadDataLCD(void)
{
 LCD_RS = 1; 
 LCD_RW = 1;
 LCD_E = 0;
 LCD_E = 0;
 LCD_E = 1;
 return(LCD_Data);
}

//读状态
unsigned char ReadStatusLCD(void)
 {
 LCD_Data = 0xFF; 
 LCD_RS = 0;
 LCD_RW = 1; 
 LCD_E = 1;
 while (LCD_Data & Busy); //检测忙信号
 LCD_E = 0;
 return(LCD_Data);
}

void LCDInit(void) //LCM初始化
{
 WriteCommandLCD(0x30,1); //显示模式设置,开始要求每次检测忙信号
 WriteCommandLCD(0x01,1); //显示清屏
 WriteCommandLCD(0x06,1); // 显示光标移动设置
 WriteCommandLCD(0x0C,1); // 显示开及光标设置
}
void LCDClear(void) //清屏
{
 WriteCommandLCD(0x01,1); //显示清屏
 WriteCommandLCD(0x34,1); // 显示光标移动设置
 WriteCommandLCD(0x30,1); // 显示开及光标设置
}
//按指定位置显示一个字符
void DisplayOneChar(unsigned char X,  char Y, unsigned char DData)
{
 if(Y<1)
 	Y=1;
 if(Y>4)
 	Y=4;
 X &= 0x0F; //限制X不能大于16，Y不能大于1
 switch(Y){
	case 1:X|=0X80;break;
	case 2:X|=0X90;break;
	case 3:X|=0X88;break;
	case 4:X|=0X98;break;
	}
 WriteCommandLCD(X, 0); //这里不检测忙信号，发送地址码
 WriteDataLCD(DData);
}

//按指定位置显示一串字符
void DisplayListChar(unsigned char X, unsigned char Y,  unsigned char code*DData)
{
 unsigned char ListLength,X2;
  ListLength = 0;
  X2=X;
 if(Y<1)
 	Y=1;
 if(Y>4)
 	Y=4;
 X &= 0x0F; //限制X不能大于16，Y在1-4之内
 switch(Y){
	case 1:X2|=0X81;break;	//根据行数来选择相应地址
	case 2:X2|=0X91;break;
	case 3:X2|=0X89;break;
	case 4:X2|=0X98;break;
	}
 WriteCommandLCD(X2, 1); //发送地址码
  while (DData[ListLength]>=0x20) //若到达字串尾则退出
  {
   if (X <= 0x0f) //X坐标应小于0xF
    {
     WriteDataLCD(DData[ListLength]); //
     ListLength++;
	 X++;
    }
  }
}

//图形显示128*32
void DisplayImage ( unsigned char code*DData){
	unsigned char x,y,i;
	unsigned int tmp=0;
	for(i=0;i<9;){		//分两屏，上半屏和下半屏，因为起始地址不同，需要分开
	for(x=0;x<32;x++){				//32行
		WriteCommandLCD(0x34,1);
		WriteCommandLCD((0x80+x),1);//列地址
		WriteCommandLCD((0x80+i),1);	//行地址，下半屏，即第三行地址0X88
		WriteCommandLCD(0x30,1);		
		for(y=0;y<16;y++)
		  
		 WriteDataLCD(DData[tmp+y]);
		tmp+=16;		
	}
	i+=8;
	}
	WriteCommandLCD(0x36,1);	//扩充功能设定
	WriteCommandLCD(0x30,1);
}


//5ms延时
void Delay5Ms(void)
{
 unsigned int TempCyc = 5552;
 while(TempCyc--);
}

//400ms延时
void Delay400Ms(void)
{
 unsigned char TempCycA = 5;
 unsigned int TempCycB;
 while(TempCycA--)
 {
  TempCycB=7269;
  while(TempCycB--);						  
 }
}
