#include "stdafx.h"
//#include <atlbase.h>

#include "RoXMLParser.h"

#include <iostream>
#include <codecvt> 

class CRoPugiXMLNode : public CRoXMLNode
{
public:
	CRoPugiXMLNode(){}
	CRoPugiXMLNode(pugi::xml_node node):m_xmlNode(node){}
	~CRoPugiXMLNode()
	{}

	virtual std::wstring getName()
	{
		std::string strName = m_xmlNode.name();
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
		return convert.from_bytes(strName);
	}
	virtual bool getAttribute(const std::wstring& wsAttr, std::wstring& wsValue)
	{
		if (!m_xmlNode.empty())
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
			std::string strAttr = convert.to_bytes(wsAttr);
			std::string strValue = m_xmlNode.attribute(strAttr.c_str()).as_string();
			wsValue = convert.from_bytes(strValue);
			return true;
		}
		return false;
	}
	virtual std::shared_ptr<CRoXMLNode> getFirstChild()
	{
		std::shared_ptr<CRoXMLNode> xmlNode;
		if (!m_xmlNode.empty())
		{
			pugi::xml_node firstNode = m_xmlNode.first_child();
			if (!firstNode.empty())
			{
				xmlNode = std::make_shared<CRoPugiXMLNode>(firstNode);
			}
		}
		return xmlNode;
	}
	virtual bool hasChildNodes()
	{
		if (!m_xmlNode.empty())
		{
			return !(m_xmlNode.first_child()).empty();
		}
		return false;
	}
	virtual std::shared_ptr<CRoXMLNode> getNextSibling()
	{
		std::shared_ptr<CRoXMLNode> xmlNode;
		if (!m_xmlNode.empty())
		{
			pugi::xml_node sibling = m_xmlNode.next_sibling();
			if (!sibling.empty())
			{
				xmlNode = std::make_shared<CRoPugiXMLNode>(sibling);
			}
		}
		return xmlNode;
	}

protected:
	pugi::xml_node m_xmlNode;
};


CRoPugiXMLParser::CRoPugiXMLParser()
{

}

CRoPugiXMLParser::~CRoPugiXMLParser()
{

}

bool CRoPugiXMLParser::parse(const std::wstring& wsXmlText)
{
	if (wsXmlText.empty())
	{
		return false;
	}
	pugi::xml_parse_result result = m_doc.load_buffer(wsXmlText.c_str(), wsXmlText.size()*sizeof(wchar_t));
	//std::cout << result.description() << std::endl;
	return (result);
}

std::shared_ptr<CRoXMLNode> CRoPugiXMLParser::getFirstChild()
{
	std::shared_ptr<CRoXMLNode> xmlNode;
	if (m_doc.empty())
	{
		return xmlNode;
	}
	pugi::xml_node firstNode = m_doc.first_child();
	if (firstNode.empty())
	{
		return xmlNode;
	}
	xmlNode = std::make_shared<CRoPugiXMLNode>(firstNode);
	return xmlNode;
}
