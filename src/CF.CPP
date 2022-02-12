///////////////////////////////////////////////////////////////////////////////
//	AFS converter
//		Create File
//			030909
//				by	AZUCO
///////////////////////////////////////////////////////////////////////////////

#include	<windows.h>
#include	<stdio.h>

HANDLE	NonOverWriteCreateFile(LPCSTR);

HANDLE	NonOverWriteCreateFile(LPCSTR name)
{	HANDLE			htmp;
	char			tfna[0x100];
	char			tfnb[0x100];
	char			*tfnp;
	unsigned long	tcnt;

	htmp=CreateFile(name,GENERIC_WRITE,0,0,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,0);
	if(htmp!=INVALID_HANDLE_VALUE)	return(htmp);

	for(tcnt=1;tcnt!=0x10000;tcnt++){
		strcpy(tfna,name);

		tfnp=strrchr(tfna,'.');
		if(tfnp==NULL)	
			tfnp=tfna+strlen(tfna);
		strcpy(tfnb,tfnp);
	
		sprintf(tfnp,"_%04X",tcnt);
		tfnp+=5;
		strcpy(tfnp,tfnb);

		htmp=CreateFile(tfna,GENERIC_WRITE,0,0,CREATE_NEW,
													FILE_ATTRIBUTE_NORMAL,0);
		if(htmp!=INVALID_HANDLE_VALUE)	return(htmp);
	}

	return((HANDLE)-1);
}
