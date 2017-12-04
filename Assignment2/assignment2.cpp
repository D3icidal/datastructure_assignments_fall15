/*
Thomas Ng
CISC 3130 Data Structures
Assignment2 
*/ 
 
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std; 
 

//String to Number and Number to String
// http://www.cplusplus.com/forum/articles/9645/
template <typename T>
T StringToNumber ( const string &Text )//Text not by const reference so that the function can be used with a 
{                               //character array as argument
	stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

// http://www.cplusplus.com/forum/articles/9645/
template <typename T>
string NumberToString ( T Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
} 



int main()
{ 

//Declare Variables
int invRecord [5] [4]={};        // Make a 2D array 5x4, with the horizontal row being warehouse, item1 qty, item2 qty, item3 qty 
int transactions [100] [5]={};    // Make 2D array 100x5 for: O/S, Warehouse,  item1 qty, item2 qty, item3 qty // "0" = Order, "5" = Shipment
string transactionLine [20]={};
string substr1;
float itm1, itm2, itm3;         // Make 3 variables for the 3 amounts 
string tempInv1D, substr;
bool unfilled = false, tmpMarker=false;
int warehouse,resultCounter=0,tranCounter=0,qtyneeded=0, x=0,y=0,z=0;
int tmpWHInv=0, tmpTranqty=0,tmpQty=0;
string warehouses []={"New York", "Los Angeles", "Miami", "Houston", "Chicago"};
float price []= {0,2,7,8.5};        //prices of each item, "0" added to make it easier during processing    
float linePrice=0; 
float transferFee=1.1;          // 10% transfer fee from one warehouse to another
vector<string> resulttran(100);
int whWidth = 15; //width for columns "Shipment for *wharehous*e"

cout << "\n\t\tBegin Updating Master Balances for Accounts\n\n"<<endl;
cout.precision(2);
cout<<fixed;        //to display $0.xx double decimal

/*
warehouses []={
0 = "New York"
1 = "Los Angeles"
2 = "Miami"
3 = "Houston"
4 = "Chicago"
*/

//Fill invRecord with zeros for debugging
//for (int x=0;x<5;x++)
//    for (int y=0;y<4;y++)
//        invRecord[x][y]="0";
        
        

//Load files
fstream transactionFile ("Assignment 2 Transactions.txt");
if (transactionFile.is_open())
    cout << "(Transaction file loaded successfully)" << endl;
else
    cout << "(Problem loading transaction file! Is the \"Assignment 2 transaction.txt\" file in the same folder as this program?)" << endl;


do   //load records from transaction file into 1D transactionLine array until EOF
{
    getline(transactionFile, transactionLine[x]);
    x++;
    tranCounter++;
} while (!transactionFile.eof());
x=0;
resulttran.clear();    


//Load transrecord 1D  into  2D array without commas  
while(x < (tranCounter))
{
    stringstream ssTempTran (transactionLine[x]);
    while ( ssTempTran.good() )
    {
        substr1 = "";
        getline( ssTempTran, substr1, ',' );
        //cout<<"\n\t\t\t\t\tsubstr1: "<<substr1;
        resulttran.push_back(substr1);
        if (tmpMarker==true)         //reassign warehouse names as numbers in order to work with Int arrays. Plus Switches suck with strings and even chars on cloud9
        {
                if (substr1 == "New York")
                    transactions[y][z]=0;
                if (substr1 ==  "Los Angeles")
                    transactions[y][z]=1;
                if (substr1 ==  "Miami")
                    transactions[y][z]=2;
                if (substr1 ==  "Houston")
                    transactions[y][z]=3;
                if (substr1 ==  "Chicago")
                    transactions[y][z]=4;
                tmpMarker=false;
        }
        else
        {
             if (substr1 == "s")            //if Order or Shipment, set to "0" for order, or "5" for shipment
            {
                transactions[y][z]=5; 
                tmpMarker=true;
            }
            else
                if (substr1 == "o")            //if Order or Shipment, set to "0" for order, or "5" for shipment
                {
                    transactions[y][z]=0;        
                    tmpMarker=true;
                }
                else
                    transactions[y][z]=StringToNumber<int>(substr1);
                   
        }
        //resulttran[resultCounter];
        z++;
    }
    resulttran.clear(); //must use clear otherwise counter goes to 0, but push_back goes back to end of vector.
    z=0;
    resultCounter++;
    x++;
    y++;
}


cout<<"resultCounter: "<<resultCounter<<endl;
//Process transactions: Order or Shipment
for (x=0; x<resultCounter; x++)
{
    if (transactions[x][0] == 5)   //if shipment
    {
        warehouse=transactions[x][1];   //use "warehouse" to avoid as many calls to the array.
        cout<<"\nShipment for "<<setw(whWidth)<<left<<warehouses[warehouse]<<"\t"   //cout each element (city amt1 amt2 amt3)
            <<transactions[x][2]<<"\t"<<transactions[x][3]<<"\t"<<transactions[x][4]<<endl;
        tmpQty=invRecord[warehouse][1] + transactions[x][2];
            invRecord[warehouse][1] = tmpQty;
        tmpQty=invRecord[warehouse][2] + transactions[x][3];
            invRecord[warehouse][2] = tmpQty;
        tmpQty=invRecord[warehouse][3] + transactions[x][4];
            invRecord[warehouse][3] = tmpQty;
        cout<<"  Updated Inventory"<<"\t\t"<<right<<invRecord[warehouse][1]
            <<"\t"<<invRecord[warehouse][2]<<"\t"<<invRecord[warehouse][3];
    }

    cout<<endl;
    unfilled=false;  
    
    if (transactions[x][0] == 0)   //if Order
    {
        warehouse=transactions[x][1];
        for (y=1;y<4;y++)
        {
            if (transactions[x][y+1] > invRecord[warehouse][y])      // if insufficient supply
            {
                int idx1=0, idx2=0, idx3=0, largestWH=0, secondLargest=0;
                qtyneeded=transactions[x][y+1]-invRecord[warehouse][y];
                
                for (idx1=0;idx1<3;idx1++)         //begin searching for largest warehouse
                {
                    if (invRecord [idx1][y] > invRecord [idx1+1][y])  
                    {
                        largestWH=idx1;
                    }
                }
                //cout<<"\n\t\tlargestWwarehouse: " << largestWH << warehouses[largestWH]<<endl;
                        
                if ( invRecord[largestWH][y] >= qtyneeded )        //transfer if other largest warehouse has qtyneeded of item 
                {   
                    tmpQty=invRecord [largestWH][y] - qtyneeded;   //subtract from largest wh in stocks
                        invRecord [largestWH][y] = tmpQty;     
                    tmpQty=invRecord [warehouse][y] + qtyneeded;
                        invRecord [warehouse][y] = tmpQty;                  //ship to warehouse needed
                    tmpQty=invRecord [warehouse][y] - transactions[x][y+1];
                        invRecord [warehouse][y] = tmpQty;                  //subtraction for order;
                    cout <<endl << qtyneeded << " of item " << y << " shipped from "
                        << warehouses[largestWH] << " to " << warehouses[warehouse] << endl;
                    cout<<"  Updated Inventory"<<"\t"<<right<<"\t"<<invRecord[warehouse][1]
                        <<"\t"<<invRecord[warehouse][2]<<"\t"<<invRecord[warehouse][3]<<endl;
                    linePrice=linePrice + (qtyneeded * (price[y]*transferFee))+((transactions[x][y+1]-qtyneeded) * price[y]); //Current Lineprice + price with transfers + normal price
                }
                else    //Order Unfilled
                {
                    cout<<"\n\tOrder Unfilled\n\n";
                    unfilled =true;
                }
            }
            else    // If sufficient supply
            {
                tmpQty=(invRecord[warehouse][y]) - transactions[x][y+1];
                invRecord [warehouse][y] = tmpQty;
                linePrice=linePrice + (transactions[x][y+1]) * (price[y]);
            }
        }
        
        cout << "Order for " <<setw(whWidth)<<left<< warehouses[warehouse] <<"\t"<< invRecord[warehouse][1] <<"\t"<< invRecord[warehouse][2] <<"\t"<< invRecord[warehouse][3] << endl
            << "  Price of Order: $" << linePrice<<endl;
        linePrice=0;
        unfilled=false;
    }
}        
        
}