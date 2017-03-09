// ImageSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Render.h"
#include "ImageSettings.h"
#include "afxdialogex.h"
#include "XmlHandlePlus.h"

// ImageSetting �Ի���

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


// ImageSetting ��Ϣ��������


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


	
	SetBtnImage(IDC_BEGIN_BTN,IDB_BEGIN_BMP);
	SetBtnImage(IDC_SETTING_BTN,IDB_SETTING_BMP);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void ImageSettings::SetBtnImage(int _btn_marco,int _res_marco)
{
	HBITMAP   hBitmap;   
	hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(_res_marco)); // IDB_BITMAP_TESTΪ��ԴͼƬID 
	((CButton *)GetDlgItem(_btn_marco))->SetBitmap(hBitmap);
}

void ImageSettings::OnOK()
{
	// TODO: �ڴ�����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void ImageSettings::OnCancel()
{
	// TODO: �ڴ�����ר�ô����/����û���

	//CDialogEx::OnCancel();
}