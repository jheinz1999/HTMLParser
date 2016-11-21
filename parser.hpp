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
		void addChild(std::shared_ptr<HTMLObject> child);
		void list(int tabCount);
		void setParent(std::shared_ptr<HTMLObject> parent);
		std::shared_ptr<HTMLObject> getParent();
		std::shared_ptr<HTMLObject> findChild(std::shared_ptr<HTMLObject> child, int numFound, int numLookingFor);
		bool tagExists(std::string tag);
		void addTag(std::string tag);
		void incrementTagCount(std::string tag);
		int getTagCount(std::string tag);
		std::map<std::string, int> numTags;

	private:

		std::map<std::string, std::string> attributes;
		std::string content, type;
		std::vector<std::shared_ptr<HTMLObject>> children;

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

		std::shared_ptr<HTMLObject> tree;

		void parseHTML();

};
