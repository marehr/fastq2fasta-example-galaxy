#include "gc_counter.hpp"

std::map<std::string, std::tuple<size_t, size_t>> count_gc(std::filesystem::path fasta_file)
{
    using namespace seqan3::literals; // gives us the _dna4 suffix
    std::map<std::string, std::tuple<size_t, size_t>> results;

    seqan3::sequence_file_input fin{fasta_file};
    for (auto & record : fin)
    {
        size_t countC{};
        size_t countG{};
        for (auto c : record.sequence())
        {
            if (c == 'C'_dna5) {
                countC += 1;
            }
            if (c == 'G'_dna5) {
                countG += 1;
            }
        }
        results.try_emplace(record.id(), countC, countG);
    }

    return results;
}
