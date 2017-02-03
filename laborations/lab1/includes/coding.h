#ifndef CODING_H
#define CODING_H

#include <string>

class Coding {
    public:
        /* For any character c, encode(c) is a character different from c. */
        static unsigned char encode(unsigned char c);

        /* For any character c, decode(encode(c)) == c. */
        static unsigned char decode(unsigned char c);
};

class FileCoder {
    public:
        /* Take a filename, encode the file contents and write encoded output
         * to specific output file. */
        static int encode(std::string filepath);

        /* Take a filename, decode the file contents and write decoded output
         * to specific output file. */
        static int decode(std::string filepath);

        /* Print usage message with supplied binary filename. */
        static void usage(std::string executable_name);
};

#endif
