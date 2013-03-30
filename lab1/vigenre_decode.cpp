#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include "Vigenre.h"
using namespace std;

string text , cipher , key ;
int main()
{
	ifstream fin ;
	fin .open( "C.txt" ) ;
	getline( fin , cipher ) ;
	fin .close() ;

	fin .open( "key_vigenre.txt" ) ;
	fin >> key ;
	fin .close() ;

	Vigenre machine( key ) ;
	text = machine .decode( cipher ) ;

	cout << text << endl;

	ofstream fout ;
	fout .open( "M.txt" ) ;
	fout << text << endl;
	fout .close() ;
}