#include<iostream>
#include<queue>
#include<map>
#include<climits>
#include<iterator>
#include<algorithm>

const int AlphabetSize = 1 <<CHAR_BIT;

typdef std::vector<bool> HuffCode;
typdef std::map<char, HuffCode> HuffMap;

class INode
{
	public:
		const int f;
		virtual ~INode(){}
	protected:
		INode(int f): f(f){}
}; //generic node class that carried the cumulative frequencies of all nodes to the left and right (f)

class InternalNode : public INode //Internal node that connects either leaf nodes or other internal nodes
{
	public:
		INode *const left;
		INode *const right;

		InternalNode(INode* c0, INode* c1): INode(c0->f + c1->f), left(c0), right(c1){}
		
		~InternalNode(){ 
			delete left;
			delete right;
		}
};

class LeafNode : public INode//Leaf class that also contains a character
{
	public:
		const char c;

		LeafNode(char c, int f) : INode(f) , c(c){}

		~LeafNode(){
			delete c;
		}
};

struct NodeCompare //compare two nodes
{
	bool operator()(const INode* node1, const INode* node2) const {return node1->f > node2->f;}
};

*INode BuildHuffmanTree(const int (&frequencies)[AlphabetSize]){
	std::priority_queue<INode*, std::vector<INode*>, NodeCompare> trees;

	for(int i=0;i < AlphabetSize;++i){
		if(frequencies[i] != 0)
			trees.push(new LeafNode(frequencies[i], (char)i ));
	}

	while(trees.size()>1)
}

int main(){
	:x

}


