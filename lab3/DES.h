/*
	================================================
	DES Machine
	================================================

	This library is using to simulate DES algorithm.
	DES algorithm is using to encode and decode text
	and it using smae method to encode and decode.
	DES algorithm using 56 bit code to encode.

	Author: Pan Gu
	Date: May 1st, 2013. On the train to ShangHai
*/

#ifndef __DES__KEY__GP__
#define __DES__KEY__GP__
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

/*  ================================================
	Class key for the cipher key of DES algorithm.
	Key object need 'string' or 'short*' to initialize
	and it can doing some transform or get its element.
	================================================ */
const int KEY_LENGTH = 64 ;
const int HALF_KEY_LENGTH = 32 ;
const int OUTPUT_KEY_LENGTH = 48 ;

class Key {
private:
	short key[ KEY_LENGTH ] ; // each is 0/1
public:
	Key() ; // Initialize cipher key with NULL
	Key( const short* ) ; // Initialize cipher key with short array
	void set_key( const short * ) ; // Rewrite cipher key with new array
	void set_key( const string ) ; // Rewrite cipher key with new string 
	void PC1_transform() ; // Doing PC1 transform
	short *PC2_transform() ; // Doing PC2 transform and return the 48bit key
						   // This method can't change the 'key' of object
						   // just return a 'int*' for the generate key
						   // And the int* will be malloc in this method
	void LS_transform( int turn ) ; // Doing LS transform with No turn
	void generate_checksum() ; // Generate the 8th 16th.. checksum bit
	short element( int i ) ; // get the ith element of key
} ;

Key::Key()
{
	memset( this -> key , 0 , sizeof( short ) * KEY_LENGTH ) ;
}

Key::Key( const short * data ) 
{
	set_key( data ) ;
}
void Key::set_key( const short *data )
{
	memcpy( this -> key , data , sizeof( short ) * KEY_LENGTH ) ;
}

void Key::set_key( const string str )
{
	if ( str .length() > 8 ) 
	{
		printf( "Error: The length of string not correct.\n" ) ;
		exit( 1 ) ;
	}
	memset( this -> key , 0 , sizeof( short ) * KEY_LENGTH ) ;
	for ( int i = 0 ; i < str .length() ; i ++ ) 
	{
		int x = str[ i ] ;
		int j = i * 8 + 7 ;
		while ( x > 0 )
		{
			this -> key[ j -- ] = x % 2 ;
			x /= 2 ;
		}
	}
	//generate_checksum() ;
}

void Key::generate_checksum()
{
	for ( int i = 7 ; i < KEY_LENGTH ; i += 8 )
	{
		this -> key[ i ] = 0 ; 
		for ( int j = i - 7 ; j < i ; j ++ )
			this -> key[ i ] ^= this -> key[ j ] ;
	}
}

const int PC1[ 8 ] [ 7 ] = {
	{ 57 , 49 , 41 , 33 , 25 , 17 , 9 } ,
	{ 1 , 58 , 50 , 42 , 34 , 26 , 18 } ,
	{ 10 , 2 , 59 , 51 , 43 , 35 , 27 } ,
	{ 19 , 11 , 3 , 60 , 52 , 44 , 36 } , 
	{ 63 , 55 , 47 , 39 , 31 , 23, 15 } ,
	{ 7 , 62 , 54 , 46 , 38 , 30 , 22 } ,
	{ 14 , 6 , 61 , 53 , 45 , 37 , 29 } , 
	{ 21 , 13 , 5 , 28 , 20 , 12 , 4 } 
} ;
void Key::PC1_transform() 
{
	short cici[ KEY_LENGTH ] ;
	memcpy( cici , this -> key , sizeof( short ) * KEY_LENGTH ) ;
	for ( int i = 0 ; i < 8 ; i ++ )
		for ( int j = 0 ; j < 7 ; j ++ )
			this -> key[ i * 8 + j ] = cici[ PC1[ i ] [ j ] - 1 ] ;
	//generate_checksum() ;
}

const int PC2[ 8 ] [ 6 ] = {
	/*
	{ 14 , 17 , 11 , 24 , 1 , 5 } ,
	{ 3 , 28 , 15 , 6 , 21 , 10 } ,
	{ 23 , 19 , 12 , 4 , 26 , 8 } ,
	{ 16 , 7 , 27 , 20 , 13 , 2 } ,
	{ 41 , 52 , 31 , 37 , 47 , 55 } ,
	{ 30 , 40 , 51 , 45 , 33 , 48 } ,
	{ 44 , 49 , 39 , 56 , 34 , 53 } ,
	{ 46 , 42 , 50 , 36 , 29 , 32 }
	*/
	{ 15 , 19 , 12 , 27 , 1 , 5 } ,
	{ 3 , 31 , 17 , 6 , 23 , 11 } ,
	{ 26 , 21 , 13 , 4 , 29 , 9 } ,
	{ 18 , 7 , 30 , 22 , 14 , 2 } ,
	{ 46 , 59 , 35 , 42 , 53 , 62 } ,
	{ 34 , 45 , 58 , 51 , 37 , 54 } ,
	{ 50 , 55 , 44 , 63 , 38 , 60 } ,
	{ 52 , 47 , 57 , 41 , 33 , 36 } 
} ;
short* Key::PC2_transform()
{
	short *res = new short[ OUTPUT_KEY_LENGTH ] ;
	for ( int i = 0 ; i < 8 ; i ++ )
		for ( int j = 0 ; j < 6 ; j ++ )
			res[ i * 6 + j ] = this -> key[ PC2[ i ] [ j ] - 1 ] ;
	return res ;
}

const int LS[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1} ;
void Key::LS_transform( int turn ) // Begin with 0
{
	short cici[ KEY_LENGTH ] ;
	memcpy( cici , this -> key , sizeof( short ) * KEY_LENGTH ) ;

	for ( int i = 0 ; i < HALF_KEY_LENGTH ; i ++ )
	{
		if ( i % 8 == 7 ) continue ;
		int x = i + LS[ turn ] ;
		if ( x % 8 == 7 || ( LS[ turn ] == 2 && ( x - 1 ) % 8 == 7 ) ) x ++ ;
		if ( x >= HALF_KEY_LENGTH ) x -= HALF_KEY_LENGTH ;
		this -> key[ i ] = cici[ x ] ;
	}

	for ( int i = HALF_KEY_LENGTH ; i < KEY_LENGTH ; i ++ )
	{
		if ( i % 8 == 7 ) continue ;
		int x = i + LS[ turn ] ;
		if ( x % 8 == 7 || ( LS[ turn ] == 2 && ( x - 1 ) % 8 == 7 ) ) x ++ ;
		if ( x >= KEY_LENGTH ) x -= HALF_KEY_LENGTH ;
		this -> key[ i ] = cici[ x ] ;
	}
	//generate_checksum() ;
}

short Key::element( int i )
{
	if ( i < 0 || i >= KEY_LENGTH ) return -1 ;
	return this -> key[ i ] ;
}


/*  ================================================
	Class DES_machine is using to simulate DES 
	algorithm.
	Key object (in front) is included in DES machine
	object.
	================================================*/

void swap( int &a , int &b )
{
	a ^= b ; b ^= a ; a ^= b ;
}

const int DES_TEXT_LENGTH = 64 ;
const int HALF_DES_TEXT_LENGTH = 32 ;
const int DES_SBOX_LENGTH = 48 ;

class DES_machine {
private:
	short text[ DES_TEXT_LENGTH ] ; // each short number is 0/1
	Key cipher ; // cipher key for DES algorithm
	int states_code ; // If is 1 means DES algorithm is running

public:
	DES_machine() ; // Initialize DES with NULL
	DES_machine( const short * , const short * ) ; // Initialize DES with two short array which is text and cipher
	DES_machine( const string , const string ) ; // Initialize DES with two string which length limit 8

	void set_text( const short * ) ; // Rewrite text with short array
	void set_cipher( const short * ) ; // Rewrite cipher with short array
	void set_text( string ) ; // Rewrite text with string
	void set_cipher( string ) ; // Rewrite cipher with string 

	void iteration( int ) ; // One encode iteration for DES algorithm
	void iteration_decode( int ) ; // One decode iteration for DES algorithm

	void PU_transform() ; // Doing PU_transform before DES iteration
	void PU_slide_transform() ; // Doing PU_transform after DES iteration
	short* E_transform() ; // Doing E transform for R part
						   // The 48 bit array will malloc in this method
	void S_box_transform( const short * , const short * ) ;
							// Make two array go through sbox and save result in R part
	void reverse_transform() ; // Reverse L part and R part
	void P_transform() ; // Doing P transform for R part

	short element( int i ) ; // Get ith element of text
	void encode() ; // Start DES encode algorithm
	void decode() ;
} ;

DES_machine::DES_machine()
{
	memset( text , 0 , sizeof( text ) ) ;
	states_code = 0 ;
}

DES_machine::DES_machine( const short * text , const short * cipher )
{
	set_text( text ) ;
	set_cipher( cipher ) ;
	states_code = 0 ;
}

DES_machine::DES_machine( const string text , const string cipher )
{
	set_text( text ) ;
	set_cipher( cipher ) ;
	states_code = 0 ;
}

void DES_machine::set_text( const short * data )
{
	if ( states_code == 1 ) return ;
	memcpy( this -> text , data , sizeof( short ) * DES_TEXT_LENGTH ) ;	
}

void DES_machine::set_cipher( const short *data )
{
	if ( states_code == 1 ) return ;
	this -> cipher .set_key( data ) ;
}

void DES_machine::set_text( const string str ) 
{
	if ( states_code == 1 ) return ;
	if ( str .length() > 8 ) 
	{
		printf( "Error: The length of string not correct.\n" ) ;
		exit( 1 ) ;
	}
	memset( this -> text , 0 , sizeof( short ) * DES_TEXT_LENGTH ) ;
	for ( int i = 0 ; i < str .length() ; i ++ ) 
	{
		int x = str[ i ] ;
		int j = i * 8 + 7 ;
		while ( x > 0 )
		{
			this -> text[ j -- ] = x % 2 ;
			x /= 2 ;
		}
	}
}

void DES_machine::set_cipher( const string str )
{
	if ( states_code == 1 ) return ;
	this -> cipher .set_key( str ) ;
}

short DES_machine::element( int i )
{
	return this -> text[ i ] ;
}

void DES_machine::encode()
{
	PU_transform() ;
	this -> cipher .PC1_transform() ;

	states_code = 1 ;
	for ( int iteration_num = 1 ; iteration_num <= 16 ; iteration_num ++ )
	{
		iteration( iteration_num ) ;
		/*
		printf( "Case %d: " , iteration_num ) ;
		for ( int i = 0 ; i < 64 ; i ++ )
		{
			printf( "%d" , this -> text[ i ] ) ;
			if ( i % 32 == 31 ) printf( " " ) ;
		}
		printf( "\n" ) ;
		*/
	}
	PU_slide_transform() ;
}

void DES_machine::decode()
{
	PU_transform() ;
	this -> cipher .PC1_transform() ;
	states_code = 1 ;

	iteration_decode( 1 ) ;

	PU_slide_transform() ;
}

void DES_machine::iteration( int turn )
{
	// Save R part
	short tmp[ 32 ] ;
	memcpy( tmp , &( this -> text[ 32 ] ) , sizeof( short ) * 32 ) ; 

	// Cipher to LS transform
	this -> cipher .LS_transform( turn - 1 ) ;

	// S box operate
	S_box_transform( E_transform() , this -> cipher .PC2_transform() ) ;

	// R part to P transform
	P_transform() ;

	// Xor L part
	for ( int i = HALF_DES_TEXT_LENGTH ; i < DES_TEXT_LENGTH ; i ++ )
		this -> text[ i ] ^= this -> text[ i - HALF_DES_TEXT_LENGTH ] ;

	// Copy R part to L part 
	memcpy( this -> text , tmp , sizeof( short ) * 32 ) ;

	// If turn == 16 will not reverse
	if ( turn == 16 ) reverse_transform() ;
}

void DES_machine::iteration_decode( int turn )
{
	// Save cipher and Doing LS transform
	this -> cipher .LS_transform( turn - 1 ) ;
	Key tmp_cipher = this -> cipher ;

	// Doing Keyi+1 first
	if ( turn < 16 ) iteration_decode( turn + 1 ) ;

	// Save R part
	short tmp[ 32 ] ;
	memcpy( tmp , &( this -> text[ 32 ] ) , sizeof( short ) * 32 ) ; 

	// S box operate with tmp_cipher
	S_box_transform( E_transform() , tmp_cipher .PC2_transform() ) ;

	// R part to P transform
	P_transform() ;

	// Xor L part
	for ( int i = HALF_DES_TEXT_LENGTH ; i < DES_TEXT_LENGTH ; i ++ )
		this -> text[ i ] ^= this -> text[ i - HALF_DES_TEXT_LENGTH ] ;

	// Copy R part to L part
	memcpy( this -> text , tmp , sizeof( short ) * 32 ) ;

	// If turn == 1 will not reverse
	if ( turn == 1 ) reverse_transform() ;
}

int S[ 8 ] [ 64 ] = {
	{14,0,4,15,13,7,1,4,2,14,15,2,11,13,8,1,3,10,10,6,6,12,12,11,5,9,9,5,0,3,7,8,4,15,1,12,14,8,8,2,13,4,6,9,2,1,11,7,15,5,12,11,9,3,7,14,3,10,10,0,5,6,0,13} , // S1
	{15,3,1,13,8,4,14,7,6,15,11,2,3,8,4,14,9,12,7,0,2,1,13,10,12,6,0,9,5,11,10,5,0,13,14,8,7,10,11,1,10,3,4,15,13,4,1,2,5,11,8,6,12,7,6,12,9,0,3,5,2,14,15,9} , // S2 
	{10,13,0,7,9,0,14,9,6,3,3,4,15,6,5,10,1,2,13,8,12,5,7,14,11,12,4,11,2,15,8,1,13,1,6,10,4,13,9,0,8,6,15,9,3,8,0,7,11,4,1,15,2,14,12,3,5,11,10,5,14,2,7,12} , // S3
	{7,13,13,8,14,11,3,5,0,6,6,15,9,0,10,3,1,4,2,7,8,2,5,12,11,1,12,10,4,14,15,9,10,3,6,15,9,0,0,6,12,10,11,1,7,13,13,8,15,9,1,4,3,5,14,11,5,12,2,7,8,2,4,14} , // S4
	{2,14,12,11,4,2,1,12,7,4,10,7,11,13,6,1,8,5,5,0,3,15,15,10,13,3,0,9,14,8,9,6,4,11,2,8,1,12,11,7,10,1,13,14,7,2,8,13,15,6,9,15,12,0,5,9,6,10,3,4,0,5,14,3} , // S5
	{12,10,1,15,10,4,15,2,9,7,2,12,6,9,8,5,0,6,13,1,3,13,4,14,14,0,7,11,5,3,11,8,9,4,14,3,15,2,5,12,2,9,8,5,12,15,3,10,7,11,0,14,4,1,10,7,1,6,13,0,11,8,6,13} , // S6
	{4,13,11,0,2,11,14,7,15,4,0,9,8,1,13,10,3,14,12,3,9,5,7,12,5,2,10,15,6,8,1,6, 1,6,4,11,11,13,13,8,12,1,3,4,7,10,14,7,10,9,15,5,6,0,8,15,0,14,5,2,9,3,2,12} , // S7
	//{8,1,13,15,2,13,8,8,4,10,6,3,15,7,11,4,1,12,10,5,9,6,3,11,14,0,5,14,0,9,12,2,7,2,11,1,4,14,1,7,9,4,12,10,14,8,2,13,0,15,6,12,10,9,13,0,15,3,3,5,5,6,8,11} // S8
	{13,1,2,15,8,13,4,8,6,10,15,3,11,7,1,4,10,12,9,5,3,6,14,11,5,0,0,14,12,9,7,2,7,2,11,1,4,14,1,7,9,4,12,10,14,8,2,13,0,15,6,12,10,9,13,0,15,3,3,5,5,6,8,11}
} ;
void DES_machine::S_box_transform( const short * text , const short * cipher )
{
	short cici[ DES_SBOX_LENGTH ] ;
	for ( int i = 0 ; i < DES_SBOX_LENGTH ; i ++ )
		cici[ i ] = text[ i ] ^ cipher[ i ] ;
	delete text ;
	delete cipher ;

	for ( int i = 0 ; i < 8 ; i ++ )
	{
		int x = 0 ;
		for ( int j = i * 6 ; j < ( i + 1 ) * 6 ; j ++ )
			x = x * 2 + cici[ j ] ;
		x = S[ i ] [ x ] ;
		for ( int j = HALF_DES_TEXT_LENGTH + ( i + 1 ) * 4 - 1 ; j >= HALF_DES_TEXT_LENGTH + i * 4 ; j -- )
		{
			this -> text[ j ] = x % 2 ;
			x /= 2 ;
		}
	}
}

int PU[ 8 ] [ 8 ] = {
	{ 58 , 50 , 42 , 34 , 26 , 18 , 10 , 2 } ,
	{ 60 , 52 , 44 , 36 , 28 , 20 , 12 , 4 } ,
	{ 62 , 54 , 46 , 38 , 30 , 22 , 14 , 6 } , 
	{ 64 , 56 , 48 , 40 , 32 , 24 , 16 , 8 } ,
	{ 57 , 49 , 41 , 33 , 25 , 17 , 9 , 1 } ,
	{ 59 , 51 , 43 , 35 , 27 , 19 , 11 , 3 } ,
	{ 61 , 53 , 45 , 37 , 29 , 21 , 13 , 5 } ,
	{ 63 , 55 , 47 , 39 , 31 , 23 , 15 , 7 } 
} ;
void DES_machine::PU_transform()
{
	short tmp[ DES_TEXT_LENGTH ] ;
	memcpy( tmp , this -> text , sizeof( short ) * DES_TEXT_LENGTH ) ;
	for ( int i = 0 ; i < 8 ; i ++ )
		for ( int j = 0 ; j < 8 ; j ++ ) 
			this -> text[ i * 8 + j ] = tmp[ PU[ i ] [ j ] - 1 ] ;
}

int PU_[ 8 ] [ 8 ] = {
	{ 40 , 8 , 48 , 16 , 56 , 24 , 64 , 32 } ,
	{ 39 , 7 , 47 , 15 , 55 , 23 , 63 , 31 } ,
	{ 38 , 6 , 46 , 14 , 54 , 22 , 62 , 30 } ,
	{ 37 , 5 , 45 , 13 , 53 , 21 , 61 , 29 } ,
	{ 36 , 4 , 44 , 12 , 52 , 20 , 60 , 28 } ,
	{ 35 , 3 , 43 , 11 , 51 , 19 , 59 , 27 } ,
	{ 34 , 2 , 42 , 10 , 50 , 18 , 58 , 26 } ,
	{ 33 , 1 , 41 , 9 , 49 , 17 , 57 , 25 }
} ;
void DES_machine::PU_slide_transform()
{
	short tmp[ DES_TEXT_LENGTH ] ;
	memcpy( tmp , this -> text , sizeof( short ) * DES_TEXT_LENGTH ) ;
	for ( int i = 0 ; i < 8 ; i ++ )
		for ( int j = 0 ; j < 8 ; j ++ ) 
			this -> text[ i * 8 + j ] = tmp[ PU_[ i ] [ j ] - 1 ] ;
}

int P[ 8 ] [ 4 ] = {
	{ 16 , 7 , 20 , 21 } ,
	{ 29 , 12 , 28 , 17 } , 
	{ 1 , 15 , 23 , 26 } ,
	{ 5 , 18 , 31 , 10 } ,
	{ 2 , 8 , 24, 14 } ,
	{ 32 , 27 , 3 , 9 } ,
	{ 19 , 13 , 30 , 6 } ,
	{ 22 , 11 , 4 , 25 }
} ;
void DES_machine::P_transform()
{
	short tmp[ DES_TEXT_LENGTH ] ;
	memcpy( tmp , this -> text , sizeof( short ) * DES_TEXT_LENGTH ) ;
	for ( int i = 0 ; i < 8 ; i ++ )
		for ( int j = 0 ; j < 4 ; j ++ ) 
			this -> text[ HALF_DES_TEXT_LENGTH + i * 4 + j ] = tmp[ HALF_DES_TEXT_LENGTH + P[ i ] [ j ] - 1 ] ;
}

int E[ 8 ] [ 6 ] = {
	{ 32 , 1 , 2 , 3 , 4 , 5 } ,
	{ 4 , 5 , 6 , 7 , 8 , 9 } ,
	{ 8 , 9 , 10 , 11 , 12 , 13 } ,
	{ 12 , 13 , 14 , 15 , 16 , 17 } ,
	{ 16 , 17 , 18 , 19 , 20 , 21 } ,
	{ 20 , 21 , 22 , 23 , 24 , 25 } ,
	{ 24 , 25 , 26 , 27 , 28 , 29 } ,
	{ 28 , 29 , 30 , 31 , 32 , 1 }
} ;
short* DES_machine::E_transform() 
{
	short *res = new short[ DES_SBOX_LENGTH ] ;
	for ( int i = 0 ; i < 8 ; i ++ ) 
		for ( int j = 0 ; j < 6 ; j ++ )
			res[ i * 6 + j ] = this -> text[ E[ i ] [ j ] + HALF_DES_TEXT_LENGTH - 1 ] ;
	return res ;
}

void DES_machine::reverse_transform()
{
	for ( int i = 0 ; i < HALF_DES_TEXT_LENGTH ; i ++ )
		swap( this -> text[ i ] , this -> text[ HALF_DES_TEXT_LENGTH + i ] ) ;
}

#endif 
