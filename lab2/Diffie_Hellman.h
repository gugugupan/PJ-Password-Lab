#ifndef __DIFFIE__HELLMAN__
#define __DIFFIE__HELLMAN__

#include <iostream>
using namespace std;

int prime ;
int a ;

class Diffie_hellman
{
private:
	int private_key ;

public:
	int public_key ;
	Diffie_hellman( int ) ;
	int get_key( int ) ;
} ;

Diffie_hellman :: Diffie_hellman( int key ) 
{
	this -> private_key = key ;
	int cici = 1 ;
	for ( int t = key ; t ; t -- )
		cici = ( cici * a ) % prime ;
	this -> public_key = cici ;
}

int Diffie_hellman :: get_key( int other_key ) 
{
	int cici = 1 ;
	for ( int t = this -> private_key ; t ; t -- )
		cici = ( cici * other_key ) % prime ;
	return cici ;
}

#endif 
