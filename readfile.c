#include "stdio.h"
#include "stdlib.h"
  
 
int main( void )
{
    FILE *fp;
    fp = fopen("C:\\Users\\LoveSky\\Desktop\\test_string.txt" , "r");
    fseek( fp , 0 , SEEK_END );
    int file_size;
    file_size = ftell( fp );
    printf( "%d" , file_size );
    char *tmp;
    fseek( fp , 0 , SEEK_SET);
    tmp =  (char *)malloc( file_size * sizeof( char ) );
    fread( tmp , file_size , sizeof(char) , fp);
    printf("%s" , tmp );
    return 0;
}