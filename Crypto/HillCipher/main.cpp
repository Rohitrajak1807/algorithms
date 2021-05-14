#include <iostream>
#include <vector>
#include <string_view>
#include <algorithm>
#include <numeric>

#define ALPHABET_COUNT 26
#define FIRST 'a'

std::string hill_encipher(std::string str, std::vector<std::vector<int32_t>> &key);

void init_key(std::vector<std::vector<int32_t>> &key);

void inline ascii_to_index(std::string &str);

void pad_string(std::string &str, size_t key_size);

void encrypt(std::string &str, size_t start, size_t end, const std::vector<std::vector<int32_t>> &key);

void inline index_to_ascii(std::string &str);

int main() {
	std::string message = "discovery";
	std::vector<std::vector<int32_t>> key = {
			{1, 3},
			{4, 2}
	};
	std::string cipher = hill_encipher(message, key);
	std::cout << cipher;
	return 0;
}

std::string hill_encipher(std::string str, std::vector<std::vector<int32_t>> &key) {
	init_key(key);
	ascii_to_index(str);
	pad_string(str, key.size());
	for (size_t i = 0; i < str.length(); i += key.size()) {
		encrypt(str, i, i + key.size(), key);
	}
	index_to_ascii(str);
	return str;
}

void init_key(std::vector<std::vector<int32_t>> &key) {
	for (auto &i: key) {
		for (int32_t &j : i)
			j %= ALPHABET_COUNT;
	}
}

void inline ascii_to_index(std::string &str) {
	std::for_each(str.begin(), str.end(), [](char &c) {
		c = c - FIRST;
	});
}

void pad_string(std::string &str, size_t key_size) {
	size_t pad_len = str.size() % key_size;
	str.insert(str.size(), pad_len, 0);
}

void encrypt(std::string &str, size_t start, size_t end, const std::vector<std::vector<int32_t>> &key) {
	std::vector<int32_t> vals(key.size());
	for (size_t i = 0; i < key.size(); ++i) {
		for (size_t j = 0; j < key.size(); ++j) {
			vals[i] += key[i][j] * str[start + j];
		}
		vals[i] %= ALPHABET_COUNT;
	}
	for (size_t i = 0; i < key.size(); ++i) {
		str[i + start] = vals[i];
	}
}

void inline index_to_ascii(std::string &str) {
	std::for_each(str.begin(), str.end(), [](char &c) {
		c = c + FIRST;
	});
}
