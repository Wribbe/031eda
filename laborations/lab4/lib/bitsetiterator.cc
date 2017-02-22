#include "bitsetiterator.h"

BitsetIterator::BitsetIterator(Bitset::BitStorage * pb, std::size_t p) :
    ref(pb, p)
{
    /* Empty constructor. */
}

bool BitsetIterator::operator!=(const BitsetIterator& bsi) const {
    return true;
}

BitsetIterator& BitsetIterator::operator++() {
    return *this;
}

BitReference BitsetIterator::operator*() {
    return ref;
}

BitsetIterator& BitsetIterator::operator=(const BitsetIterator& rhs) {
    ref.p_bits = rhs.ref.p_bits;
    ref.pos = rhs.ref.pos;
    return *this;
}
