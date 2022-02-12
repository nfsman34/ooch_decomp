///////////////////////////////////////////////////////////////////////////////
//	AFS converter
//		Palette decode
//			030909
//				by	AZUCO
///////////////////////////////////////////////////////////////////////////////

#include	<windows.h>
#include	<stdio.h>

void	decode_palette_8bit(unsigned char *src);
void	decode_palette_4bit(unsigned char *src);
void	extend_palette_h2t(unsigned char *src);



void	decode_palette_8bit(unsigned char *src)
{
	unsigned long	z;
	unsigned char	tmp[16];

	for(z=0;z<0x100;z+=32){
		memcpy(tmp,				src+(z+8)*4,	16);
		memcpy(src+(z+8)*4,		src+(z+16)*4,	16);
		memcpy(src+(z+16)*4,	tmp,			16);

		memcpy(tmp,				src+(z+12)*4,	16);
		memcpy(src+(z+12)*4,	src+(z+20)*4,	16);
		memcpy(src+(z+20)*4,	tmp,			16);
	}

	for(z=0;z<0x400;z+=4){
		tmp[0  ]=src[z+2];
		src[z+2]=src[z+0];
		src[z+0]=tmp[0  ];	}
}



void	decode_palette_4bit(unsigned char *src)
{
	unsigned long	z;
	unsigned char	tmp[16];

/*
	for(z=0;z<0x10;z+=32){
		memcpy(tmp,				src+(z+8)*4,	16);
		memcpy(src+(z+8)*4,		src+(z+16)*4,	16);
		memcpy(src+(z+16)*4,	tmp,			16);

		memcpy(tmp,				src+(z+12)*4,	16);
		memcpy(src+(z+12)*4,	src+(z+20)*4,	16);
		memcpy(src+(z+20)*4,	tmp,			16);
	}
*/
	for(z=0;z<0x40;z+=4){
		tmp[0  ]=src[z+2];
		src[z+2]=src[z+0];
		src[z+0]=tmp[0  ];	}
}



void	extend_palette_h2t(unsigned char *src)
{
	unsigned long	x,y,z;
//	unsigned char	tmp[16];

	for(z=0x100;z!=0;z--){
		x=(z-1)*2;
		y=(z-1)*4;

		src[y+2]=	 (src[x+1]&0x7c)<<1;
		src[y+1]=	((src[x+1]&0x03)<<6)|
					((src[x+0]&0xe0)>>2);
		src[y+0]=	 (src[x+0]&0x1f)<<3;
		src[y+3]=	0;
	}
}



