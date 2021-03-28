#include <iostream>
#include <string_view>

#define ALPHABET_LENGTH 26
#define FIRST 'a'

std::string caesar_cipher(std::string_view, int32_t);

int main() {
    int32_t key = -1;
//    we assume that the message is always lower case
    std::string message = "once you and your friend both understand how to use a caesar cipher it should be relatively easy to send encrypted communications to each other";
    std::string cipher_text = caesar_cipher(message, key);
    std::cout << cipher_text;
    return 0;
}

std::string caesar_cipher(std::string_view message, int32_t key) {
    std::string cipher = std::string(message);
    key %= ALPHABET_LENGTH;
    for (char &c : cipher) {
        if (!isalpha(c)) continue;
        char shift = (c - FIRST + key) % ALPHABET_LENGTH;
        c = shift >= 0 ? shift + FIRST : shift + ALPHABET_LENGTH + FIRST;   // ALPHABET_LENGTH + FIRST, basically 'z'
    }
    return cipher;
}
