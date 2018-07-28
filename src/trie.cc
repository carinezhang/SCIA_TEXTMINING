#include "trie.hh"

Trie::Trie()
{
}

Trie::~Trie()
{
}

void Trie::insert(std::string word, int freq)
{
  root_.insert(word, freq, data_);
}
