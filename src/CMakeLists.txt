cmake_minimum_required (VERSION 3.8)

# An object library (without main) to be used in multiple targets.
add_library ("${PROJECT_NAME}_lib" STATIC fastq_conversion.cpp)
target_link_libraries ("${PROJECT_NAME}_lib" PUBLIC seqan3::seqan3)
target_include_directories ("${PROJECT_NAME}_lib" PUBLIC ../include)

add_executable ("fastq_to_fasta" fastq_conversion_main.cpp)
target_link_libraries ("fastq_to_fasta" PRIVATE "${PROJECT_NAME}_lib")

add_executable ("gc_counter" gc_counter_main.cpp gc_counter.cpp)
target_link_libraries ("gc_counter" PUBLIC seqan3::seqan3)
target_include_directories ("gc_counter" PUBLIC ../include)
