#ifndef THREAD_OPERATION_H
#define THREAD_OPERATION_H

#include "common.h"

#include <pthread.h>

void open_threads();
void *PrintHello(void *threadid);

#endif