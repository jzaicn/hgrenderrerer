// ImageSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogImageSettings.h"
#include "afxdialogex.h"
#include "XmlHandlePlus/XmlHandlePlus.h"
#include "XmlHandlePlus/tinyxml.h"
#include "HGCode.h"
#include "HgLog/HgLog.h"

// ImageSetting 对话框

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


// ImageSetting 消息处理程序

#include "XmlHandlePlus/XmlHandlePlus.h"

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
				m_RenderQuality.AddString(HGCode::convert(optItemPlus.getAttr("cn_name").c_str()));
				m_RenderQualityValue.push_back(atoi(optItemPlus.getAttr("value").c_str()));
			}
			m_RenderQuality.SetCurSel(findQualityCurSelByValue(atoi(node.getAttr("default").c_str())));
		}
		else if (node.getAttr("en_name").compare("ImageSize") == 0)
		{
			std::vector<TiXmlNode*> options = node.findAll("Option");
			for (auto optItem = options.begin(); optItem != options.end() ; optItem++)
			{
				XmlHandlePlus optItemPlus(*optItem);
				m_ImageSize.AddString(HGCode::convert(optItemPlus.getAttr("cn_name").c_str()));
			}
			m_ImageSize.SetCurSel(atoi(node.getAttr("default").c_str()));
		}
	}


	
	SetBtnImage(IDC_BEGIN_BTN,IDB_BEGIN_BMP);
	SetBtnImage(IDC_SETTING_BTN,IDB_SETTING_BMP);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void DialogImageSettings::OnBnClickedBeginBtn()
{
	DialogPlus::Post(RENDER_BEGIN);
}


void DialogImageSettings::OnBnClickedSettingBtn()
{
	DialogPlus::Post(RENDER_TOOLBAR_SHOW_HIDE);
}

HG_RenderParam DialogImageSettings::get_RenderParam()
{
	HG_RenderParam param;

	try
	{
		int qualitySel = ((CComboBox*)GetDlgItem(IDC_IMAGE_SIZE_COMBO))->GetCurSel();
		param.set_render_quality(m_RenderQualityValue[qualitySel]);

		CString width_heigh;
		((CComboBox*)GetDlgItem(IDC_IMAGE_SIZE_COMBO))->GetWindowText(width_heigh);
		int splitx = width_heigh.Find(_T("x"));
		if (splitx == -1 || splitx == 0 || splitx == width_heigh.GetLength() )
		{
			return param;
		}
		CString width = width_heigh.Left(splitx);
		CString height = width_heigh.Right(width_heigh.GetLength() - splitx -1);
		param.set_render_width(atoi(HGCode::convert(width.GetBuffer())));
		param.set_render_height(atoi(HGCode::convert(height.GetBuffer())));


		return param;
	}
	catch (...)
	{
		HGLOG_ERROR("保存界面参数到数据结构错误 [DialogImageSettings::get_RenderParam]");
	}
}

void DialogImageSettings::set_RenderParam(HG_RenderParam param)
{
	int quality = param.get_render_quality();
	((CComboBox*)GetDlgItem(IDC_IMAGE_SIZE_COMBO))->SetCurSel(findQualityCurSelByValue(quality));

	
	int width = param.get_render_width();
	int height = param.get_render_height();
	CString width_heigh;
	width_heigh.Format(_T("%dx%d"),width,height);
	((CComboBox*)GetDlgItem(IDC_IMAGE_SIZE_COMBO))->SetWindowText(width_heigh);
}

int DialogImageSettings::findQualityCurSelByValue(int val)
{
	for (int i = 0; i < m_RenderQualityValue.size() ; i++)
	{
		if(val == m_RenderQualityValue.at(i))
		{
			return i;
		}
	}
	return 0;
}

