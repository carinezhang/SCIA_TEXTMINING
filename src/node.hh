#include <list>
#include <string>

class Node {
  public:
    Node();
    ~Node();
		void insert(char* word, int frequency, std::string data);
		void serialize();
	private:
		int start;
		int length;
		int frequency;
		std::list<Node> sons;
		//char padding[7];
};