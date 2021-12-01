// Binay_Search_Tree.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include<stdlib.h> // For exit function
#include <string>
#include <sstream> 
#include <fstream> // For file handling

using namespace std;

class BST // Struture of Node of Threaded Binary Searh Tree
{
	public:
		
		int data;
        BST *left, *right;
        bool rightthread; 
        bool leftthread;
        
		
};

class SinglyLL // Struture of Node of Binary Searh Tree
{
	public:
		
		int content;
		SinglyLL *next;
		
		SinglyLL()
		{
			next=NULL;
		}
};


BST* globalArray[100]; // Global Array for printing the threaded tree
int i=0;               // Global index for printing the threaded tree
int NoOfElements=0;    // Number of elements in threaded tree for printing



BST* insert(BST *root, int key) // This function is used to insert data in Threaded Tree
{
    
    BST *ptr = root;
    BST *par = NULL; // Parent of key to be inserted
    

    while (ptr != NULL)
    {
        // If key already exists, return
        if (key == (ptr->data))
        {
            printf("Duplicate Key !\n");
            return root;
        }
 
        par = ptr; // Update parent pointer
 
        // Moving on left subtree.
        if (key < ptr->data)
        {
            if (ptr -> leftthread == false)
                ptr = ptr -> left;
            else
                break;
        }
 
        // Moving on right subtree.
        else
        {
            if (ptr->rightthread == false)
                ptr = ptr -> right;
            else
                break;
        }
    }
 
    // Create a new node
    BST *tmp = new BST();
    tmp -> data = key;
    tmp -> leftthread = true;
    tmp -> rightthread = true;
 
    if (par == NULL)
    {
        root = tmp;
        tmp -> left = NULL;
        tmp -> right = NULL;
    }
    else if (key < (par -> data))
    {
        tmp -> left = par -> left;
        tmp -> right = par;
        par -> leftthread = false;
        par -> left = tmp;
    }
    else
    {
        tmp -> left = par;
        tmp -> right = par -> right;
        par -> rightthread = false;
        par -> right = tmp;
    }

    ++NoOfElements;
    return root;
}

BST* Successor(BST* ptr) // Returns  pointer to Inorder Successor of given pointer
{
    if (ptr->rightthread == true)
        return ptr->right;
 
    ptr = ptr->right;

    while (ptr->leftthread == false)
        ptr = ptr->left;
 
    return ptr;
}

                   
void inorder(BST *root)// Printing the Inorder Traersal of threaded tree
{
    if (root == NULL)
        printf("Tree is empty");
 
    // Reach leftmost node
    BST *ptr = root;

    while (ptr -> leftthread == false)
        ptr = ptr -> left;
 
    // One by one print successors
    while (ptr != NULL)
    {
        printf("%d ",ptr -> data);
        ptr = Successor(ptr);
    }
}

BST* inPred(BST* ptr)// Returns  pointer to Inorder Predeccessor of given pointer
{
    if (ptr->leftthread == true)
        return ptr->left;
 
    ptr = ptr->left;

    while (ptr->rightthread == false)
        ptr = ptr->right;

    return ptr;
}
 
BST* caseA(BST* root, BST* par, BST* ptr) // O child case for deletion
{
    // If Node to be deleted is root
    if (par == NULL)
        root = NULL;
 
    // If Node to be deleted is left of its parent
    else if (ptr == par->left) 
	{
        par->leftthread = true;
        par->left = ptr->left;
    }
    else 
	{
        par->rightthread = true;
        par->right = ptr->right;
    }
 
    // Free memory and return new root
    free(ptr);

    return root;
}
 
BST* caseB(BST* root, BST* par, BST* ptr) // 1 Child Case for deletion
{
    BST* child;
 
    // Initialize child Node to be deleted has left child.
    if (ptr->leftthread == false)
        child = ptr->left;
 
    // Node to be deleted has right child.
    else
        child = ptr->right;
 
    // Node to be deleted is root Node.
    if (par == NULL)
        root = child;
 
    // Node is left child of its parent.
    else if (ptr == par->left)
        par->left = child;

    else
        par->right = child;
 
    // Find successor and predecessor
    BST* s = Successor(ptr);
    BST* p = inPred(ptr);
 
    // If ptr has left subtree.
    if (ptr->leftthread == false)
        p->right = s;
 
    // If ptr has right subtree.
    else 
	{
        if (ptr->rightthread == false)
            s->left = p;
    }
 
    free(ptr);

    return root;
}
 
BST* caseC(BST* root, BST* par, BST* ptr) // 2 Child Case for deletion
{
    // Find inorder successor and its parent.
    BST* parsucc = ptr;
    BST* succ = ptr->right;
 
    // Find leftmost child of successor
    while (succ->leftthread==false) 
	{
        parsucc = succ;
        succ = succ->left;
    }
 
    ptr->data = succ->data;
 
    if (succ->leftthread == true && succ->rightthread == true)
        root = caseA(root, parsucc, succ);

    else
        root = caseB(root, parsucc, succ);
 
    return root;
}
 
 
BST* del(BST* root, int key) // Deletes an element from tree
{
    // Initialize parent as NULL and parent Node as root.
    BST *par = NULL, *ptr = root;
 
    // Set true if key is found
    int found = 0;
 
    // Search key in BST : find Node and its parent.
    while (ptr != NULL) 
	{
        if (key == ptr->data) 
		{
            found = 1;
            break;
        }

        par = ptr;

        if (key < ptr->data) 
		{
            if (ptr->leftthread == false)
                ptr = ptr->left;

            else
                break;
        }
        else 
		{
            if (ptr->rightthread == false)
                ptr = ptr->right;

            else
                break;
        }
    }
 
    if (found == 0)
        printf("key not present in tree\n");
 
    // Two Children
    else if (ptr->leftthread == false && ptr->rightthread == false)
        root = caseC(root, par, ptr);
 
    // Only Left Child
    else if (ptr->leftthread == false)
        root = caseB(root, par, ptr);
 
    // Only Right Child
    else if (ptr->rightthread == false)
        root = caseB(root, par, ptr);
 
    // No child
    else
        root = caseA(root, par, ptr);
 
    --NoOfElements;
	return root;
}

BST* search(BST* root, int key) // Search for a key and return it's pointer node
{
	
	BST *ptr = root ;

    int counter=0;
     

     while( ptr != NULL  ){

         if( ptr->data == key )
		 {
             // indicating that the element is found then
             return ptr ;
         }
		 else if( ptr->data < key)
		 {
             // moving to inorder predecessor of the current node 
             ptr = ptr->right ;
         
		 }
		 else if(ptr->data > key )
		 {
             // moving to inorder successor of the current node
            ptr = ptr->left ;
         }
         counter++;
         
         if(counter>100)
         break;

     }

     // if element is not found then we can return nullptr indicating element not  found in the given binary search tree
     return NULL;
}


SinglyLL* allElementsBetween(BST *root,int k1,int k2) // Returns singly linked list of elements lying between k1 and k2
{
	
	SinglyLL *list=NULL,*listptr=NULL;
	
	if(k1>k2) // Ensuring always that k1 is smaller than k2
	{
		int temp=k1;
		k1=k2;
		k2=temp;
	}
	
	BST* node=root;

	while(node->left)
		node=node->left; // Finding Smallest Element in tree
	
	while( node != root ) // Until root node reached, find element greater than k1 and less than k2
	{
		if(node->data >= k1 && node->data <= k2)
		{
			if(!list)
		    {
			    list=new SinglyLL();
			    list->content=node->data;
			    listptr=list;
		    }
		    else
		    {
			    list->next=new SinglyLL();
			    list=list->next;
			    list->content=node->data;
			
		    }
		}
		node=node->right;
		
	}

	// Add root if necessary
	if(node->data >= k1 && node->data <= k2)
	{

	    if(!list)
        {
	        list=new SinglyLL();
	        list->content=node->data;
	        listptr=list;
	    }
	    else
	    {
		     list->next=new SinglyLL();
		     list=list->next;
		     list->content=node->data;
	    }
	}


	// Add required elements from right subtree
	if(node->right)
	{
		BST *q=NULL,*r=NULL;
		
		while(node)
		{
			r=node;

		    node=node->right;

			if(!node)
				break;

		    q=node;

		    while(q->left != r)
			q=q->left;

		    while(q != node)
		    {
				if(node->data >= k1 && node->data <= k2)
			    {
					if(!list)
                    {
	                      list=new SinglyLL();
				   
	                      list->content=q->data;
	                      listptr=list;
	                }
	                else
	                {
		                   list->next=new SinglyLL();
		                   list=list->next;
				   
		                   list->content=q->data;
			
				     }
				}
			    q=q->right;
		     }

		     if(q==node)
	         {
				 if(node->data >= k1 && node->data <= k2)
	        	 {
					 if(!list)
	                 {
		                   list=new SinglyLL();
		                   list->content=q->data;
		                   listptr=list;
	                 }
	            
	                 else
                     {
			
		                    list->next=new SinglyLL();
		                    list=list->next;
	                        list->content=q->data;
			
				     }
				 }
				
			 }
		
		}
	}
	
	return listptr;
	
}

SinglyLL* reverseInorder(BST* root) // Returns Singly Linked list of reverse in-order traversal of tree
{
	BST *p;                 
	
	SinglyLL *list=NULL;    // Linked list implementation 
	SinglyLL *listptr=NULL; // listptr maintains starting of linked list
	
	p=root;                 // Pointer to root
	
	while(p->right)
	p=p->right;             // Largest element in tree

	
	// Add data from right subtree until root
	while(p->data != root->data)
	{
		if(!list)
		{
			list=new SinglyLL();
			list->content=p->data;
			listptr=list;
			
		}
		else
		{
			list->next=new SinglyLL();
			list=list->next;
			list->content=p->data;
			
		}
		
		p=p->left;
	}
	
	// Add Root
	if(!list)
	{
		list=new SinglyLL();
		list->content=p->data;
		listptr=list;
		
	}
	else
	{
		list->next=new SinglyLL();
		list=list->next;
	    list->content=p->data;
		
	}
	
	// Add nodes from left subtree	
	if(p->left)	
	{
		BST *q=NULL, *r=NULL;
		
		while(p)	
		{
	        q=p;
		
		    p=p->left;
		
		    r=p;

			if(!p)
				break;
		
		    while(p->right != q)
		    p=p->right;		
		
		
		    while(p  != r)
		    {
		       if(!list)
	            {
		            list=new SinglyLL();
		            list->content=p->data;
		            listptr=list;
	            }
	            
	           else
                {
			
		            list->next=new SinglyLL();
		            list=list->next;
	                list->content=p->data;
			
	            }
	              
	              p=p->left;         
				  
	        }
	        
	        if(p==r)
	        {
	        	if(!list)
	            {
		            list=new SinglyLL();
		            list->content=p->data;
		            listptr=list;
	            }
	            
	           else
                {
			
		            list->next=new SinglyLL();
		            list=list->next;
	                list->content=p->data;
			
	            }
				
			}
		
		}
	}
	
    
    
	// Return head to the list
	return listptr;
}

void kthElement(BST *root,int k) // Finds kth largest element and prints it
{
	SinglyLL *ptr=reverseInorder(root); // Call reverse Inorder to have a list from max to min elements

	int temp=k;

	while(--k && ptr)
		ptr=ptr->next;
	
	if(ptr)
	cout<<ptr->content<<" is "<<temp<<"th Largest Element"<<endl;
	
	else
	cout<<"Cannot identify kth element"<<endl;
	
	return;
}

void inputInGlobalArray(BST* root) // Put nodes in Global Array
{
	
	if(root==NULL)
		return;

	// Add Pre-order traversal nodes from tree to Global Array

	// Add root
	BST* p=root;
	globalArray[i++]=p;


	// Add left subtree elements in pre-order
	if(p->left)
	{
		p=p->left;

		while(p->left)
	    {
		    globalArray[i++]=p;
		    p=p->left;
	    }

	}

	while(p != root)
	{
		if(p->rightthread==true)
		globalArray[i++]=p;

		p=p->right;
	}
	
	// Add right subtree elements in pre-order
	if(p->right)
	{
		BST *r,*q=NULL;

		while(p)
		{  
			r=p;

			p=p->right;

			if(!p)
				break;

		    q=p;

			while(q->left != r)
			q=q->left;

		    while(q != p)
		    {
			    globalArray[i++]=q;
			    q=q->right;
		    }

			if(q==p)
				globalArray[i++]=q;
		}

	}

}

void printtree(BST* root) // Prints the tree by writing in DOT File Format and store in same directory as program then finally giving a PNG image as output
{
	BST* ptr=NULL;

	int restore=NoOfElements;

	ofstream MyFile("myfile.gv");

    // Write to the file
    MyFile << "digraph G{\n";

	inputInGlobalArray(root);

	NoOfElements=restore;

	for(int index=0;index<NoOfElements;index++)
	{
		if(globalArray[index]->left != NULL)
		MyFile << globalArray[index]->data <<"->"<< globalArray[index]->left->data<<";\n";

		if(globalArray[index]->right != NULL)
		MyFile << globalArray[index]->data <<"->"<< globalArray[index]->right->data<<";\n";
	}
	

	MyFile << "}";

	for(int index=0;index<NoOfElements;index++) // Global array reintialising
	{
		globalArray[index]=NULL;
	}

	i=0;

    // Close the file
    MyFile.close();

}

void split(BST* root,int k)
{
	if(root==NULL)
		return;

	BST *p1,*p2;
	BST *p1end,*p2end;

	p1=root;p2end=root;

	while(p1->left != NULL)
	{
		p1=p1->left;
	}

	p1end=search(root,k);

	p2=p1end->right;

	while(p2end->right != NULL)
	{
		p2end=p2end->right;
	}

	SinglyLL *list1=allElementsBetween(root,p1->data,p1end->data);
	SinglyLL *list2=allElementsBetween(root,p2->data,p2end->data);

	cout<<"Inorder of first tree=";
    
                        while(list1)
                        {
                            cout<<list1->content<<" ";
                            list1=list1->next;
	                    }
					    cout<<endl;
						cout<<endl;

	cout<<"Inorder of second tree=";
    
                        while(list2)
                        {
                            cout<<list2->content<<" ";
                            list2=list2->next;
	                    }
					    cout<<endl;
						cout<<endl;
}

int main()
{
	 BST *root = NULL;

	 int choice=0;
	 int X,Y;

	 while(1)
	 {
		 cout<<"\n\n\n******MENU DRIVEN MODE******\n\n\n";
		 cout<<"1. Insertion\n\n2. Deletion\n\n3. Search\n\n4. Reverse InOrder\n\n5. Successor\n\n6. Split\n\n7. ALL elements between 2 numbers\n\n8. K-th Largest element\n\n9. Print tree\n\n10. Inorder Traversal\n\n11. Exit";
		 cout<<"\n\n\n";

		 cout<<"Input Your Choice of Operation:";
		 cin>>choice;

		 switch(choice)
		 {
             case 1:
				    {
						cout<<"Enter Element to insert:";
					    cin>>X;

					    root = insert(root, X); // Insert element with data X in Threaded tree
					}
                    break;

			 case 2:
				    {
						cout<<"Enter Element to delete:";
					    cin>>X;

					    root = del(root, X); // Deletes element with data X in Threaded tree
					}
                    break;

			 case 3:
				    {
						cout<<"Enter Element to search:";
					    cin>>X;

				        BST* search_result=search(root,X); // Searches for element with data X in Threaded tree
    
                        if(search_result)
                        cout<<"Element Found!!"<<endl;
    
                        else
						cout<<"No such element"<<endl;
					}
				    
					break;

			 case 4:
				    {
						SinglyLL* list=reverseInorder(root); // list contains reverse Inorder traversal of Threaded tree
    
                        cout<<"Contents of Reverse Inorder=";
    
                        while(list)
                        {
                            cout<<list->content<<"->";
                            list=list->next;
	                    }
					    cout<<"/"<<endl;
					}

	 			    break;

			 case 5:
				   {
					   cout<<"Enter Element to find Successor:";
				       cin>>X;

				       BST* searchForElement=search(root,X); // Searches for node with data X and returns pointer to it

				       if(!searchForElement)
				       {
					       cout<<"No Such element exist\n\n";
					       break;
				       }

				       BST* succesor_result=Successor(searchForElement); // The search result is used for finding inorder Successor if it exist
    
                       if(succesor_result)
                       cout<<"Successor of node="<<succesor_result->data<<endl;
    
                       else
					   cout<<"No Successor exist"<<endl;
				   }

				   break;

			 case 6:
				   {
					    cout<<"Enter Element by which split occur:";
					    cin>>X;

						split(root,X);
						
				   }
				   break;

			 case 7:
				    {
						cout<<"Enter 1st Bound:";
				        cin>>X;

					    cout<<"Enter 2nd Bound:";
				        cin>>Y;

				        SinglyLL* list2=allElementsBetween(root,X,Y); // Returns list of elements with data in between X and Y
    
                        cout<<"Contents between given items=";
    
                        while(list2)
                        {
                            cout<<list2->content<<"->";
                            list2=list2->next;
	                    }
					    cout<<"/"<<endl;
					
					}

				   break;

			 case 8:
				   {
					   cout<<"Enter Element to find K-th Largest Element:";
				       cin>>X;

				       kthElement(root,X); // Finds X-th largest element and prints value
  
					   cout<<endl;
				   }

				   break;

			 case 9:
				   printtree(root); // creates a DOT file which can later be run in cmd to produce png image
				   break;

			 case 10:
				   {
					   cout<<"Inorder Traversal of tree=";
				       inorder(root); // Prints Inorder traversal of tree
					   cout<<endl;
					   break;
				   }
             
    
			 case 11:
				   exit(0); // exits Menu Driven Mode
    

			 default:
				  cout<<"Invalid Choice....\n\n";
				  break;

	      }


	 }
    return 0;
}

