#pragma once
#include <vector>
#include <string>

class Node{
	public:
		Node();
		Node(std::string c, int frequence);
		void add(std::string word, int frequence);
	private:
		std::string val;
		int frequence;
		std::vector<Node> sons;

};

