# Overview
Find ORFs in a FASTA file based on the standard codon table i.e. starts: ATG, stops: TAA, TGA, TAG.

## Manual
```
Input requires the argument:
  -i    input file
  ```
The output is a file named "renamed_output.fast(a|q)" in the same directory as the binary. Output format is sequence_name, start, end, sequence_length, ORF_sequence.
## Future implementations
- Find ORFs in reverse complement
- Support for FASTQ files
- User defined start and stop codons
- Filter by minimum length threshold
- Handling lower case letters
