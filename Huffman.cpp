#include<iostream>
#include<queue>
#include<map>
#include<climits>
#include<iterator>
#include<algorithm>

const int AlphabetSize = 1 <<CHAR_BIT;

typedef std::vector<bool> HuffCode;
typedef std::map<char, HuffCode> HuffCodeMap;

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
};

struct NodeCompare //compare two nodes
{
	bool operator()(const INode* node1, const INode* node2) const {return node1->f > node2->f;}
};

INode* BuildHuffmanTree(const int (&frequencies)[AlphabetSize]){
	std::priority_queue<INode*, std::vector<INode*>, NodeCompare> trees;

	for(int i=0;i < AlphabetSize;++i){
		if(frequencies[i] != 0){
			trees.push(new LeafNode(frequencies[i], (char)i ));
		}
	}
	while(trees.size()>1){
		INode* lhs  = trees.top();
		trees.pop();

		INode* rhs = trees.top();
		trees.pop();
		
		INode* parent = new InternalNode(lhs, rhs);
		trees.push(parent);
	}

	return trees.top() ;
}

void GenerateCodes(const INode* node, const HuffCode& prefix, HuffCodeMap& outCodes)
{
	if(const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
	{
		outCodes[lf->c] = prefix;
	}

	else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
	{
	
		HuffCode leftPrefix = prefix;
		leftPrefix.push_back(false);
		GenerateCodes(in->left, leftPrefix, outCodes);
		
		HuffCode rightPrefix = prefix;
		rightPrefix.push_back(true);
		GenerateCodes(in->right, rightPrefix, outCodes);
	}
}



HuffCode* HuffmanCompress(const char* string){
	std::cout<<"Huffman Compression called"<<std::endl;
	HuffCode compressedCode;  
	int frequencies[AlphabetSize] = {0};
	const char* ptr = string;
	
	while(*ptr != '\0'){
		++frequencies[*ptr++];
	}
	INode* root = BuildHuffmanTree(frequencies);

	HuffCodeMap codes; 
	GenerateCodes(root, HuffCode(), codes);
	std::cout<<codes.size()<<std::endl;
	
	delete root;
	
	for(ptr = string;*ptr != '\0'; ++ptr){
		compressedCode.insert(compressedCode.end(), codes[*ptr].begin(), codes[*ptr].end());
	}
	return &compressedCode;
}

int main(){
	std::cout<<"Test Started"<<std::endl;
	const char* s = "this is a test";
	HuffCode* code = HuffmanCompress(s);
	for(HuffCode::const_iterator i = code->begin(); i!=code->end(); ++i){
		std::cout<< "This has been called  times" <<std::endl;	
		std::cout<< *i << ' ' ;
	}
	std::cout<<"Test Ended"<<std::endl;
}
