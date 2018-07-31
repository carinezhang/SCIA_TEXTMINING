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

std::vector<Search> Trie::search(std::string word, int dist) {
  std::vector<Search> res;
  auto sons = root_.get_sons();
  for (auto son = sons.begin(); son != sons.end(); son++) {
    std::cout << "son" << std::endl;
    auto tmp = son->distance(data_, word, 0, dist, 0, "");
    res = root_.merge_set(res, tmp);
  }
  return res;
  //return root_.distance(data_, word, -1, dist, 0, "");
}
std::vector<Search> Trie::sort(std::vector<Search> s) {
  std::sort(s.begin(), s.end(), sortVector);
  return s;
}

bool Trie::sortVector(Search s1, Search s2){
  if (s1.dist_ < s2.dist_)
    return true;
  if (s1.dist_ > s2.dist_)
    return false;
  if (s1.freq_ > s2.freq_)
    return true;
  if (s1.freq_ < s2.freq_)
    return false;
  if (s1.word_ < s2.word_)
    return true;
  return false;
}

void Trie::printword(){
  root_.printword(data_, "");
} 
void Trie::printdist(std::vector<Search> distances) {
	for (auto d = distances.begin(); d != distances.end(); d++) {
		std::cout << "word: " << d->word_ << " freq: " << d->freq_ << " dist: " << d->dist_ << std::endl;
	}
}