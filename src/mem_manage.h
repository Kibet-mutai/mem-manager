#include "bitmap.h"
#include "bst.h"

class MemoryManager {
private:
    BinarySearchTree bst;
    BitMap* b_map;

    unsigned char* mem; // actual memory to manage
    unsigned long mem_len; // size in bytes of memory

public:
    MemoryManager(unsigned long total_bytes);
    ~MemoryManager();
    void* allocate(unsigned long n_bytes);
    void release(void* ptr);
    void print_state();
};
