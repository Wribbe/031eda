#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "coding.h"

// Local functions.
// ----------------

bool in_range(unsigned char c)
    /* Return bool reflecting if the char is in the set range. */
{
    return c >= ' ' && c <= '~';
}


std::string get_filename(std::string filepath)
    /* Return filename base that matches <path/><filename><.filending>. */
{
    std::stringstream buffer;
    std::string reversed = filepath;
    std::reverse(reversed.begin(), reversed.end());
    bool record = false;
    for (auto c : reversed) {
        if (c == '.') {
            record = true;
            continue;
        }
        if (record) {
            if (c == '/' || c == '\\') { // Break on file-path separator.
                break;
            }
            buffer << c;
        }
    }
    // Re-reverse the string.
    std::string reversed_filename = buffer.str();
    std::reverse(reversed_filename.begin(), reversed_filename.end());
    return reversed_filename;
}


int general_file_processing(bool encode,
                             std::string filepath,
                             std::string output_extension)
    /* General purpose file processing method, toggle encoding/decoding with
     * encoding boolean. */
{
    std::stringstream buffer;

    std::string output_directory = "output";

    // Get filename from argumtens.
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "No such file: " << filepath << ", aborting." << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename = get_filename(filepath);
    buffer << output_directory << '/' << filename << output_extension;
    std::string output_path = buffer.str();
    // Clear buffer, also clears error states.
    std::stringstream().swap(buffer);

    // Open output file.
    std::ofstream output_file(output_path);

    if (!output_file.is_open()) {
        std::cerr << "Could not open path: " << output_path << ", aborting." \
            << std::endl;
        return EXIT_FAILURE;
    }

    char c;
    while (file.get(c))
        if (encode) {
            output_file.put(Coding().encode(c));
        } else {
            output_file.put(Coding().decode(c));
        }
    file.close();
    output_file.close();
    return EXIT_SUCCESS;
}


// Public functions.
// -----------------

// ----------------------------------------------------------------------------
// -- Coding.
// ----------------------------------------------------------------------------

unsigned char Coding::encode(unsigned char c)
    /* Encode a character and return its encoded form. */
{

    if (in_range(c)) {
        return c+1;
    }
    return c;
}

unsigned char Coding::decode(unsigned char c)
    /* Take a encoded character and return its decoded form. */
{
    if (in_range(c)) {
        return c-1;
    }
    return c;
}

// ----------------------------------------------------------------------------
// -- FileCoder.
// ----------------------------------------------------------------------------

void FileCoder::usage(std::string executable_name)
{
    /* Print usage message for File Encode. */
    std::cerr << "[Usage:] ./" << executable_name << " <filename>."<<std::endl;
}

int FileCoder::encode(std::string filepath)
    /* Encoding specific implementation of local general_file_processing
     * function. */
{
    return general_file_processing(true, filepath, ".enc");
}

int FileCoder::decode(std::string filepath)
    /* Decoding specific implementation of local general_file_processing
     * function. */
{
    return general_file_processing(false, filepath, ".dec");
}
