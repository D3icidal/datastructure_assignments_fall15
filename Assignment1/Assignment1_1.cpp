/*
Thomas Ng
CISC 3130 Data Structures
Assignment 1 (2nd try)
*/

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

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
    int custNumber,transactionNumber, masterLineCounter=0,temp1,temp2, i=0,x=0, y=0, z=0,idx=0,idx2=0; //XYZ for array
    int balanceDue, itemPrice, closingBalance, abcTotalBalance;
    int nameWidth=21, amountWidth=9, itemWidth=17; //table sizing
    
    string custName, masterRecord[100][3], masterRecordTemp, masterLine [30];//masterLine is for entire row/record until I get to split it into individual variables
    string transactionItem, strgCustNum, transactionRecord[100][15][5], tempTransactionRecord[200][8], transactionLine [200]; //transactionrecord up to 100 customers containing up to 15 transactions with 5 columns.
    vector<string> result(100);
    vector<string> resulttran(100);
    //ringTemp.str ("test");
    masterLine[1]="a"; //for debugging use later.
    masterLine[2]="a"; //for debugging use later.
    
    char transactionType; //"O" for purchase, "P" for payment
    
    double qty, tempMasterBal, tempTransAmtP, tempTransAmtO;

// intro stuff
    cout << "\n\tABC Hardware Company Inc Accounts Receivable" << endl;
    cout << "\t\t End-Of-Month Invoice Processing\n" << endl;

//Load Files Master and Transaction - Test if they opened - Notify User
//void loadFiles() //function not worth the trouble ATM. Maybe come back to it when finished.
fstream masterFile ("Assignment 1 Master.txt");
ifstream transactionFile ("Assignment 1 Transactions.txt");

    if (transactionFile.is_open())
        cout << "(Transaction file loaded successfully)" << endl;
    else
        cout << "(Problem loading transaction file! Is the \"Assignment 1 Master.txt\" file in the same folder as this program?)" << endl;
    if (masterFile.is_open())
        cout << "(Master file loaded successfully)" << endl <<endl<<endl;
    else
    {
        cout << "(Problem loading master file! Is the \"Assignment 1 Master.txt\" file in the same folder as this program?)" << endl;

    }
    
//load customer records from Master file into 1D array until EOF
do 
{
    getline(masterFile, masterLine[x]);
    //cout<<endl<<"MasterLine: "<<masterLine[x]<<endl; //just for debugging
    x++;
    masterLineCounter++;
}while (!masterFile.eof());   
//cout << x++ << " lines from MasterFile loaded succesffully" << endl;

//Confirm masterfile read properly
if (masterLine[1] != "a") //and (masterLine[2][1] != "a")
    cout << "Master file read sucessfully\n";
    
x=0;
y=0;
z=0;
masterRecordTemp=masterRecord[y][z];
int resultCounter=0,tranCounter=0;


result.clear();
//Load 1D masterline into masterRecord 2D array without commas
while(y<masterLineCounter)
{
    stringstream ssTemp (masterLine[x]);
    while( ssTemp.good() )
    {
        string substr;
        getline( ssTemp, substr, ',' );
        result.push_back( substr );
        masterRecord[y][z]=result[resultCounter];
        resultCounter++;
        z++;
    }
    resultCounter=0;
    result.clear(); //must use clear otherwise counter goes to 0, but push_back goes bak to end of vector.
    cout <<masterRecord[y][0]<<"\t"<< setw(nameWidth) << left << masterRecord[y][1]<<right<< setw(amountWidth) <<masterRecord[y][2]<<endl;
    z=0;
    x++; //increment masterLine
    y++;
}

resultCounter=0;
tranCounter=0;
x=0;
y=0;
z=0;


do   //load records from transaction file into 1D transactionLine array until EOF
{
    getline(transactionFile, transactionLine[x]);
    //cout<<endl<<"TransactionLine "<<x<<": "<<transactionLine[x]; //debuging
    x++;
    tranCounter++;
} while (!transactionFile.eof());

x=0;
y=0;
z=0;
resulttran.clear();
resultCounter=0;


tranCounter--;
string substr1;



//Load transrecord 1D  into  2D array without commas  
while(x < (tranCounter))
{
    stringstream ssTempTran (transactionLine[x]);

    while ( ssTempTran.good() )
    {
        substr1 = "";
        getline( ssTempTran, substr1, ',' );
        resulttran.push_back( substr1 );
        //resulttran[z]=substr1;
        tempTransactionRecord[y][z]=substr1;//resulttran[resultCounter];
        resultCounter++;
        z++;
    }
    resultCounter=0;
    resulttran.clear(); //must use clear otherwise counter goes to 0, but push_back goes back to end of vector.
    z=0;
    x++;
    y++;
}
//cout << "\n tempTransactionRecord[1][5]" <<tempTransactionRecord[1][5]<<endl;
resulttran.clear();
i=0;
x=0;
y=0;
z=0;

x=0;
//END OF READ IN PORTION
//BEGIN UPDATING MASTER BALANCES

masterLineCounter--;
//UPDATE BALANCES
cout << "\n\t\tBegin Updating Master Balances for Accounts\n\n"<<endl;
cout.precision(2);
cout<<fixed;        //to display $0.xx double decimal
do
{
    cout<< "\n\t"<<setw(nameWidth) << left<< masterRecord[idx][1]<<"\tCustomer Number: " << masterRecord[idx][0] <<endl;
    cout<<endl<<"\t\t\t Previous Balance $" <<right<<setw(amountWidth)<<masterRecord[idx][2]<<endl<<endl;
    
    while (masterRecord[idx][0] == tempTransactionRecord[y][1] )
    { 
        double tempBalance =0;
        substr1 = masterRecord[idx][2];  //Because dealing with Arrays is a PITA. Set string to array element, then convert that string to floating point number.
        tempMasterBal = StringToNumber<double>(substr1);
        //cout << tempMasterBal << endl;
        
        substr1 = tempTransactionRecord[y][4];
        qty = StringToNumber<double>(substr1);
        //cout << tempTransAmtO << endl;
        
        substr1 = tempTransactionRecord[y][5];
        tempTransAmtO = StringToNumber<double>(substr1);
        tempTransAmtO *= qty;                           //Total line cost of QTY times Item Price
        //cout << tempTransAmtO << endl;
        
        substr1 = tempTransactionRecord[y][3];
        tempTransAmtP = StringToNumber<double>(substr1);
        //cout << tempTransAmtO << endl;
        
        if (tempTransactionRecord[y][0] == "O")     //IF ORDER
        {
            tempBalance=tempMasterBal;
            tempMasterBal += tempTransAmtO;
            substr1 = NumberToString(tempMasterBal);
            masterRecord[idx][2] = substr1;
            cout<< "Tran # " << tempTransactionRecord[y][2] << "\t" << setw(itemWidth) << left << tempTransactionRecord[y][3] <<setw(amountWidth)
                <<right<<"\t($"<<tempTransactionRecord[y][5]<<")"<<left<<setw(amountWidth)<<"   \tQTY: " << tempTransactionRecord[y][4] 
                << right<<"  \t$ " <<setw(amountWidth)<< right <<setw(amountWidth)<< tempTransAmtO << endl;
        }
            else 
            {
                if (tempTransactionRecord[y][z] == "P") //IF PAYMENT
                {
                    tempBalance=tempMasterBal;
                    tempMasterBal -= tempTransAmtP;
                    substr1 = NumberToString(tempMasterBal);
                    masterRecord[idx][2] = substr1;
                    cout<< "Tran # " << tempTransactionRecord[y][2] << "\t" << setw(14) 
                        << left << " Payment To Account!" << setw(itemWidth) <<""<<setw(amountWidth)<<right<<"\t\t\t-$" <<setw(amountWidth)<< right <<tempTransAmtP << endl;
                }
                    else                                    //IF NOT ORDER AND NOT PAYMENT, BOOM
                    {
                        cout << "Error, transaction line not O or P (order or payment)";
                        return 40;
                    }
            }
        y++;
    }
    
    cout<<"\n\t\t\t Balance Due $" << setw(amountWidth) << right << masterRecord[idx][2]<<endl<<endl<<endl<<endl<<endl;
    x++;
    idx++;
    
    
}   while (x < masterLineCounter);
   
   
   //std::cin.get(); 
    }
