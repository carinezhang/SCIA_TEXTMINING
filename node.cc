#include "node.hh"

Node::Node() {
	val = "";
	frequence = 0;
}

Node::Node(std::string c, int freq) {
	val = c;
	frequence = freq;
}