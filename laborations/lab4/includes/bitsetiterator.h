/*
 * A BitsetIterator is an iterator for Bitsets.
 * Postfix ++, ==, and -> are not implemented.
 */

#ifndef BITSET_ITERATOR_H
#define BITSET_ITERATOR_H

#include <iterator>
#include "bitreference.h"

class BitsetIterator : public std::iterator<std::forward_iterator_tag, bool> {
public:
    /* Constructors: */
    BitsetIterator(Bitset::BitStorage * pb, std::size_t p);
    /* Member methods. */
    bool operator!=(const BitsetIterator& bsi) const;
    BitsetIterator& operator++();
    BitReference operator*();
    BitsetIterator& operator=(const BitsetIterator& rhs);
private:
    BitReference ref;
};
#endif
