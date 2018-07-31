#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <set>
#include <vector>

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
		std::list<Node> get_sons();
    
    std::vector<Search> distance(
        std::string& data, 
        std::string search, 
        int dist, 
        int maxDist, 
        int idx, 
        std::string word);

    /**
     * Merge two sets and remove same elements.
     *
     * @param The first set.
     * @param The second set.
     */
    std::vector<Search> merge_set(
        std::vector<Search> s1, 
        std::vector<Search> s2);
    void printword(std::string& data, std::string begin);
	private:
		int start_;
		int length_;
		int frequency_;
		std::list<Node> sons_;
		//char padding[7];
};
