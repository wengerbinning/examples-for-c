#include <stdio.h>

struct talloc_reference_handle {
	struct talloc_reference_handle *next, *prev;
	void *ptr;
	const char *location;
};

typedef int (*talloc_destructor_t)(void *);

struct talloc_chunk {
	struct talloc_chunk *next, *prev;
	struct talloc_chunk *parent, *child;
	struct talloc_reference_handle *refs;
	talloc_destructor_t destructor;
	const char *name;
	size_t size;
	unsigned flags;

	/*
	 * "pool" has dual use:
	 *
	 * For the talloc pool itself (i.e. TALLOC_FLAG_POOL is set), "pool"
	 * marks the end of the currently allocated area.
	 *
	 * For members of the pool (i.e. TALLOC_FLAG_POOLMEM is set), "pool"
	 * is a pointer to the struct talloc_chunk of the pool that it was
	 * allocated from. This way children can quickly find the pool to chew
	 * from.
	 */
	void *pool;
};


#define INFO(ptr, type) printf(#ptr" in %p,type is "#type", size is %d\n", &ptr, sizeof(type))


int main(int argc, const char **argv) {
    struct talloc_chunk var;
    INFO(var,struct talloc_chunk);

    return 0;
}