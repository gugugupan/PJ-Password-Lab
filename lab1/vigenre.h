#ifndef __GP__VIGENRE__
#define __GP__VIGENRE__
#include <string>
using namespace std;

class Vigenre
{
private:
	string key ;
	bool check_char( char &c ) ;
public:
	Vigenre( string s ) ;
	string encode( string text ) ;
	string decode( string cipher ) ;
} ;

Vigenre :: Vigenre( string s )
{
	this -> key = s ;
}

bool Vigenre ::check_char( char &c )
{
	if ( 'a' <= c && c <= 'z' ) c = c - 'a' + 'A' ;
	if ( !( 'A' <= c && c <= 'Z' ) && c != ' ' ) return false ;
	return true ;
}

string Vigenre ::encode( string text )
{
	string res = "" ;
	int x = 0 ;
	int key_len = this -> key .length() ;
	for ( int i = 0 ; i < text .length() ; i ++ )
	{
		char c = text[ i ] ;
		if ( !check_char( c ) ) return "Error: text to encode is wrong" ;
		if ( c != ' ' ) 
			res += ( char ) ( ( c - 'A' + this -> key[ x ++ % key_len ] - 'A' ) % 26 + 'A' ) ;
		else 
			res += ' ' ;
	}
	return res ;
}

string Vigenre ::decode( string cipher )
{
	string res = "" ;
	int x = 0 ;
	int key_len = this -> key .length() ;
	for ( int i = 0 ; i < cipher .length() ; i ++ )
	{
		char c = cipher[ i ] ;
		if ( !check_char( c ) ) return "Error: cipher to decode is wrong" ;
		if ( c != ' ' ) 
			res += ( char ) ( ( 26 + c - 'A' - this -> key[ x ++ % key_len ] + 'A' ) % 26 + 'A' ) ;
		else 
			res += ' ' ;
	}
	return res ;
}

#endif