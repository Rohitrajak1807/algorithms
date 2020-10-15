#include <iostream>
#include <vector>

void kmp_matcher(const std::string &str, const std::string &pattern);

const std::vector<ssize_t> compute_prefix_function(const std::string &pattern);

int main() {
    const std::string str = "FFMPEG(1)                                                                                                                                                                                                                      FFMPEG(1)\n"
                            "\n"
                            "NAME\n"
                            "       ffmpeg - ffmpeg video converter\n"
                            "\n"
                            "SYNOPSIS\n"
                            "       ffmpeg [global_options] {[input_file_options] -i input_url} ... {[output_file_options] output_url} ...\n"
                            "\n"
                            "DESCRIPTION\n"
                            "       ffmpeg is a very fast video and audio converter that can also grab from a live audio/video source. It can also convert between arbitrary sample rates and resize video on the fly with a high quality polyphase filter.\n"
                            "\n"
                            "       ffmpeg reads from an arbitrary number of input \"files\" (which can be regular files, pipes, network streams, grabbing devices, etc.), specified by the \"-i\" option, and writes to an arbitrary number of output \"files\", which are\n"
                            "       specified by a plain output url. Anything found on the command line which cannot be interpreted as an option is considered to be an output url.\n"
                            "\n"
                            "       Each input or output url can, in principle, contain any number of streams of different types (video/audio/subtitle/attachment/data). The allowed number and/or types of streams may be limited by the container format. Selecting\n"
                            "       which streams from which inputs will go into which output is either done automatically or with the \"-map\" option (see the Stream selection chapter).\n"
                            "\n"
                            "       To refer to input files in options, you must use their indices (0-based). E.g.  the first input file is 0, the second is 1, etc. Similarly, streams within a file are referred to by their indices. E.g. \"2:3\" refers to the\n"
                            "       fourth stream in the third input file. Also see the Stream specifiers chapter.\n"
                            "\n"
                            "       As a general rule, options are applied to the next specified file. Therefore, order is important, and you can have the same option on the command line multiple times. Each occurrence is then applied to the next input or\n"
                            "       output file.  Exceptions from this rule are the global options (e.g. verbosity level), which should be specified first.\n"
                            "\n"
                            "       Do not mix input and output files -- first specify all input files, then all output files. Also do not mix options which belong to different files. All options apply ONLY to the next input or output file and are reset between\n"
                            "       files.\n"
                            "\n"
                            "       •   To set the video bitrate of the output file to 64 kbit/s:\n"
                            "\n"
                            "                   ffmpeg -i input.avi -b:v 64k -bufsize 64k output.avi\n"
                            "\n"
                            "       •   To force the frame rate of the output file to 24 fps:\n"
                            "\n"
                            "                   ffmpeg -i input.avi -r 24 output.avi\n"
                            "\n"
                            "       •   To force the frame rate of the input file (valid for raw formats only) to 1 fps and the frame rate of the output file to 24 fps:\n"
                            "\n"
                            "                   ffmpeg -r 1 -i input.m2v -r 24 output.avi\n"
                            "\n"
                            "       The format option may be needed for raw input files.";
    const std::string pattern = "ffmpeg";
    kmp_matcher(str, pattern);
    return 0;
}

void kmp_matcher(const std::string &str, const std::string &pattern) {
    ssize_t str_len = str.length();
    ssize_t pattern_len = pattern.length();
    auto prefix_table = compute_prefix_function(pattern);
    ssize_t q = -1;
    for (ssize_t i = 0; i < str_len; ++i) {
        while (q >= 0 && pattern[q + 1] != str[i]) {
            q = prefix_table[q];
        }
        if (pattern[q + 1] == str[i])
            ++q;
        if (q == pattern_len - 1) {
            std::cout << "Pattern occurs at index " << i - pattern_len + 1 << '\n';
            q = prefix_table[q];
        }
    }
}

const std::vector<ssize_t> compute_prefix_function(const std::string &pattern) {
    ssize_t m = pattern.length();
    std::vector<ssize_t> prefix_table(m);
    prefix_table[0] = -1;
    ssize_t k = -1;
    for (ssize_t i = 1; i < m; i++) {
        while (k >= 0 && pattern[k + 1] != pattern[i]) {
            k = prefix_table[k];
        }
        if (pattern[k + 1] == pattern[i]) {
            ++k;
        }
        prefix_table[i] = k;
    }
    return prefix_table;
}
