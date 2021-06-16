#include <sstream>

#include <seqan3/argument_parser/all.hpp>
#include <seqan3/core/debug_stream.hpp>

#include "gc_counter.hpp"

int main(int argc, char ** argv)
{
    seqan3::argument_parser parser{"GC-Counter", argc, argv};

    // Declarations for argument parser
    std::filesystem::path fasta_file{};
    std::filesystem::path output_file{};
    bool verbose = false;

    // Parser
    parser.info.author = "SeqAn-Team"; // give parser some infos
    parser.info.version = "1.0.0";
    parser.add_positional_option(fasta_file, "Please provide a fasta file.",
                                 seqan3::input_file_validator{{"fa","fasta"}}); // Takes a fasta file and validates it
    //output path as option, otherwise output is printed
    parser.add_option(output_file, 'o', "output", "The file for fasta output. Default: stdout");
    parser.add_flag(verbose, 'v', "verbose", "Give more detailed information here."); // example for a flag

    try
    {
         parser.parse();                                                  // trigger command line parsing
    }
    catch (seqan3::argument_parser_error const & ext)                     // catch user errors
    {
        seqan3::debug_stream << "Parsing error. " << ext.what() << "\n"; // give error message
        return -1;
    }

    auto results = count_gc(fasta_file);
    auto outputResults = [&](auto& ofs) {
        ofs << "id,C,G,CG\n";

        size_t countAllC{};
        size_t countAllG{};

        for (auto [id, gcs] : results) {
            auto [c, g] = gcs;
            countAllC += c;
            countAllG += g;
            ofs << id << ',' << c << ',' << g << ',' << (c + g) << '\n';
        }
        ofs << "~Total" << ',' << countAllC << ',' << countAllG << ',' << (countAllC + countAllG) << '\n';
    };

    if (output_file.empty()) {
        outputResults(std::cout);
    } else {
        std::ofstream ofs{output_file};
        outputResults(ofs);

    }



    if (verbose) // if flag is set
        seqan3::debug_stream << "Conversion was a success. Congrats!\n";



    return 0;
}
