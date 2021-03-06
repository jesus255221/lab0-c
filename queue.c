/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

#define NULL_CHECK(condition) \
    if (condition == NULL) {  \
        return false;         \
    }



/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (!q) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->q_size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    if (!q) {
        return;
    }
    /* Free queue structure */
    if (!q->head) {
        free(q);
        return;
    }
    list_ele_t *current_ptr = q->head;  //, *prev;
    do {
        free(current_ptr->value);  // Free the current string
        // prev = current_ptr;               // Save the previous list node
        current_ptr = current_ptr->next;  // Go to the next node
        free(current_ptr->prev);          // free the previous node
    } while (current_ptr !=
             q->tail);  // Do the action until it reachs the tail of the queue
    free(current_ptr->value);
    free(current_ptr);
    free(q);
    return;
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
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    NULL_CHECK(q);
    newh = malloc(sizeof(list_ele_t));
    NULL_CHECK(newh);
    /* Don't forget to allocate space for the string and copy it */
    // malloc string size plus the terminating character
    newh->value = malloc(strlen(s) + 1);

    /* What if either call to malloc returns NULL? */
    /* If malloc failed... */
    if (!newh->value) {
        free(newh);
        return false;
    }

    /* Copy the string */
    strcpy(newh->value, s);
    newh->value[strlen(s)] = '\0';

    /* If this is the first node in the list, set the tail to it*/
    if (!q->q_size) {
        q->head = newh;
        q->tail = newh;
    } else {
        q->head->prev = newh;
        q->tail->next = newh;
    }
    newh->next = q->head;
    newh->prev = q->tail;
    q->head = newh;
    q->q_size++;
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
    list_ele_t *newt;
    NULL_CHECK(q);
    newt = malloc(sizeof(list_ele_t));
    NULL_CHECK(newt);

    newt->value = malloc(strlen(s) + 1);

    /* What if either call to malloc returns NULL? */
    /* If malloc failed... */
    if (!newt->value) {
        free(newt);
        return false;
    }

    /* Copy the string */
    strcpy(newt->value, s);
    newt->value[strlen(s)] = '\0';

    /* If this node is the first node */
    if (!q->q_size) {
        q->head = newt;
        q->tail = newt;
    } else {
        q->head->prev = newt;
        q->tail->next = newt;
    }
    newt->next = q->head;
    newt->prev = q->tail;
    q->tail = newt;
    q->q_size++;
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
    NULL_CHECK(q);
    NULL_CHECK(q->head);
    if (sp) {
        if (strlen(q->head->value) >= (bufsize - 1)) {
            strncpy(sp, q->head->value, bufsize - 1);
            sp[bufsize - 1] = '\0';
        } else {
            strncpy(sp, q->head->value, strlen(q->head->value));
            sp[strlen(q->head->value)] = '\0';
        }
    }
    free(q->head->value);
    list_ele_t *head;
    head = q->head;
    q->head->next->prev = q->head->prev;
    q->head->prev->next = q->head->next;
    q->head = q->head->next;
    q->q_size--;
    free(head);
    if (!q->q_size) {
        q->head = NULL;
        q->tail = NULL;
    }
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
    if (q)
        return q->q_size;
    else
        return 0;
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
    if (!q || !q->head) {
        return;
    }
    list_ele_t *current = q->head, *next;

    do {
        next = current->next;
        current->next = current->prev;
        current->prev = next;
        current = next;
    } while (next != q->head);

    current = q->head;
    q->head = q->tail;
    q->tail = current;

    return;
}
