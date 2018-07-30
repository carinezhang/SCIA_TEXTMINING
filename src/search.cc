#include "search.hh"

Search::Search(std::string w, int f, int d)
  : word_(w)
  , freq_(f)
  , dist_(d)
{}

Search::~Search()
{}

void Search::dist_set(int a)
{
  dist_ = a;
}

int Search::dist_get()
{
  return dist_;
}
