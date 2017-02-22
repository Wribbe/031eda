/*
 * A BitReference is a "pointer to a bit" in a Bitset. It
 * has a reference to the word containing the bits (p_bits)
 * and an int (pos) which is the position of the bit in the word.
 */

#ifndef BITSET_REFERENCE_H
#define BITSET_REFERENCE_H

#include <cstddef>

class BitReference {
    friend class BitsetIterator;
public:
    /* Constructors. */

    BitReference(unsigned long * pb, std::size_t p);

    /* Public methods. */

    // This operator= is used for bs[i] = b.
    BitReference& operator=(bool b);

    // This operator= is used for bs[i] = bs[j].
    BitReference& operator=(const BitReference& rhs);

    // Operator bool() is used for b = bs[i].
    operator bool() const;
private:
    unsigned long * p_bits;    // Pointer to the word containing bits.
    std::size_t pos;           // Position of the bit in the word.
    BitReference& generic_setter(size_t pos, bool b);
};

#endif
