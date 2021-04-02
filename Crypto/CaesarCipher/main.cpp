#include <iostream>
#include <string_view>
#include <algorithm>
#include <array>
#include <cmath>
#include <cassert>

#define ALPHABET_LENGTH 26
#define FIRST 'a'
//remaps ascii code of a...z from 97...123 to 0...25
#define IDX(c) ((c) - FIRST)

//stealing frequency data from https://mitchellkember.com/blog/post/caesar-cipher/
static constexpr std::array<double, ALPHABET_LENGTH> english_freqs[] = {
        0.0804, 0.0148, 0.0334, 0.0382, 0.1249, 0.024, 0.0187, 0.0505, 0.0757, 0.0016,
        0.0054, 0.0407, 0.0251, 0.0723, 0.0764, 0.0214, 0.0012, 0.0628,
        0.0651, 0.0928, 0.0273, 0.0105, 0.0168, 0.0023, 0.0166, 0.0009
};

//takes an input string and a shift value(aka key)
std::string caesar_encipher(std::string_view, int32_t);

//reverses the action of caesar_encipher on a string using the same shift value
inline std::string caesar_decipher(std::string_view, int32_t);

std::string caesar_cipher_cracker(std::string);

//only removing spaces for now, may expand to all non alpha-numericals
void sanitize(std::string &str);

double chi_sqr(std::array<double, ALPHABET_LENGTH> &);

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

inline std::string caesar_decipher(std::string_view cipher_txt, int32_t key) {
    return caesar_encipher(cipher_txt, -1 * key);
}

std::string caesar_cipher_cracker(std::string str) {
    std::string original_message = str;
    sanitize(str);

    size_t len = str.size();

    double min_chi_sqr = std::numeric_limits<double>::infinity();
    int key = std::numeric_limits<int>::infinity();
//TODO parallelize this loop
    for (int i = 0; i < ALPHABET_LENGTH; ++i) {
        std::string possible_message = caesar_decipher(str, i);
        std::array<double, ALPHABET_LENGTH> message_freqs{};

        std::for_each(possible_message.begin(), possible_message.end(),
                      [&message_freqs](const char &c) { message_freqs[IDX(c)]++; });

        std::for_each(message_freqs.begin(), message_freqs.end(), [&len](double &f) { f /= len; });

        double chi_res = chi_sqr(message_freqs);
        if (chi_res < min_chi_sqr) {
            min_chi_sqr = chi_res;
            key = i;
        }
    }

    return caesar_decipher(original_message, key);
}

void sanitize(std::string &str) {
    auto end = std::remove_if(str.begin(), str.end(), [](char &c) {
        return c == ' ';
    });
    str.resize(end - str.begin());
}

double chi_sqr(std::array<double, ALPHABET_LENGTH> &obs) {
    double chi_sqr_res = 0;
    for (int i = 0; i < ALPHABET_LENGTH; ++i) {
        chi_sqr_res += pow((obs.at(i) - english_freqs->at(i)), 2) / english_freqs->at(i);
    }
    return chi_sqr_res;
}
