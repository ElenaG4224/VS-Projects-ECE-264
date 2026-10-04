# include <stdio.h>

typedef struct node {

int value;

struct node* next;

} Node;





Node* List_insert(Node* h, int v)

{

printf("insert %d\n", v);

Node* p = Node_construct(v);//assume this creates the node

if (h == NULL) return p; // Empty list (I think this also takes care of the end of the list!)

if (v < h->value)
{
    p->next = h;
    h = p;
    
}
else if (h->value < v)
{
    h->next = List_insert(h->next, v); //corrections: this would create new nodes, making memory issues. you need to free p.

}
else if (h->value == v)
{
    free(p);
}

//alternate code starts here(no recursion). would reflace the else if statements.
Node * curr = h;
while(curr->next != NULL && curr->next->value < v)
{
    curr = curr->next;
}

p->next = curr->next;
curr->next = p;

//end

return h;

}





