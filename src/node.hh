#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <string>

class Node {
  public:
    Node();
		Node(int start, int length, int frequency);
    ~Node();
		void insert(std::string word, int frequency, std::string& data);
		void addSon(int frequency, std::string& data, std::string word);
		void serialize(std::fstream& output);
    /**
     * Print the node and its sons.
     *
     * @param The string containing all the substrings.
     */
    void print(const std::string data);
	private:
		int start_;
		int length_;
		int frequency_;
		std::list<Node> sons_;
		//char padding[7];
};
