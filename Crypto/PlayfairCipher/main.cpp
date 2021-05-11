#include <iostream>
#include <array>
#include <caesar_cipher.h>

// the dimension of playfair cipher lookup table is a 5x5
#define TABLE_DIM 5

#define ROW(idx) ((idx) / TABLE_DIM)
#define COL(idx) ((idx) % TABLE_DIM)

std::string playfair_encipher(std::string_view message, std::string_view key);

std::string replace_all_j(std::string_view message);

void fill_table(std::array<std::array<char, TABLE_DIM>, TABLE_DIM> &alphabet_table,
                const std::array<bool, ALPHABET_LENGTH> &used_chars, size_t i, size_t j);

std::array<size_t, ALPHABET_LENGTH> make_map(const std::array<std::array<char, TABLE_DIM>, TABLE_DIM> &used_chars);

std::string form_digrams(const std::string &input);

int main() {
	std::string message = "hidethegoldinthetreestump";
	std::string key = "playfairexample";
	std::string cipher_text = playfair_encipher(message, key);
	std::cout << cipher_text;
	return 0;
}

std::string playfair_encipher(std::string_view message, std::string_view key) {

//	we swap all j's in the message into i cause we consider them to be identical
	std::string changed_message = replace_all_j(message);
	std::string output;
	output.reserve(message.size() * 2);
	std::array<bool, ALPHABET_LENGTH> used_chars = {false};
//	we assume i and j to be identical and as such 'j' never appears in the 5x5 grid, so
//	marking it as a used character by default removes it from further consideration, Since
//	we claim i and j to be identical, every j in the message will also be substituted for j
//	as the first step during enciphering
	used_chars[IDX('j')] = true;
	std::array<std::array<char, TABLE_DIM>, TABLE_DIM> alphabet_table = {'\0'};
	size_t i = 0, j = 0;

//	fill the 5x5 grid used for encryption
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

	changed_message = form_digrams(changed_message);

	for (size_t idx = 0; idx < changed_message.size(); idx += 2) {
		size_t curr = alphabet_map[IDX(changed_message[idx])];
		size_t next = alphabet_map[IDX(changed_message[idx + 1])];
		size_t r1 = ROW(curr),
				r2 = ROW(next),
				c1 = COL(curr),
				c2 = COL(next);
		if(r1 != r2 && c1 != c2) {
			output.push_back(alphabet_table[r1][c2]);
			output.push_back(alphabet_table[r2][c1]);
		} else if(c1 == c2) {
			output.push_back(alphabet_table[(r1 + 1) % TABLE_DIM][c1]);
			output.push_back(alphabet_table[(r2 + 1) % TABLE_DIM][c2]);
		} else if(r1 == r2) {
			output.push_back(alphabet_table[r1][(c1 + 1) % TABLE_DIM]);
			output.push_back(alphabet_table[r2][(c2 + 1) % TABLE_DIM]);
		}
	}
	output.resize(output.size());
	return output;
}

std::string replace_all_j(std::string_view message) {
	std::string new_str(message);
	std::for_each(new_str.begin(), new_str.end(), [](char &c) {
		c = (c == 'j') ? 'i' : c;
	});
	return new_str;
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

std::string form_digrams(const std::string &input) {
	std::string new_str;
	new_str.reserve(input.size() * 2);
	for (size_t i = 0; i < input.size(); i += 2) {
		const char &curr = input[i],
				&next = (i + 1) >= input.size() ? '\0' : input[i + 1];
		new_str.push_back(curr);
		if (curr == next) {
			new_str.push_back('x');
		}
		if (next != '\0')
			new_str.push_back(next);
	}
	if (new_str.size() % 2 == 0) {
		new_str[new_str.size()] = 'x';
	}
	new_str.resize(new_str.size());
	return new_str;
}
