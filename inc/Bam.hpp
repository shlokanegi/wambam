#pragma once

#include "htslib/include/htslib/hts.h"
#include "htslib/include/htslib/sam.h"
#include "Filesystem.hpp"
#include "Sam.hpp"

using ghc::filesystem::path;

#include <functional>
#include <string>

using std::function;
using std::string;

namespace gfase {

class Bam {
    path bam_path;

    samFile* bam_file;
    bam_hdr_t* bam_header;
//    hts_idx_t* bam_index;
    hts_itr_t* bam_iterator;
    bam1_t* alignment;

public:
    // Define AlignmentSummary struct
    struct AlignmentSummary {
        string ref_name;
        int64_t start;
        int64_t end;
        int64_t matches;
        int64_t nonmatches;
        int64_t indels;
        int64_t indel_length;
        int64_t inferred_length;
        double identity;
        int64_t mapq;
    };


    Bam(path bam_path);
    ~Bam();
    void for_alignment_in_bam(const function<void(const string& ref_name, const string& query_name, int32_t query_length, uint8_t map_quality, uint16_t flag)>& f);
    void for_alignment_in_bam(bool get_cigar, const function<void(SamElement& alignment)>& f);
    static bool is_first_mate(uint16_t flag);
    static bool is_second_mate(uint16_t flag);
    static bool is_not_primary(uint16_t flag);
    static bool is_primary(uint16_t flag);
    static bool is_supplementary(uint16_t flag);

    // Helper function to generate unique key for an alignment
    string createUniqueKey(const string& ref_name, int start, int end, int matches, int nonmatches, string qname);
};

}

