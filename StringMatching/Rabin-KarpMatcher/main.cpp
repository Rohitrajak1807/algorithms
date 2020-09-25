#include <iostream>
#include <string_view>

#define MOD 1000000007
#define ALPHABET_COUNT 256
static int64_t msb = 1;

void search(const std::string &text, const std::string &pattern);

void init_msb(size_t len);

int64_t hash(std::string_view string);

int64_t rehash(int64_t curr_hash, const char &to_remove, const char &to_add);

int main() {
    const std::string text = "3.141592653589793";
    const std::string pattern = "3";
    search(text, pattern);
}

void search(const std::string &text, const std::string &pattern) {
    int64_t text_len = text.length();
    int64_t pattern_len = pattern.length();
    int64_t length = text_len - pattern_len + 1;
    init_msb(pattern_len - 1);

    int64_t pattern_hash = hash(std::string_view(pattern.c_str()));
    int64_t text_hash = hash(std::string_view(text.c_str(), pattern_len));

    for (size_t i = 0; i < length; ++i) {
        if (pattern_hash == text_hash) {
            std::string_view text_view = std::string_view(text.c_str() + i, pattern_len);
            if (text_view.compare(pattern) == 0) {
                std::cout << "pattern found at index " << i << '\n';
            }
        }
        text_hash = rehash(text_hash, text[i], text[i + pattern_len]);
    }
}

void init_msb(size_t len) {
    for (size_t i = 0; i < len; ++i) {
        msb = (msb * ALPHABET_COUNT) % MOD;
    }
}

int64_t hash(std::string_view string) {
    int64_t hash_val = 0;
    for (const char &c : string) {
        hash_val = (hash_val * ALPHABET_COUNT + c) % MOD;
    }
    return hash_val;
}

int64_t rehash(int64_t curr_hash, const char &to_remove, const char &to_add) {
    int64_t new_hash = (ALPHABET_COUNT * (curr_hash - to_remove * msb) + to_add) % MOD;
    if( new_hash < 0) {
        new_hash = new_hash + MOD;
    }
    return new_hash;
}