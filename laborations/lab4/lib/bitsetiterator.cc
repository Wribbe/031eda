#include "bitsetiterator.h"

BitsetIterator::BitsetIterator(Bitset::BitStorage * pb, std::size_t p) :
    ref(pb, p)
{
    /* Empty constructor. */
}

bool BitsetIterator::operator!=(const BitsetIterator& bsi) const
    /* Method for determining if one BitsetIterator is non-equal to another
     * BitsetIterator. */
{
    if (ref.p_bits != bsi.ref.p_bits) {
        return true;
    }
    if (ref.pos != bsi.ref.pos) {
        return true;
    }
    return false;
}

BitsetIterator& BitsetIterator::operator++()
    /* Increment ref.pos as long as it does not exceed the digit count of the
     * BitStorage type. */
{
    if (ref.pos < Bitset().BPW) {
        ref.pos++;
    }
    return *this;
}

BitReference BitsetIterator::operator*()
    /* Defines what should be returned when the iterator is dereferenced. */
{
    return ref;
}

BitsetIterator& BitsetIterator::operator=(const BitsetIterator& rhs) {
    ref.p_bits = rhs.ref.p_bits;
    ref.pos = rhs.ref.pos;
    return *this;
}
