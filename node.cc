#include "node.hh"

Node::Node() {
	val = "";
	frequence = 0;
}

Node::Node(std::string c, int freq) {
	val = c;
	frequence = freq;
}


void Node::add(std::string word, int frequence) {
	char ch = word.at(0);
	std::stringstream ss;
	std::string c;
	ss << ch;
	ss >> c;
	Node n = this->searchSon(c);
	if (n==NULL) {
		this->sons.push_back(Node(c, 0));
		//create new node 
	} else {
		n.add(word.substr(1, word.length() - 1), frequence);
	}
	if (word.length() == 1) {
		n.frequence = frequence;
	}
}

Node Node::searchSon(std::string c)
{
  auto res = std::find_if(this->sons.begin(), this->sons.end(), 
      [c](const Node n) -> bool
      {return n.val == c;});
  return res[0];
}
