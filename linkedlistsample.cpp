struct node {
  int x;
  node *next;
};

int main()
{
  node *head;       // This won't change, or we would lose the list in memory
  node *current;  // This will point to each node as it traverses the list

  head = new node;  // Sets it to actually point to something
  head->next = 0;   //  Otherwise it would not work well
  head->x = 12;
  current = head; // The current points to the first node
  if ( current != 0 ) {
    while ( current->next != 0)
      current = current->next;
  }
  current->next = new node;  // Creates a node at the end of the list
  current = current->next; // Points to that node
  current->next = 0;        // Prevents it from going any further
  current->x = 42;
}