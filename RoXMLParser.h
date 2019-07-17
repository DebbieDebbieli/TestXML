#pragma once

#include <memory>
#include "pugixml-1.9/src/pugixml.hpp"

class CRoXMLNode
{
public:
	virtual std::wstring getName() = 0;
	virtual bool getAttribute(const std::wstring& wsAttr, std::wstring& wsValue) = 0;
	virtual std::shared_ptr<CRoXMLNode> getFirstChild() = 0;
	virtual bool hasChildNodes() = 0;
	virtual std::shared_ptr<CRoXMLNode> getNextSibling() = 0;
	
protected:
	CRoXMLNode() {}
	virtual ~CRoXMLNode() {}
};

class CRoXMLParser
{
public:
	virtual bool parse(const std::wstring& wsXmlText) = 0;
	virtual std::shared_ptr<CRoXMLNode> getFirstChild() = 0;

protected:
	CRoXMLParser() {};
	virtual ~CRoXMLParser() {};
};
                
class CRoPugiXMLParser : public CRoXMLParser
{
public:
	CRoPugiXMLParser();
	~CRoPugiXMLParser();

	virtual bool parse(const std::wstring& wsXmlText);
	virtual std::shared_ptr<CRoXMLNode> getFirstChild();

protected:
	pugi::xml_document m_doc;
};
