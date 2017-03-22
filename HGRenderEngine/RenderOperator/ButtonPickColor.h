#pragma once


// ButtonPickColor

class ButtonPickColor : public CButton
{
	DECLARE_DYNAMIC(ButtonPickColor)

public:
	ButtonPickColor()
	{
		m_color = RGB(255,0,0); 
	};
	virtual ~ButtonPickColor();

protected:
	DECLARE_MESSAGE_MAP()

public:
	COLORREF Color() const { return m_color; }
	void Color(COLORREF val) { m_color = val; }

	afx_msg void OnPaint();
private:
	COLORREF m_color;
};


