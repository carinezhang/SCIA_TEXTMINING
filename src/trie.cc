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

void Trie::insert(std::string word, int freq)
{
}

void Trie::serialize(std::fstream& output)
{
}
