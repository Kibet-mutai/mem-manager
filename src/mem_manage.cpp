#include "mem_manage.h"

/* sets the total amount of memory, no resizing in this case each
 * byte in bitmap represent BYTES_BITMAP_BYTE bytes in memory
 */
MemoryManager::MemoryManager(unsigned long total_bytes)
{
    // initialize 3 dynamic objects: bmap, bst, mem[]
    b_map = new BitMap((total_bytes / BYTES_PER_BITMAP_BYTE) + 1);
    mem_len = b_map->get_byte_size() * BYTES_PER_BITMAP_BYTE;

    std::cout << '\n';
    mem = new unsigned char[mem_len];
    if (mem == nullptr) {
        std::cerr << "MemoryManager::MemoryManager(): could not allocate memory\n";
        std::exit(1);
    }
    std::cout << "MemoryManager::MemoryManager(): malloc() memory"
              << "[" << mem_len << "]"
              << '\n';
}

MemoryManager::~MemoryManager()
{
    bst.delete_all(&(bst.root_ptr));
    delete[] mem;
    delete b_map;
}

void* MemoryManager::allocate(unsigned long n_bytes)
{
    unsigned long run_bits = 0;
    long index = 0;
    struct BiNode* node = new BiNode;

    std::cout << "MemoryManager::allocate(): requested bytes = " << n_bytes << '\n';

    // translate n_bytes into NO. of bits in BitMap
    run_bits = (n_bytes / BYTES_PER_BITMAP_BIT) + 1;

    std::cout << "MemoryManager::allocate(): run_bits = " << run_bits << '\n';
    // look for NO. of free bits in BitMap

    index = b_map->get_bit_run(run_bits);
    std::cout << "MemoryManager::allocate(): run of bits found = " << run_bits
              << " at index: " << index << '\n';

    // reserved bits in the bitmap
    b_map->set_bits(0, run_bits, index);

    if (index * 16 >= mem_len) {
        std::cerr << "MemoryManager::allocate(): memory out of bounds\n";
        return nullptr;
    }
    node->value = reinterpret_cast<unsigned long>((&mem[index * 16]));
    node->index = index;
    node->n_reserved = run_bits;

    bst.insert_node_ptr(&(bst.root_ptr), node);

    delete node;
    // return memory represented by BitMap bits

    std::cout << "MemoryManager::allocate(): address allocated = "
              << (&mem[index * 16]);
    void* alloc_mem = &mem[index * 16];
    return alloc_mem;
}

void MemoryManager::release(void* address)
{
    struct BiNode* ptr;

    unsigned long addr = reinterpret_cast<unsigned long>(address);
    ptr = bst.find_node(bst.root_ptr, addr);
    if (ptr != nullptr) {
        std::cout << "MemoryManager::release(): following address freed: "
                  << (unsigned long)address << '\n';
        b_map->set_bits(1, ptr->n_reserved, ptr->index);
        bst.delete_node(&(bst.root_ptr), addr);
    }
    return;
}
void MemoryManager::print_state()
{
    std::cout << "-----------------------------------------------\n";
    b_map->print_map();
    std::cout << "-----------------------------------------------\n";
    bst.print_tree(bst.root_ptr, 0);
    std::cout << "-----------------------------------------------\n";
}
