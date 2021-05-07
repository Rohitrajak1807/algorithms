#include <caesar_cipher.h>
#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

std::string vigenere_encipher(std::string_view message, std::string_view key);

std::string vigenere_decipher(std::string_view message, std::string_view key);

int main() {
	std::string message = "curl  is  a  tool  to  transfer data from or to a "
	                      "server, using one of the supported protocols (dict, "
	                      "file, ftp, ftps, gopher, http, https, imap, imaps, "
	                      "ldap, ldaps, mqtt, pop3, pop3s, rtmp, rtmps, rtsp,"
	                      " scp, sftp, smb, smbs, smtp, smtps, telnet and tftp)."
	                      " the command is designed to work without user interaction.";
//	we assume that key is only composed of lowercase alphabets
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
			// we dont iterate over the key for non alphabetic values, so store
			// the non character count in non_char and use it to balance the
			// offset into the key
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