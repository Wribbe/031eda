#include "coding.h"

int main(int argc, char * argv[])
{
    if (argc < 2) {
        FileCoder().usage(argv[0]);
        return EXIT_FAILURE;
    }
    return FileCoder().encode(argv[1]);
}
