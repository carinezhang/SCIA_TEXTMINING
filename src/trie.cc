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
  output << data_;
}

void Trie::print()
{
  std::cout << "===================" << std::endl;
  this->root_.print(data_);
}


int Trie::nbprint()
{
  std::cout << "===================" << std::endl;
  return this->root_.nbprint();
}