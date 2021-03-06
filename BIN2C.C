
/*
   bin2c v98.10.20

   MAF 98.10.20 Created from bin2c 1.0 by Christian Padovano
   MAF 98.10.20 Converted to my format and compiled 32bit win95
*/


#include <stdio.h>
#include <string.h>

#define BUF_LEN 1
#define LINE     12

int main( argc, argv )
int argc;
char *argv[];
{
    FILE *source,*dest;
    unsigned char buffer[BUF_LEN], Dummy[20];
    int c;

    if ( (argc < 4) )
    {

      puts("bin2c  v98.10.20 by MaFF args:\n---------------------------------\n"
           " bin2c <binfile> <cfile> <struct>\n");
      exit(0L);
    }

    if( (source=fopen( argv[1], "rb" )) == NULL )
    {
      printf("err : source file %s unavailable\n",argv[1]);
      exit(20L);
    }

    strcpy(Dummy,argv[2]);

    if( (dest=fopen( Dummy, "wb+" )) == NULL )
    {
      printf("err : destination file %s unavailable\n",Dummy);
      fclose(source);
      exit(20L);
    }

    fprintf( dest, "char %s[]=\n {\n  ", argv[3] );

    if( ferror( dest ) )
    {
     printf( "ERROR writing on target file:  %s\n",argv[2] );
     fclose(source);
     fclose(dest);
     exit(20L);
    }

    do
    {
     for ( c=0; ((c <= LINE) && (! feof( source ) )) ; c++)
     {
      fread( buffer, 1, 1, source );
      if (! feof( source ) ) fprintf(dest,"0x%02x,",*buffer);
      else fprintf(dest,"0x%02x",*buffer);
     }
     fprintf(dest,"\n  ");
    }
    while( ! feof( source ) );

    fprintf(dest,"};\n\n");

    fclose(source);
    fclose(dest);

}



