#include "bitreference.h"
#include "bitset.h"
/* Constructors: */

BitReference::BitReference(Bitset::BitStorage * pb, size_t p) :
    p_bits(pb),
    pos(p)
{
    /* Empty constructor. */
}

BitReference& BitReference::generic_setter(size_t pos, bool b)
    /* Generic internal bit setter/unsetter. */
{
    if (b) { // Set the bit at pos to 1.
        *p_bits |= 1uL << pos;
    } else { // Set the bit at pos to 0.
        *p_bits &= ~ (1uL << pos);
    }
    return *this;
}

BitReference& BitReference::operator=(bool b)
    /* Class method that enables BitReference assignment with a boolean. */
{
    return generic_setter(pos, b);
}

BitReference& BitReference::operator=(const BitReference& rhs)
    /* Class method that enables BitReference assignment with another
     * BitReference object. */
{
    return generic_setter(rhs.pos, rhs);
}

BitReference::operator bool() const
    /* Class method that defines how the object should be converted to a
     * boolean value. */
{
    return (*p_bits & (1uL << pos)) != 0;
}
