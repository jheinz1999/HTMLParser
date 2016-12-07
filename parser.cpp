/*

parser.cpp
by Jonathan Heinz
Last Modified: 6/10/16

*/

#include <iostream>
#include <cstdlib>
#include <locale>
#include <memory>
#include <stack>

#include "parser.hpp"

HTMLParser::HTMLParser(std::string filePath) {

	file.open(filePath.c_str());

	if (file.fail()) {

		std::cout << "Failed to open file. Perhaps the file is nonexistent?\n";
		exit(0);

	}

	file.close();

	this->filePath = filePath;

}

bool HTMLParser::parse() {

	file.open(filePath.c_str());

	char input;

	bool tagEnded = 0, firstPass = 1, comment = 0;

	std::string object, data, parentName;

	std::shared_ptr<HTMLObject> html, top;

	html = std::make_shared<HTMLObject>();
	html->setType("html");

	top = std::make_shared<HTMLObject>();
	top->setType("top");

	tree = html;
	
	tree->setParent(top);

	std::stack<std::shared_ptr<HTMLObject>> closingTags;

	while (file.get(input)) {
	
		std::shared_ptr<HTMLObject> parent(new HTMLObject);	
		std::shared_ptr<HTMLObject> htmlItem(new HTMLObject);

		//if (closingTags.size() > 0)
			//std::cout << "AAATOP: " << closingTags.top().getType() << "\nSIZE: " << closingTags.size() << std::endl;

		if (input == '<') {

			if (!tagEnded && !firstPass) {

				//parent = htmlItem;
				//parent->setType(htmlItem->getType());
	
			}

			else if (firstPass == 0) {

				tagEnded = 0;

			}

			else 
				firstPass = 0;

			object = std::string();

			while (1) {
				
				if (comment)
					comment = 0;

				file.get(input);
				
				int pos = file.tellg();

				if (input == '>') {
				
					break;

				}

				if (input == '/') {

					file.get(input);

					if (input == closingTags.top()->getType()[0]) {

						tagEnded = 1;
						closingTags.pop();

					}

					else {

						file.seekg(pos);
						std::cout << "not found\n";
						std::cout << closingTags.top()->getParent()->getType()[0] << "\n" << input << "\n"; 

					}

				}
				
				if (input == '!') {
					
					std::cout << "FOUND A COMMENT\n";
					
					file.get(input);
					
					if (input == '-') {
						
						file.get(input);
						
						std::cout << "dash\n";
						
						if (input == '-') {
							
							std::cout << "dash2\n\n";
							
							file.get(input);
								
							while (input != '<') {
								
								file.get(input);
								
							}
							
							comment = 1;
							tagEnded = 0;
							pos = file.tellg();

						}
						
					}
					
					file.seekg(pos);
					
				}

				if (!comment)
					object += input;
	
			}

			std::locale loc;

			std::string obj = object;

			if (!tagEnded) {

				htmlItem->setType(object);	

				if (closingTags.size() > 1) {

					parent->setType(closingTags.top()->getType());
					parent->setParent(closingTags.top()->getParent());

				}

				else {

					parent->setType(html->getType());
					parent->setParent(html);

				}

				htmlItem->setParent(parent);
				closingTags.push(htmlItem);

				if (htmlItem->getParent()->getType() == "html")
					tree->addChild(htmlItem);	

				else if (htmlItem->getType() != "html") {

					//std::cout << "NEW HTML CALLED " << htmlItem->getType() << ", LOOKING FOR PARENT " << htmlItem->getParent()->getType() << std::endl;
					tree->findChild(htmlItem->getParent(), 0, top->getTagCount(htmlItem->getParent()->getType()))->addChild(htmlItem);

				}

			}

			else if (tagEnded && object == "html") {

				tree->list(0);
				
				std::shared_ptr<HTMLObject> top = tree->getParent();

				while (top->getType() != "top")
					top = top->getParent();

				std::map<std::string, int>::iterator it = top->numTags.begin();

				while (it != top->numTags.end()) {

					std::cout << "Number of " << it->first << ": " << top->numTags[it->first] << "\n";

				it++;

				}

				return 1; 

			}

		}

	}

}

std::string HTMLObject::getContent() {

	return content;

}

std::string HTMLObject::getType() {

	return type;

}

bool HTMLObject::hasAttribute(std::string attribute) {

	std::map<std::string, std::string>::iterator it;

	it = attributes.find(attribute);

	if (it != attributes.end())
		return true;

	else
		return false;

}

void HTMLObject::setType(std::string type) {

	this->type = type;

}

void HTMLObject::setContent(std::string content) {

	this->content = content;

}

void HTMLObject::addAttribute(std::string attribute, std::string val) {

	attributes.insert(std::pair<std::string, std::string>(attribute, val));

}

void HTMLObject::addChild(std::shared_ptr<HTMLObject> child) {

	children.push_back(child);
	
	std::shared_ptr<HTMLObject> top = child->getParent();

	while (top->getType() != "top")
		top = top->getParent();


	if (top->tagExists(child->getType())) {

		std::cout << "incrementing tag of type " << child->getType() << "\n";
		top->incrementTagCount(child->getType());

	}

	else {

		std::cout << "first tag of type " << child->getType() << "\n";
		top->addTag(child->getType());

	}

}

void HTMLObject::setParent(std::shared_ptr<HTMLObject> parent) {

	this->parent = parent;

}

std::shared_ptr<HTMLObject> HTMLObject::getParent() {

	return parent;

}

void HTMLObject::list(int tabCount) {

	tabCount++;

	std::cout << "\n";

	for (std::shared_ptr<HTMLObject> o : children) {

		for (int i = 0; i < tabCount; i++)
		std::cout << "    ";

		std::cout << o->getType();
		std::cout << "\n";
		o->list(tabCount);

	}

	tabCount--;

}

std::shared_ptr<HTMLObject> HTMLObject::findChild(std::shared_ptr<HTMLObject> child, int numFound, int numLookingFor) {

	//std::cout << "I'm looking for " << child->getType() << " inside " << this->type << std::endl;

	std::shared_ptr<HTMLObject> found;

	for (std::shared_ptr<HTMLObject> o : children) {

		//std::cout << "looking...\n";
		//std::cout << "found is " << numFound << std::endl;

		if (o->getType() == child->getType()) {

			numFound++;
			//std::cout << "found # " << numFound << "/" << numLookingFor << std::endl;
			if (numFound == numLookingFor) {
				found = o;
				return found;
			}

		}

		//std::cout << "found is " << numFound << std::endl;

		found = o->findChild(child, numFound, numLookingFor);

	}

	return found;

}

bool HTMLObject::tagExists(std::string tag) {

	std::map<std::string, int>::iterator it;

	it = numTags.find(tag);

	if (it != numTags.end())
		return true;

	else
		return false;	

}

void HTMLObject::addTag(std::string tag) {

	numTags.insert(std::pair<std::string, int>(tag, 1));

}

void HTMLObject::incrementTagCount(std::string tag) {

	numTags[tag]++;

}

int HTMLObject::getTagCount(std::string tag) {

	return numTags[tag];

}

void HTMLParser::list() {

	

}
