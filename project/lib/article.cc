#include <cmath>
#include <iterator>
#include <sstream>

#include "article.h"

using bin_iter = std::string::iterator;

std::string encode_number(packtype_t number, size_t base=BASE, size_t chunk_size=CHUNK_SIZE)
{
    std::stringstream stream;

    packtype_t divisor = 1 << (chunk_size-1);

    while (divisor > 0) {
        packtype_t result = number/divisor;
        if (result) {
            stream << 1;
            number -= divisor;
        } else {
            stream << 0;
        }
        divisor >>= 1; // goto next lower power of 2.
    }
    std::string binary_encoding = stream.str();
    if (base > 2) {
        // Refresh stream.
        std::stringstream().swap(stream);
        double log_result = log2(base);
        size_t num_bits = log_result;
        if (log_result - static_cast<int>(log_result) > 0) {
            num_bits++;
        }
        bin_iter p1 = binary_encoding.begin();
        bin_iter p2 = p1+num_bits;
        bin_iter end = binary_encoding.end();
        std::string current_subsection;
        while (p1 != end) {
            size_t diff = num_bits - (p2-p1);
            if (diff) { // Pad with leading 0's.
                current_subsection = std::string('0', diff);
                current_subsection += std::string(p1,p2);
            } else {
                current_subsection = std::string(p1,p2);
            }
            // Re-encode current_subsection to new base.
            packtype_t number = std::stoul(std::string(p1,p2),nullptr,2);
            stream << static_cast<char>(number + '0');
            if(p2 + num_bits > end) {
                p2 = end;
            } else {
                p2 += num_bits;
            }
            if(p1 + num_bits > end) {
                p1 = end;
            } else {
                p1 += num_bits;
            }
        }
        // Return other than binary encoding.
        return stream.str();
    }
    return binary_encoding;
}

std::string encode_string(std::string string, packtype_t base)
{
    std::stringstream stream;

    packtype_t current = 0;
    packtype_t shifts = 0;
    size_t length = string.length();

    for(size_t i=0; i<length; ++i) {
        if (i%chars_in_packtype > 0) {
            current <<= bitsize_char;
            shifts++;
        }
        current += string[i];
        if (shifts == chars_in_packtype-1) {
            stream << encode_number(current, base);
            current = 0;
            shifts = 0;
        }
    }
    if (current > 0) {
        stream << encode_number(current, base);
    }
    return stream.str();
}

std::string encode_with_length_prefix(std::string string, packtype_t base)
{
    std::stringstream stream;
    stream << encode_number(string.length(), base);
    stream << encode_string(string, base);
    return stream.str();
}

packtype_t get_prefix(bin_iter& p1, bin_iter& p2, packtype_t bits, packtype_t base)
{
    packtype_t prefix = std::stoul(std::string(p1,p2),nullptr,base);
    p1 += bits;
    p2 += bits;
    return prefix;
}

packtype_t num_32chunks_to_read(packtype_t string_length)
{
    packtype_t chunks = string_length/chars_in_packtype;
    if (string_length%chars_in_packtype) {
        chunks++;
    }
    return chunks;
}

std::string chunks_to_string(bin_iter& p1, bin_iter& p2, size_t chunks, packtype_t base)
{
    std::stringstream stream;
    for (size_t i=0; i<chunks; ++i) {
        while(p1 != p2) {
            packtype_t number = std::stoul(std::string(p1,p1+bitsize_char),
                                         nullptr,
                                         base);
            if (number > 0) { // Ignore null values.
                stream << static_cast<char>(number);
            }
            p1 += bitsize_char;
        }
        p2 += bitsize_packtype_t;
    }
    return stream.str();
}

Article article_from_encoded(std::string& encoded_string, packtype_t bits, packtype_t base)
{
    bin_iter p1 = encoded_string.begin();
    bin_iter p2 = encoded_string.begin()+bits;

    // Decode id.
    packtype_t id = get_prefix(p1,p2,bits,base);
    // Decode title length.
    packtype_t length_title = get_prefix(p1,p2,bits,base);
    // Get number of 32-bit chunks to read.
    packtype_t chunks = num_32chunks_to_read(length_title);
    // Decode title chunks.
    std::string title = chunks_to_string(p1,p2,chunks,base);
    // Decode author chunks.
    chunks = num_32chunks_to_read(get_prefix(p1,p2,bits,base));
    std::string author = chunks_to_string(p1,p2,chunks,base);
    // Decode text chunks.
    chunks = num_32chunks_to_read(get_prefix(p1,p2,bits,base));
    std::string text = chunks_to_string(p1,p2,chunks,base);

    return Article(id,title,author,text);
}


Article::Article(packtype_t id) :
    pid(id),
    ptitle(""),
    pauthor(""),
    ptext("")
    /* Default constructor for Article. */
{
    /* Empty */
}

const packtype_t& Article::id() {
    return pid;
}

const std::string& Article::title() {
    return ptitle;
}
const std::string& Article::author() {
    return pauthor;
}
const std::string& Article::text() {
    return ptext;
}

Article::Article(packtype_t id,
                 std::string title,
                 std::string author,
                 std::string text) :
    pid(id),
    ptitle(title),
    pauthor(author),
    ptext(text)
    /* Specified constructor for Article. */
{
    /* Empty */
}

std::string Article::encode(packtype_t base)
{
    std::stringstream stream;
    stream << encode_number(id(),base);
    stream << encode_with_length_prefix(title(), base);
    stream << encode_with_length_prefix(author(), base);
    stream << encode_with_length_prefix(text(), base);
    return stream.str();
}

std::ostream& operator<<(std::ostream& stream, Article& article)
{
    stream << article.encode();
    return stream;
}


