#include "PS2.H"
#include "delay.h"

//------GPIO�汾-----
uchar PS2_RWByte(uchar id)
{
	uchar i=0,j;
	uchar od=0;

	for(i=0;i<8;i++)
	{
	if( id&(1<<i) )
	PS2_mosi=1;
	else
	PS2_mosi=0;

	PS2_sck=0;

	for(j=0;j<50;j++);

	PS2_sck=1;

	if(PS2_miso_indat)
	od|=1<<i;
	else
	od|=0<<i;

	for(j=0;j<50;j++);
	}

	return (od);
}


void PS2_Init(void)   //--SPI�˿ڳ�ʼ��
{
PS2_sck_outmode;
PS2_mosi_outmode;
PS2_miso_inmode;

PS2_miso=1;
PS2_mosi=1;

PS2_CS_outmode;
PS2_CS=1;


delay(30);
}



/*
������Ҫ20ms�ļ��ʱ�����һ��
buf������Ҫ9���ռ�
����0,ʧ��
1���ɹ�����ͨģʽ
2���ɹ���ҡ����չģʽ
*/
uchar Get_PS2Dat(uchar *buf)
{
usint i;

	PS2_CS=0;

	for(i=0;i<500;i++);
	buf[0]=PS2_RWByte(0x01);for(i=0;i<500;i++); //��ʱ�ٶ�ȡ
	buf[1]=PS2_RWByte(0x42);for(i=0;i<500;i++);
	buf[2]=PS2_RWByte(0x00);for(i=0;i<500;i++);
	buf[3]=PS2_RWByte(0x00);for(i=0;i<500;i++);
	buf[4]=PS2_RWByte(0x00);for(i=0;i<500;i++);
	buf[5]=PS2_RWByte(0x00);for(i=0;i<500;i++);
	buf[6]=PS2_RWByte(0x00);for(i=0;i<500;i++);
	buf[7]=PS2_RWByte(0x00);for(i=0;i<500;i++);
	buf[8]=PS2_RWByte(0x00);for(i=0;i<500;i++);

	PS2_CS=1;

if((buf[0]==0xff)&&(buf[1]==0x41)&&(buf[2]==0x5a))  //�ɹ�����ͨģʽ
return 1;

if((buf[0]==0xff)&&(buf[1]==0x73)&&(buf[2]==0x5a))  //�ɹ���ҡ����չģʽ
return 2;

return 0;
}

/*
����������ĳһλ��1Ϊ����
���µ���ĤֵΪ_PS2_Key_Dir_U ��...

*/
usint PS2_ChangeKey(uchar *inBuf)
{
	usint i;
	usint k;
	i = (~inBuf[4]) << 8;
	k=((usint)(~inBuf[3])) & 0x00ff ;
	i = i|k;
	return(i) ;
}





