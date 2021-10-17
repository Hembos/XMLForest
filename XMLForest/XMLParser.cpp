#include "XMLParser.h"

#include <regex>

XMLParser::XMLParser(std::string const& fileName)
{
	in.open(fileName);

	if (!in.is_open())
		throw std::runtime_error("File not opened");

	root = new Node();
}

XMLParser::XMLParser()
{
	root = nullptr;
}

XMLParser::~XMLParser()
{
	in.close();
	clear(root);
}

void XMLParser::clear(Node* node)
{
	if (node == nullptr)
		return;

	for (Node* n : node->children)
	{
		clear(n);
		delete n;
	}
}

void XMLParser::parse()
{
	const std::regex rOpen("\\s*<\\s*" + tagName + "\\s* (\\w*)\\s*>\\s*");
	const std::regex rClose("\\s*<\\s*\/\s*" + tagName + "\\s*>\\s*");
	const std::regex rEmptyStr("\\s*");

	size_t numNotClosedTag = 0;

	Node* curNode = root;

	while (in)
	{
		std::string str = getNextLine();

		std::cmatch matchs;
		std::string name;
		if (std::regex_match(str.c_str(), matchs, rOpen))
		{
			name = matchs[1];
			numNotClosedTag++;
			curNode = addNode(name, curNode);
		}
		else if (std::regex_match(str, rClose))
		{
			numNotClosedTag--;
			if (numNotClosedTag >= 0)
				curNode = curNode->parent;
			else
				throw new std::runtime_error("Too many closer tags");
		}
		else if (std::regex_match(str, rEmptyStr))
		{
			continue;
		}
		else
		{
			throw new std::runtime_error("Not true tag");
		}

	}
}

void XMLParser::recursivePrint(Node* node)
{
	if (node == nullptr)
		return;

	for (const auto& n : node->children)
	{
		recursivePrint(n);
		std::cout << n->name << std::endl;
	}
}

void XMLParser::printInConsole() 
{
	recursivePrint(root);
}

void XMLParser::openStream(std::string fileName)
{
	if (!in.is_open())
		in.open(fileName);
	else
		throw new std::runtime_error("File not opened, because other open");
}

void XMLParser::closeStream()
{
	in.close();
}

std::string XMLParser::getNextLine()
{
	std::string line;
	std::getline(in, line);

	return line;
}

XMLParser::Node* XMLParser::addNode(std::string name, Node* dest)
{
	Node* newNode = new Node();

	newNode->name = name;
	newNode->parent = dest;

	dest->children.push_back(newNode);

	return newNode;
}
