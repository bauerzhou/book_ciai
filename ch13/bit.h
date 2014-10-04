#ifndef BIT_INCLUDED
#define BIT_INCLUDED  

#define T Bit_T
typedef struct T *T;

T Bit_new(int length);
int Bit_length(T set);
int Bit_count(T set);

int Bit_get(T set, int n);
int Bit_put(T set, int n, int bit);

void Bit_clear(T set, int lo, int hi);
void Bit_set(T set, int lo, int hi);
void Bit_not(T set, int lo, int hi);

int Bit_lt (T s, T t);
int Bit_eq (T s, T t);
int Bit_leq (T s, T t);

void Bit_map(T set, 
		void apply(int n, int bit, void *cl), void *cl);

T Bit_union(T s, T t);
T Bit_inter(T s, T t);
T Bit_minus(T s, T t);
T Bit_diff (T s, T t);

#undef T
#endif