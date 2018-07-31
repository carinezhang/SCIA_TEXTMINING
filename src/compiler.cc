#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

#include "trie.hh"
#include "node.hh"

int main(int argc, char **argv)
{
  
  std::cout << "Size structure: 4" << std::endl;
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
    
    //std::cout << "Line : " << word << " " << freq << std::endl;
    //std::cout << "data :" << trie.data_ << std::endl;

    trie.insert(word, freq);
  }
  //trie.print();

  infile.close();
  // Write the trie in the output file
  std::fstream output(output_name, std::fstream::out | std::fstream::binary);
  trie.serialize(output);
  std::cout << "nb:" << trie.nbprint() << std::endl;
  output.close();

  std::cout << "===============================" << std::endl;
  std::cout << "DESERIALIZE" << std::endl;

  std::fstream test_in(output_name, std::fstream::in | std::fstream::binary);
  Trie trie_test = Trie();
  trie_test.deserialize(test_in);
  trie_test.printword(); 
  std::cout << "nb:" << trie_test.nbprint() << std::endl;
  
  std::cout << argc << argv << std::endl;
  std::cout << "=========================" << std::endl;
  
  auto res = trie_test.search("test", 0);
  std::cout << "SEARCH nb:" << res.size() << std::endl;
  trie_test.printdist(res);
  std::cout << "=========================" << std::endl;
  return 0;
}
