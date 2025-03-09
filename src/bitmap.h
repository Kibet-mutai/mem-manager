#ifndef BITMAP_H
#define BITMAP_H

#ifndef PRINT
#define PRINT
#include <iostream>
#endif
/*
 * 1 bitmap bit = 16 byte block of memory
 * 1 bitmap byte (i.e, block) = 128-byte block of memory
 * */

#define BYTES_PER_BITMAP_BIT 16
#define BYTES_PER_BITMAP_BYTE 128

class BitMap {
private:
    unsigned char* map;
    unsigned long nbytes;
    unsigned long nbits;

public:
    BitMap(unsigned long blocks);
    ~BitMap();
    unsigned long get_byte_size();
    void set_bits(int value, unsigned long nbits, unsigned long index);
    int get_bits(unsigned long index);
    long get_bit_run(unsigned long size);

    void print_map();
    unsigned char* get_map();
    friend std::ostream& operator<<(std::ostream& OS, BitMap& map);
};
#endif
