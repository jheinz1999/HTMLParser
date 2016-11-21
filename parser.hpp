/*

Parser.hpp
By Jonathan Heinz
Last Modified: 6/10/16

*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <memory>

class HTMLObject;

class HTMLObject {

	public:

	    std::string getContent();
		std::string getType();
		bool hasAttribute(std::string attribute);
		void setType(std::string name);
		void setContent(std::string content);
		void addAttribute(std::string attribute, std::string val);
		void addChild(HTMLObject child);
		void list();
		void setParent(std::shared_ptr<HTMLObject> parent);
		std::shared_ptr<HTMLObject> getParent();
		HTMLObject findChild(HTMLObject child);

	private:

		std::map<std::string, std::string> attributes;
		std::string content, type;
		std::vector<HTMLObject> children;

		std::shared_ptr<HTMLObject> parent;

};

class HTMLParser {

	public:

		HTMLParser(std::string filePath);

		bool parse();
		void list();
	
	private:

		std::ifstream file;
		std::string filePath;

		void parseHTML();

};
