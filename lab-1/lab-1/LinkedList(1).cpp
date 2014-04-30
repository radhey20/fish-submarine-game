//LinkedList.cpp

// Note: This implementation of LinkedList is based on 
// Chapter 4 of Bruno R. Preiss's Textbook: 
// "Data Structures and Algorithms with Object-Oriented Design Patterns
//    in C++"

#include <cstdlib>
#include <cassert>
#include "LinkedList.h"
using namespace std;

//---------------------------------------------------
//List Element Members
//---------------------------------------------------
ListElement::ListElement(int _fish_no, float _distan_, ListElement * _next):
	fish_no (_fish_no), next (_next), distan(_distan_)
{}


int ListElement::getDatum () const
{ 
   return fish_no; 
}


ListElement const* ListElement::getNext () const
{ 
   return next; 
}



//---------------------------------------------------
//LinkedList Members
//---------------------------------------------------
LinkedList::LinkedList () :
	head (NULL), total_element(0)
{}

void LinkedList::insertItem(int fish_no, float dista)
{
   ListElement *currPtr = head;
   ListElement *prevPtr = NULL;
   ListElement *lastPtr=NULL;
   ListElement *newNodePtr; 

   //while(currPtr != NULL && item > currPtr->datum)
   //{
   //   prevPtr = currPtr;
   //   currPtr = currPtr->next;
   //} 

 //  newNodePtr = new ListElement(fish_no, dista, currPtr);
   // 
   //if (prevPtr == NULL) // insert at the beginning
   //   head=newNodePtr;
   //else
   //   prevPtr->next = newNodePtr;

   currPtr=head; 
      newNodePtr=new ListElement(fish_no, dista, NULL);
	  if (head == NULL || head->distan >= dista)
    {   
		if(head==NULL)
		{
			p=newNodePtr;
			
		}
		

        newNodePtr->next = head;
		if(head!=NULL)
		{
		head->previous=newNodePtr;
		}
        head = newNodePtr;
		newNodePtr->previous=head;
		++total_element;

		
		 if(total_element >5)
		{
			ListElement* g;
			g=p;
			p=p->previous;
			p->next=NULL;
			delete g;
			--total_element;
		}
    }

	else
	{

		while (currPtr->next!=NULL &&
			currPtr->next->distan < newNodePtr->distan)
        {
            currPtr = currPtr->next;
        }
		if(currPtr->next==NULL)
		{
			p=newNodePtr;
		}
        newNodePtr->next = currPtr->next;
		if(currPtr->next!=NULL)
		{
			newNodePtr->next->previous=newNodePtr;
		}
		
        currPtr->next = newNodePtr;
		newNodePtr->previous=currPtr;

		
		++total_element;
		if(total_element >5)
		{
			ListElement* g;
			g=p;
			p=p->previous;
			p->next=NULL;
			delete g;
			--total_element;
		}
	}
}

//void LinkedList::makeList()
//{
//   int InValue;
//   ListElement *currPtr = head;
//   ListElement *prevPtr = NULL;
//   ListElement *lastPtr=NULL;
//   ListElement *newNodePtr;      //points to a new node
//   
//   cout << "Enter values for a linked list, one per line." << endl
//	<< "Enter 999 to end the list." << endl;
//
// //  cin >> InValue;
//   //Adding elements to end so that "next" will be NULL
//  /// newNodePtr=new ListElement(InValue, NULL);
//   //head=newNodePtr;  //assign head to the first Node
//   currPtr=head; 
//   cin >> InValue;
//
//   while ( InValue != 999)
//   {
//	  currPtr=head; 
//      newNodePtr=new ListElement(InValue, NULL);
//	  if (head == NULL || head->fish_no >= InValue)
//    {   
//		if(head==NULL)
//		{
//			p=newNodePtr;
//			
//		}
//		
//
//        newNodePtr->next = head;
//		if(head!=NULL)
//		{
//		head->previous=newNodePtr;
//		}
//        head = newNodePtr;
//		newNodePtr->previous=head;
//		++total_element;
//
//		
//		 if(total_element >4)
//		{
//			ListElement* g;
//			g=p;
//			p=p->previous;
//			p->next=NULL;
//			delete g;
//			--total_element;
//		}
//    }
//
//	else
//	{
//
//		while (currPtr->next!=NULL &&
//               currPtr->next->fish_no < newNodePtr->fish_no)
//        {
//            currPtr = currPtr->next;
//        }
//		if(currPtr->next==NULL)
//		{
//			p=newNodePtr;
//		}
//        newNodePtr->next = currPtr->next;
//		if(currPtr->next!=NULL)
//		{
//			newNodePtr->next->previous=newNodePtr;
//		}
//		
//        currPtr->next = newNodePtr;
//		newNodePtr->previous=currPtr;
//
//		
//		++total_element;
//		if(total_element >4)
//		{
//			ListElement* g;
//			g=p;
//			p=p->previous;
//			p->next=NULL;
//			delete g;
//			--total_element;
//		}
//	}
//      cin >> InValue;
//   }
//              
//}

//void LinkedList::appendItem (int item)
//{
//   ListElement *currPtr;
//   ListElement *newNodePtr;
//
//   currPtr = head;
//
//   //Find the end of the list...
//   while (currPtr->next != NULL)
//   {
//      currPtr = currPtr->next;
//   }
//
//   //Now current-pointer points to the last node...
//   newNodePtr = new ListElement(item, NULL);	       
//   currPtr->next = newNodePtr;
//
//}

void LinkedList::deleteItem (int item)
{
   ListElement *delPtr;
   ListElement *currPtr;

   //Treat the first node as a special case... head needs to be updated
   if (head->fish_no == item)
   {
      delPtr = head;
      head = head->next;
   }
   else
   {
      currPtr = head;
      //Look for the node to deleted
      while (currPtr->next->fish_no != item)
      {
	 currPtr = currPtr->next;
      }
      //Save its location
      delPtr = currPtr->next;
      
      //Route the list around the node to be deleted
      currPtr->next = delPtr->next;
   }

   //Delete the node
   delete delPtr;
}


void LinkedList::printList () 
{
   ListElement *currPtr;
   currPtr = head;

   while (currPtr != NULL)
   {
	  cout << currPtr->fish_no <<"   " <<currPtr->distan<< endl;
      currPtr = currPtr->next;
   }
    cout<<endl;
}


LinkedList:: ~ LinkedList()
{


   while( head != NULL ) {
    ListElement* next1= head->next;
    delete head;
    head = next1;
   }
}