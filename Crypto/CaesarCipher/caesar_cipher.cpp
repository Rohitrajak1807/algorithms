//
// Created on 5/7/21.
//

#include "caesar_cipher.h"
#include <cmath>

std::string caesar_encipher(std::string_view message, int32_t key) {
    std::string cipher = std::string(message);
    key %= ALPHABET_LENGTH;
    for (char &c : cipher) {
        if (!isalpha(c)) continue;
        c = shift(c, key);
    }
    return cipher;
}

char shift(const char &c, const int32_t& key) {
  char shift = (c - FIRST + key) % ALPHABET_LENGTH;
  return shift >= 0 ? shift + FIRST : shift + ALPHABET_LENGTH + FIRST;   // ALPHABET_LENGTH + FIRST, basically 'z'
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
//  TODO parallelize this loop
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
        return !std::isalpha(c);
    });
    str.resize(end - str.begin());
}

double chi_sqr(std::array<double, ALPHABET_LENGTH> &obs) {
    double chi_sqr_res = 0;
    for (int i = 0; i < ALPHABET_LENGTH; ++i) {
        chi_sqr_res += pow((obs[i] - english_freqs[i]), 2) / english_freqs[i];
    }
    return chi_sqr_res;
}
