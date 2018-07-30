#pragma once

#include <string>

class Search
{
  public:
    Search(std::string word, int freq, int dist);
    ~Search();
  private:
    std::string word_;
    int freq_;
    int dist_;
};
