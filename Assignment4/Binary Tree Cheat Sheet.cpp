//BINARY TREE
  struct TreeNode {
     int item;         // The data in this node.
     TreeNode *left;   // Pointer to the left subtree.
     TreeNode *right;  // Pointer to the right subtree.
  }
 
 //COUNT NODES
 
 int countNodes( TreeNode *root ) {
           // Count the nodes in the binary tree to which
           // root points, and return the answer.
        if ( root == NULL )
           return 0;  // The tree is empty.  It contains no nodes.
        else {
           int count = 1;   // Start by counting the root.
           count += countNodes(root->left);  // Add the number of nodes
                                            //     in the left subtree.
           count += countNodes(root->right); // Add the number of nodes
                                            //    in the right subtree.
           return count;  // Return the total.
        }
     } // end countNodes()
     
 
 
 //PREORDER PRINT  
 preorderPrint outputs:   1  2  4  5  3  6
 
      void preorderPrint( TreeNode *root ) {
           // Print all the items in the tree to which root points.
           // The item in the root is printed first, followed by the
           // items in the left subtree and then the items in the
           // right subtree.
        if ( root != NULL ) {  // (Otherwise, there's nothing to print.)
           cout << root->item << " ";      // Print the root item.
           preorderPrint( root->left );    // Print items in left subtree.
           preorderPrint( root->right );   // Print items in right subtree.
        }
     } // end preorderPrint()
     
     
  
 //POSTORDER PRINT 
 postorderPrint outputs:  4  5  2  6  3  1
 
      void postorderPrint( TreeNode *root ) {
           // Print all the items in the tree to which root points.
           // The items in the left subtree are printed first, followed 
           // by the items in the right subtree and then the item in the
           // root node.
        if ( root != NULL ) {  // (Otherwise, there's nothing to print.)
           postorderPrint( root->left );    // Print items in left subtree.
           postorderPrint( root->right );   // Print items in right subtree.
           cout << root->item << " ";       // Print the root item.
        }
     } // end postorderPrint()
     
     

//INORDER PRINT
inorderPrint outputs:    4  2  5  1  3  6

     void inorderPrint( TreeNode *root ) {
           // Print all the items in the tree to which root points.
           // The items in the left subtree are printed first, followed 
           // by the item in the root node, followed by the items in
           // the right subtree.
        if ( root != NULL ) {  // (Otherwise, there's nothing to print.)
           inorderPrint( root->left );    // Print items in left subtree.
           cout << root->item << " ";     // Print the root item.
           inorderPrint( root->right );   // Print items in right subtree.
        }
     } // end inorderPrint()
     
     


//OUTCOMES OF PRINTS:
          preorderPrint outputs:   1  2  4  5  3  6
       
          postorderPrint outputs:  4  5  2  6  3  1
       
          inorderPrint outputs:    4  2  5  1  3  6
          
          