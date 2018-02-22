/*
bin2c v98.10.20

MAF 98.10.20 Created from bin2c 1.0 by Christian Padovano
MAF 98.10.20 Converted to my format and compiled 32bit win95
Maf 16.12.26 Recompiled in VS2015 couple of code changes for compatability
*/


#include <stdio.h>
#include <string.h>
#include "stdafx.h"

#define BUF_LEN 1
#define LINE     12

int main(int argc, char *argv[])
{
	FILE *source, *dest;
	unsigned char buffer[BUF_LEN]; //, Dummy[20];
	int c;
	errno_t err;

	if ((argc < 4))
	{

		puts("bin2c  v16.12.26 by MaFF args:\n---------------------------------\n"
			" bin2c <binfile> <cfile> <struct>\n");
		return(0L);
	}

	if((err = fopen_s(&source,argv[1], "rb")) != 0)
//	if ((source = fopen(argv[1], "rb")) == NULL) DEPRICATED
	{
		printf("err : source file %s unavailable\n", argv[1]);
		return(20L);
	}

//	strcpy(Dummy, argv[2]);
	if(( err = fopen_s(&dest,argv[2], "wb+")) != 0)
//	if ((dest = fopen(argv[2], "wb+")) == NULL)
	{
		printf("err : destination file %s unavailable\n", argv[2]);
		fclose(source);
		return(20L);
	}

	fprintf(dest, "char %s[]=\n {\n  ", argv[3]);

	if (ferror(dest))
	{
		printf("ERROR writing on target file:  %s\n", argv[2]);
		fclose(source);
		fclose(dest);
		return(20L);
	}

	do
	{
		for (c = 0; ((c <= LINE) && (!feof(source))); c++)
		{
			fread(buffer, 1, 1, source);
			if (!feof(source)) fprintf(dest, "0x%02x,", *buffer);
			else fprintf(dest, "0x%02x", *buffer);
		}
		fprintf(dest, "\n  ");
	} while (!feof(source));

	fprintf(dest, "};\n\n");

	fclose(source);
	fclose(dest);

}



