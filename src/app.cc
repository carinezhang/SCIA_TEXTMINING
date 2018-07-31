#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cstdlib>
#include <string>

#include "trie.hh"
#include "node.hh"

int main(int argc, char **argv)
{
  // Get the dict
  if (argc != 2)
  {
    std::cout << "Usage: ./TextMiningApp /path/to/compiled/dict.bin" << std::endl;
    return 1;
  }

  // Deserialize the dict
  std::string dictname = argv[1];
  std::fstream test_in(dictname, std::fstream::in | std::fstream::binary);
  Trie trie = Trie();
  trie.deserialize(test_in);

  // Get the inputs
  std::string inputLine;
  while (getline(std::cin, inputLine))
  {
    std::stringstream ss;
    ss << inputLine;
    std::vector<std::string> strings;
    std::string s;    
    
    // Get the args
    while (getline(ss, s, ' ')) {
      strings.push_back(s);
    }
    if (strings.size() != 3 && strings[0] != "approx")
    {
      std::cout << "Usage: ./TextMiningApp /path/to/compiled/dict.bin" << std::endl;
      return 1;
    }
    int maxDist = std::stoi(strings[1]);
    std::string search = strings[2];

    auto result = trie.search(search, maxDist);
    trie.printdist(trie.sort(result));
  }

  return 0;
}
