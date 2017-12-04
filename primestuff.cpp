/*
Thomas Ng
CISC 3130 Data Structures
Assignment6


build array 2 ... max (2mil)


loop (make idx=3, idx is less then half of max, idx ++2 (skip the odds)
	set all multiples of idx to nil

compress
==================

build array 2 ... max (2mil)


for (x=3, x< 1/10 of max, x++)			//increment by 2, not 1, don't need evens.
	for (y=3, y< 1/10 of max, y++)		//increment by 2, not 1, don't need evens.
		if array is here, delete

compress
print array?


=====================

build bool array []2 ... max] (2mil)

for (x=3, x< 1/10 of max, x++)			//increment by 2, not 1, don't need evens.
	for (y=3, y< 1/10 of max, y++)		//increment by 2, not 1, don't need evens.
		set array to false

compress
print array?


*/ 
 
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
//#include <array>            // WARNING: Must use c++11 which is NOT standard on cloud9. Terminal here: g++ -std=c++11 Assignment6.cpp -o main

using namespace std; 

int main()
{

    //vector<bool> array (2000000, false);
    bool array[2000000]={};
    int maxSize=2000000;
    int x;
    int y;
    int z;
    int half=(maxSize/2);
    int tenper = (maxSize/10);
    cout<<"Array Size: "<<maxSize<<endl;
    cout<<"Half: "<<half<<endl;
    cout<<"10 percent: "<<tenper<<endl;
    
    
    //cout<<"Print all non primes:"<<endl;
    for (x=2; x< half; x++) {	        //10%//increment by 2, not 1, don't need evens.
    	for (y=2; y< tenper; y++){		//50%//increment by 2, not 1, don't need evens.
        	z=x*y;
        	if (z>maxSize)
        	    y=tenper;
        	else
        	    array[z]=true;
        	//cout<<z<<"\t";
    	}
    }
    cout<<endl<<"z: "<<z<<endl;
    
    cout<<endl<<endl<<"print primes"<<endl<<endl;
    
    for (int i=3;i<maxSize;i++){
        //cout<<endl<<endl<<"print primes"<<endl<<endl;
        if (array[i] == 0){
            cout<<i<<endl;
        }
    }
		
}