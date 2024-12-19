#pragma once
#include <stdio.h>

#if defined(STACK_INCLUDED)
    #define _POP_STACK(ds) popS(ds)
    #define _PEEK_STACK(ds) peekS(ds)
    #define _CLEAR_STACK(ds) clearStack(ds)
    #define _ISEMPTY_STACK(ds) isStackEmpty(ds)
#else
    #define _POP_STACK(ds) NULL
    #define _PEEK_STACK(ds) NULL
    #define _CLEAR_STACK(ds) NULL
    #define _ISEMPTY_STACK(ds) NULL
#endif

#if defined(QUEUE_INCLUDED)
    #define _PEEK_QUEUE(ds) peekQueue(ds)
    #define _CLEAR_QUEUE(ds) clearQueue(ds)
    #define _ISEMPTY_QUEUE(ds) isQueueEmpty(ds)
#else
    #define _POP_QUEUE(ds) NULL
    #define _PEEK_QUEUE(ds) NULL
    #define _CLEAR_QUEUE(ds) NULL
    #define _ISEMPTY_QUEUE(ds) NULL
#endif

#if defined(INTLIST_INCLUDED)
    #define _POP_LIST(ds) popL(ds)
    #define _POPAT_LIST(ds) popAtL(ds)
    #define _PEEK_LIST(ds) peekL(ds)
    #define _CLEAR_LIST(ds) clearList(ds)
    #define _LENGTH_LIST(ds) listLength(ds)
    #define _ADD_LIST(ds) addL(ds)
    #define _APPEND_LIST(ds) appendL(ds)
#else
    #define _POP_LIST(ds) NULL
    #define _POPAT_LIST(ds) NULL
    #define _PEEK_LIST(ds) NULL
    #define _CLEAR_LIST(ds) NULL
    #define _LENGTH_LIST(ds) NULL
    #define _ADD_LIST(ds) NULL
    #define _APPEND_LIST(ds) NULL
#endif

#if defined(CYCLIC_INCLUDED)
    #define _POP_CYCLIC(ds) popC(ds)
    #define _POPAT_CYCLIC(ds) popAtC(ds)
    #define _PEEK_CYCLIC(ds) peekC(ds)
    #define _CLEAR_CYCLIC(ds) clearCyclic(ds)
    #define _LENGTH_CYCLIC(ds) cyclicLength(ds)
    #define _ADD_CYCLIC(ds) addC(ds)
    #define _APPEND_CYCLIC(ds) appendC(ds)
#else
    #define _POP_CYCLIC(ds) NULL
    #define _POPAT_CYCLIC(ds) NULL
    #define _PEEK_CYCLIC(ds) NULL
    #define _CLEAR_CYCLIC(ds) NULL
    #define _LENGTH_CYCLIC(ds) NULL
    #define _ADD_CYCLIC(ds) NULL
    #define _APPEND_CYCLIC(ds) NULL
#endif

#define pop(ds) _Generic((ds), \
    Stack *: _POP_STACK(ds), \
    List *: _POP_LIST(ds),\
    Cyclic *: _POP_CYCLIC(ds)\
    )(ds)

#define popAt(ds) _Generic((ds), \
    Stack *: _POPAT_STACK(ds), \
    List *: _POPAT_LIST(ds),\
    Cyclic *: _POPAT_CYCLIC(ds)\
    )(ds)

#define peek(ds) _Generic((ds), \
    Stack *: _PEEK_STACK(ds), \
    List *: _PEEK_LIST(ds),\
    Cyclic *: _PEEK_CYCLIC(ds)\
    Queue *: _PEEK_QUEUE(ds) \
    )(ds)

#define clear(ds) _Generic((ds), \
    Stack *: _CLEAR_STACK(ds), \
    List *: _CLEAR_LIST(ds),\
    Cyclic *: _CLEAR_CYCLIC(ds)\
    )(ds)

#define dslength(ds) _Generic((ds), \
    List *: _LENGTH_LIST(ds),\
    Cyclic *: _LENGTH_CYCLIC(ds)\
    )(ds)

#define isEmpty(ds) _Generic((ds), \
    Stack *: _ISEMPTY_STACK(ds),\
    Queue *: _ISEMPTY_QUEUE(ds)\
    )(ds)

#define add(ds) _Generic((ds), \
    List *: _ADD_LIST(ds),\
    Cyclic *: _ADD_CYCLIC(ds)\
    )(ds)

#define append(ds) _Generic((ds), \
    List *: _APPEND_LIST(ds),\
    Cyclic *: _APPEND_CYCLIC(ds)\
    )(ds)