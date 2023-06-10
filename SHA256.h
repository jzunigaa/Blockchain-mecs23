#ifndef SHA256_H
#define SHA256_H

#include <string>
#include "picosha2.h"
#include <sstream>

std::string sha256(const std::string& input) {
    std::string hash;
    picosha2::hash256_hex_string(input, hash);
    return hash;
}

#endif  // SHA256_H
