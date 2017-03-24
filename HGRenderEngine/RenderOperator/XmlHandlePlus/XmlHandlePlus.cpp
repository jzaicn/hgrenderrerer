#include "XmlHandlePlus.h"

#include <vector>
#include <string>
#include <algorithm>
// 
// #ifndef XmlHandlePlus_TestProject
// #define TINY_HEADING TinyXml::
// namespace TinyXml{
// #else
// #define TINY_HEADING 
// #pragma comment(lib,"tinyxmlSTL.lib")
// #endif

	//	ԭHandle
#if 1


XmlHandlePlus XmlHandlePlus::FirstChild() const
{
	if ( good(node) )
	{
		TiXmlNode* child = node->FirstChild();
		if ( child )
			return XmlHandlePlus( child );
	}
	return XmlHandlePlus( 0 );
}


XmlHandlePlus XmlHandlePlus::FirstChild( const char * value ) const
{
	if ( good(node) )
	{
		TiXmlNode* child = node->FirstChild( value );
		if ( child )
			return XmlHandlePlus( child );
	}
	return XmlHandlePlus( 0 );
}


XmlHandlePlus XmlHandlePlus::FirstChildElement() const
{
	if ( good(node) )
	{
		TiXmlElement* child = node->FirstChildElement();
		if ( child )
			return XmlHandlePlus( child );
	}
	return XmlHandlePlus( 0 );
}


XmlHandlePlus XmlHandlePlus::FirstChildElement( const char * value ) const
{
	if ( good(node) )
	{
		TiXmlElement* child = node->FirstChildElement( value );
		if ( child )
			return XmlHandlePlus( child );
	}
	return XmlHandlePlus( 0 );
}


XmlHandlePlus XmlHandlePlus::Child( int count ) const
{
	if ( good(node) )
	{
		int i;
		TiXmlNode* child = node->FirstChild();
		for (	i=0;
			child && i<count;
			child = child->NextSibling(), ++i )
		{
			// nothing
		}
		if ( child )
			return XmlHandlePlus( child );
	}
	return XmlHandlePlus( 0 );
}


XmlHandlePlus XmlHandlePlus::Child( const char* value, int count ) const
{
	if (good(node) )
	{
		int i;
		TiXmlNode* child = node->FirstChild( value );
		for (	i=0;
			child && i<count;
			child = child->NextSibling( value ), ++i )
		{
			// nothing
		}
		if ( child )
			return XmlHandlePlus( child );
	}
	return XmlHandlePlus( 0 );
}


XmlHandlePlus XmlHandlePlus::ChildElement( int count ) const
{
	if ( good(node) )
	{
		int i;
		TiXmlElement* child = node->FirstChildElement();
		for (	i=0;
			child && i<count;
			child = child->NextSiblingElement(), ++i )
		{
			// nothing
		}
		if ( child )
			return XmlHandlePlus( child );
	}
	return XmlHandlePlus( 0 );
}


XmlHandlePlus XmlHandlePlus::ChildElement( const char* value, int count ) const
{
	if ( good(node) )
	{
		int i;
		TiXmlElement* child = node->FirstChildElement( value );
		for (	i=0;
			child && i<count;
			child = child->NextSiblingElement( value ), ++i )
		{
			// nothing
		}
		if ( child )
			return XmlHandlePlus( child );
	}
	return XmlHandlePlus( 0 );
}

#endif






	//	XmlHandlePlus
#if 1

//�����·����Ҫ��"/"б�ָܷ�
//������õı����ַ��У�"/"��Ŀ¼��"."��ǰĿ¼��".."��һ��Ŀ¼
//�Լ�һ���Ӣ��������ϴ����л�����Ŀ¼��������ֵĽڵ���
//����������·������������ո񡢷�������ⲻ�����ʹ��"."
//���һ���ڵ���Ҫ�ⲿ�����ж��������ڶ��ͬ���ڵ��н���ɸѡ
void XmlHandlePlus::changeDirectoryTo(const std::string& pathname,IXmlHandlePlusCompare& compareObj)
{
	std::vector<TiXmlNode*> arr = findAll(pathname,compareObj);
	if (arr.size()>0)
	{
		node = arr[0];
	}
	else
	{
		node = NULL;
	}
}


//�������з��������Ľڵ㷵�ص�����֮��
std::vector<TiXmlNode*> XmlHandlePlus::findAll(const std::string& pathname,IXmlHandlePlusCompare& compareObj)
{
	std::vector<TiXmlNode*> resultNode;

	if(good() == false) return resultNode;

	std::string path = pathname;

	//�滻б���ַ�
	replace(path.begin(),path.end(),'\\','/');

	//·������
	std::vector<std::string> pathList = createPathlistFromPath(path);


	//ѭ������ÿһ��Ԫ��
	TiXmlNode* tempNode = node;
	for (size_t i = 0 ; i< pathList.size() ; i++)
	{
		if (good(tempNode))
		{
			if (pathList.at(i).compare("/") == 0)
			{
				tempNode = getRoot(tempNode);
			}
			else if (pathList.at(i).compare("..") == 0)
			{
				tempNode = tempNode->Parent();
			}
			else if (pathList.at(i).compare(".") == 0)
			{
				tempNode = tempNode;
			}
			else if ( i == pathList.size() -1)	//���һ��Ԫ��
			{
				//��������������ֵĶ����ܵ����Ѱ��ͬ���Ľڵ�Ȼ�󷵻�
				tempNode = tempNode->FirstChild(pathList.at(i));
				resultNode = getSameNameBotherNode(tempNode,pathList.at(i),compareObj,false);
				return resultNode;
			}
			else
			{
				tempNode = tempNode->FirstChild(pathList.at(i));
			}
		}
	}
	//��������£������Ŀ¼�ǲ��������ַ������Բ���ȥ�������һ��Ԫ���ǲ���
	if (tempNode)
	{
		resultNode.push_back(tempNode);
	}
	return resultNode;

}

//����⼶�ڵ�����ͬ�����ܱȽϺ���ȷ�ϵĽڵ��б�
std::vector<TiXmlNode*> XmlHandlePlus::getSameNameBotherNode(TiXmlNode* curElem,std::string& nodeName,IXmlHandlePlusCompare& compareObj,bool firstBreak)
{
	std::vector<TiXmlNode*> elements;
	if (good(curElem))
	{
		XmlNodeNameCompare nodeNameCompare(nodeName);
		for( auto child = curElem; child; child = child->NextSibling() )
		{
			if (nodeNameCompare.compare(child))
			{
				if (compareObj.compare(child))
				{
					elements.push_back(child);
					if (firstBreak)
					{
						break;
					}
				}
			}
		}
	}
	return elements;
}

//Ĭ�ϱȽϺ������������ж�Ϊ��
bool XmlHandlePlus::defaultCompare(TiXmlNode* node)
{
	return true;
}

//Ĭ�ϱȽ϶���
IXmlHandlePlusCompare& XmlHandlePlus::defaultCompareObj = XmlOuterFunctionCompare(XmlHandlePlus::defaultCompare);

//////////////////////////////////////////////////////////////////////////
//�ڵ����

//���ýڵ�����ֵ
void XmlHandlePlus::setAttr(std::string name,std::string value)
{
	if (good())
	{
		if (node->ToElement())
		{
			node->ToElement()->SetAttribute(name,value);
		}
	}
}

//��ȡ�ڵ�����ֵ��������ֵ������ʱ����Ĭ������
std::string XmlHandlePlus::getAttr(std::string name , std::string defaultValue )
{
	if (good())
	{
		if (node->ToElement())
		{
			if (node->ToElement()->Attribute(name))
			{
				const std::string* result = node->ToElement()->Attribute(name);
				if (result)
				{
					return *result;
				}
			}
		}
	}
	return defaultValue;
}

//����Param�ڵ������ṹ����{|Name|}��ʾName��{|Value|}��ʾValue
void XmlHandlePlus::setParamElementName(std::string paramName)
{
	m_ParamName = paramName;
}

//���ڵ�ǰ·����ͬ���ӽڵ�������nameƥ�������
void XmlHandlePlus::setParam(std::string name, std::string value ,
	std::string nameOfAttr,
	void (*setName)(TiXmlElement*,std::string value) ,
	void (*setValue)(TiXmlElement*,std::string value) )
{
	if (good())
	{
		//Ŀ¼�����л�һ��
		std::vector<TiXmlNode*> elements = findAll(m_ParamName,XmlAttrValueCompare(nameOfAttr,name));
		for(int i = 0;i<elements.size();i++)
		{
			if (setValue)
			{
				setValue(elements.at(i)->ToElement(),value);
				return;
			}
		}

		//���нڵ㶼û�����Ԫ��,����һ������ӵ�����
		TiXmlElement newElement( m_ParamName );
		if (setName)
		{
			setName(&newElement,name);
		}
		if (setValue)
		{
			setValue(&newElement,value);
		}
		node->InsertEndChild(newElement);
	}
	return;
}

//��ȡ�����ڵ�����
std::string XmlHandlePlus::getParam(std::string name, std::string defaultValue , 
	std::string (*findElement)(TiXmlElement*) ,
	std::string (*getValue)(TiXmlElement*) )
{
	if (good())
	{
		for(TiXmlNode* child = node->FirstChild(); child; child = child->NextSibling() )
		{
			TiXmlElement* element = child->ToElement();
			if (findElement)
			{
				if (findElement(element).compare(name) == 0)
				{
					if (getValue)
					{
						return getValue(element);
					}
				}
			}
		}
	}
	return defaultValue;
}

//��ȡԪ��Name����ֵ
//FIXME: ��ʱ���滻�ɶ�����ʽ
std::string XmlHandlePlus::getElementName(TiXmlElement* element)
{
	if (element && element->Attribute(std::string("Name")))
	{
		return *element->Attribute(std::string("Name"));
	}
	return std::string("");
}

//����Ԫ��Name����ֵ
//FIXME: ��ʱ���滻�ɶ�����ʽ
void XmlHandlePlus::setElementName(TiXmlElement* element, std::string value)
{
	if (element)
	{
		element->SetAttribute(std::string("Name"),value);
	}
}

//��ȡԪ��Value����ֵ
//FIXME: ��ʱ���滻�ɶ�����ʽ
std::string XmlHandlePlus::getElementValue(TiXmlElement* element)
{
	if (element && element->Attribute(std::string("Value")))
	{
		return *element->Attribute(std::string("Value"));
	}
	return std::string("");
}

//����Ԫ��Value����ֵ
//FIXME: ��ʱ���滻�ɶ�����ʽ
void XmlHandlePlus::setElementValue(TiXmlElement* element, std::string value)
{
	if (element)
	{
		element->SetAttribute(std::string("Value"),value);
	}
}

//////////////////////////////////////////////////////////////////////////
//�ڵ����

//���Լ������ж�Ӧ��λ���Ƴ�,���ѽڵ��л������״�
void XmlHandlePlus::remove()
{
	if (good())
	{
		if (good(node->Parent()))
		{
			TiXmlNode* parent = node->Parent();
			parent->RemoveChild(node);
			node = parent;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//���ߺ���

//�ӵ�ǰ�ڵ㷵��Root�ڵ�
TiXmlNode* XmlHandlePlus::getRoot(TiXmlNode* node)
{
	if (good(node))
	{
		TiXmlNode* root = node->GetDocument();
// 		TiXmlNode* temp = node;
// 		while (temp->Parent())
// 		{
// 			root = temp->Parent();
// 			temp = temp->Parent();
// 		}
// 		TiXmlDocument* doc = root->doc;
//		return doc->RootElement();
		return root;
	}
	return NULL;
}

//���ص�ǰ�ڵ㵽Root�ڵ�֮���·��������·����
std::string XmlHandlePlus::getPWD(TiXmlNode* node)
{
	if (good(node))
	{
		std::string fullpath = "/";
		TiXmlNode* root = node;
		TiXmlNode* temp = node;
		while (temp->Parent())
		{
			fullpath = "/" + temp->ValueStr() + fullpath;

			root = temp->Parent();
			temp = temp->Parent();


		}
		return fullpath;
	}
	return "";
}

//·��Ԥ�������".."·��\"."·��\"/"
std::vector<std::string> XmlHandlePlus::createPathlistFromPath( std::string path )
{
	//����path����/ת����list
	std::vector<std::string> pathList;
	split(path,"/",pathList);

	std::vector<std::string> tempList;
	if (path.size() > 0)
	{
		//��һ���ڵ��ǡ�/��
		if (path.at(0) == '/')
		{
			tempList.push_back("/");
		}

		//ѭ������ÿһ����..����.��
		for (size_t i = 0; i<pathList.size() ; i++)
		{
			std::string temp = pathList.at(i);
			if (temp.compare("") == 0)//û����Ϣ
			{
				if (tempList.empty())
				{
					tempList.push_back(".");
				}
			}
			else if (temp.compare(" ") == 0)//û����Ϣ
			{
				if (tempList.empty())
				{
					tempList.push_back(".");
				}
			}
			else if(temp.compare(".") == 0)//�л�����ǰ·����������Ӧ
			{
				if (tempList.empty())
				{
					tempList.push_back(".");
				}
			}
			else if (temp.compare("..") == 0)//�л����������������ǰ�滹�н���ĳ��Ŀ¼�����͵�����
			{
				if (!tempList.empty())
				{
					tempList.pop_back();
				}
				else
				{
					tempList.push_back("..");
				}
			}
			else//һ�����
			{
				tempList.push_back(temp);
			}
		}
	}
	else
	{
		tempList.push_back(".");
	}

	return tempList;
}

//���ַ����ָ���ַ�������
void XmlHandlePlus::split(const std::string& s,const std::string& delim,std::vector< std::string >& ret)  
{  
	size_t last = 0;  
	size_t index=s.find_first_of(delim,last);  
	while (index!=std::string::npos)  
	{  
		ret.push_back(s.substr(last,index-last));  
		last=index+1;  
		index=s.find_first_of(delim,last);  
	}  
	if (index-last>0)  
	{  
		ret.push_back(s.substr(last,index-last));  
	}  
} 

//·���л���
TiXmlNode* XmlHandlePlus::changeDirectoryByPath( TiXmlNode* node ,std::string &path)
{
	//�л�����Ŀ¼
	TiXmlNode* curElem = node;
	if (path.size() > 0)
	{
		if (path.at(0) == '/')
		{
			curElem = getRoot(node);
		}

		std::vector<std::string> pathList = createPathlistFromPath(path);



	}
	return curElem;
}


//�жϽڵ��Ƿ�Ϊ��
bool XmlHandlePlus::good(TiXmlNode* node)
{
	if (!node || (node->ToDocument() && node->ToDocument()->Error()))
	{
		return false;
	}
	return true;
}

#endif

#ifndef XmlHandlePlus_TestProject
}
#endif

