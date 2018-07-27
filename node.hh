#pragma once
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

class Node{
	public:
		Node();
		Node(std::string c, int frequence);
		void add(std::string word, int frequence);
		Node searchSon(std::string c);
	private:
		std::string val;
		int frequence;
		std::vector<Node> sons;
	
};

