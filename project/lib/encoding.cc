#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "encoding.h"

#define UNUSED(x) (void)x

static char base_char = '0';

size_t get_bits(uint32_t base)
{
    double log_result = log2(base);
    size_t num_bits = log_result;
    if (log_result != trunc(log_result)) {
        num_bits++;
    }
    return num_bits;
}

/* Encoding functions. */
/* =================== */

std::string libencode(uint64_t number, uint32_t base, uint32_t chunk_size)
{
    // How many bits does the base use?
    size_t num_bits = get_bits(base);
    packtype_t mask = 1;

    // Since e.g. base 64 on 32-bits is uneven, figure out how many bits we can
    // use.
    mask <<= (static_cast<size_t>(chunk_size/num_bits)*num_bits);

    std::stringstream stream;

    while(mask >= 1) {
        double result = number/mask;
        if (result >= 1) {
            size_t truncated = result;
            stream << static_cast<char>(base_char+truncated);
            number -= truncated*mask;
        } else {
            stream << base_char;
        }
        // Move maskk
        mask >>= num_bits;
    }
    return stream.str();
}

std::string libencode(std::string& string, uint32_t base, uint32_t chunk_size)
{
//    // Reverse string for easier decoding.
//    std::reverse(string.begin(),string.end());
    std::stringstream stream;
    std::string::iterator p1 = string.begin();
    std::string::iterator end = string.end();
    std::string::iterator p2 = p1;
    if (p2 + chars_in_packtype > end) {
        p2 = end;
    } else {
        p2 += chars_in_packtype;
    }

    while(p1 != end) { // Iterate until reached end of string.
        packtype_t current = 0;
        std::vector<char> char_vector;
        while(p1 < p2) {
            char_vector.push_back(*p1++);
        }
        // Reverse order of input to make decoding easier.
        std::reverse(char_vector.begin(),char_vector.end());
        bool atleast_two_values = false;
        for (char c : char_vector) {
            // Don't shift on a single value.
            if (atleast_two_values) {
                current <<= bitsize_char;
            }
            current += c;
            atleast_two_values = true;
        }
        stream << libencode(current, base, chunk_size);
        // Don't overshoot the end.
        if (p2 + chars_in_packtype >= end) {
            p2 = end;
        } else {
            p2 += chars_in_packtype;
        }
    }
    return stream.str();
}

std::string libencode_with_prefix(std::string& string,
                                  uint32_t base,
                                  uint32_t chunk_size)
{
    std::stringstream stream;
    stream << libencode(string.length(),base,chunk_size);
    stream << libencode(string,base,chunk_size);
    return stream.str();
}

/* Decoding functions. */
/* =================== */

packtype_t libdecode_value(std::istream& stream,
                            uint32_t base,
                            uint32_t chunk_size)
{
    size_t num_bits = get_bits(base);
    char c;

    packtype_t mask = 1 << static_cast<size_t>((chunk_size/num_bits))*num_bits;
    packtype_t return_value = 0;
    while (mask >= 1) {
        stream.get(c);
        return_value += mask * (c - base_char);
        mask >>= num_bits;
    }
    return return_value;
}

std::string libdecode_string(std::istream& stream,
                             uint32_t base,
                             uint32_t chunk_size)
{
    std::stringstream return_stream;

    packtype_t length = libdecode_value(stream, base, chunk_size);
    size_t num_chunks = length/chars_in_packtype;
    if (length%chars_in_packtype) {
        num_chunks++;
    }
    packtype_t current_value = 0;
    packtype_t lower_mask = 255;

    for (size_t i=0; i<num_chunks; ++i) {
        current_value = libdecode_value(stream, base, chunk_size);
        while (current_value > 0) {
            // Mask out first character and put in stream.
            return_stream << static_cast<char>(current_value & lower_mask);
            current_value >>= bitsize_char;
        }
    }

    return return_stream.str();
}
