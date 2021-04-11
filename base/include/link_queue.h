//双向链表 引用于ngnix

#ifndef _LINK_QUEUE_H_INCLUDED_
#define _LINK_QUEUE_H_INCLUDED_
 #include <stddef.h>             /* offsetof() */

typedef struct link_queue_s  link_queue_t;

struct link_queue_s {
    link_queue_t  *prev;
    link_queue_t  *next;
};


#define link_queue_init(q)                                                     \
    (q)->prev = q;                                                            \
    (q)->next = q


#define link_queue_empty(h)                                                    \
    (h == (h)->prev)


#define link_queue_insert_head(h, x)                                           \
    (x)->next = (h)->next;                                                    \
    (x)->next->prev = x;                                                      \
    (x)->prev = h;                                                            \
    (h)->next = x


#define link_queue_insert_after   link_queue_insert_head


#define link_queue_insert_tail(h, x)                                           \
    (x)->prev = (h)->prev;                                                    \
    (x)->prev->next = x;                                                      \
    (x)->next = h;                                                            \
    (h)->prev = x


#define link_queue_head(h)                                                     \
    (h)->next


#define link_queue_last(h)                                                     \
    (h)->prev


#define link_queue_sentinel(h)                                                 \
    (h)


#define link_queue_next(q)                                                     \
    (q)->next


#define link_queue_prev(q)                                                     \
    (q)->prev


#if (link_DEBUG)

#define link_queue_remove(x)                                                   \
    (x)->next->prev = (x)->prev;                                              \
    (x)->prev->next = (x)->next;                                              \
    (x)->prev = NULL;                                                         \
    (x)->next = NULL

#else

#define link_queue_remove(x)                                                   \
    (x)->next->prev = (x)->prev;                                              \
    (x)->prev->next = (x)->next

#endif


#define link_queue_split(h, q, n)                                              \
    (n)->prev = (h)->prev;                                                    \
    (n)->prev->next = n;                                                      \
    (n)->next = q;                                                            \
    (h)->prev = (q)->prev;                                                    \
    (h)->prev->next = h;                                                      \
    (q)->prev = n;


#define link_queue_add(h, n)                                                   \
    (h)->prev->next = (n)->next;                                              \
    (n)->next->prev = (h)->prev;                                              \
    (h)->prev = (n)->prev;                                                    \
    (h)->prev->next = h;


#define link_queue_data(q, type, link)                                         \
    (type *) ((u_char *) q - offsetof(type,link))


// link_queue_t *link_queue_middle(link_queue_t *queue);
// void link_queue_sort(link_queue_t *queue,
//     link_int_t (*cmp)(const link_queue_t *, const link_queue_t *));


#endif /* _LINK_QUEUE_H_INCLUDED_ */
