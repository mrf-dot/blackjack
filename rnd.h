/* A cryptographically random header file with only one dependency */
#define NSEEDS 4
#define ULONG_MAX 0xffffffff
#define ROTL(X, K) (((X) << (K)) | ((X) >> (64 - (K))))

static unsigned long seeds[NSEEDS];

extern int srnd();

extern unsigned long rnd();

extern int rndint(int lo, int hi);

extern void shuffle(int *a, int sz);

