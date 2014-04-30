// LinkedList.h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <cstdlib>
#include <iostream>
using namespace std;



class LinkedList;  // needed for friend line below

class ListElement
{
	public:
   int fish_no;
   float distan;

  
   ListElement* previous;
  
   ListElement* next;
   ListElement (int rad, float fac, ListElement*);
   
   int getDatum () const;
   ListElement const* getNext () const;

   friend class LinkedList;  // gives LinkedList access to datum and next
};


class LinkedList
{
public:
   ListElement* head;
   ListElement* p;
   int total_element;

  
   LinkedList ();
   
   void insertItem (int fish_no, float dist);
   void makeList ();
   void appendItem (int);
   void deleteItem (int);
   void printList ();
   ~LinkedList();
};

#endif
