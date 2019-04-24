#if !defined(AFX_HALCONWND_H__41CAF5F2_2DB6_4426_9C62_70B0229EEA12__INCLUDED_)
#define AFX_HALCONWND_H__41CAF5F2_2DB6_4426_9C62_70B0229EEA12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HalconWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHalconWnd window
#include "Hobject.h"

class CHalconWnd : public CWnd
{
// Construction
public:
	enum DRAW_MODE
	{
		DRAW_RECTANGLE1,
		DRAW_RECTANGLE2,
		DRAW_CIRCLE,
		DRAW_ELLIPSE,
		DRAW_POLYGON,
		DRAW_REGION,
	};

	CHalconWnd();
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	BOOL DrawRectangle1();
	BOOL DrawRectangle2();
	BOOL DrawCircle();
	BOOL DrawEllipse();
	BOOL DrawPolygon();
	BOOL DrawRegion();
	BOOL DrawArea(UINT nMode);
	BOOL IsDrawingArea();

	BOOL ZoomIn();
	BOOL ZoomOut();
	BOOL Zoom(double dbFactor);
	double GetZoomFactor();
// Attributes
public:
	Hlong m_hWindow;

// Operations
public:
	BOOL LoadImage(LPCSTR szImagePath);
	CString GetLastError();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHalconWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHalconWnd();

	// Generated message map functions
protected:
	BOOL InitHalcon(int x,int y,int w,int h);
	void SetHalconError(Herror hr);
	//{{AFX_MSG(CHalconWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CHobject m_hoImage;
	Hlong m_nImageWidth;
	Hlong m_nImageHeight;
	double m_dbZoomFactor;
	BOOL m_bDrawingArea;
	int m_nLastHorzPos;
	int m_nLastVertPos;
	CString m_strLastError;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HALCONWND_H__41CAF5F2_2DB6_4426_9C62_70B0229EEA12__INCLUDED_)
