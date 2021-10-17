#include "XMLParser.h"

int main()
{
	XMLParser xml("text.txt");

	xml.parse();

	xml.printInConsole();

	xml.closeStream();

	return 0;
}