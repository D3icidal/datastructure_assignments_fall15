/*
Thomas Ng
CISC 3130 Data Structures
Assignment6
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

//My understanding of the instructions is that threeSort "will call three seperate sorts". "call" implies seperate functions.



void printvector(vector<int> vectorarr,int sizeOfvector)
{   
    for(int x=0;x<sizeOfvector;x++)
    {
        cout<<vectorarr[x];
    }
    cout<<endl;
}

void swap(vector<int>& vectorarr, int i, int j)
{
    
    int tempvector = vectorarr[i];
    vectorarr[i] = vectorarr[j];
    vectorarr[j] = tempvector;
}

void bubbleSort (vector<int>  bubblevector,int sizeOfvector)
{
    //int limbo=0;
    bool swapped=false;
    
    //Begin Dumb Sort (bubble maybe?)
    for(int x=0;x<sizeOfvector && swapped==false;x++)
    {
        swapped=false;
        for(int y=0;y<sizeOfvector;y++)
        {
            if (bubblevector[y]>bubblevector[y+1])
            {
                swap(bubblevector,y,y+1);
                //limbo=bubblevector[y];
                //bubblevector[y]=bubblevector[y+1];
                //bubblevector[y+1]=limbo;
                swapped=true;
            }   
        }
    }
}


void quickSort (vector<int>& quickvector,int left, int right)
{
    cout<<"Quicksort: "<<left<<", "<<right<<endl;
    int mid = left + (right - left) / 2;        
    int x = left;
    int y = right;
    int pivot = quickvector[mid];   //use quickSort with pivot at mid instead of at the end

    while (left<y || x<right)  
    {
        while(quickvector)
            x++;
        while(quickvector[y]>pivot)
            y--;
                    if(x<=y)
        {
            swap(quickvector,x,y);
            x++;
            y--;
        }
        else
        {
            if(left<y)
                quickSort(quickvector,left,y);
            if(x<right)
                quickSort(quickvector,x,right);
            return;
        }
    }
}


bool threeSortSubProgram (vector<int>& vectorTBS, const int sizeOfvector)        //use vector size of "100" because " initializer fails to determine size of" error
{
    
//Use seperate vector for each sort. Small enough anyway. after Debug maybe clean up?
    int bubblevector[sizeOfvector]={};
    bubblevector=vectorTBS;
    bubbleSort(bubblevector,sizeOfvector);
    cout<<endl<<"Bubble Sort Output: ";
    printvector(bubblevector,sizeOfvector);
    
    std::vector<int,sizeOfvector> quickvector = vectorTBS;
    quickSort(quickvector,0,sizeOfvector-1);
    cout<<endl<<"Quick Sort Output: ";
    printvector(quickvector,sizeOfvector);
    
    std::vector<int,sizeOfvector> tournvector = vectorTBS;
    //CALL TOURN
    
}

int main()
{
    int vectorTBS[]={1,2,3,4,5,7,6};
    int size = (sizeof(vectorTBS)/sizeof(vectorTBS[0]));  //simpliest way I can find of getting # of elements in vector in c++ -_-
    cout<<endl;
}