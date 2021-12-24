#ifndef _SILVERSE_H_
#define _SILVERSE_H_

#include "runtime.h"

struct _HttpResponse;

extern RuntimeType RUNTIME;

extern unsigned int PORT;

extern unsigned int CERVER_RECEIVE_BUFFER_SIZE;
extern unsigned int CERVER_TH_THREADS;
extern unsigned int CERVER_CONNECTION_QUEUE;

// inits silverse main values
extern unsigned int silverse_init (void);

// ends silverse main values
extern unsigned int silverse_end (void);

#endif