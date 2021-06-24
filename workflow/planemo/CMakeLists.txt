project (fastq_to_fasta_planemo CXX)

cmake_minimum_required(VERSION 3.8)

# Dependency: SeqAn3.
find_package (SeqAn3 QUIET REQUIRED HINTS ../../lib/seqan3/build_system)

# Use ccache.
include ("${SEQAN3_CLONE_DIR}/test/cmake/seqan3_require_ccache.cmake")
seqan3_require_ccache ()

add_subdirectory (../../src app_binary)

file (
    GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/fastq_to_fasta.xml
    INPUT ${CMAKE_CURRENT_SOURCE_DIR}/fastq_to_fasta.xml.in
)

file (
    GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gc_counter.xml
    INPUT ${CMAKE_CURRENT_SOURCE_DIR}/gc_counter.xml.in
)

find_package (PythonInterp 3 REQUIRED)

add_custom_target (
    create_test_data ALL
    ${CMAKE_COMMAND} -E
        create_symlink
            ${CMAKE_CURRENT_SOURCE_DIR}/test-data
            ${CMAKE_CURRENT_BINARY_DIR}/test-data
)

enable_testing ()

add_test(
    NAME test_planemo
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test_planemo.sh
)
