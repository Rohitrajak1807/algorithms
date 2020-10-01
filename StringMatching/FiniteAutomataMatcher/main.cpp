#include <iostream>
#include <vector>

#define ALPHABET_COUNT 256
#define SHIFT_INDEX(i, text_len) ((i) - (text_len) + 1)


void search(const std::string &text, const std::string &pattern);

void make_automata(const std::string &pattern, std::vector<std::vector<size_t>> &transition_matrix);

size_t next_state(const std::string &pattern, size_t curr_state, int curr_char);

int main() {
    std::string text = "In this post, we will discuss Finite Automata (FA) based pattern searching algorithm. In FA based algorithm, we preprocess the pattern and build a 2D array that represents a Finite Automata. Construction of the FA is the main tricky part of this algorithm. Once the FA is built, the searching is simple. In search, we simply need to start from the first state of the automata and the first character of the text. At every step, we consider next character of text, look for the next state in the built FA and move to a new state. If we reach the final state, then the pattern is found in the text. The time complexity of the search process is O(n).\n"
                       "Before we discuss FA construction, let us take a look at the following FA for pattern ACACAGA.";
    std::string pattern = "text";
    search(text, pattern);
    return 0;
}

void search(const std::string &text, const std::string &pattern) {
    int state = 0;
    size_t text_len = text.length(), pattern_len = pattern.length();
    std::vector<std::vector<size_t>> transition_matrix(pattern_len + 1, std::vector<size_t>(ALPHABET_COUNT, 0));
    make_automata(pattern, transition_matrix);
    for (size_t i = 0; i < text_len; ++i) {
        state = transition_matrix[state][text[i]];
        if (state == pattern_len) {
            std::cout << "Pattern found at shift " << SHIFT_INDEX(i, pattern_len) << '\n';
        }
    }
}

void make_automata(const std::string &pattern, std::vector<std::vector<size_t>> &transition_matrix) {
    for (size_t i = 0; i < pattern.length() + 1; ++i) {
        for (int j = 0; j < ALPHABET_COUNT; ++j) {
            transition_matrix[i][j] = next_state(pattern, i, j);
        }
    }
}

size_t next_state(const std::string &pattern, size_t curr_state, int curr_char) {
    size_t result_state = 0;
    if (curr_state < pattern.length() && curr_char == pattern[curr_state]) {
        result_state = curr_state + 1;
    }
    for (size_t next_state = curr_state; next_state > 0; --next_state) {
        if (pattern[next_state - 1] == curr_char) {
            for (size_t i = 0; i < next_state - 1; ++i) {
                if (pattern[i] != pattern[curr_state - next_state + 1 + i]) {
                    break;
                }
            }
            if (result_state == next_state - 1) {
                result_state = next_state;
            }
        }
    }
    return result_state;
}