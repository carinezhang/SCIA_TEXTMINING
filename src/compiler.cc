#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

#include "trie.hh"
#include "node.hh"

int main(int argc, char **argv)
{
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
  std::string line;
  while (std::getline(infile, line))
  {
    std::istringstream iss(line);
    std::string word;
    int freq;
    if (!(iss >> word >> freq))
      break;
    trie.insert(word, freq);
  }

  infile.close();

  std::fstream output(output_name, std::fstream::out | std::fstream::binary);
  trie.serialize(output);
  std::cout << "nb:" << trie.nbprint() << std::endl;
  output.close();


  return 0;
}
