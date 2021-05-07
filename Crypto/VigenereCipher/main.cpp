#include <iostream>
#include <string>
#include <string_view>
#include <caesar_cipher.h>

std::string vigenere_encipher(std::string_view message, std::string_view key);

int main() {
    std::string message = "attackatdawn";
    std::string key = "lemon";
    std::string cipher_text = vigenere_encipher(message, key);
	std::cout << cipher_text;
    return 0;
}

std::string vigenere_encipher(std::string_view message, std::string_view key) {
	std::string cipher = std::string(message);
	for (int32_t i = 0; i < cipher.size(); ++i) {
		if (!std::isalpha(cipher[i])) continue;
		cipher[i] = shift(cipher[i], IDX(key[i % key.size()]));
	}
	return cipher;
}