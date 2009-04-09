#include "intersectBed.h"

using namespace std;

// define our program name
#define PROGRAM_NAME "intersectBed"

// define the version
#define VERSION "1.1.0"

// define our parameter checking macro
#define PARAMETER_CHECK(param, paramLen, actualLen) (strncmp(argv[i], param, min(actualLen, paramLen))== 0) && (actualLen == paramLen)

// function declarations
void ShowHelp(void);

int main(int argc, char* argv[]) {

	// our configuration variables
	bool showHelp = false;

	// input files
	string bedAFile;
	string bedBFile;

	// input arguments
	float overlapFraction = 1E-9;

	bool haveBedA = false;
	bool haveBedB = false;
	bool noHit = false;
	bool anyHit = false;
	bool writeB = false;
	bool writeCount = false;

	// check to see if we should print out some help
	if(argc <= 1) showHelp = true;

	for(int i = 1; i < argc; i++) {
		int parameterLength = (int)strlen(argv[i]);

		if(PARAMETER_CHECK("-h", 2, parameterLength) || 
		PARAMETER_CHECK("--help", 5, parameterLength)) {
			showHelp = true;
		}
	}

	if(showHelp) ShowHelp();

	// do some parsing (all of these parameters require 2 strings)
	for(int i = 1; i < argc; i++) {

		int parameterLength = (int)strlen(argv[i]);

		if(PARAMETER_CHECK("-a", 2, parameterLength)) {
			haveBedA = true;
			bedAFile = argv[i + 1];
			i++;
		}
		else if(PARAMETER_CHECK("-b", 2, parameterLength)) {
			haveBedB = true;
			bedBFile = argv[i + 1];
			i++;
		}	
		else if(PARAMETER_CHECK("-u", 2, parameterLength)) {
			anyHit = true;
			i++;
		}
		else if(PARAMETER_CHECK("-f", 2, parameterLength)) {
			overlapFraction = atof(argv[i + 1]);
			i++;
		}
		else if(PARAMETER_CHECK("-wb", 3, parameterLength)) {
			writeB = true;
			i++;
		}
		else if(PARAMETER_CHECK("-c", 2, parameterLength)) {
			writeCount = true;
			i++;
		}
		else if (PARAMETER_CHECK("-v", 2, parameterLength)) {
			noHit = true;
			i++;
		}
		else {
			cout << endl << "*****ERROR: Unrecognized parameter: " << argv[i] << " *****" << endl << endl;
			showHelp = true;
		}		
	}

	// make sure we have both input files
	if (!haveBedA || !haveBedB) {
		cout << endl << "*****" << endl << "*****ERROR: Need -a and -b files. " << endl << "*****" << endl;
		showHelp = true;
	}

	if (anyHit && noHit) {
		cout << endl << "*****" << endl << "*****ERROR: Request either -u OR -v, not both." << endl << "*****" << endl;
		showHelp = true;
	}

	if (writeB && writeCount) {
		cout << endl << "*****" << endl << "*****ERROR: Request either -wb OR -c, not both." << endl << "*****" << endl;
		showHelp = true;
	}

	if (!showHelp) {

		BedIntersect *bi = new BedIntersect(bedAFile, bedBFile, anyHit, writeB, overlapFraction, noHit,  writeCount);
		bi->IntersectBed();
		return 0;
	}
	else {
		ShowHelp();
	}
}

void ShowHelp(void) {

	cout << "=======================================================" << endl;
	cout << PROGRAM_NAME << " v" << VERSION << endl ;
	cout << "Aaron Quinlan, Ph.D." << endl;
	cout << "aaronquinlan@gmail.com" << endl ;
	cout << "Hall Laboratory" << endl;
	cout << "Biochemistry and Molecular Genetics" << endl;
	cout << "University of Virginia" << endl; 
	cout << "=======================================================" << endl << endl;
	cout << "Description: Report overlaps between a.bed and b.bed." << endl << endl;
	cout << "***NOTE: Only BED3 - BED6 formats allowed.***"<< endl << endl;

	cout << "Usage: " << PROGRAM_NAME << " [OPTIONS] -a <a.bed> -b <b.bed>" << endl << endl;

	cout << "OPTIONS: " << endl;
	cout << "\t" << "-u\t\t\t"            	<< "Write ORIGINAL a.bed entry ONCE if ANY overlap bed." << endl << "\t\t\t\tIn other words, ignore multiple overlaps." << endl << endl;
	cout << "\t" << "-v \t\t\t"             << "Only report those entries in A that have NO OVERLAP in B." << endl << "\t\t\t\tSimilar to grep -v." << endl << endl;
	cout << "\t" << "-f (e.g. 0.05)\t\t"	<< "Minimum overlap req'd as fraction of a.bed." << endl << "\t\t\t\tDefault is 1E-9 (effectively 1bp)." << endl << endl;
	cout << "\t" << "-c \t\t\t"				<< "For each entry in A, report the number of hits in B while restricting to -f." << endl << "\t\t\t\tReports 0 for A entries that have no overlap with B." << endl << endl;
	cout << "\t" << "-wb \t\t\t"			<< "Write the entry in B for each overlap." << endl << "\t\t\t\tUseful for knowing _what_ A overlaps. Restricted by -f." << endl << endl;
	// end the program here
	exit(1);

}