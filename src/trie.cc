#include "trie.hh"

Trie::Trie()
{
  this->root_ = Node();
  this->data_ = "";
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
  // TODO: Add output into the node.serialize() prototype
  output.is_open();
  root_.serialize();
}
