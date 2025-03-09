#include "bitmap.h"
#include <iostream>
#include <stdlib.h>

BitMap::BitMap(unsigned long nblocks)
{
    unsigned long i;
    map = (unsigned char*)calloc(nblocks, 1);
    if (map == nullptr) {
        std::cerr << "could not allocate bitmap\n";
        std::exit(1);
    }

    nbytes = nblocks;
    nbits = nbytes * 8;

    for (i = 0; i < nbytes; ++i) {
        map[i] = 0xFF;
    }

    std::cout << "BitMap::BitMap(): No. of bytes = " << nbytes << '\n';
    std::cout << "BitMap::BitMap(): No. of bits = " << nbits << '\n';
}

BitMap::~BitMap()
{
    std::cout << "BitMap::~BitMap(): Freeing map bytes: " << nbytes << '\n';
    free(map);
}

unsigned long BitMap::get_byte_size()
{
    return nbytes;
}

/* set bits to value (i.e., 0,1) starting at bit specified by index*/
void BitMap::set_bits(int value, unsigned long nbits, unsigned long index)
{
    unsigned long bit, i, j;
    unsigned char mask;

    bit = 0;

    for (i = 0; i < nbytes; ++i) {
        mask = 1;

        for (j = 0; j < 8; ++j) {
            if (bit >= index) {
                if (bit == index + nbits)
                    return;
                if (value) {
                    map[i] = map[i] | mask;
                } else {
                    map[i] = map[i] & (~mask);
                }
            }
            ++bit;
            mask = 1 << j;
        }
    }
    return;
}

/* returns that value of the specified bit (i.e., 0 or 1) or -1 if the index is
 * out of bounds
 */
int BitMap::get_bits(unsigned long index)
{
    unsigned long bit, i, j;
    unsigned char mask;

    bit = 0;

    for (i = 0; i < nbytes; ++i) {
        mask = 1;

        for (j = 0; j < 8; ++j) {
            if (bit == index) {
                if (map[i] & mask) {
                    return 1;
                } else {
                    return 0;
                }
            }
            ++bit;
            mask = 1 << j;
        }
    }
    return -1;
}

/* returns the index that marks the start of 'size' bits set to 1 or returns -1
 * if such run wasn't found
 */
long BitMap::get_bit_run(unsigned long size)
{
    unsigned long curr_size = 0, bit = 0, i, j;
    unsigned char mask;
    if (!map) { // Ensure map is not null
        std::cerr << "Error: map is null!" << std::endl;
        return -1;
    }
    for (i = 0; i < nbytes; ++i) {
        mask = 1;

        for (j = 0; j < 8; ++j) {
            if (map[i] & mask) {
                ++curr_size;
                if (curr_size == size) {
                    return bit - size + 1;
                }
            } else {
                curr_size = 0;
            }
            ++bit;
            mask <<= 1;
        }
    }
    return -1;
}

unsigned char* BitMap::get_map()
{
    return map;
}

void BitMap::print_map()
{
    unsigned long bit, i, j;
    unsigned char mask;
    bit = 0;

    for (i = 0; i < nbytes; i++) {
        mask = 1;
        std::cout << "bytes= " << map[i];

        for (j = 0; j < 8; ++j) {
            if (map[i] & mask) {
                std::cout << 1;
            } else {
                std::cout << 0;
            }
            ++bit;
            mask = 1 << j;
        }
        std::cout << '\n'
                  << '\n';
    }
}
