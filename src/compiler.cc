#include <iostream>
#include <fstream>
#include <cstdlib>

#include "trie.hh"
#include "node.hh"

int main(int argc, char **argv)
{
  std::cout << "Size structure: 4";
  if (argc != 3)
  {
    std::cout << "Usage: ./TextMiningCompiler /path/to/word/freq.txt /path/to/output/dict.bin" << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  std::string output_name = argv[2];
  // Open file
  std::ifstream infile(filename); 
  if (!infile.is_open())
  {
    std::cout << "File not found: " << filename << std::endl;
    return 255;
  }
  // Process file
  Trie trie = Trie();
  char *word = nullptr;
  int freq;
  while (infile >> word >> freq)
  {
    std::string w(word);
    trie.insert(w, freq);
  }
  infile.close();
  // Write the trie in the output file
  std::fstream output(output_name, std::ios::binary);
  if (!output.is_open())
  {
    std::cout << "File not found: " << filename << std::endl;
    return 255;
  }
  trie.serialize(output);
  output.close();
  return 0;
}
