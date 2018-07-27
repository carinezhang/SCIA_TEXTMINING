#include "parser.hh"

#include <iostream>

Node parseFile(std::string filename) {
  std::ifstream infile(filename);
	std::string line;
	std::string word;
	int frequence;
	Node trie("", 0);
  while (infile >> word >> frequence) {
		trie.add(word, frequence);
		std::cout << word << frequence << std::endl;
	}
	return trie;
}

int main( int argc, const char* argv[] )
{
	std::cout << argc;
	parseFile(argv[1]);
}