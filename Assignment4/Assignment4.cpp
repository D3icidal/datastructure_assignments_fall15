/*
Thomas Ng
CISC 3130 Data Structures
Assignment4
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
 

//String to Number and Number to String+

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
} // http://www.cplusplus.com/forum/articles/9645/

/*
struct TreeNode 
{
     int data;         // The data in this node.
     TreeNode *left;   // Pointer to the left subtree.
     TreeNode *right;  // Pointer to the right subtree.
};
*/
 
struct TreeNode 
{
    // An object of type TreeNode represents one node
    // in a binary tree of strings.
    
    int data;           // The data in this node.
    TreeNode *left;      // Pointer to left subtree.
    TreeNode *right;     // Pointer to right subtree.
    
    TreeNode(int num) 
    {
    // Constructor.  Make a node containing num.
    data = num;
    left = NULL; //NULL doesnt work with cloud9
    right = NULL;
    }

};  
  
  
  //http://math.hws.edu/eck/cs225/s03/binary_trees/
  
int countNodes( TreeNode *root ) 
{
       // Count the nodes in the binary tree to which
       // root points, and return the answer.
    if ( root == NULL )
       return 0;  // The tree is empty.  It contains no nodes.
    else 
    {
       int count = 1;   // Start by counting the root.
       count += countNodes(root->left);  // Add the number of nodes
                                        //     in the left subtree.
       count += countNodes(root->right); // Add the number of nodes
                                        //    in the right subtree.
       return count;  // Return the total.
    }
 } 
     
 
 
 //PREORDER PRINT  
 //preorderPrint outputs:   1  2  4  5  3  6
 
void preorderPrint( TreeNode *root )
{
       // Print all the items in the tree to which root points.
       // The item in the root is printed first, followed by the
       // items in the left subtree and then the items in the
       // right subtree.
    if ( root != NULL ) 
    {  // (Otherwise, there's nothing to print.)
       cout << root->data << " ";      // Print the root item.
       preorderPrint( root->left );    // Print items in left subtree.
       preorderPrint( root->right );   // Print items in right subtree.
    }
} 
     
     
  
 //POSTORDER PRINT 
// postorderPrint outputs:  4  5  2  6  3  1
 
void postorderPrint( TreeNode *root ) 
{
       // Print all the items in the tree to which root points.
       // The items in the left subtree are printed first, followed 
       // by the items in the right subtree and then the item in the
       // root node.
    if ( root != NULL )
    {  // (Otherwise, there's nothing to print.)
       postorderPrint( root->left );    // Print items in left subtree.
       postorderPrint( root->right );   // Print items in right subtree.
       cout << root->data << " ";       // Print the root item.
    }
}
     
     

//INORDER PRINT
//inorderPrint outputs:    4  2  5  1  3  6

void inorderPrint( TreeNode *root ) 
{
       // Print all the items in the tree to which root points.
       // The items in the left subtree are printed first, followed 
       // by the item in the root node, followed by the items in
       // the right subtree.
    if ( root != NULL )
    {  // (Otherwise, there's nothing to print.)
       inorderPrint( root->left );    // Print items in left subtree.
       cout << root->data << " ";     // Print the root item.
       inorderPrint( root->right );   // Print items in right subtree.
    }
}


// NEEDS TESTING
void childrenPrint (TreeNode *root)
{
    if ( root != NULL )
    {   childrenPrint(root->left);
        childrenPrint(root->right);
        if (root->left != NULL && root->right !=NULL)
        {
            cout<<root->data<<" Node has 2 children."<<endl;
        }
        else if (root->data != NULL || root->right !=NULL)
        {
            cout<<root->data<<" Node has 1 child."<<endl;
        }
    }
}


// NEEDS TESTING
void deleteTree(TreeNode *root)
{
    if ( root != NULL )
    {
        deleteTree(root->left);
        deleteTree(root->right);
        root->left=NULL;
        root->right=NULL;
    }
    //if(root->left==NULL && root->right==NULL)
      
}

void insertNode(TreeNode *&root, int newItem) 
{
          // Add the item to the binary sort tree to which the parameter
          // "root" refers.  Note that root is passed by reference since
          // its value can change in the case where the tree is empty.
    
      if ( root == NULL ) {
        //cout<<"insertNode. root == NULL  newItem: "<<newItem<<endl;   //DEBUGING
             // The tree is empty.  Set root to point to a new node containing
             // the new item.  This becomes the only node in the tree.
         root = new TreeNode( newItem );
                 // NOTE:  The left and right subtrees of root
                 // are automatically set to NULL by the constructor.
                 // This is important!
         return;
      }
      else if ( newItem < root->data ) {
         insertNode( root->left, newItem );
      }
      else {
         insertNode( root->right, newItem );
      }
   }  // end insertNode()
   
   //TreeNode findSmallest(TreeNode root)
TreeNode* findSmallest(TreeNode *root)
{
  while(root->left != NULL)
    root = root->left;
  return root;
}

//delete node using temp cursor to keep track of previous parent location
void deleteNode(TreeNode *&root, int data) 
{
    if(root == NULL)    //if empty tree (aka set#3)
        cout<<"Empty Tree, can't delete empty"<<endl<<endl;
    else if(data < root->data)  //if smaller
        deleteNode(root->left,data);
    else if(data > root->data)  //if larger
        deleteNode(root->right, data);
    else //if (data == root->data)
    {
        if(root->left == NULL && root->right == NULL)   // if leaf / no children
        {
            delete root;
            root = NULL;
        } 
        else if(root->left == NULL)       // if only right child
        {
            TreeNode *temp = root;          //do I have to keep calling TreeNode?
            root = root->right;
            delete temp;
        } 
        else if(root->right == NULL)    //if only has left child
        {
            TreeNode *temp = root;  
            root = root->left;
            delete temp;
        } 
        else
        {
            TreeNode *temp = findSmallest(root->right);
            root->data = temp->data;
            deleteNode (root->right, temp->data);
        }
    }
}


int main()
{
    
//DECALRE VARIABLES
    bool treeFlag=false;
    string transactionLine [30]={};
	string substr1;
	
	int x=0, tranCounter=0;
	
	cout.precision(2);
	cout<<fixed; 
    
    
//Create a binary tree
    TreeNode *root;  // Pointer to the root node in the tree.
    root = NULL;     // Start with an empty tree.
    //*head = root    //not linked list, resursive doesn't need head. //to keep track of start of tree
    
//Read in "sets" into 1D array
	fstream transactionFile ("Assignment4Transactions.txt");
	if (transactionFile.is_open())
	    cout << "(Transaction file loaded successfully)" << endl;
	else
	    cout << "(Problem loading transaction file! Is the \"Assignment4Transactions.txt\" file in the same folder as this program?)" << endl;
	
	cout<<"Start loading transactions into 1D array"<<endl<<endl;
	do   //load records from transaction file into 1D transactionLine array until EOF
	{	
	    //cout<<"test1"<<endl;    //DEBUGING 
	    getline(transactionFile, transactionLine[x]);
	    cout<<transactionLine[x]<<endl;
	    x++;
	    tranCounter++;
	} while (!transactionFile.eof());
	//cout<<"tranCounter: "<<tranCounter<<endl;    //DEBUGING 

//Read in 1D array to determine if number or word
    for(x=0;x<tranCounter;x++)	
	{
    	//cout<<"for loop"<<endl;    //DEBUGING 
    	stringstream ssTempTran (transactionLine[x]);
    	while ( ssTempTran.good() )	
        {	
            substr1 = "";
    		getline( ssTempTran, substr1, ',' );
            //cout<<"While(ssTempTran.good) loop. substr1: "<<substr1<<"\t StringToNumber<int>(substr1): "<<StringToNumber<int>(substr1)<<endl;    //DEBUGING 
            //cout<<"substr1.find('e'): "<<substr1.find('e')<<endl; //DEBUGING
            if  (treeFlag==true) //if time to read in main BST numbers
            {   
                //cout<<"treeFlag==true"<<endl;    //DEBUGING
                if (StringToNumber<int>(substr1) != -999)   //while not terminator
                {
                    cout<<substr1<<" ";
                    //cout<<"begin insert, substr1:"<<substr1<<endl;      //DEBUGING
                    insertNode(root, StringToNumber<int>(substr1));
                }
                //cout<<"\tfinished while loop for set numbers"<<endl; //DEBUGING
                if (StringToNumber<int>(substr1) == -999)
                {
                    treeFlag=false;
                    cout<<"\tEnd of Set Input."<<endl;    //DEBUGING
                    cout<<endl<<"inorderPrint():\t\t";
                    inorderPrint(root);
                    cout<<endl<<"preorderPrint():\t";
                    preorderPrint(root);
                    cout<<endl<<"postorderPrint():\t";
                    postorderPrint(root);
                    cout<<endl<<"countNodes():\t\t";
                    cout<<countNodes(root);
                    cout<<endl<<"childrenPrint():\t"<<endl;
                    childrenPrint(root);
                }
    
            }
            else if (substr1.find('e') < 10)   // if substr1 has letters (as in Set Delete Insert)  //"==-1" did not return -1 for numbers, weird.
            {
                //cout<<"substr1.find('e') < 10)"<<endl; //DEBUGING
                if(substr1.find("set") != -1)   //if substr1 contains "set"
                {
                    cout<<endl<<endl<<"\t\tBeginning new tree for "<<substr1<<endl<<endl;
                    treeFlag=true;                
                }
                else if (substr1.find("delete") != -1)  //if delete
                {
                    cout<<"\tDelete "<<substr1<<endl;
                    deleteNode(root, StringToNumber<int>(substr1));
                }
                else        //if insert
                {
                    cout<<"\tInsert "<<substr1<<endl;
                    insertNode(root, StringToNumber<int>(substr1));
                }
                
            }
    
        }

        cout<<"\tEnd of Set Input."<<endl;
        cout<<endl<<"inorderPrint():\t\t";
        inorderPrint(root);
        cout<<endl<<"preorderPrint():\t";
        preorderPrint(root);
        cout<<endl<<"postorderPrint():\t";
        postorderPrint(root);
        cout<<endl<<"countNodes():\t\t";
        cout<<countNodes(root);
        cout<<endl<<"childrenPrint():\t"<<endl;
        childrenPrint(root);
        deleteTree(root);
        root=NULL;
    }
}

    


            //run inorder, preorder, postorder, count, children,
            
        
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

     
     