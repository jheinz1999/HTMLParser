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

	bool tagEnded = 0, firstPass = 1;

	std::string object, data, parentName;

	std::shared_ptr<HTMLObject> html, htmlItem, tree;

	html = std::make_shared<HTMLObject>();			
	htmlItem = std::make_shared<HTMLObject>();

	tree = html;

	html->setType("html");
	html->setParent(html);

	std::stack<HTMLObject> closingTags;

	while (file.get(input)) {
	
	HTMLObject parent;

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

				file.get(input);

				if (input == '>') {
				
					break;

				}

				if (input == '/') {

					file.get(input);

					int pos = file.tellg();

					if (input == closingTags.top().getType()[0]) {

						tagEnded = 1;
						std::cout << "Tag ended\n";
						closingTags.pop();

					}

					else {

						file.seekg(pos);
						std::cout << "not found\n";
						std::cout << closingTags.top().getParent()->getType()[0] << "\n" << input << "\n"; 

					}

				}

				object += input;

			}

			std::locale loc;

			std::string obj = object;

			if (!tagEnded) {

				htmlItem->setType(object);

				if (closingTags.size() > 1) {

					parent.setType(closingTags.top().getType());
					parent.setParent(closingTags.top().getParent());

				}

				else {

					parent.setType(html->getType());
					parent.setParent(html);

				}

				htmlItem->setParent(std::make_shared<HTMLObject>(parent));

				std::cout << "new HTMLObject called " << htmlItem->getType() << " with parent " << htmlItem->getParent()->getType() << std::endl;
				closingTags.push(*htmlItem);
				htmlItem->getParent()->addChild(*htmlItem);	

				if (htmlItem->getParent()->getType() == "html")	
					tree->addChild(*htmlItem);	

				else
					tree->findChild(*htmlItem->getParent()).addChild(*htmlItem);


			}

			else if (tagEnded && object == "html") {

				//tree->list();
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

void HTMLObject::addChild(HTMLObject child) {

	children.push_back(child);

}

void HTMLObject::setParent(std::shared_ptr<HTMLObject> parent) {

	this->parent = parent;

}

std::shared_ptr<HTMLObject> HTMLObject::getParent() {

	return parent;

}

void HTMLObject::list() {

	std::cout << this->type << "\n";

	for (HTMLObject o : children) {

		std::cout << o.getType() << std::endl;
		o.list();

	}

}

HTMLObject HTMLObject::findChild(HTMLObject child) {

	for (HTMLObject o : children) {

		if (o.getType() == child.getType()) {

			std::cout << "found " << o.getType() << std::endl;
			return o;

		}

	}

	HTMLObject error;
	error.setType("error");

	return error;

}

void HTMLParser::list() {

	

}
