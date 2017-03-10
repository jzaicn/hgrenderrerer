#pragma once


// PickColorButton

class PickColorButton : public CButton
{
	DECLARE_DYNAMIC(PickColorButton)

public:
	PickColorButton()
	{
		m_color = RGB(255,0,0); 
	};
	virtual ~PickColorButton();

protected:
	DECLARE_MESSAGE_MAP()

public:
	COLORREF Color() const { return m_color; }
	void Color(COLORREF val) { m_color = val; }

	afx_msg void OnPaint();
private:
	COLORREF m_color;
};


