#pragma once


#include <string>
#include <list>
#include <vector>

#define XmlHandlePlus_TestProject
#ifndef XmlHandlePlus_TestProject
#include "tinyxml.h"
namespace TinyXml{
#else
#include "tinyxml.h"
#endif

class IXmlHandlePlusCompare
{
public:
	virtual bool compare(TiXmlNode* element) = 0;
};


typedef bool (*FuncCompare)(TiXmlNode*);
class XmlOuterFunctionCompare;
class XmlHandlePlus
{
	/************************************************************************/
	/* ������TiXmlHandle                                                                     */
	/************************************************************************/
#if 1
public:

	XmlHandlePlus operator=( const XmlHandlePlus& ref ) { if ( &ref != this ) this->node = ref.node; return *this; }

	/// Return a handle to the first child node.
	XmlHandlePlus FirstChild() const;
	/// Return a handle to the first child node with the given name.
	XmlHandlePlus FirstChild( const char * value ) const;
	/// Return a handle to the first child element.
	XmlHandlePlus FirstChildElement() const;
	/// Return a handle to the first child element with the given name.
	XmlHandlePlus FirstChildElement( const char * value ) const;

	/** Return a handle to the "index" child with the given name. 
		The first child is 0, the second 1, etc.
	*/
	XmlHandlePlus Child( const char* value, int index ) const;
	/** Return a handle to the "index" child. 
		The first child is 0, the second 1, etc.
	*/
	XmlHandlePlus Child( int index ) const;
	/** Return a handle to the "index" child element with the given name. 
		The first child element is 0, the second 1, etc. Note that only TiXmlElements
		are indexed: other types are not counted.
	*/
	XmlHandlePlus ChildElement( const char* value, int index ) const;
	/** Return a handle to the "index" child element. 
		The first child element is 0, the second 1, etc. Note that only TiXmlElements
		are indexed: other types are not counted.
	*/
	XmlHandlePlus ChildElement( int index ) const;

	#ifdef TIXML_USE_STL
	XmlHandlePlus FirstChild( const std::string& _value ) const				{ return FirstChild( _value.c_str() ); }
	XmlHandlePlus FirstChildElement( const std::string& _value ) const		{ return FirstChildElement( _value.c_str() ); }

	XmlHandlePlus Child( const std::string& _value, int index ) const			{ return Child( _value.c_str(), index ); }
	XmlHandlePlus ChildElement( const std::string& _value, int index ) const	{ return ChildElement( _value.c_str(), index ); }
	#endif

	/** Return the handle as a TiXmlNode. This may return null.
	*/
	TiXmlNode* ToNode() const			{ return node; } 
	/** Return the handle as a TiXmlElement. This may return null.
	*/
	TiXmlElement* ToElement() const		{ return ( ( node && node->ToElement() ) ? node->ToElement() : 0 ); }
	/**	Return the handle as a TiXmlText. This may return null.
	*/
	TiXmlText* ToText() const			{ return ( ( node && node->ToText() ) ? node->ToText() : 0 ); }
	/** Return the handle as a TiXmlUnknown. This may return null.
	*/
	TiXmlUnknown* ToUnknown() const		{ return ( ( node && node->ToUnknown() ) ? node->ToUnknown() : 0 ); }

	/** @deprecated use ToNode. 
		Return the handle as a TiXmlNode. This may return null.
	*/
	TiXmlNode* Node() const			{ return ToNode(); } 
	/** @deprecated use ToElement. 
		Return the handle as a TiXmlElement. This may return null.
	*/
	TiXmlElement* Element() const	{ return ToElement(); }
	/**	@deprecated use ToText()
		Return the handle as a TiXmlText. This may return null.
	*/
	TiXmlText* Text() const			{ return ToText(); }
	/** @deprecated use ToUnknown()
		Return the handle as a TiXmlUnknown. This may return null.
	*/
	TiXmlUnknown* Unknown() const	{ return ToUnknown(); }

private:
	TiXmlNode* node;
#endif


	/************************************************************************/
	/* �Լ���ʵ��                                                                     */
	/************************************************************************/
#if 1
public:
	/// �ӽڵ㴴���������.
	XmlHandlePlus(TiXmlNode& _rnode) {
		TiXmlNode* _node = &_rnode;
		if (_node->ToDocument())
		{
			if (_node->ToDocument()->Error())
			{
				node = NULL;
			}
		}
		m_ParamName = "Param";
		node = _node;
	}

	/// �ӽڵ㴴���������.
	XmlHandlePlus(TiXmlNode* _node) {
		if (_node != NULL)
		{
			if (_node->ToDocument())
			{
				if (_node->ToDocument()->Error())
				{
					node = NULL;
				}
			}
		}
		m_ParamName = "Param";
		node = _node;
	}
	/// �������캯��
	XmlHandlePlus(const XmlHandlePlus& refr , std::string path = "/") {
		m_ParamName = "Param";
		node = refr.node;
	}

	/// ��������
	~XmlHandlePlus() {}




	//////////////////////////////////////////////////////////////////////////
	//�ڵ�������
public:
	//�����·����Ҫ��"/"б�ָܷ�
	//������õı����ַ��У�"/"��Ŀ¼��"."��ǰĿ¼��".."��һ��Ŀ¼
	//�Լ�һ���Ӣ��������ϴ����л�����Ŀ¼��������ֵĽڵ���
	//����������·������������ո񡢷�������ⲻ�����ʹ��"."

	//�л�����Ŀ¼������ʵ��ɸѡ�ӿ���
	void changeDirectoryTo(const std::string& path,IXmlHandlePlusCompare& compareObj = defaultCompareObj);

	//�������з��������Ľڵ㷵�ص�����֮��
	std::vector<TiXmlNode*> findAll(const std::string& pathname,IXmlHandlePlusCompare& compareObj = defaultCompareObj);

protected:

	//����⼶�ڵ�����ͬ�����ܱȽϺ���ȷ�ϵĽڵ��б�,��������һ�������Ϸ���
	static std::vector<TiXmlNode*> getSameNameBotherNode(TiXmlNode* curElem,std::string& name,IXmlHandlePlusCompare& compareObj,bool firstBreak = false);

	//�ڵ�·���л�
	static TiXmlNode* changeDirectoryByPath( TiXmlNode* curElem ,std::string &pathList);

	//Ĭ�ϱȽϺ������������ж�Ϊ��
	static bool defaultCompare(TiXmlNode* node);

	//Ĭ�ϱȽ϶���,���ж��󷵻�true
	static IXmlHandlePlusCompare& defaultCompareObj;


private:
	std::string m_ParamName;
	//////////////////////////////////////////////////////////////////////////
	//�ڵ����
public:
	//���ýڵ�����ֵ
	void setAttr(std::string name,std::string value);
	//��ȡ�ڵ�����ֵ��������ֵ������ʱ����Ĭ������
	std::string getAttr(std::string name , std::string defaultValue = "" );

	//����Param�ڵ������ṹ����{|Name|}��ʾName��{|Value|}��ʾValue
	void setParamElementName(std::string paramName);

	//���ڵ�ǰ·����ͬ���ӽڵ�������nameƥ�������
	void setParam(std::string name, std::string value, std::string nameOfAttr = "Name" ,void (*setName)(TiXmlElement*,std::string value) = setElementName,void (*setValue)(TiXmlElement*,std::string value) = setElementValue);
	
	//��ȡ�����ڵ�����
	std::string getParam(std::string name, std::string defaultValue = "" , std::string (*findElement)(TiXmlElement*) = getElementName ,std::string (*getValue)(TiXmlElement*) = getElementValue);

	//��ȡԪ��Name����ֵ
	static std::string getElementName(TiXmlElement* element);

	//����Ԫ��Name����ֵ
	static void setElementName(TiXmlElement* element, std::string value);

	//��ȡԪ��Value����ֵ
	static std::string getElementValue(TiXmlElement* element);

	//����Ԫ��Value����ֵ
	static void setElementValue(TiXmlElement* element, std::string value);

	//��ȡhandle��װ
	XmlHandlePlus getHandle(){	return XmlHandlePlus(node); }

	//////////////////////////////////////////////////////////////////////////
	//�ڵ����
public:
	//���Լ������ж�Ӧ��λ���Ƴ�,���ѽڵ��л������״�
	void remove();

	TiXmlNode* RawData() { return node; }

	//////////////////////////////////////////////////////////////////////////
	//���ߺ���
public:
	//�ӵ�ǰ�ڵ㷵��Root�ڵ�
	static TiXmlNode* getRoot(TiXmlNode* node);

	//���ص�ǰ�ڵ㵽Root�ڵ�֮���·��������·����
	static std::string getPWD(TiXmlNode* node);

	//·��Ԥ�������".."·��\"."·��\"/"
	static std::vector<std::string> createPathlistFromPath( std::string path );

	//���ص�ǰ�ڵ㵽Root�ڵ�֮���·��������·����
	std::string getPWD(){	return getPWD(node);}

	//�жϽڵ��Ƿ�Ϊ��
	bool good() const{	return good(node);	}

	//�жϽڵ��Ƿ�Ϊ��
	static bool good(TiXmlNode* node);

	//���ַ����ָ���ַ�������
	static void split(const std::string& s,const std::string& delim,std::vector< std::string >& ret);
#endif
};

/************************************************************************/
/*  �Ƚ���                                                                     */
/************************************************************************/
#if 1

//�Ƚ��࣬���������ⲿ�ȽϺ���
class XmlOuterFunctionCompare : public IXmlHandlePlusCompare
{
private:
	FuncCompare m_lastCompare;
public:
	XmlOuterFunctionCompare(FuncCompare lastCompare) :m_lastCompare(lastCompare) {}
	virtual bool compare( TiXmlNode* node ) {
		if (m_lastCompare)
		{
			if (m_lastCompare(node))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}
};

//�Ƚ��࣬����ɸѡ ������ �� ֵ ƥ��Ľڵ�
class XmlAttrValueCompare : public IXmlHandlePlusCompare
{
private:
	std::string m_name;
	std::string m_value;
public:
	XmlAttrValueCompare(std::string name,std::string val) :m_name(name),m_value(val){}
	virtual bool compare( TiXmlNode* node ) {
		XmlHandlePlus han(node);
		return han.getAttr(m_name).compare(m_value) == 0 ? true : false;
	}
};

//�Ƚ��࣬���ڽڵ�����ƥ��Node
class XmlNodeNameCompare : public IXmlHandlePlusCompare
{
private:
	std::string m_nodeName;
public:
	XmlNodeNameCompare(std::string nodeName) :m_nodeName(nodeName){}
	virtual bool compare( TiXmlNode* node ) {
		return node->ValueStr() == m_nodeName ? true : false;
	}
};

//�Ƚ��࣬���ڵڼ����ڵ�
class XmlIndexCompare : public IXmlHandlePlusCompare
{
private:
	int m_index;	//Ҫ���ڼ����ͷ���
	int m_count;	//��ǰ���㵽�ڼ���
public:
	XmlIndexCompare(int index) :m_index(index){ 
		m_count = 0;
	}
	virtual bool compare( TiXmlNode* node ) {
		if (m_index == m_count)
		{
			m_count++;
			return true;
		}
		else
		{
			m_count++;
			return false;
		}
	}
};


#endif

#ifndef XmlHandlePlus_TestProject
}
#endif