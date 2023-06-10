/*#include "sha256.h"
#include <openssl/sha.h>
#include <sstream>

std::string sha256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.length());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}*/

#include "sha256.h"
#include "picosha2.h"
#include <sstream>

std::string sha256(const std::string& input) {
    std::string hash;
    picosha2::hash256_hex_string(input, hash);
    return hash;
}
