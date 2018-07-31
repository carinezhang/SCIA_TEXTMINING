#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

/**
 * @file
 * @author drapal_g zhang_d
 *
 * @section DESCRIPTION
 *
 * The Trie class represent the class that contains the tree.
 * It works like a Patricia Trie with the attribute data_ being 
 * the vector of strings that exists in this trie.
 * It is the class to use to insert and search for a word 
 * in his patricia trie.
 *
 */

#include "node.hh"

class Trie {
  public:
    /**
     * Default constructor.
     */
    Trie();

    /**
     * Default destructor.
     */
    ~Trie();

    /**
     * Insert a new word into the trie.
     *
     * @param The word to insert.
     * @param The frequency of the word.
     */
    void insert(std::string word, int freq);

    /**
     * Write the current trie into the output file.
     *
     * @param The stream linked to the output file.
     */
    void serialize(std::fstream& output);

    /**
     * Read a file and convert it to a Trie.
     *
     * @param The stream of the file.
     */
    void deserialize(std::fstream& in);

    /**
     * Print the trie.
     */
    void print();

    /**
     * Print all the words contained in the trie.
     */
    void printword();

    /**
     * Search all the words at max dist distance of the given word.
     *
     * @param word  The word to search for.
     * @param dist  The max distance to search for.
     *
     * @return The vector containing all the words at max dist distance.
     */
    std::vector<Search> search(std::string word, int dist);

    /**
     * Sort a Search vector.
     *
     * @param s The vector to search.
     *
     * @return The sorted vector.
     */
    std::vector<Search> sort(std::vector<Search> s);

    /**
     * Determine if a Search s1 is smaller than s2.
     * Compare first its distance, then its frequency and finally its word.
     *
     * @param s1 The first Search object.
     * @param s2 The second Search object.
     *
     * @return True if s1 is smaller than s2, false otherwise..
     */
    static bool sortVector(Search s1, Search s2);

    /**
     * Print all the words found after a search function as a JSON 
     * in the standard output.
     *
     * @param distances The Search word.
     */
    void printdist(std::vector<Search> distances);

    /**
     * Print the number of words in the trie.
     */
    int nbprint();

    /**
     * The string containing all the words (or substrings) of all the words
     * including in the trie.
     */
    std::string data_;
  private:
    /**
     * The root node.
     */
    Node root_;
};
