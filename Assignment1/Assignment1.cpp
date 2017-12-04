/*
Thomas Ng
CISC 3130 Data Structures
Assignment 1

*/

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
//#include <boost/tokenizer.hpp>   //NVM - failed //after hours of headaches with getline and stringstream parsing, this seemed to be the answer. http://www.boost.org/doc/libs/1_36_0/libs/tokenizer/introduc.htm

using namespace std;
//using namespace boost; //http://www.boost.org/doc/libs/1_36_0/libs/tokenizer/introduc.htm

int main()
{

//Declare Variables
int custNumber,transactionNumber, qty, masterLineCounter=0,temp1,temp2, i=0,x=0, y=0, z=0; //XYZ for array
double balanceDue, itemPrice, closingBalance, abcTotalBalance;
string custName, masterRecord[100][3], masterRecordTemp, masterLine [30];//masterLine is for entire row/record until I get to split it into individual variables
string transactionItem, strgCustNum, transactionRecord[100][15][5], tempTransactionRecord[200][5], transactionLine [200]; //transactionrecord up to 100 customers containing up to 15 transactions with 5 columns.
vector<string> result;
//ctor<string> resulttran;
//ringTemp.str ("test");
masterLine[1]="a"; //for debugging use later.
masterLine[2]="a"; //for debugging use later.
char transactionType; //"O" for purchase, "P" for payment


// intro stuff
cout << "\n\tABC Hardware Company Inc Accounts Receivable" << endl;
cout << "\t\t End-Of-Month Invoice Processing\n" << endl;

//void loadFiles() //function not worth the trouble. maybe come back to it when finished.
ifstream transactionFile ("Assignment 1 Transactions.txt");
fstream masterFile ("Assignment 1 Master.txt");
    if (transactionFile.is_open())
        cout << "(Transaction file loaded successfully)" << endl;
    else
        cout << "(Problem loading transaction file! Is the \"Assignment 1 Master.txt\" file in the same folder as this program?)" << endl;
    if (masterFile.is_open())
        cout << "(Master file loaded successfully)" << endl;
    else
    {
        cout << "(Problem loading master file! Is the \"Assignment 1 Master.txt\" file in the same folder as this program?)" << endl;
    }


do   //load customer records from Master file into array until EOF
{
    getline(masterFile, masterLine[x]);
    cout<<endl<<"MasterLine: "<<masterLine[x]<<endl; //just for debugging
    x++;
    masterLineCounter++;
} while (!masterFile.eof());


if (masterLine[1] != "a") //and (masterLine[2][1] != "a")//Confirm masterfile read properly
    cout << "Master file read sucessfully\n";
    x=0;
    y=0;
    z=0;
    masterRecordTemp=masterRecord[y][z];
    int resultCounter=0,counter1=0;

//Load masterFile record array into segmented 2D array without commas
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
    result.clear(); //must use clear otherwise counter goes to 0, but push_back goes back to end of vector.
    cout <<"MasterRecord " <<x<<":  "<<masterRecord[y][0]<<"\t"<<masterRecord[y][1]<<"\t\t"<<masterRecord[y][2]<<endl<<endl<<endl;
    z=0;
    x++; //increment masterLine
    y++;
    }

resultCounter=0;
counter1=0;
x=0;
y=0;
z=0;
cout<<endl<<"test"<<endl<<endl;

do   //load records from transaction file into array until EOF
{
    getline(transactionFile, transactionLine[x]);
    cout<<endl<<"TransactionLine "<<x<<transactionLine[x]<<endl; //debuging
    x++;
    counter1++;
} while (!transactionFile.eof());

x=0;
y=0;
z=0;
resulttran.clear();
resultCounter=0;

cout<<endl<<endl<<"x: "<<x<<"\tcounter1: "<<counter1<<"y: "<<y<<"z: "<<z<<endl<<endl; //debuging


//I fucked this up. Now all gibberish
while(x < counter1) //Load trans record 1D array into segmented 2D array without commas
{
    stringstream ssTemp (transactionLine[x]);

    while (ssTemp.good()) //good didn't seem to get it past 5th colomn)
    {
        string substr1;
        getline( ssTemp, substr1, ',' );
        resulttran.push_back( substr1 );
        tempTransactionRecord[y][z]=resulttran[resultCounter];
        cout<<"\n\nResult: "<<resulttran[resultCounter];
        resultCounter++;
        z++;
        cout<<"\n\nResult: "<<resulttran[resultCounter];
    }
    cout << endl << "resultCounter at line 127 = " << resultCounter<<endl;
    resultCounter=0;
    resulttran.clear(); //must use clear otherwise counter goes to 0, but push_back goes back to end of vector.
    cout <<"TransactionLine " <<x<<":  "<<tempTransactionRecord[y][0]<<"\t"<<tempTransactionRecord[y][1]<<"\t\t"<<tempTransactionRecord[y][5]<<endl<<endl<<endl;
    z=0;
    x++; //increment masterLine
    y++;
}



resulttran.clear();
i=0;
x=0;
y=0;
z=0;

cout<<endl<<endl<<"Test tempTransactionRecord[0][5]: "<<tempTransactionRecord[0][5] <<endl;

while (x<(counter1-1)) //start filling in x
{
    strgCustNum = tempTransactionRecord[i][1];
    //cout<<endl<<"\nCustNum: "<<strgCustNum<<" X:"<<x<<"  Y:"<<y<<"  Z:"<<z<<"\t"<<endl<<endl; //debuging

   while (strgCustNum == tempTransactionRecord[i][1]) //start filling in y
   {

        while(z<7) //start filling in Z
        {
            //ssTemp (tempTransactionRecord[y][z]);
           // getline( ssTemp, substr);
            //result.push_back( substr );
            //tempTransactionRecord[y][z]=result[resultCounter];r
            //resultCounter++;
            transactionRecord[x][y][z]=tempTransactionRecord[i][z];
            cout <<transactionRecord[x][y][z]<<"\t";
            z++;
        }
        //result.clear();
        z=0;
        i++;
        y++;
        cout<<endl;
        }
    y=0;
    z=0;
    x++;
}

//if tempTransactionRecord[y][z] = tempTransactionRecord[y][0]






cout<<endl<<endl<<"x: "<<x<<"\tcounter1: "<<counter1<<"y: "<<y<<"z: "<<z<<endl<<endl; //debuging




//cout << result[0] << "\t" << result[1] << "  result 2: "<< result[2] << endl; //worked!!!! weeee
//cout <<"\t" << masterRecord[1][0] <<endl;

    /*
Something less verbose, std and takes anything separated by a comma.

stringstream ss( "1,1,1,1, or something else ,1,1,1,0" );
vector<string> result;

while( ss.good() )
{
    string substr;
    getline( ss, substr, ',' );
    result.push_back( substr );
}
http://stackoverflow.com/questions/1894886/parsing-a-comma-delimited-stdstring
*/

/*
do
{
    stringstream ss (masterLine[x]);
    getline (ss, masterRecordTemp, ',');
        cout << endl << "ss: (MasterRecordTemp)" << masterRecordTemp <<endl;
    x++;

} while(x < masterLineCounter);
*/


/*
//do
//{
cout<< "\nmasterLine[x]: "<<masterLine[x]<<"\nmasterRecord[y][z]: "<<masterRecord[y][z]<<"\nmasterRecordTemp: "<<masterRecordTemp<<"\n stringTemp.str():" << stringTemp.str()<<endl;
    stringTemp.str() = masterLine[x];
    cout<< "\nmasterLine[x]: "<<masterLine[x]<<"\nmasterRecord[y][z]: "<<masterRecord[y][z]<<"\nmasterRecordTemp: "<<masterRecordTemp<<"\n stringTemp.str():" << stringTemp.str()<<endl;
    getline (stringTemp, masterRecordTemp, ',');
    masterRecord[y][z]= masterRecordTemp;
    cout<< "\nmasterLine[x]: "<<masterLine[x]<<"\nmasterRecord[y][z]: "<<masterRecord[y][z]<<"\nmasterRecordTemp: "<<masterRecordTemp<<"\n stringTemp.str():" << stringTemp.str()<<endl;
//} while (x<masterLineCounter);
*/

*/

//system ("pause");
return (0);
}

