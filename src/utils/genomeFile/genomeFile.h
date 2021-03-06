/*****************************************************************************
  genomeFile.h

  (c) 2009 - Aaron Quinlan
  Hall Laboratory
  Department of Biochemistry and Molecular Genetics
  University of Virginia
  aaronquinlan@gmail.com

  Licensed under the GNU General Public License 2.0 license.
******************************************************************************/
#ifndef GENOMEFILE_H
#define GENOMEFILE_H

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "api/BamReader.h"
#include "api/BamAux.h"
using namespace BamTools;

using namespace std;


// typedef for mapping b/w chrom name and it's size in b.p.
typedef map<string, int, std::less<string> > chromToSizes;


class GenomeFile {

public:

    // Constructor using a file
    GenomeFile(const string &genomeFile);
    
    // Constructor using a vector of BamTools RefVector
    GenomeFile(const RefVector &genome);

    // Destructor
    ~GenomeFile(void);

    // load a GENOME file into a map keyed by chrom. value is size of chrom.
    void loadGenomeFileIntoMap();
    
    pair<string, uint32_t> projectOnGenome(uint32_t genome_pos);
    
    uint32_t getChromSize(const string &chrom);     // return the size of a chromosome
    uint32_t getGenomeSize(void);              // return the total size of the geonome
    vector<string> getChromList();             // return a list of chrom names
    int getNumberOfChroms();                   // return the number of chroms
    string getGenomeFileName();                // return the name of the genome file




private:
    string  _genomeFile;
    chromToSizes _chromSizes;
    vector<string> _chromList;

    // projecting chroms into a single coordinate system
    uint32_t _genomeLength;
    vector<uint32_t> _startOffsets;
    
};

#endif /* GENOMEFILE_H */
