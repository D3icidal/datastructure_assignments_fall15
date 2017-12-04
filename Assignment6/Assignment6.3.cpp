/*
Thomas Ng
CISC 3130 Data Structures
Assignment6
*/ 

//VERSION 3 of ASSIGNMENT6. 
    //No C++11 array, cloud9 fails with it. fewer vectors. Reduced passing by reference and pointers. No structs.
    //No memcpy. Just make all arrays sized 1000 and then manually copy contents from a different method.
    //external swap method. use std instead 
//My understanding of the instructions is that threeSort "will call three seperate sorts". "call" implies seperate functions.

#include <iostream>
//#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
//#include <iomanip>
//#include <stdio.h>
//#include <stdlib.h>
//#include <array>          // ***WARNING: Must use c++11 which is NOT standard on cloud9. Terminal here: g++ -std=c++11 Assignment6.cpp -o main

using namespace std; 

template <typename T>

T StringToNumber ( const string &Text, T defValue = T() )
{
    stringstream ss;
    for ( string::const_iterator i=Text.begin(); i!=Text.end(); ++i )
        if ( isdigit(*i) || *i=='-')         //MUST keep '-' or you will miss terminator "-999"
            ss << *i;
    T result;
    return ss >> result ? result : defValue;
}

template <typename T>
string NumberToString ( T Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
}


void printArray(int *array,const int sizeOfArray)
{   
    for(int x=0;x<sizeOfArray;x++)
    {
        cout<<array[x]<<", ";
    }
    cout<<endl;
}

/*
void swap(int array[1000], int i, int j)
{
    cout<<"Swapping: "<<array[i]<<" and "<<array[j]<<endl; //DEBUGING
    int tempArray = array[i];
    array[i] = array[j];
    array[j] = tempArray;
}
*/

void bubbleSort (int *bubbleArray,const int sizeOfArray, int& bubbleComp, int& bubbleInter)   //pass by reference to keep void
{
    //bool swapped=false;
    /*int limbo=0;
    for(int i=0; i<sizeOfArray; i++)
    {
        for(int j=0; j<sizeOfArray-1; j++) 
        { 
            if(bubbleArray[j]>bubbleArray[j+1])
            {
                limbo=bubbleArray[j];
                bubbleArray[j]=bubbleArray[j+1];
                bubbleArray[j+1]=limbo;
            }
        }
    }*/
    for(int x=0;x<sizeOfArray;x++)
    {
        bubbleComp++;
        for(int y=0;y<sizeOfArray-1;y++)
        {   
            bubbleComp++;
            //cout<<bubbleComp<<endl;   //DEBUGING
            if (bubbleArray[y]>bubbleArray[y+1])
            {
                bubbleInter++;
                std::swap(bubbleArray[y],bubbleArray[y+1]);
                //swap(bubbleArray,y,y+1);
            }   
        }
    }
}



//QUICK SORT
    /*
    find the pivot (mid point)
    move all values less than the pivot value to the left.
    move all values larger than the pivot to the right.
    recursivly quick-sort the values less than(or equal)
    recursivly quick-sort the values larger than.
    */
int quickPartion(int *quickArray, const int left, const int right, int& quickComp, int& quickInter) 
{
    const int mid = left + (right - left) / 2;
    const int pivot = quickArray[mid];
    quickInter++;
    std::swap(quickArray[mid],quickArray[left]); //ust std swap. might need c++11
    int i = left + 1;
    int j = right;
    //cout<<"i: "<<i<<" j:"<<j<<endl; //DEBUGING
    while (i <= j) 
    {   
        quickComp++;
        while(i <= j && quickArray[i] <= pivot) 
        {
            quickComp++;
            i++;
        }
        
        while(i <= j && quickArray[j] > pivot) 
        {
            quickComp++;
            j--;
        }

        quickComp++;
        if (i < j) 
        {
            quickInter++;
            std::swap(quickArray[i], quickArray[j]);
        }
    }
    quickInter++;
    std::swap(quickArray[i - 1],quickArray[left]);
    //cout<<"i: "<<i<<endl; //DEBUGING
    return i - 1;
}

void quickSort(int *quickArray, const int left, const int right, const int sizeOfArray, int& quickComp, int& quickInter)
{
    quickComp++;    // this if statement counts as comparison
    if (left >= right) 
    {
        return;
    }
    int part = quickPartion(quickArray, left, right,quickComp, quickInter);
    //cout << "Quick Sort:" << left << "," << right << " part=" << part << "\n"; //DEBUGIG
    //printArray(quickArray, sizeOfArray);

    quickSort(quickArray, left, part - 1, sizeOfArray, quickComp, quickInter);
    quickSort(quickArray, part + 1, right, sizeOfArray, quickComp, quickInter);
}

//HEAP SORT
/*
	HeapSort: a form of tree sort with 2 stages. 
	Stage 1: create heap. (Heap: is an almost complete binary tree with the property that no node is less than it's children node (in value).
	Can actually just use a temp variable and swap the elements around.
	Stage 2: adjusting Heap: Remove the largest (root) node from the file and you put it into a list - 
	by moving the last tree time with the largest. Then readjust the heap: rerun the rules against elements in the tree to confirm it conforms to the rules. 

    
    1. Remove the topmost item (the largest) and replace it with the rightmost leaf. The topmost item is stored in an array. 
    2. Re-establish the heap.
    3. Repeat steps 1 and 2 until there are no more items left in the heap. The sorted elements are now stored in an array.
*/


void maxHeap(int *heapArray, int i, const int sizeOfArray, int& heapComp, int& heapInter)
{
    int j=0;
    int temp=0;
    temp = heapArray[i];
    j = 2*i;
    while (j <= sizeOfArray)
    {   
        heapComp++;
        //cout<<"j: "<<j<<endl;   //DEBUGING
        //if (j < n)
        //    if (heapArray[j+1] > heapArray[j])
        if (j < sizeOfArray && heapArray[j+1] > heapArray[j])
        {
            heapComp++;
            j = j+1;
        }
            
        if (temp > heapArray[j])
        {
            heapComp++;
            break;
        }
        else if (temp <= heapArray[j])
        {
            heapComp++;
            heapInter++;
            heapArray[j/2] = heapArray[j];
            j = 2*j;
        }
    }
    heapArray[(j/2)] = temp;
    return;
}


void buildMaxHeap(int *heapArray, const int sizeOfArray,int& heapComp, int& heapInter)
{
    
    for(int i = sizeOfArray/2; i >= 1; i--)
    {
        maxHeap(heapArray, i, sizeOfArray,heapComp, heapInter);
    }
}

void heapSort(int *heapArray, const int sizeOfArray, int& heapComp, int& heapInter)
{
    buildMaxHeap(heapArray,sizeOfArray,heapComp, heapInter);
    int temp;
    for (int i = sizeOfArray-1; i >= 2; i--)
    {
        heapInter++;
        temp = heapArray[i];
        //cout<<"temp: "<<temp<<endl; //DEBUGING
        heapArray[i] = heapArray[1];
        heapArray[1] = temp;
        maxHeap(heapArray, 1, i - 1, heapComp, heapInter);
    }
}


void arrayCopier (int *arrayOriginal, int arrayCopy[1000], const int sizeOfArray)
{
    //cout<<endl<<endl<<"arrayCopier Started!"<<endl; //DEBUGING
    for (int x=0;x<sizeOfArray;x++)
    {
        arrayCopy[x]=arrayOriginal[x];
        //cout<<"arrayCopy[x]: "<<arrayCopy[x]<<endl; //DEBUGING
    }   
}


void comparisonSubProgram(int& bC,int& bI,int& qC,int& qI,int& hC,int& hI)
{
    int compArray[3]={bC,qC,hC}; //presort
    int nullComp=0;
    int nullInter=0;
    bubbleSort(compArray, 3, nullComp, nullInter);
    
    
    if (bC==compArray[2])    //if largest
        cout<<"Most Comparisons: Bubble Sort"<<endl;
    else if (qC==compArray[2])    //if largest
            cout<<"Most Comparisons: Quick Sort"<<endl;
        else if (hC==compArray[2])    //if largest
            cout<<"Most Comparisons: Heap Sort"<<endl;
    
    if (bC==compArray[0])    //if least
        cout<<"Least Comparisons: Bubble Sort"<<endl;
    else if (qC==compArray[0])    //if least
            cout<<"Least Comparisons: Quick Sort"<<endl;
        else if (hC==compArray[0])    //if least
            cout<<"Least Comparisons: Heap Sort"<<endl;
     
    int interArray[3]={bI,qI,hI}; //presort
    nullComp=0;
    nullInter=0;
    bubbleSort(interArray, 3, nullComp, nullInter);
    //cout<<bI<<qI<<hI;
    if (bI==interArray[2])    //if largest
        cout<<"Most Interchanges: Bubble Sort"<<endl;
    else if (qI==interArray[2])    //if largest
            cout<<"Most Interchanges: Quick Sort"<<endl;
        else if (hI==interArray[2])    //if largest
            cout<<"Most Interchanges: Heap Sort"<<endl;
    
    if (bI==interArray[0])    //if least
        cout<<"Least Interchanges: Bubble Sort"<<endl;
    else if (qI==interArray[0])    //if least
            cout<<"Least Interchanges: Quick Sort"<<endl;
        else if (hI==interArray[0])    //if least
            cout<<"Least Interchanges: Heap Sort"<<endl;        
}


void threeSortSubProgram (int *arrayTBS,const int sizeOfArray)        //use array size of "100" because " initializer fails to determine size of" error
{
    
//Use seperate array for each sort. Small enough anyway. after Debug maybe clean up?
    int bubbleComp=0;
    int bubbleInter=0;
    int bubbleArray[1000]={};    //compile time array: can't use variable qty.
    arrayCopier(arrayTBS,bubbleArray, sizeOfArray);
    bubbleSort(bubbleArray, sizeOfArray, bubbleComp, bubbleInter);
    cout<<endl<<"Bubble Sort Output: \t";
    printArray(bubbleArray,sizeOfArray);
    cout<<"\tBubble Comparisons: "<< bubbleComp <<endl;
    cout<<"\tBubble Interchanges: "<< bubbleInter <<endl;
    
    int quickComp=0;
    int quickInter=0;
    int quickArray[1000]={};
    arrayCopier(arrayTBS, quickArray, sizeOfArray);
    quickSort(quickArray,0,(sizeOfArray-1), sizeOfArray, quickComp, quickInter);
    cout<<endl<<"Quick Sort Output: \t";
    printArray(quickArray,sizeOfArray);
    cout<<"\tQuick Comparisons: "<< quickComp <<endl;
    cout<<"\tQuick Interchanges: "<< quickInter <<endl;
    
    int heapComp=0;
    int heapInter=0;
    int heapArray[1000]={};
    arrayCopier(arrayTBS, heapArray, sizeOfArray);
    heapSort(heapArray, sizeOfArray, heapComp, heapInter);
    cout<<endl<<"Heap Sort Output: \t";
    printArray(heapArray,sizeOfArray);
    cout<<"\tHeap Comparisons: "<< heapComp <<endl;
    cout<<"\tHeap Interchanges: "<< heapInter <<endl;
    
    cout<<endl;
    comparisonSubProgram(bubbleComp, bubbleInter, quickComp, quickInter, heapComp, heapInter);
}

void readInSubProgram()
{
    int i=0;
    int arrayTBS[1000]={};
    //Open transaction file
	fstream transactionFile ("Assignment6Transactions.txt");
	if (transactionFile.is_open())
	    cout << "(Transaction file loaded successfully)" << endl;
	else
	    cout << "(Problem loading transaction file! Is the \"Assignment6Transactions.txt\" file in the same folder as this program?)" << endl;
	    
	string transactionLine [30]={};
    int tranCounter=0,x=0;
    string substr1;    
	    
	do   //load records from transaction file into 1D transactionLine array until EOF
	{	
	    //cout<<"test1"<<endl;    //DEBUGING 
	    getline(transactionFile, transactionLine[x]);
	    //cout<<transactionLine[x]<<endl;   //DEBUGING
	    x++;
	    tranCounter++;
	} while (!transactionFile.eof());
	//cout<<"tranCounter: "<<tranCounter<<endl;    //DEBUGING 
	
	for(x=0;x<tranCounter;x++)	
	{
    	//cout<<"for loop"<<endl;    //DEBUGING 
    	stringstream ssTempTran (transactionLine[x]);
    	while ( ssTempTran.good() )	
        {	
            substr1 = "";
    		getline( ssTempTran, substr1, ',' );
    		if (substr1.find("num") < 10)   //if it is the description portion
    		    cout<<"============================================================================"<<endl
    		        <<"\t\tSorting "<<substr1<<endl<<endl<<"Original order: ";
    	    else
    	    {   
    	        arrayTBS[i]=StringToNumber<int>(substr1);
                cout<<substr1;
                i++;
    	    }
        }
        //int size = (sizeof(arrayTBS)/sizeof(arrayTBS[0]));  //simpliest way I can find of getting # of elements in array in c++ -_-
        cout<<"\nOriginal Array:  \t";
        printArray(arrayTBS,i);
        threeSortSubProgram(arrayTBS, i);
	}
}


int main()
{
    readInSubProgram();
	
	//int arrayTBS[]={1,2,3,9,5,7,6,5,4};
    //cout<<"\nOriginal Array:  \t";
    //printArray(arrayTBS,size);
    //threeSortSubProgram(arrayTBS, size);
}

