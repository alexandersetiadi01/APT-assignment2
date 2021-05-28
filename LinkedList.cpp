
#include "LinkedList.h"
#include <stdexcept>

LinkedList::LinkedList()
{
   head = nullptr;
}

LinkedList::LinkedList(LinkedList &other)
{
   head = nullptr;
   for (int i = 0; i < other.size(); ++i)
   {
      Tile *tile = new Tile(*other.get(i));
      add_back(tile);
   }
}

LinkedList::~LinkedList()
{
   clear();
}

int LinkedList::size()
{
   //Loop will start at 0
   int count = 0;
   //This points to the first element in the LinkedList
   Node *current = head;
   /**
   * The While loop is being implemented so when the value is 
   * null it will go to the end of the list
   */
   while (current != nullptr)
   {
      ++count;
      //Makes the current = null to return count = 0
      current = current->next;
   }
   //size will return the count
   return count;
}

//Get the value of the node at a Coordinate
Tile *LinkedList::get(int coord)
{
   Tile *retTile = nullptr;

   if (coord >= 0 && coord < size())
   {

      int counter = 0;
      Node *current = head;

      while (counter < coord)
      {
         ++counter;
         current = current->next;
      }
      retTile = current->tile;
   }
   return retTile;
}

void LinkedList::add_front(Tile *data)
{
   Node *node = new Node(data, head);
   node->tile = data;
   node->next = head;

   head = node;
}

void LinkedList::add_back(Tile *data)
{
   Node *node = new Node(data, nullptr);
   node->tile = data;
   node->next = nullptr;

   if (head == nullptr)
      head = node;
   else
   {
      Node *current = head;

      while (current->next != NULL)
      {
         current = current->next;
      }
      current->next = node;
   }
}

void LinkedList::remove_front()
{
   if (head != nullptr)
   {
      Node *toDelete = head;
      head = head->next;

      delete toDelete->tile;
      delete toDelete;
   }
   else
   {
      throw std::runtime_error("Nothing to remove");
   }
}

void LinkedList::remove_back()
{
   if (head != nullptr)
   {
      Node *current = head;
      //pre should point to node before current;
      Node *prev = nullptr;

      while (current->next != nullptr)
      {
         prev = current;
         current = current->next;
      }

      if (prev == nullptr)
      {
         head = nullptr;
      }
      else
      {
         prev->next = nullptr;
      }

      delete current->tile;
      delete current;
   }
}

void LinkedList::remove(int count)
{
   if (count >= 0 && count < size())
   {
      if (head != nullptr)
      {
         int counter = 0;
         Node *current = head;
         //pre should point to node before current;
         Node *prev = nullptr;

         while (counter != count)
         {
            ++counter;
            prev = current;
            current = current->next;
         }

         if (prev == nullptr)
         {
            head = current->next;
         }
         else
         {
            prev->next = current->next;
         }

         delete current->tile;
         delete current;
      }
   }
}

void LinkedList::clear()
{
   while (head != nullptr)
   {
      remove_front();
   }
}
