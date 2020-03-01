#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"
#include "strnatcmp.h"

#ifndef strlcpy
#define strlcpy(dst, src, sz) snprintf((dst), (sz), "%s", (src))
#endif
/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */

queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (q) {
        q->size = 0;
        q->head = NULL;
        q->tail = NULL;
        return q;
    }
    return NULL;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    if (q != NULL) {
        list_ele_t *cur = q->head;
        while (cur != NULL) {
            list_ele_t *nxt = cur->next;
            free(cur->value);
            free(cur);
            cur = nxt;
        }
    }
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* TODO: What should you do if the q is NULL? */
    if (q == NULL)
        return false;
    list_ele_t *newh;
    newh = (list_ele_t *) malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;

    /* Don't forget to allocate space for the string and copy it */
    newh->value = malloc((strlen(s) + 1));
    if (newh->value == NULL) {
        free(newh);
        return false;
    }

    strlcpy(newh->value, s, (strlen(s) + 1));
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    if (q->head == NULL)
        q->tail = newh;
    q->head = newh;
    q->size += 1;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL)
        return false;
    list_ele_t *newt;
    newt = (list_ele_t *) malloc(sizeof(list_ele_t));
    if (newt == NULL)
        return false;

    newt->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (newt->value == NULL) {
        free(newt);
        return false;
    }

    strlcpy(newt->value, s, strlen(s) + 1);
    newt->next = NULL;
    q->head = q->head ? q->head : newt;
    if (q->tail != NULL)
        q->tail->next = newt;
    q->tail = newt;
    q->size += 1;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || q->head == NULL)
        return false;
    if (sp != NULL)
        strlcpy(sp, q->head->value, bufsize);
    list_ele_t *p = q->head;
    free(p->value);
    q->head = q->head->next;
    free(p);
    q->size -= 1;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    return (q == NULL) ? 0 : q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || q->head == NULL)
        return;
    list_ele_t *pre, *cur, *nxt;
    pre = NULL;
    cur = q->head;
    nxt = cur->next;

    q->tail = cur;
    while (nxt != NULL) {
        cur->next = pre;
        pre = cur;
        cur = nxt;
        nxt = nxt->next;
    }
    cur->next = pre;
    q->head = cur;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q != NULL && q->head)
        q->head = sort(q->head);
}

list_ele_t *sort(list_ele_t *start)
{
    if (!start || !start->next)
        return start;
    list_ele_t *left = start;
    list_ele_t *right = left->next;
    left->next = NULL;

    left = sort(left);
    right = sort(right);


    for (list_ele_t *merge = NULL; left || right;) {
        if (!right || (left && strnatcmp(left->value, right->value) == -1)) {
            if (!merge) {
                start = merge = left;
            } else {
                merge->next = left;
                merge = merge->next;
            }
            left = left->next;
        } else {
            if (!merge) {
                start = merge = right;
            } else {
                merge->next = right;
                merge = merge->next;
            }
            right = right->next;
        }
    }
    return start;
}
