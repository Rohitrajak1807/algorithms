#include <caesar_cipher.h>
#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

std::string vigenere_encipher(std::string_view message, std::string_view key);

std::string vigenere_decipher(std::string_view message, std::string_view key);

int main() {
	std::string message = "nydz  me  l  hbzp  gz ffnywrse hmhn jdcz sd gz mgrczqf, yewar abr sr gsi ghatafgph dezxaqbww(rvnx, stpq, qxb, qxbg, kadupv, uexb, sxfdf, uana, wzlte, whmd, ppocd,  zbxf,  tad3,  dba3e,  vfac,  fgxte, cxed,  eqc,  gset, fxf, fmqe, dqfd, wyhcd, hrwrqh lrp gqxb)";
	std::string key = "lemon";
	std::string cipher_text = vigenere_encipher(message, key);
	std::string deciphered = vigenere_decipher(cipher_text, key);
	assert(message == deciphered);
	std::cout << cipher_text << '\n';
	std::cout << deciphered;
	return 0;
}

std::string vigenere_encipher(std::string_view message, std::string_view key) {
	std::string cipher = std::string(message);
	for (int32_t i = 0, non_char = 0; i < cipher.size(); ++i) {
		if (!std::isalpha(cipher[i])) {
			non_char++;
			continue;
		}
		cipher[i] = shift(cipher[i], IDX(key[(i - non_char) % key.size()]));
	}
	return cipher;
}

std::string vigenere_decipher(std::string_view message, std::string_view key) {
	std::string dec_key = std::string(key);
	for (char &c : dec_key) {
		c = ASCII((-IDX(c) + ALPHABET_LENGTH) % ALPHABET_LENGTH);
	}
	return vigenere_encipher(message, dec_key);
}