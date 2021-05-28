
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include "Tile.h"

//LinkedList implementation will include Tile class
class LinkedList {
public:

   LinkedList();
   LinkedList(LinkedList& other);
   ~LinkedList();

   int size();

   Tile* get(int coord);

   void add_front(Tile* data);

   void add_back(Tile* data);

   void remove_front();

   void remove_back();

   void remove(int count);

   void clear();

   void display(Node* node);

private:
   Node* head;

   //void display(Node* node);
};

#endif // ASSIGN2_LINKEDLIST_H
