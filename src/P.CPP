#include	<windows.h>
#include	<stdio.h>

extern	void			decode_tim2(	char *,
										unsigned long,
										unsigned char *	);
extern	unsigned long	ps2_dcb_lzss(	unsigned char *,
										unsigned char *,
										unsigned long,
										unsigned long	);
extern	HANDLE	NonOverWriteCreateFile(LPCSTR);
		void	decode_p(char *,unsigned long,unsigned char *, char *);

void	decode_p(char *name,unsigned long slen,unsigned char *sbuf, char *ext)
{
	HANDLE				hitm;
	char				tfn[0x100];
	unsigned long		tul1;
	char				*file_ext;

	if(	(*(sbuf+0x00)=='O')&&
		(*(sbuf+0x01)=='O')&&
		(*(sbuf+0x02)=='C')&&
		(*(sbuf+0x03)=='H')		){
		unsigned long slen = *(unsigned long*)(sbuf + 0x08);
		unsigned long dlen = *(unsigned long*)(sbuf + 0x0c);
		unsigned long in_endian = *(unsigned long*)(sbuf + 0x20);
		printf("endian check: %x\n", in_endian);
		if (in_endian == 0x8000000) {
			// this swaps the endianness of the thing.
			// this will only run if the file has 0x00000008 at offset 0x20
			// The value gets read as little endian, so it's checking for it's value in little endian, not big endian.
			slen = _byteswap_ulong(slen);
			dlen = _byteswap_ulong(dlen);
		}
		unsigned char	*dbuf;
		dbuf=new unsigned char[dlen+0x200];

		printf("Compressed length: %x\n", slen);
		printf("Decompressed length: %x\n", dlen);

		ps2_dcb_lzss(	sbuf+0x800,
						dbuf,
						slen,
						dlen	);

//		sprintf(tfn,"%s.pex",name);
//		hitm=NonOverWriteCreateFile((LPCSTR)tfn);
//		WriteFile(hitm,dbuf,*(unsigned long *)(sbuf+0x0c),&tul1,NULL);
//		CloseHandle(hitm);

		decode_p(name,dlen,dbuf, ext);
		delete[]	dbuf;
	}
	else {
		file_ext = _strlwr(ext);
		sprintf(tfn, "%s_decomp%s", name, file_ext);
		hitm = NonOverWriteCreateFile((LPCSTR)tfn);
		WriteFile(hitm, sbuf, slen, &tul1, NULL);
		CloseHandle(hitm);
	}
}
