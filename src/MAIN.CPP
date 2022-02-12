///////////////////////////////////////////////////////////////////////////////
//	PS2	Code Geass Lelouch of the Rebellion Lost Colors converter
//	Original program made on 08/06/2011 by	AZUCO
//		Original program name: kallen.exe
//		Link to original program: https://azuco.sakura.ne.jp/column/ag_ps2cglc/
//		
//	Edited on 16/08/2021 by nfsman34 to make the program more versitale
//		with games that share the same compression (like Sonic Riders Zero Gravity)
//		as well as with files in big endian.
///////////////////////////////////////////////////////////////////////////////
#include	<windows.h>
#include	<stdio.h>

extern	void	decode_tim2	(char *,unsigned long,unsigned char *);
extern	void	decode_p	(char *,unsigned long,unsigned char *, char*);



int	main(int argc,char *argv[])
{
	unsigned char	*buff=NULL;

	HANDLE			hndl;

	unsigned long	file_size;

	unsigned long	tul;
	unsigned long	fnargc=1;

	char			drive[MAX_PATH];
	char			dir[MAX_PATH];
	char			fname[MAX_PATH];
	char			ext[MAX_PATH];

	printf("PS2 Code Geass Lelouch of the Rebellion Lost Colors Converter\n\tOriginal program by AZUCO\n\tEdited by nfsman34\n");

	if(argc==1){
		printf("How to use:\n\ooch_decomp.exe <filename>\n");
		exit(0);
	}

	hndl=CreateFile(argv[1],
					GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hndl==(HANDLE)-1){
		printf("\t%s - %d\n",argv[fnargc],fnargc);
		printf("\tError\tsource file not found\n");
		exit(-1);	}

	file_size=GetFileSize(hndl,NULL);

	_splitpath(argv[fnargc],drive,dir,fname,ext);

	buff=new unsigned char[file_size];
	ReadFile(hndl,buff,file_size,&tul,NULL);
	decode_p(fname,file_size,buff, ext);

esc:
	CloseHandle(hndl);
	if(buff!=NULL){	delete[]	buff;	buff=NULL;	}
}
