#pragma once

#include <seqan3/alphabet/nucleotide/dna5.hpp>
#include <seqan3/io/sequence_file/all.hpp>
#include <seqan3/std/filesystem>


/*! \brief Function, counts Cs and Gs occurences in an fasta file
 *  \param fasta_file input file path to the fsta file
 *  \return returns a map of each genome and their C and G occurences
 *
 *  Simple function, counting C, G in an fasta file using the seqan3 library.
 *  For more information about the SeqAn Library functions see https://docs.seqan.de/seqan/3-master-user/.
 */
std::map<std::string, std::tuple<size_t, size_t>> count_gc(std::filesystem::path fasta_file);


