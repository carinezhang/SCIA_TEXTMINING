#include "node.hh"

Node::Node()
{
	start_ = 0;
	length_ = 0;
	frequency_ = 0;
}

Node::Node(int start, int length, int frequency)
	: start_(start),
		length_(length),
		frequency_(frequency)
{
}

Node::~Node()
{}


void Node::addSon(int frequency, std::string& data, std::string word) {
	//std::cout << "add son " << word   << " "<< data.length() << std::endl;
	sons_.push_back(Node(data.length(), word.length(), frequency));
	data.append(word);
	//return node
}

void Node::insert(std::string word, int frequency, std::string& data) {

	int wordLength = word.length();
	// int dataLength = data.size();

	for (auto it = sons_.begin(); it != sons_.end(); it++) {
		int start = it->start_;
		int length = it->length_;
		// same first letter
		if (data[start] == word.at(0)) {
			int i = 0;
			//not at the end of the word, not at the end of the node, same letter at ith letter in node and word 
			while (i < wordLength && i <length && data[start + i] == word.at(i)){
				i++;
			}
			//end of the word and end of the node
			if (i == wordLength && length == i) {
				it->frequency_ = frequency;
				return;
			}
			// word longer than node
			if (i >= length) {
				it->insert(word.substr(i), frequency, data);
				return;
			}
			//split current Node
			Node node(start + i, length - i, it->frequency_);
			it->length_ = i;
			it->frequency_ = frequency;
			node.sons_ = it->sons_;
			it->sons_.clear();
			it->sons_.push_back(node);
			if (i < wordLength) {
				it->frequency_ = 0;
        		it->addSon(frequency, data, word.substr(i));
			}
			return;

		}
	}
	addSon(frequency, data, word);
}

void Node::serialize(std::fstream& output) {
  output.write((char*)&start_, sizeof(start_));
  output.write((char*)&length_, sizeof(length_));
  output.write((char*)&frequency_, sizeof(frequency_));
  unsigned char nbSon = sons_.size();
  output.write((char*)&nbSon, sizeof(nbSon));
  for (auto it = sons_.begin(); it != sons_.end(); it++)
    it->serialize(output);
}

void Node::deserialize(std::istream& in)
{
  in.read((char*)&start_, sizeof(start_));
  in.read((char*)&length_, sizeof(length_));
  in.read((char*)&frequency_, sizeof(frequency_));
  unsigned char nb_sons = 0;
  in.read((char*)&nb_sons, sizeof(nb_sons));
  sons_.resize(nb_sons);
  for (unsigned char i = 0; i < nb_sons; i++)
  {
    Node new_node;
    new_node.deserialize(in);
    sons_.push_back(new_node);
  }
}

void Node::print(const std::string data)
{
  for (int i = start_; i < start_ + length_; i++)
    std::cout << data[i];

  std::cout << " " << frequency_ << std::endl;
  for (auto son : sons_)
    son.print(data);
}

int Node::nbprint() {
	int nb = 0;
	for (auto son = sons_.begin(); son != sons_.end(); son++)
		nb+= son->nbprint();
	if (frequency_ != 0)
		return nb+1;
	return nb;
}

std::set<Search> Node::distance(std::string data, std::string search, int dist, int maxDist, int idx, std::string word)
{
  std::set<Search> res;
  if (dist > maxDist)
    return res;
  // Noeud contenant un mot
  if (frequency_ != 0 && idx == length_)
  {
    std::string c = data.at(start_ + idx);
    tmp_dist = c == search[0] ? 0 : 1;
    tmp_dist += (search.size() - 1);
    if (dist + tmp_dist <= maxDist)
    {
      auto s = Search(word + c, frequency_, dist + tmp_dist);
      res.push_back(s);
    }
  }
  if (dist + 1 < maxDist)
  {
    if (search.substr(1))
    {
      auto res_supp = 
        distance(data, search.substr(1), dist + 1, maxDist, idx, word);
    }
  }
  return res;
}

std::set<Search> Node::merge_set(std::set<Search> s1, std::set<Search> s2)
{
  for (auto s: s1)
  {
    auto ele = s2.find(s);
    if (ele != s2.end())
    {
      if ((*ele).dist_ > s.dist_)
        ele->dist_ = (s.dist_);
      s2.erase(s);
    }
  }
  for (auto s : s2)
    s1.insert(s);
  return s1;
}
