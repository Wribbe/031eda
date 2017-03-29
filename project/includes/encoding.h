#ifndef ENCODING_H
#define ENCODING_H

#include <string>
#include <sstream>

using packtype_t = uint32_t;

static uint32_t base = 64;

static size_t bitsize_char = sizeof(char)*8;
static size_t bitsize_packtype_t = sizeof(packtype_t)*8;
static size_t chars_in_packtype = bitsize_packtype_t/bitsize_char;

/* Utility */
size_t get_bits(uint32_t base);

/* Encoding functions. */
std::string libencode(uint64_t number,
                      uint32_t base=base,
                      uint32_t chunk_size=bitsize_packtype_t);

std::string libencode(std::string& string,
                      uint32_t base=base,
                      uint32_t chunk_size=bitsize_packtype_t);

std::string libencode_with_prefix(std::string& string,
                                  uint32_t base=base,
                                  uint32_t chunk_size=bitsize_packtype_t);


/* Decoding functions. */
packtype_t libdecode_value(std::istream& stream,
                            uint32_t base=base,
                            uint32_t chunk_size=bitsize_packtype_t);

std::string libdecode_string(std::istream& stream,
                             uint32_t base=base,
                             uint32_t chunk_size=bitsize_packtype_t);

#endif
