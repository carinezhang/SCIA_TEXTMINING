#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <set>

#include "search.hh"

class Node {
  public:
    Node();
		Node(int start, int length, int frequency);
    ~Node();
		void insert(std::string word, int frequency, std::string& data);
		void addSon(int frequency, std::string& data, std::string word);
		void serialize(std::fstream& output);
    /**
     * Read a file and convert it to a Node. Also construct its sons.
     *
     * @param The stream of the file.
     */
    void deserialize(std::istream& in);

    /**
     * Print the node and its sons.
     *
     * @param The string containing all the substrings.
     */
    void print(const std::string data);
		int nbprint();
    
    std::set<Search> distance(
        std::string& data, 
        std::string search, 
        int dist, 
        int maxDist, 
        int idx, 
        std::string word);
        
	private:
    std::set<Search> merge_set(
        std::set<Search> s1, 
        std::set<Search> s2);
		int start_;
		int length_;
		int frequency_;
		std::list<Node> sons_;
		//char padding[7];
};
