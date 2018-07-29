#include "node.hh"

Node::Node()
{
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
	sons_.push_back(Node(data.length(), word.length(), frequency));
	data.append(word);
	//return node
}

void Node::insert(std::string word, int frequency, std::string& data) {

  //std::cout << data << std::endl;

	int wordLength = word.length();
	// int dataLength = data.size();

	for (auto it = sons_.begin(); it != sons_.end(); it++) {
		int start = it->start_;
		int length = it->length_;
		if (data[start] == word.at(0)) {
			int i = 1;
			while (data[start + i] == word.at(i)){
				i++;
			}
			if (i == wordLength && length == i) {
				it->frequency_ = frequency;
				return;
			}
			if (i > length) {
				insert(word.substr(i), frequency, data);
				return;
			}
			//split current Node
			Node node(start + i, length - i, it->frequency_);
			it->length_ = i;
			it->frequency_ = frequency;
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

void Node::serialize() {

}

void Node::print(const std::string data)
{
  for (int i = start_; i < start_ + length_; i++)
    std::cout << data[i];

  std::cout << " " << frequency_ << std::endl;
  for (auto son : sons_)
    son.print(data);
}
