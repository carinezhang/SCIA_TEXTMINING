#include "node.hh"

Node::Node()
{
	start_ = 0;
	length_ = 0;
	frequency_ = 0;
}

Node::Node(int start, int length, int frequency)
		: start_(start),
			length_(length),
			frequency_(frequency)
{
}

Node::~Node()
{
}

void Node::addSon(int frequency, std::string &data, std::string word)
{
	//std::cout << "add son " << word   << " "<< data.length() << std::endl;
	sons_.push_back(Node(data.length(), word.length(), frequency));
	data.append(word);
	//return node
}

void Node::insert(std::string word, int frequency, std::string &data)
{

	int wordLength = word.length();
	// int dataLength = data.size();

	for (auto it = sons_.begin(); it != sons_.end(); it++)
	{
		int start = it->start_;
		int length = it->length_;
		// same first letter
		if (data[start] == word.at(0))
		{
			int i = 0;
			//not at the end of the word, not at the end of the node, same letter at ith letter in node and word
			while (i < wordLength && i < length && data[start + i] == word.at(i))
			{
				i++;
			}
			//end of the word and end of the node
			if (i == wordLength && length == i)
			{
				it->frequency_ = frequency;
				return;
			}
			// word longer than node
			if (i >= length)
			{
				it->insert(word.substr(i), frequency, data);
				return;
			}
			//split current Node
			Node node(start + i, length - i, it->frequency_);
			it->length_ = i;
			it->frequency_ = frequency;
			node.sons_ = it->sons_;
			it->sons_.clear();
			it->sons_.push_back(node);
			if (i < wordLength)
			{
				it->frequency_ = 0;
				it->addSon(frequency, data, word.substr(i));
			}
			return;
		}
	}
	addSon(frequency, data, word);
}

void Node::serialize(std::fstream &output)
{
	output.write((char *)&start_, sizeof(start_));
	output.write((char *)&length_, sizeof(length_));
	output.write((char *)&frequency_, sizeof(frequency_));
	unsigned char nbSon = sons_.size();
	output.write((char *)&nbSon, sizeof(nbSon));
	for (auto it = sons_.begin(); it != sons_.end(); it++)
		it->serialize(output);
}

void Node::deserialize(std::istream &in)
{
	in.read((char *)&start_, sizeof(start_));
	in.read((char *)&length_, sizeof(length_));
	in.read((char *)&frequency_, sizeof(frequency_));
	unsigned char nb_sons = 0;
	in.read((char *)&nb_sons, sizeof(nb_sons));
	sons_.resize(nb_sons);
	for (unsigned char i = 0; i < nb_sons; i++)
	{
		Node new_node;
		new_node.deserialize(in);
		sons_.push_back(new_node);
	}
}

void Node::print(const std::string data)
{
	for (int i = start_; i < start_ + length_; i++)
		std::cout << data[i];

	std::cout << " " << frequency_ << std::endl;
	for (auto son : sons_)
		son.print(data);
}

int Node::nbprint()
{
	int nb = 0;
	for (auto son = sons_.begin(); son != sons_.end(); son++)
		nb += son->nbprint();
	if (frequency_ != 0)
		return nb + 1;
	return nb;
}

std::vector<Search> Node::distance(std::string &data, std::string search, int dist, int maxDist, int idx, std::string word)
{
	char c = data.at(start_ + idx);		
	std::cout << search <<" dist: " <<dist << " idx: "<< idx << " word: "<<word << " 1st letter data:"<<data[start_ + idx]<<std::endl;
	std::vector<Search> res;

	if (search.length() > 0 && c == search.at(0)) {
		if (idx < length_ - 1)
			res = distance(data, search.substr(1), dist, maxDist, idx + 1, word + c);
		else {
			for (auto son = sons_.begin(); son != sons_.end(); son++) {
				auto tmp = son->distance(data, search.substr(1), dist, maxDist, 0, word + c);
				res = merge_set(res, tmp);
			}
		}
	}

	if (dist > maxDist) {
		std::cout << "RETURN RES dist > maxDist" << dist << " " << maxDist << std::endl;
		return res;
	}
	// Noeud contenant un mot
	if (frequency_ != 0 && idx == length_ -1)
	{
		std::cout << "1if" <<std::endl;
		auto tmp_dist = c == search[0] ? 0 : 1;
		if (search != "") 
			tmp_dist += (search.length() - 1);
		if (dist + tmp_dist <= maxDist)
		{
			std::cout << "1if insert search" << std::endl;

			auto s = Search(word + c, frequency_, dist + tmp_dist);
			res.push_back(s);
		}
	}
	if (dist + 1 <= maxDist)
	{
		std::cout << "2if" <<std::endl;
		std::string searchsub = "";
		if (search.length() > 1)
			searchsub = search.substr(1);
		std::cout << "2if dist" << std::endl;

			auto res_supp =
					distance(data, searchsub, dist + 1, maxDist, idx, word);
			res = merge_set(res, res_supp);
		
		// We iterate over the word
		if (idx < length_ - 1)
		{
			if (search.length() > 1 && c == search.at(1) && search.at(0) == data[start_ + idx + 1])
			{
				auto res_transp = 
					distance(data, searchsub, dist, maxDist, idx + 1, word + c );
				res = merge_set(res, res_transp);
			}
			std::cout << "IDX != max length" << std::endl;
			// if (search.length() > 0)// && search())
			std::cout << "IDX != max length subs" << std::endl;
			std::cout << search <<"idx " << idx << "length" << length_ << std::endl;
			auto res_subs =
					distance(data, searchsub, dist + 1, maxDist, idx + 1, word + c);
			res = merge_set(res, res_subs);
			std::cout << "IDX != max length insert" << std::endl;

			auto res_insert =
					distance(data, search, dist + 1, maxDist, idx + 1, word + c);
			res = merge_set(res, res_insert);
		}
		else
		{
			std::cout << "IDX == max length" << std::endl;

			// for loop with all the sons
			for (auto son = sons_.begin(); son != sons_.end(); son++)
			{
				if (search.length() > 1 && c == search.at(1) && search.at(0) == data[son->start_])
				{
					auto res_transp = 
						son->distance(data, searchsub, dist, maxDist, 0, word + c );
					res = merge_set(res, res_transp);
				}
				int mdist = 1;
				if (search.length() > 0 && data[son->start_] == search.at(0))
					mdist = 0;
				std::cout << "IDX == max length subs" << std::endl;
				std::cout << search << " " <<c<< std::endl;

				auto res_subs =
						son->distance(data, searchsub, dist + 1, maxDist, 0, word + c);
				res = merge_set(res, res_subs);
				std::cout << "IDX == max length insert" << std::endl;

				auto res_insert =
						son->distance(data, search, dist + 1, maxDist, 0, word + c);
				res = merge_set(res, res_insert);
			}
		}
	}
	return res;
}

std::vector<Search> Node::merge_set(std::vector<Search> s1, std::vector<Search> s2)
{
	for (auto s: s2) {
		bool b = false;
		for (auto tmp: s1) {
			if (tmp.word_ == s.word_) {
				if (tmp.dist_ > s.dist_) {
					tmp.dist_ = s.dist_; 
				}
				b = true;
				break;
			}
		}
		if (!b)
			s1.push_back(s);
	}
	return s1;
}

void Node::printword(std::string& data, std::string begin){
	for (int i = 0; i < length_; i++) {
		begin +=data[start_ + i];
	}
	
	if (frequency_ != 0) {
		std::cout << begin << std::endl;
	}
	for (auto son = sons_.begin(); son != sons_.end(); son++) {
		son->printword(data, begin);
	}
}


std::list<Node> Node::get_sons(){
	return sons_;
}