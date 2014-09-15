
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
};

static int cmpatom(const void *x, const void *y){
	return x != y;
}

static unsigned hashatom(const void *key){
	return (unsigned long)key >> 2;
}

T Table_new(int hint,
	int cmp(const void *x, const void *y),
	unsigned hash(const void *key)){
	T table;
	int i;
	static int primes[] = {509, 509, 1021, 2053, 4093,
		8191, 16381, 32771, 65521, INT_MAX};
	
	assert(hint >= 0);
	for(i = 1; primes[i] < hint; i++)
		;
	talbe = ALLOC(sizeof (*table) +
		primes[i-1] * sizeof (table->bukets[0]));
	table->size = primes[i-1];
	table->cmp = cmp ? cmp : cmpatom;
	table->hash = hash ? hash : hashatom;
	table->buckets = (struct binding **)(table +1);

	for(i = 0; i < table->size; i++)
		table->buckets[i] = NULL;
	table->length = 0;
	table->timestamp = 0;

	return table;
}

void *Table_get(T table, const void *key){
	int i ;
	struct bind *p;
	assert(table);
	assert(key);

	//search table for key
	i = (*table->hash)(key) % table->size;
	for(p = table->buckets[i]; p; p = p->link)
		if((*table->cmp)(key, p->key) == 0)
			break;

	return p ? p->value : NULL;
}

void *Table_put(T table, const void *key, void *value){
	int i;
	struct binding *p;
	void *prev;

	assert(table);
	assert(key);

	//search table for key
	i = (*table->hash)(key) % table->size;
	for(p = table->buckets[i]; p; p = p->link)
		if((*table->cmp)(key, p->key) == 0)
			break;
	if( p == NULL){
		NEW(p);
		p->key = key;
		p->link = table->buckets[i];
		table->buckets[i] = p;
		table->length ++;
	}else{
		p->value = value;
	}

	return p;
}









