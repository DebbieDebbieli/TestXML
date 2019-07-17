// TestPugi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "RoXMLParser.h"
#include <codecvt>

using namespace std;

void apiTraverseXML(std::shared_ptr<CRoXMLNode> pNode)
{
	std::shared_ptr<CRoXMLNode> childNode = pNode->getFirstChild();
	while (childNode)
	{
		std::wstring wsKey = childNode->getName();
		if (childNode->hasChildNodes())
		{
			apiTraverseXML(childNode);
		}
		else
		{
			std::wstring wsValue, wsType;
			if (childNode->getAttribute(L"Value", wsValue))
			{
				//do something
			}
			else if (childNode->getAttribute(L"type", wsType))
			{
				//do something
			}
		}
		childNode = childNode->getNextSibling();
	}
}


void pugiP(const std::wstring& wsText)
{
	CRoPugiXMLParser msXML;
	clock_t beg, mid, end;
	std::cout << "********** pugi xml **********" << std::endl;
	beg = clock();
	if (msXML.parse(wsText))
	{
		mid = clock();
		std::cout << "parse t = " << (double)(mid - beg) / CLOCKS_PER_SEC << std::endl;

		std::shared_ptr<CRoXMLNode> xnode = msXML.getFirstChild();
		if (xnode)
		{
			std::wstring wsName = xnode->getName();
			std::wstring wsAttrName, wsAttrVers;
			xnode->getAttribute(L"Name", wsName);
			xnode->getAttribute(L"Version", wsAttrVers);
			apiTraverseXML(xnode);
		}
		end = clock();
		std::cout << "traversal t = " << (double)(end - beg) / CLOCKS_PER_SEC << std::endl;
	}
}

int main()
{
	std::string strFileName("Path.xml");

	std::wfstream fs;
	fs.open(strFileName, std::ios::in | ios::ate);
	std::ifstream::pos_type pos = fs.tellg();
	fs.seekg(0, std::ios::beg);
	long lsize = (long)pos;
	wchar_t* pszFile = new wchar_t[lsize];
	fs.read(pszFile, lsize);
	fs.close();

	std::wstring wsText(pszFile);

	pugiP(wsText);

	return 0;
}

