//
// Created on 5/7/21.
//

#ifndef CAESARCIPHER_CAESAR_CIPHER_H
#define CAESARCIPHER_CAESAR_CIPHER_H

#include <array>
#include <string>
#include <string_view>

#define ALPHABET_LENGTH 26
#define FIRST 'a'
// remaps ascii code of a...z from 97...123 to 0...25
#define IDX(c) ((c)-FIRST)

// stealing frequency data from
// https://mitchellkember.com/blog/post/caesar-cipher/
static constexpr std::array<double, ALPHABET_LENGTH> english_freqs = {
    0.0804, 0.0148, 0.0334, 0.0382, 0.1249, 0.024,  0.0187, 0.0505, 0.0757,
    0.0016, 0.0054, 0.0407, 0.0251, 0.0723, 0.0764, 0.0214, 0.0012, 0.0628,
    0.0651, 0.0928, 0.0273, 0.0105, 0.0168, 0.0023, 0.0166, 0.0009};

// takes an input string and a shift value(aka key)
std::string caesar_encipher(std::string_view, int32_t);

char shift(const char &c, const int32_t& key);

// reverses the action of caesar_encipher on a string using the same shift value
inline std::string caesar_decipher(std::string_view, int32_t);

std::string caesar_cipher_cracker(std::string);

// removing non alphabetic
void sanitize(std::string &str);

double chi_sqr(std::array<double, ALPHABET_LENGTH> &);

#endif // CAESARCIPHER_CAESAR_CIPHER_H
