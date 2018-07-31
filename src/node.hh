#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <set>
#include <vector>

#include "search.hh"
/**
 * @file
 * @author drapal_g zhang_d
 *
 * @section DESCRIPTION
 *
 * The Node class represent a node of a Patricia-Trie containing in Trie class.
 * It contains the start, length and frequency of the word 
 * in the Trie's data_ attribute.
 *
 */

class Node {
  public:
    /**
     * Default constructor.
     */
    Node();

    /**
     * Construct with all the attributes.
     *
     * @param start     The index which this node's word starts in the data attribute in the Trie.
     * @param length    The length of this node's word.
     * @param frequency The frequency of this node's word, 0 if the word is not a complete word.
     */
		Node(int start, int length, int frequency);

    /**
     * Default destructor.
     */
    ~Node();
    
    /**
     * Insert a word into the Patricia-trie.
     *
     * @param word      The word to insert.
     * @param frequency The frequency of the inserted word.
     * @param data      The string containing all the words. This string is in the Trie containing the root of the trie.
     */
		void insert(std::string word, int frequency, std::string& data);

    /**
     * Insert a son to this node.
     *
     * @param frequency The frequency of the inserted word.
     * @param data      The string containing all the words. This string is in the Trie containing the root of the trie.
     * @param word      The word to insert.
     */
		void addSon(int frequency, std::string& data, std::string word);

    /**
     * Serialize the trie starting with this node into the given output stream.
     *
     * @param output  The stream to be written into.
     */
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
     * @param data The string containing all the substrings.
     */
    void print(const std::string data);

    /**
     * Print the number of words in the trie which root is this node. 
     * Compute the number of words recursivly.
     */
		int nbprint();

    /**
     * Return the sons of the node.
     *
     * @return The sons of the node.
     */
		std::list<Node*> get_sons();
    
    /**
     * Compute the vector of Search containing the word at a maxDist Demereau-Levenstein distance.
     *
     * @param data    The string containing all the words.
     * @param search  The string to search.
     * @param dist    The current distance.
     * @param maxDist The max distance to search for.
     * @param idx     The index of the char that is analysed. 
     *                  Because we use a patricia trie, a node contains a string 
     *                  and not 1 char so we iterate over them.
     * @param word    The word we are currently on from the root node to the current node.
     *
     * @return All the words at max maxDist distance.
     */
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
     *
     * @return The 2 sets merged.
     */
    std::vector<Search> merge_set(
        std::vector<Search> s1, 
        std::vector<Search> s2);

    /**
     * Print the word of the node if this node contains a frequency not equal to 0.
     * Print the words of its sons recursivly.
     */
    void printword(std::string& data, std::string begin);
	private:
    /**
     * The index of which the word starts in the Trie's data_.
     */
		int start_;

    /**
     * The length of the word.
     */
		int length_;

    /**
     * The frequency of the word.
     */
		int frequency_;

    /**
     * The sons of this node.
     */
		std::list<Node*> sons_;
};
