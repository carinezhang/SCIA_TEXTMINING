#include "trie.hh"

Trie::Trie()
{
  this->root_ = Node();
}

Trie::~Trie()
{
}

void Trie::insert(std::string word, int freq)
{
  root_.insert(word, freq, data_);
}

void Trie::serialize(std::fstream& output)
{
  root_.serialize(output);
}

void Trie::print()
{
  std::cout << "===================" << std::endl;
  this->root_.print(data_);
}
