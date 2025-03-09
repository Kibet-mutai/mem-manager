#include "mem_manage.h"

MemoryManager* mem_manage_ptr;

void init_mgr(unsigned long total_bytes)
{
    mem_manage_ptr = new MemoryManager(total_bytes);
}

void close()
{
    delete mem_manage_ptr;
}

void* new_malloc(unsigned long size)
{
    void* ptr = mem_manage_ptr->allocate(size);
    if (ptr == nullptr) {
        std::cerr << "allocation failed\n";
        return nullptr;
    }
    return ptr;
}

void new_free(void* ptr)
{
    mem_manage_ptr->release(ptr);
}

int main(int argc, char* argv[])
{
    init_mgr(1024);
    void* ptr = mem_manage_ptr->allocate(sizeof(int));
    new_free(ptr);
    close();
    return 0;
}
