/******************************************************************************
	PS2 Discreat Compress Bit LZss
******************************************************************************/
#include	<windows.h>
#include	<intrin.h>
#include	<stdio.h>

unsigned char	bs_get8(	unsigned char *,
							unsigned long ,
							unsigned long 	);


unsigned long	ps2_dcb_lzss(	unsigned char *sbuf,
								unsigned char *dbuf,
								unsigned long slen,
								unsigned long dlen	)
{	
	printf("\tSTART LZSS\n");
	unsigned long	sbp,sp,dp,cp,cc,el;
	unsigned char	fl;
	unsigned char	ct;

	for (sbp = 0, sp = 0, dp = 0; (sp < slen) && (dp < dlen);) {
				sp			=sbp>>3;
				fl			=bs_get8(sbuf,sbp,1);	sbp++;
		if(fl==0){
				dbuf[dp]	=bs_get8(sbuf,sbp,8);	sbp+=8;	dp++;
		}else{
				el			=bs_get8(sbuf,sbp,8);	sbp+=8;
				ct			=bs_get8(sbuf,sbp,8);	sbp+=8;
				cp			=dp-el;
			for(cc=0;cc<ct;cc+=el){
				memcpy(dbuf+dp+cc,dbuf+cp,el);
			}
		dp+=ct;
		}
		//printf("\t%u bytes of %u done. (%u of %u decompressed)\n", sp, slen, dp, dlen);
	}
	return(dp);
}



unsigned char	bs_get8(	unsigned char *bsrc,
							unsigned long bit_pos,
							unsigned long bit_len	)
{	unsigned long	byte_pos=bit_pos>>3;
	unsigned long	byte_mod=bit_pos&0x7;
	unsigned short	rval=((	(*(bsrc+byte_pos+0)<<8)|
							(*(bsrc+byte_pos+1)   )	)<<byte_mod);
	if(bit_len>8)	bit_len=8;
	return((unsigned char)(rval>>(8+8-bit_len)));
}