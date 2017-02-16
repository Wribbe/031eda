#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

int main(void)
{
    char prime = 'P';
    char non_prime = 'C';

    const size_t num_numbers = 1e5;
    std::string base(num_numbers, prime);

    // Mark first values.
    base[0] = non_prime;
    base[1] = non_prime;

    for(size_t i=2; i<num_numbers; ++i) {
        if (base[i] == prime) {
            for(size_t mul=i+i; mul<num_numbers; mul += i) {
                base[mul] = non_prime;
            }
        }
    }

    size_t prim_max = 200;
    /* Print the prime numbers up to prim_max. */
    std::stringstream buffer;
    for(size_t i = 1; i<=prim_max; ++i) {
        if (base[i] == prime) {
            buffer << i << ',';
        }
    }
    std::string buffer_string = buffer.str();
    // Remove last ',' char.
    buffer_string.pop_back();
    // Send to cout.
    std::cout << "Primes up to " << prim_max << ": " << buffer_string;
    std::cout << std::endl;

    size_t max_prime = 0;
    for(size_t i=num_numbers-1; i>0; --i) {
        if (base[i] == prime) {
            max_prime = i;
            break;
        }
    }

    std::cout << "Largest prime between 0 and " << num_numbers << " is: " << \
        max_prime << std::endl;

}
