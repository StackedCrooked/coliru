//#define _CRT_SECURE_NO_WARNINGS
#define TIXML_USE_STL
#include <iostream>
#include "tinyxml.h"

static inline std::string RemoveNs(std::string const& xmlName)
{
    return xmlName.substr(xmlName.find_last_of(":") + 1);
}

void  RemoveAllNamespaces(TiXmlNode* node)
{
	assert(node);

	if (auto element = node->ToElement()) {
		element->SetValue(RemoveNs(element->Value()));

		for (auto attr = element->FirstAttribute(); attr; attr = attr->Next())
			attr->SetName(RemoveNs(attr->Name()));

		for (auto child = node->IterateChildren(nullptr); child; child = element->IterateChildren(child))
			RemoveAllNamespaces(child);
	}
}

int main()
{
	const char* demoStart =
		"<?xml version=\"1.0\"  standalone='no' >\n"
		"<!-- Our: to do list data -->"
		"<a:ToDo xmlns:a=\"http://example.org/uri1\">\n"
		"<!-- Do I need: a secure PDA? -->\n"
		"<a:Item a:priority=\"1\" a:distance='close'> Go to the <bold>Toy store!</bold></a:Item>"
		"<a:Item a:priority=\"2\" a:distance='none'> Do bills   </a:Item>"
		"<a:Item a:priority=\"2\" a:distance='far &amp; back'> Look for Evil Dinosaurs! </a:Item>"
		"</a:ToDo>";

	TiXmlDocument doc;
	doc.Parse(demoStart);

	if (!doc.Error())
	{
		RemoveAllNamespaces(doc.GetDocument()->FirstChildElement());
		std::cout << doc << std::endl;
	} else
	{
		std::cout << "Error in " << doc.Value() << ": " << doc.ErrorDesc() << "\n";
	}
}
