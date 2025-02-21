#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

std::string filename;
std::string out_filename;
std::string seq_name;

bool isStopCodon(const std::string &codon) {
    return codon == "TAA" || codon == "TAG" || codon == "TGA";
}

void findORFs(const std::string &sequence, int frame, std::ofstream &outfile, std::string seq_name) {
    size_t start_pos = std::string::npos;

    for (size_t i = frame; i + 3 <= sequence.length(); i += 3) {
        std::string codon = sequence.substr(i, 3);

        if (start_pos == std::string::npos && codon == "ATG") {
            start_pos = i;
        } 
        else if (start_pos != std::string::npos && isStopCodon(codon)) {
            size_t end_pos = i + 3;
            std::string orf = sequence.substr(start_pos, end_pos - start_pos);

            outfile << seq_name << "\t" << start_pos +1 << "\t" << end_pos << "\t" << orf.length() << "\t" << orf << "\n";

            start_pos = std::string::npos;  // Reset for next ORF
        }
    }

}

void searchORFs(const std::string &sequence, std::ofstream &outfile, std::string seq_name) {
    for (int frame = 0; frame < 3; frame++) {
        findORFs(sequence, frame, outfile, seq_name);
    }
}

void print_info(){
      std::cout << "\n";
      std::cout << "***** ORF finder *****" << "\n";
      std::cout << "Input requires the input file argument:" << "\n";
      std::cout << "  -i    input file" << "\n";
      std::cout << "\n";
}

int main(int argc, char **argv) {

    if (argc == 1){
    print_info();
    }
    for (int i =  1; i<argc; i+=2) {
        if (strcmp(argv[i],"-i")==0 && argv[i+1]) {
          filename = argv[i+1];
          std::cout << "filename: " << filename << "\n" ;
          }
        else {
          print_info();
        }

    }
    
    std::ifstream infile(filename);
    std::string out_filename;
    out_filename = "ORFs.txt";
    
    std::ofstream outfile(out_filename);
  
    if (!infile.is_open() || !outfile.is_open()) {
        std::cerr << "Error: Unable to open file(s)!" << std::endl;
        return 1;
    }
    
    std::string sequence;
    
    while (std::getline(infile, sequence)) {

        if (!sequence.empty() && sequence[0] != '>'){
            searchORFs(sequence, outfile, seq_name);
            }
        else {
            seq_name = sequence.substr(1);
        }
    }
    
    return 0;
}
