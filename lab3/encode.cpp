#include "DES.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	string text ;
	string cipher ;

	ifstream fin( "M.txt" ) ;
	fin >> text ;
	fin .close() ;
	fin .open( "K.txt" ) ;
	fin >> cipher ;
	fin .close() ;

/*
	short text[ DES_TEXT_LENGTH ] ;
	short cipher[ KEY_LENGTH ] ;
	ifstream fin( "M.txt" ) ;
	for ( int i = 0 ; i < DES_TEXT_LENGTH ; i ++ )
	{
		char c ;
		fin >> c ;
		text[ i ] = c - '0' ;
	}
	fin .close() ;
	fin .open( "K.txt" ) ;
	for ( int i = 0 ; i < KEY_LENGTH ; i ++ )
	{
		char c ;
		fin >> c ;
		cipher[ i ] = c - '0' ;
	}
	fin .close() ;
*/

	DES_machine D ;
	D .set_text( text ) ;
	D .set_cipher( cipher ) ;
	D .encode() ;

	for ( int i = 0 ; i < 16 ; i ++ )
	{
		int x = 0 ;
		for ( int j = i * 4 ; j < ( i + 1 ) * 4 ; j ++ )
			x = x * 2 + D .element( j ) ;
		cout << hex << x ;
	}
	cout << endl;

	ofstream fout( "C.txt" ) ;
	for ( int i = 0 ; i < 64 ; i ++ )
		fout << D .element( i ) ;
	fout << endl;
	fout .close() ;
}
