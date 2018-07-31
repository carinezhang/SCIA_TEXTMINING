#pragma once

#include <string>

class Search
{
  public:
    Search(std::string word, int freq, int dist);
    ~Search();
    void dist_set(int a);
    int dist_get();
    std::string word_;
    int freq_;
    mutable int dist_;
};

inline bool operator< (const Search &left, const Search &right)
{
  return left.word_ < right.word_;
}
