/*
Thomas Ng
CISC 3130 Data Structures
Assignment3
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

using namespace std; 
 

//String to Number and Number to String
template <typename T>
T StringToNumber ( const string &Text )//Text not by const reference so that the function can be used with a 
{                               //character array as argument
	stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}
template <typename T>
string NumberToString ( T Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
} // http://www.cplusplus.com/forum/articles/9645/

//Widget Linked List Node
struct node 
{
  int nodeQty;
  float nodePrice;
  node *next;
};

int main()
{
//Create first node
	node *head;
	node *current;
	
	head = new node;
	head -> next = 0;
	head -> nodeQty = 1;
	head -> nodePrice = 1;
	current	= head;
	
	int qtyNeeded=0, qty=0, promoCount=0, promoDiscount=0,x=0;
	int tranCounter=0, qtySold=0;
	float salePrice = 0, totalSale=0,promo=0;
	
	char flagNodeQty='N', flagNodePrice='N';	//flags will use char instead of bool because of true interpreted from "1.00"
	char flagPromo='N', flagSale='N';
	
	string transactionLine [30]={};
	string substr1;
	
	cout.precision(2);
	cout<<fixed; 

	
//Load files
	fstream transactionFile ("Assignment3Transactions");
	if (transactionFile.is_open())
	    cout << "(Transaction file loaded successfully)" << endl;
	else
	    cout << "(Problem loading transaction file! Is the \"Assignment3Transactions.txt\" file in the same folder as this program?)" << endl;
	
	do   //load records from transaction file into 1D transactionLine array until EOF
	{	
	    getline(transactionFile, transactionLine[x]);
	    //cout<<transactionLine[x]<<endl;
	    x++;
	    tranCounter++;
	} while (!transactionFile.eof());
	x=0;
	
//Process list. Ineffecient due to comparing substr1 so many times, but works.
	for(x=0;x<tranCounter;x++)	
	{
		stringstream ssTempTran (transactionLine[x]);
	    while ( ssTempTran.good() )		//Load transrecord 1D  into linked list
	    {	
			substr1 = "";
			getline( ssTempTran, substr1, ',' );
			if (head->next == 0)	//if no more nodes, set current here. Will prevent segmentation faults
				current=head;
			
			
		//PROCESS FOR "R" RECEIVING
			if (substr1 == "R" | substr1 == "r")	//If receiving new widgets
			{
				while ( current->next != 0)	//Traverse to end of list
					current = current->next;
				current->next = new node;	//new node at end of list
				current = current->next; 	//point Current to new/last node
				current->next = 0;         // cap last node
				flagNodeQty = 'Y';
			}
			else if (flagNodeQty=='Y')		//if current substr1 is for nodeQty
			{
				current->nodeQty = StringToNumber<int>(substr1);
				flagNodeQty='N';
				flagNodePrice='Y';
			}
			
			else if (flagNodePrice=='Y')		//if current substr1 is for nodePrice
			{
				current->nodePrice = StringToNumber<float>(substr1);
				flagNodePrice='N';
			}
			
			
		//PROCESS FOR "P" Promotion
			else if (substr1 == "P" | substr1 == "p")		
				flagPromo='Y';
			
			else if (flagPromo=='Y')
			{
				promoCount=2;	//set promoCount to next 2 customers
				promo= (StringToNumber<float>(substr1) / 100);
				flagPromo='N';
			}
			
			
		//PROCESS FOR "S" SALE
			else if (substr1 == "S" | substr1 == "s")	//If Sale
			{
				salePrice=0;
				flagSale='Y';
			}
			else if (flagSale=='Y')
			{
				//cout<<"\n\nflagSale==true"<<endl;
				qtyNeeded=StringToNumber<int>(substr1);
				cout<<"\n\n\t\t"<<qtyNeeded<<" Widgets Sold"<<endl; //Apperently you put this first, even if sale gets unfullfilled?
				current = head->next; 		//start from begining of list
				
				while (qtyNeeded>0)			//Begin searching and selling widgets from nodes
				{
					if(head->next != 0)		//while there is more than 1 node
					{
						if (current->nodeQty > qtyNeeded)	//if current node has plenty
						{
							salePrice=(current->nodePrice)*1.30;	//sale price with mark up
							cout<<qtyNeeded<<" widgets sold at $"
								<<current->nodePrice<<" each";
							cout<<"\tSales: $"<<(qtyNeeded*salePrice)<<endl;
							totalSale=totalSale+(qtyNeeded*salePrice);
							current->nodeQty = (current->nodeQty - qtyNeeded); //subtract qtyNeeded from current node
							qtyNeeded=0;
						}
						else if (current->nodeQty > 0)		//If current node doesn't have enough to supply the sale
						{
							salePrice=(current->nodePrice)*1.30;	//sale price with mark up
							cout<<current->nodeQty<<" widgets sold at $"
								<<current->nodePrice<<" each";
							cout<<"\tSales: $"<<(current->nodeQty*salePrice)<<endl;
							qtyNeeded= qtyNeeded - current->nodeQty;
							totalSale=totalSale + (salePrice*current->nodeQty);
							current->nodeQty = 0;
							
							if (current->nodeQty==0)		//if node is empty (delete)
							{
	                    		head->next=current->next;	//set 2nd node in list to 3rd's node. skipping or deleting 2nd node entirely
	                    		current=head->next;
							}
						}
						else if (current->nodeQty == 0)	//delete node if empty
						{
		            		head->next=current->next;	//set 2nd node in list to 3rd's node. skipping or deleting 2nd node entirely
		                	current=head->next;
						}
					}
					else if (qtyNeeded>0)		//only head node remains but still have orders to fulfill
					{
						cout<<"\t***Remainder of "<<qtyNeeded <<" Widgets not available***"<<endl;
						qtyNeeded=0;
					}
				}
				if (promoCount > 0)
				{
					cout<<"TotalSale: $"<<totalSale-(totalSale*promo)<<endl
						<<" Promotion applied! Customer saved $" <<(totalSale*promo)<<" (-"<< promo*100 <<"%!)"<<endl<<endl;
					promoCount--;
				}
				else
					cout<<"TotalSale: $"<<totalSale<<endl<<endl;
				flagSale='N';
				totalSale=0;
			}
		}

	}
	
	//At the end of the data before exiting the Vogram print out under a separate heading the widgets still left in stock and their original purchase price. 
	cout<<endl<<"\t\tREMAINING WIDGET INVENTORY"<<endl;
	current=head;	//start at begining of list
	while (current->next != 0)
	{
		current = current->next;
		cout<<current->nodeQty<<" widgets remaining at $"<<current->nodePrice<<" each."<<endl;
	}
}
