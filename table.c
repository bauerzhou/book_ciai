
#include <limits.h>
#include <stddef.h>
#include "assert.h"
#include "table.h"

#define T Table_T

struct T{
	int size;
	int (*cmp) (const void *x, cont void *y);
	unsigned (*hash) (const void *key);
	
	struct binding {
		struct binding *link;
		const void *key;
		void *value;
	} **buckets;
}