// ImageSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DialogImageSettings.h"
#include "afxdialogex.h"
#include "XmlHandlePlus.h"
#include "XmlHandlePlus/tinyxml.h"

// ImageSetting �Ի���

IMPLEMENT_DYNAMIC(DialogImageSettings, CDialogEx)

DialogImageSettings::DialogImageSettings(CWnd* pParent /*=NULL*/)
	: DialogPlus(DialogImageSettings::IDD, pParent)
{

}

DialogImageSettings::~DialogImageSettings()
{
}

void DialogImageSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RENDER_QUALITY_COMBO, m_RenderQuality);
	DDX_Control(pDX, IDC_IMAGE_SIZE_COMBO, m_ImageSize);
}


BEGIN_MESSAGE_MAP(DialogImageSettings, CDialogEx)
	ON_BN_CLICKED(IDC_BEGIN_BTN, &DialogImageSettings::OnBnClickedBeginBtn)
	ON_BN_CLICKED(IDC_SETTING_BTN, &DialogImageSettings::OnBnClickedSettingBtn)
END_MESSAGE_MAP()


// ImageSetting ��Ϣ��������

#include "XmlHandlePlus.h"

BOOL DialogImageSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	TiXmlDocument doc;
	doc.LoadFile("E:\\HGRENDER\\trunk\\HGRenderEngine\\Release\\ImageParam.xml");
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


	
	SetBtnImage(IDC_BEGIN_BTN,IDB_BEGIN_BMP);
	SetBtnImage(IDC_SETTING_BTN,IDB_SETTING_BMP);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void DialogImageSettings::OnBnClickedBeginBtn()
{
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_BEGIN,NULL,NULL);
}


void DialogImageSettings::OnBnClickedSettingBtn()
{
	::PostMessage(ShareHwnd(),DialogPlus::RENDER_SETTINGS_SHOW_HIDE,NULL,NULL);
}