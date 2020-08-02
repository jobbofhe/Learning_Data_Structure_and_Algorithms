/*
* @Author: shuqiang
* @Date:   2020-07-25 18:00:42
* @Last Modified by:   Administrator
* @Last Modified time: 2020-07-25 19:18:52
*/

#if 0

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	printf("sizeof(unsigned char): %d\n", sizeof(unsigned char));
	printf("sizeof(unsigned long): %d\n", sizeof(unsigned long));


	return 0;
}

#endif


#if 0
int FindSubString( char* pch )
{
    int   count  = 0;
    char  * p1   = pch;
    while ( *p1 != '\0' )
    {   
        if ( *p1 == p1[1] - 1 )
        {
            p1++;
            count++;
        }else  {
            break;
        }
    }
    int count2 = count;
    while ( *p1 != '\0' )
    {
        if ( *p1 == p1[1] + 1 )
        {
            p1++;
            count2--;
        }else  {
            break;
        }
    }
    if ( count2 == 0 )
        return(count);
    return(0);
}
void ModifyString( char* pText )
{
    char  * p1   = pText;
    char  * p2   = p1;
    while ( *p1 != '\0' )
    {
        int count = FindSubString( p1 );
        if ( count > 0 )
        {
            *p2++ = *p1;
            sprintf( p2, "%i", count );
            while ( *p2 != '\0' )
            {
                p2++;
            }
            p1 += count + count + 1;
        }else  {
            *p2++ = *p1++;
        }
    }
}
void main( void )
{
    char text[32] = "XYBCDCBABABA";
    ModifyString( text );
    printf( text );
}  



#endif 


typedef enum TEST {
	heshu,
	qiang,
	nuli,
	jixu
	
}Tes;

int main(int argc, char const *argv[])
{
	Tes T;
	printf("%d\n", T[0]);


	return 0;
}
