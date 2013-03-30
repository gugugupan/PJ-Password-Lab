#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include "caser.h"
using namespace std;

string text , cipher ;
int key ;
int main()
{
	ifstream fin ;
	fin .open( "C.txt" ) ;
	getline( fin , cipher ) ;
	fin .close() ;

	fin .open( "key.txt" ) ;
	fin >> key ;
	fin .close() ;

	Caser machine( key ) ;
	text = machine .decode( cipher ) ;

	cout << text << endl;

	ofstream fout ;
	fout .open( "M.txt" ) ;
	fout << text << endl;
	fout .close() ;
}