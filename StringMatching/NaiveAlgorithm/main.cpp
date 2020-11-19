#include <iostream>

void naive_string_matcher(const std::string &str, const std::string &pattern);

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
    naive_string_matcher(str, pattern);
    return 0;
}

void naive_string_matcher(const std::string &str, const std::string &pattern) {
    size_t str_len = str.length();
    size_t pattern_len = pattern.length();
    for (size_t i = 0; i <= str_len - pattern_len; ++i) {
        if (pattern == std::string_view(str.begin() + i, str.begin() + i + pattern_len)) {
            std::cout << "Pattern occurs with shift " << i << '\n';
        }
    }
}