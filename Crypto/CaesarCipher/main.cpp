#include <iostream>
#include <string_view>
#include <algorithm>
#include <unordered_map>

#define ALPHABET_LENGTH 26
#define FIRST 'a'

//takes an input string and a shift value(aka key)
std::string caesar_encipher(std::string_view, int32_t);

//reverses the action of caesar_encipher on a string using the same shift value
std::string caesar_decipher(std::string_view, int32_t);

std::string caesar_cipher_cracker(std::string);

void sanitize(std::string &str);

int main() {
    int32_t key = -1;
//    we assume that the message is always lower case
    std::string message = "once you and your friend both understand how to use a caesar cipher it should be relatively easy to send encrypted communications to each other";
    std::string cipher_text = caesar_encipher(message, key);
    std::cout << caesar_cipher_cracker(cipher_text);
    return 0;
}

std::string caesar_encipher(std::string_view message, int32_t key) {
    std::string cipher = std::string(message);
    key %= ALPHABET_LENGTH;
    for (char &c : cipher) {
        if (!isalpha(c)) continue;
        char shift = (c - FIRST + key) % ALPHABET_LENGTH;
        c = shift >= 0 ? shift + FIRST : shift + ALPHABET_LENGTH + FIRST;   // ALPHABET_LENGTH + FIRST, basically 'z'
    }
    return cipher;
}

std::string caesar_decipher(std::string_view cipher_txt, int32_t key) {
    return caesar_encipher(cipher_txt, -1 * key);
}

std::string caesar_cipher_cracker(std::string str) {
    sanitize(str);
    size_t len = str.size();
//    stealing frequency data from https://mitchellkember.com/blog/post/caesar-cipher/
    constexpr double english_freqs[] = {
            0.0804, 0.0148, 0.0334, 0.0382, 0.1249, 0.024, 0.0187, 0.0505, 0.0757, 0.0016,
            0.0054, 0.0407, 0.0251, 0.0723, 0.0764, 0.0214, 0.0012, 0.0628,
            0.0651, 0.0928, 0.0273, 0.0105, 0.0168, 0.0023, 0.0166, 0.0009
    };
    std::unordered_map<char, double> message_freqs;
    for (char c = FIRST + 0; c < FIRST + ALPHABET_LENGTH; ++c) {
        message_freqs[c] = 0;
    }
    for (const char &c : str) {
        message_freqs[c]++;
    }

    for (auto&[k, v] : message_freqs)
        v /= len;

    std::vector<double> chi_sqr_res(26);

    for (auto&[k, v] : message_freqs)
        std::cout << k << '\t' << v << '\n';
    return str;
}

void sanitize(std::string &str) {
    auto end = std::remove_if(str.begin(), str.end(), [](char &c) {
        return c == ' ';
    });
    str.resize(end - str.begin());
}
