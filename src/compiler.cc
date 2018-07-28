#include <iostream>
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
  std::string output = argv[2];
  // Open file
  std::ifstream infile(filename); 
  if (!infile.is_open())
  {
    std::cout << "File not found: " << filename << std::endl;
    return 255;
  }
  // Process file
  Trie trie();
  std::string word;
  std::string freq;
  while (infile >> word >> freq)
  {
    trie.insert(word, std::atoi(freq));
  }
  infile.close();
  // Write the trie in the output file
}
