#include <iostream>
#include <cassert>
#include "caesar_cipher.h"

int main() {
    int32_t key = -1;
//    we assume that the message is always lower case
    std::string message = "once you and your friend both understand how to use a caesar cipher it should be relatively easy to send encrypted communications to each other";
    std::string cipher_text = caesar_encipher(message, key);
    std::cout << cipher_text << '\n';
    std::string deciphered_text = caesar_cipher_cracker(cipher_text);
    assert(deciphered_text == message);
    std::cout << deciphered_text << '\n';
    return 0;
}


