#ifndef __GP__LFSR__
#define __GP__LFSR__

#include <cstdio>
#include <cstring>

char cypher ;

void around() // Make cypher to new turn
{
	int bit8 = cypher & ( 1 << 7 ) ,
		bit6 = ( cypher & ( 1 << 5 ) ) << 2 ,
		bit5 = ( cypher & ( 1 << 4 ) ) << 3 ,
		bit4 = ( cypher & ( 1 << 3 ) ) << 4 ;
	cypher = ( cypher >> 1 ) | ( bit8 ^ bit6 ^ bit5 ^ bit4 ) ;
}


#endif
