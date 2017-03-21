// ImageSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "Render.h"
#include "ImageSettings.h"
#include "afxdialogex.h"
//#include "XmlHandlePlus.h"

// ImageSetting 对话框

IMPLEMENT_DYNAMIC(ImageSettings, CDialogEx)

ImageSettings::ImageSettings(CWnd* pParent /*=NULL*/)
	: DialogPlus(ImageSettings::IDD, pParent)
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
	ON_BN_CLICKED(IDC_BEGIN_BTN, &ImageSettings::OnBnClickedBeginBtn)
	ON_BN_CLICKED(IDC_SETTING_BTN, &ImageSettings::OnBnClickedSettingBtn)
END_MESSAGE_MAP()


// ImageSetting 消息处理程序


BOOL ImageSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

// 	TiXmlDocument doc;
// 	doc.LoadFile("E:\\HGRENDER\\trunk\\Render\\ImageParam.xml");
// 	XmlHandlePlus docHandler(&doc);
// 
// 	std::vector<TiXmlNode*> nodes = docHandler.findAll("/Root/Param/");
// 	for (auto it = nodes.begin(); it != nodes.end() ; it++)
// 	{
// 		XmlHandlePlus node(*it);
// 		if (node.getAttr("en_name").compare("RenderQuality") == 0)
// 		{
// 			std::vector<TiXmlNode*> options = node.findAll("Option");
// 			for (auto optItem = options.begin(); optItem != options.end() ; optItem++)
// 			{
// 				XmlHandlePlus optItemPlus(*optItem);
// 				m_RenderQuality.AddString(optItemPlus.getAttr("cn_name").c_str());
// 			}
// 			m_RenderQuality.SetCurSel(atoi(node.getAttr("default").c_str()));
// 		}
// 		else if (node.getAttr("en_name").compare("ImageSize") == 0)
// 		{
// 			std::vector<TiXmlNode*> options = node.findAll("Option");
// 			for (auto optItem = options.begin(); optItem != options.end() ; optItem++)
// 			{
// 				XmlHandlePlus optItemPlus(*optItem);
// 				m_ImageSize.AddString(optItemPlus.getAttr("cn_name").c_str());
// 			}
// 			m_ImageSize.SetCurSel(atoi(node.getAttr("default").c_str()));
// 		}
// 	}


	
	SetBtnImage(IDC_BEGIN_BTN,IDB_BEGIN_BMP);
	SetBtnImage(IDC_SETTING_BTN,IDB_SETTING_BMP);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ImageSettings::OnBnClickedBeginBtn()
{
	::PostMessage(ShareHwnd(),DialogPlus::CMD::RENDER_BEGIN,NULL,NULL);
}


void ImageSettings::OnBnClickedSettingBtn()
{
	::PostMessage(ShareHwnd(),DialogPlus::CMD::RENDER_SETTINGS_SHOW_HIDE,NULL,NULL);
}
