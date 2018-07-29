#include "trie.hh"

Trie::Trie()
{
  this.root_ = Node();
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
  root_.insert(word, freq, data_);
}

void Trie::serialize(std::fstream& output)
{
  // TODO: Add output into the node.serialize() prototype
  root_.serialize();
}
