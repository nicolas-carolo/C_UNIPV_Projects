#ifndef __DEBUG__
#define __DEBUG_H__

#include <stdio.h>

#define TRACE() fprintf(stderr, "%s (%d): %s\n", __FILE__, __LINE__, __func__)


#endif
