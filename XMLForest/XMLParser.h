#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class XMLParser {
private:
	std::ifstream in;
	struct Node {
		std::vector<Node*> children;
		Node* parent = nullptr;
		std::string name;
	};
	Node* root;

	enum TAG
	{
		open,
		close
	};

	const std::string tagName = "node";

public:
	XMLParser(std::string const& fileName);
	XMLParser();
	~XMLParser();

	void parse();

	void recursivePrint(Node* node);

	void printInConsole();

	void openStream(std::string fileName);

	void closeStream();

private:
	std::string getNextLine();
	Node* addNode(std::string name, Node* dest);
	void clear(Node* node);
};
