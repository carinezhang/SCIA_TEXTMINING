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

void Trie::deserialize(std::fstream& in)
{
  root_.deserialize(in);
  in >> data_;
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

std::set<Search> Trie::search(std::string word, int dist) {
  return root_.distance(data_, word, 0, dist, 0, "");
}

void Trie::printword(){
  root_.printword(data_, "");
} 
void Trie::printdist(std::set<Search> distances) {
	for (auto d = distances.begin(); d != distances.end(); d++) {
		std::cout << "word: " << d->word_ << "freq: " << d->freq_ << "dist: " << d->dist_ << std::endl;
	}
}