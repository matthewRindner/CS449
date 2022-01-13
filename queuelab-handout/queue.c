/* 
 * Developed by R. E. Bryant, 2017
 * Extended to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q == NULL)
    {
      return NULL; 
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0; 
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
  if(q == NULL)
    return;
  list_ele_t *curr = q->head;
  list_ele_t *temp = NULL;
  while(curr != NULL)
  {
    temp = curr->next;
    free(curr->value);  //curr.data = null
    free(curr);           //defrags 
    curr = temp;         //curr = curr.next

  }

  free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if(q == NULL)
      return false;

    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));  //Node newNode = new Node()
    if(newh == NULL)
      return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
   

    //newNode.data = length of string+1 for terminating char
    newh->value = malloc((strlen(s) + 1)*sizeof(char));
    newh->next = NULL;

    if(newh->value == NULL){
      free(newh);
      return false;           //if newNode.data == null, return false
    }
    //newh -> (int)value[strlen() + 1] = '\0'; // apend the terminating char
    
    //newh -> 
    strcpy(newh->value, s );

    if(q->head == NULL)
    {
      newh -> next = NULL;
      q->head = newh;
      q->tail = newh;

    }
    else
    {
      newh->next = q->head;   //
      q->head = newh;         //sets the head refernce to the new node
    }

    q->size++;

    return true;

}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    if(q == NULL)
        return false;

    list_ele_t *newTail;
    newTail = malloc(sizeof(list_ele_t));  //Node newNode = new Node()


    if(newTail == NULL)
      return false;

    newTail->value = malloc(strlen(s) + 1);
    newTail->next = NULL;

    if(newTail->value == NULL)
    {
      free(newTail);
      return false;
    }

    strcpy(newTail->value, s);

 
    if(q->head == NULL || q->tail == NULL)
    {
      //LL is empty, make the only node the head and tail
      q->head = newTail;
      q->tail = newTail; 
    }
    else
    {
      newTail->next = NULL;
      q->tail->next = newTail;
      q->tail = newTail;

    }

    
    q->size++;

    return true;
    
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if(q == NULL)
      return false;
 
    if(q->head == NULL)
      return false;

    list_ele_t *space_to_free = q->head;

   

    if(sp != NULL && space_to_free -> value != NULL)
    {
      strncpy(sp, space_to_free->value, bufsize-1);
      sp[bufsize-1] = '\0'; 
      
    }
    if(space_to_free -> value != NULL)
    {
      free(space_to_free -> value);
    }
      q->head = space_to_free -> next;
        free(space_to_free);

          q->size--;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
  if(q == NULL) return 0;
  return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
  
  if(q == NULL)
  {
    return;
  }
  else
  {
    list_ele_t *prev = NULL;
  list_ele_t *next = NULL; //q->head->next;
  list_ele_t *curr = q->head;
  q->tail = q->head;
    while(curr != NULL)
    {
      next = curr->next;
      curr->next = prev;

      prev = curr;
      curr = next;
    }
    q->head = prev;
  }
}

