#include <iostream>
#include <array>
#include <caesar_cipher.h>

// the dimension of playfair cipher lookup table is a 5x5
#define TABLE_DIM 5

#define ROW(idx) ((idx) / TABLE_DIM)
#define COL(idx) ((idx) % TABLEDIM)

std::string playfair_encipher(std::string_view message, std::string_view key);

void fill_table(std::array<std::array<char, TABLE_DIM>, TABLE_DIM> &alphabet_table,
                const std::array<bool, ALPHABET_LENGTH> &used_chars, size_t i, size_t j);

std::array<size_t, ALPHABET_LENGTH> make_map(const std::array<std::array<char, TABLE_DIM>, TABLE_DIM> &used_chars);


int main() {
	std::string message = "attackatdawn";
	std::string key = "playfairexample";
	std::string cipher_text = playfair_encipher(message, key);
	return 0;
}

std::string playfair_encipher(std::string_view message, std::string_view key) {
	std::array<bool, ALPHABET_LENGTH> used_chars = {false};
//	we assume i and j to be identical and as such 'j' never appears in the 5x5 grid, so
//	marking it as a used character by default removes it from further consideration, Since
//	we claim i and j to be identical, every j in the message will also be substituted for j
//	as the first step during enciphering
	used_chars[IDX('j')] = true;
	std::array<std::array<char, TABLE_DIM>, TABLE_DIM> alphabet_table = {'\0'};
	size_t i = 0, j = 0;
	for (const char &c : key) {
		if (used_chars[IDX(c)])
			continue;
		used_chars[IDX(c)] = true;
		alphabet_table[i][j] = c;
		++j;
		if (j == TABLE_DIM) {
			j = 0;
			i++;
		}
	}

	fill_table(alphabet_table, used_chars, i, j);

	std::array<size_t, ALPHABET_LENGTH> alphabet_map = make_map(alphabet_table);

	for(auto& r : alphabet_table) {
		for(char &c : r)
			std::cout << c << '\t';
		std::cout << '\n';
	}

	for(size_t &s : alphabet_map)
		std::cout << s << '\t';

	return "";
}

void fill_table(std::array<std::array<char, TABLE_DIM>, TABLE_DIM> &alphabet_table,
                const std::array<bool, ALPHABET_LENGTH> &used_chars, size_t i, size_t j) {
	auto it = used_chars.begin();
	if (j != 0) {
		for (; j < TABLE_DIM; ++j) {
			auto next_unused = std::find(it, used_chars.end(), false);
			alphabet_table[i][j] = ASCII(std::distance(used_chars.begin(), next_unused));
			it = next_unused + 1;
		}
		++i;
	}

	for (; i < TABLE_DIM; ++i) {
		for (j = 0; j < TABLE_DIM; j++) {
			auto next_unused = std::find(it, used_chars.end(), false);
			alphabet_table[i][j] = ASCII(std::distance(used_chars.begin(), next_unused));
			it = next_unused + 1;
		}
	}
}

std::array<size_t, ALPHABET_LENGTH> make_map(const std::array<std::array<char, TABLE_DIM>, TABLE_DIM> &used_chars) {
	std::array<size_t, ALPHABET_LENGTH> alphabet_map{};
//	setting the index of 'j' to an out-of-bounds value, as j and i are used interchangeably
	alphabet_map[IDX('j')] = std::numeric_limits<size_t>::max();
	for (size_t i = 0; i < TABLE_DIM; ++i) {
		for (size_t j = 0; j < TABLE_DIM; ++j) {
			char curr = used_chars[i][j];
			alphabet_map[IDX(curr)] = (TABLE_DIM * i) + j;
		}
	}
	return alphabet_map;
}
