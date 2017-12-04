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
//#include <array>          // ***WARNING: Must use c++11 which is NOT standard on cloud9. Terminal here: g++ -std=c++11 Assignment6.cpp -o main

using namespace std; 

//My understanding of the instructions is that threeSort "will call three seperate sorts". "call" implies seperate functions.

void printArray(int array[101]);
void swap(int array[101], int i, int j);
void bubbleSort (int bubbleArray[101],const int sizeOfArray);
void arrayCopier (int arrayOriginal[101], int arrayCopy[101], int sizeOfArray);
void threeSortSubProgram (int arrayTBS, int sizeOfArray) ;

int main()
{
    int arrayTBS[]={1,2,3,4,5,7,6};
    int size = (sizeof(arrayTBS)/sizeof(arrayTBS[0]));  //simpliest way I can find of getting # of elements in array in c++ -_-
    cout<<endl;
}



void printArray(int array[101],const int sizeOfArray)
{   
    for(int x=0;x<sizeOfArray;x++)
    {
        cout<<array[x];
    }
    cout<<endl;
}

void swap(int array[101], int i, int j)
{
    
    int tempArray = array[i];
    array[i] = array[j];
    array[j] = tempArray;
}

void bubbleSort (int bubbleArray[101],const int sizeOfArray)
{
    //int limbo=0;
    bool swapped=false;
    
    //Begin Dumb Sort (bubble maybe?)
    for(int x=0;x<sizeOfArray && swapped==false;x++)
    {
        swapped=false;
        for(int y=0;y<sizeOfArray;y++)
        {
            if (bubbleArray[y]>bubbleArray[y+1])
            {
                swap(bubbleArray,y,y+1);
                //limbo=bubbleArray[y];
                //bubbleArray[y]=bubbleArray[y+1];
                //bubbleArray[y+1]=limbo;
                swapped=true;
            }   
        }
    }
}

/*
void quickSort (int quickArray[101],int left, int right)    //quicksort using mid as pivot, starting from outside working inwards
{
    cout<<"Quicksort Indexes - Left: ["<<left<<"]  Right: ["<<right<<"]"<<endl;
    int mid = left + (right - left) / 2;        
    int x = left;
    int y = right;
    int pivot = quickArray[mid];  //pivot by value, not by index

    while (left<y || x<right)  
    {
        cout<<"Left: ["<<left<<"]  Right: ["<<right<<"]"<<endl;
        while(quickArray)
            x++;
        while(quickArray[y]>pivot)
            y--;
                    if(x<=y)
        {
            std::swap(quickArray[y],quickArray[y+1]);
            //swap(quickArray,x,y);
            x++;
            y--;
        }
        else
        {
            if(left<y)
                quickSort(quickArray,left,y);
            if(x<right)
                quickSort(quickArray,x,right);
            return;
        }
    }
    cout<<"fin";
}
*/
void arrayCopier (int arrayOriginal[101], int arrayCopy[101], int sizeOfArray)
{
    cout<<endl<<endl<<"arrayCopier Started!"<<endl; //DEBUGING
    for (int x=0;x<sizeOfArray;x++)
    {
        arrayCopy[x]=arrayOriginal[x];
        cout<<"arrayCopy[x]: "<<arrayCopy[x]<<endl; //DEBUGING
    }   
}


void threeSortSubProgram (int arrayTBS[101], int sizeOfArray)        //use array size of "100" because " initializer fails to determine size of" error
{
    
//Use seperate array for each sort. Small enough anyway. after Debug maybe clean up?
    int bubbleArray[101]={};    //compile time array: can't use variable qty.
    arrayCopier(arrayTBS,bubbleArray, sizeOfArray);
    //bubbleArray=arrayTBS;
    bubbleSort(bubbleArray,sizeOfArray);
    cout<<endl<<"Bubble Sort Output: ";
    printArray(bubbleArray,sizeOfArray);
    
    //array<int,sizeOfArray> quickArray = arrayTBS;
    /*
    quickSort(quickArray,0,sizeOfArray-1);
    cout<<endl<<"Quick Sort Output: ";
    printArray(quickArray,sizeOfArray);
    
    std::array<int,sizeOfArray> tournArray = arrayTBS;
    //CALL TOURN
    */
}