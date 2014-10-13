#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef struct {
    uint16_t  head;     // Start of data in queue
	uint16_t  words;    // Words in buffer now
	uint16_t  maxWords; // Length of allocated buffer in words
	uint32_t *data;     // Pointer to allowated buffer
} u32_ring_t;

u32_ring_t*  u32_ring_alloc(uint16_t words); // Create and initialize new ring buffer
int          u32_ring_free(u32_ring_t* r);   // Destroy r and deallocate memory
void         u32_ring_clear(u32_ring_t* r);  // Reset and clear data
int          u32_ring_put(u32_ring_t* r, uint32_t* data, uint16_t words);
uint32_t*    u32_ring_get(u32_ring_t* r, uint16_t* words, uint16_t maxWords);
int          u32_ring_full(u32_ring_t* r);
int          u32_ring_empty(u32_ring_t* r);

#define BLOCK_SIZE(x) (x*sizeof(uint32_t))

u32_ring_t* u32_ring_alloc(uint16_t words)
{
    void *data;
    u32_ring_t *r = calloc(1, sizeof(u32_ring_t));
	if (!r) goto err1;
	data = malloc(BLOCK_SIZE(words));
	if (!data) goto err2;
	r->data     = data;
	r->maxWords = words;
	u32_ring_clear(r);
	return r;

err2:
	free(r);
err1:
	return NULL;
}

int u32_ring_free(u32_ring_t* r)
{
	if (!r) return -EINVAL;
	if (r->data) free(r->data);
	free(r);
	return 0;
}

void u32_ring_clear(u32_ring_t* r)
{
	r->head  = 0;
	r->words = 0;
}

int u32_ring_put(u32_ring_t* r, uint32_t* data, uint16_t words)
{
	// If we can't fit all data, don't write any
	if ((r->words + words) > r->maxWords) return -ENOMEM;

	// Find end of data, wrap around if needed
	uint16_t tail = r->head + r->words;
    if (tail >= r->maxWords) {
        tail -= r->maxWords;
    }
    r->words += words;
    
    // Copy what we can at end of queue
    uint16_t cpWords = r->maxWords - tail;
	if (cpWords > words) cpWords = words;
	memcpy(r->data + tail, data, BLOCK_SIZE(cpWords));
	words -= cpWords;

	// Wrap around to beginning of array
	if (words) {
		memcpy(r->data, data + cpWords, BLOCK_SIZE(words));
	}
	return 0;
}

uint32_t* u32_ring_get(u32_ring_t* r, uint16_t* words, uint16_t maxWords)
{
	if (!r->words) return NULL;

	// Calculate return values
	uint32_t *retPtr   = r->data + r->head;
	uint16_t  retWords = r->maxWords - r->head;
	if (retWords > maxWords) retWords = maxWords;
	if (retWords > r->words) retWords = r->words;

	// Remove data from queue
	r->words -= retWords;
	r->head += retWords;
	if (r->head >= r->maxWords) {
		r->head = 0;
	}

	*words = retWords;
	return retPtr;
}

int u32_ring_full(u32_ring_t* r)
{
	return (r->words==r->maxWords);
}

int u32_ring_empty(u32_ring_t* r)
{
	return !r->words;
}

int main(int argc, const char *argv[]) {
    u32_ring_t *r = u32_ring_alloc(8);
    uint32_t array[] = {0xDEADBEEF, 0xB16B00B5, 0xBADA55E5};
    for(int i=0; i<5; i++) {
        int ret = u32_ring_put(r, array, 3);
        if (ret) {
            printf("u32_ring_put() error %d\n", ret);
        } else {
            printf("Wrote 3 words\n");
        }
        uint32_t *word;
        uint16_t words;
        while (word = u32_ring_get(r, &words, 1)) { 
            printf("Read 0x%08X from queue\n", *word);
        }
    }
}