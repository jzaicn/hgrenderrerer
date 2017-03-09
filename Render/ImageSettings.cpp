// ImageSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "Render.h"
#include "ImageSettings.h"
#include "afxdialogex.h"
#include "XmlHandlePlus.h"

// ImageSetting 对话框

IMPLEMENT_DYNAMIC(ImageSettings, CDialogEx)

ImageSettings::ImageSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(ImageSettings::IDD, pParent)
{

}

ImageSettings::~ImageSettings()
{
}

void ImageSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RENDER_QUALITY_COMBO, m_RenderQuality);
	DDX_Control(pDX, IDC_IMAGE_SIZE_COMBO, m_ImageSize);
}


BEGIN_MESSAGE_MAP(ImageSettings, CDialogEx)
END_MESSAGE_MAP()


// ImageSetting 消息处理程序


BOOL ImageSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	TiXmlDocument doc;
	doc.LoadFile("E:\\HGRENDER\\trunk\\Render\\ImageParam.xml");
	XmlHandlePlus docHandler(&doc);

	std::vector<TiXmlNode*> nodes = docHandler.findAll("/Root/Param/");
	for (auto it = nodes.begin(); it != nodes.end() ; it++)
	{
		XmlHandlePlus node(*it);
		if (node.getAttr("en_name").compare("RenderQuality") == 0)
		{
			std::vector<TiXmlNode*> options = node.findAll("Option");
			for (auto optItem = options.begin(); optItem != options.end() ; optItem++)
			{
				XmlHandlePlus optItemPlus(*optItem);
				m_RenderQuality.AddString(optItemPlus.getAttr("cn_name").c_str());
			}
			m_RenderQuality.SetCurSel(atoi(node.getAttr("default").c_str()));
		}
		else if (node.getAttr("en_name").compare("ImageSize") == 0)
		{
			std::vector<TiXmlNode*> options = node.findAll("Option");
			for (auto optItem = options.begin(); optItem != options.end() ; optItem++)
			{
				XmlHandlePlus optItemPlus(*optItem);
				m_ImageSize.AddString(optItemPlus.getAttr("cn_name").c_str());
			}
			m_ImageSize.SetCurSel(atoi(node.getAttr("default").c_str()));
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ImageSettings::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void ImageSettings::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}
