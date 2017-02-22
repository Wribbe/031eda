#include "bitreference.h"
#include "bitset.h"
/* Constructors: */

BitReference::BitReference(Bitset::BitStorage * pb, size_t p) :
    p_bits(pb),
    pos(p)
{
    /* Empty constructor. */
}

BitReference& BitReference::operator=(bool b) {
    //
    // *** IMPLEMENT ***
    // This corresponds to the set() function in SimpleBitset.
    //
    return *this;
}

BitReference& BitReference::operator=(const BitReference& rhs) {
    //
    // *** IMPLEMENT ***
    // Same as operator=(bool), but the bit is picked from rhs
    //
    return *this;
}

BitReference::operator bool() const {
    return (*p_bits & (1uL << pos)) != 0;
}
