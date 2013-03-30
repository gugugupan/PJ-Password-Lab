#ifndef __GP__CASER__
#define __GP__CASER__
#include <string>
using namespace std;

class Caser
{
private:
	int key ;
	bool check_char( char &c ) ;
public:
	Caser( int k ) ;
	string encode( string text ) ;
	string decode( string cipher ) ;
} ;

Caser :: Caser( int k )
{
	this -> key = k ;
}

bool Caser ::check_char( char &c )
{
	if ( 'a' <= c && c <= 'z' ) c = c - 'a' + 'A' ;
	if ( !( 'A' <= c && c <= 'Z' ) && c != ' ' ) return false ;
	return true ;
}

string Caser ::encode( string text )
{
	string res = "" ;
	for ( int i = 0 ; i < text .length() ; i ++ )
	{
		char c = text[ i ] ;
		if ( !check_char( c ) ) return "Error: text to encode is wrong" ;
		if ( c != ' ' ) 
			res += ( char ) ( ( c - 'A' + this -> key ) % 26 + 'A' ) ;
		else 
			res += ' ' ;
	}
	return res ;
}

string Caser ::decode( string cipher )
{
	string res = "" ;
	for ( int i = 0 ; i < cipher .length() ; i ++ )
	{
		char c = cipher[ i ] ;
		if ( !check_char( c ) ) return "Error: cipher to decode is wrong" ;
		if ( c != ' ' ) 
			res += ( char ) ( ( 26 + c - 'A' - this -> key ) % 26 + 'A' ) ;
		else 
			res += ' ' ;
	}
	return res ;
}

#endif