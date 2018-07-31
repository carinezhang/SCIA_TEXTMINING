#pragma once

#include <string>

/**
 * @file
 * @author drapal_g zhang_d
 *
 * @section DESCRIPTION
 *
 * The Node class represent a node of a Patricia-Trie containing in Trie class.
 * The Search class is the result of a call to the Trie's search function.
 * It contains all the words, their distances and frequency. 
 *
 */

class Search
{
  public:
    /**
     * Constructor with all the attributes.
     *
     * @param word  The word.
     * @param freq  The frequency of the word.
     * @param dist  The distance of this word to the word searched.
     */
    Search(std::string word, int freq, int dist);

    /**
     * Default destructor.
     */
    ~Search();

    /**
     * Setter for the dist attribute.
     */
    void dist_set(int a);

    /**
     * Getter for the dist attribute.
     */
    int dist_get();

    /**
     * The word.
     */
    std::string word_;

    /**
     * The frequency of the word.
     */
    int freq_;

    /**
     * The distance of this word to the searched word in the Trie's search function.
     */
    mutable int dist_;
};

/**
 * Operator < for Search objects.
 *
 * @param left  A search object.
 * @param right A search object.
 */
inline bool operator< (const Search &left, const Search &right)
{
  return left.word_ < right.word_;
}
