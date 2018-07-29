#include "node.hh"

Node::Node()
{
	start_ = 0;
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
	std::cout << "add son " << word   << " "<< data.length() << std::endl;
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
		if (data[start] == word.at(0)) {
			int i = 0;
			while (i < wordLength && i <length && data[start + i] == word.at(i)){
				i++;
			}
			if (i == wordLength && length == i) {
				it->frequency_ = frequency;
				return;
			}
			if (i >= length) {
				insert(word.substr(i), frequency, data);
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
				return;
			}
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

/*
void Node::deserialize(std::istream& in)
{
  in.read((char*)&start_, sizeof(start_));
  in.read((char*)&length_, sizeof(length_));
}
*/

void Node::print(const std::string data)
{
  for (int i = start_; i < start_ + length_; i++)
    std::cout << data[i];

  std::cout << " " << frequency_ << std::endl;
  for (auto son : sons_)
    son.print(data);
}
