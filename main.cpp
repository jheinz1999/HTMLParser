#include "parser.hpp"

int main(int argc, char** argv) {

	HTMLParser parser((std::string)argv[1]);

	parser.parse();

	return 0;

}
