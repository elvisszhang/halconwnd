// demoDlg.h : header file
//

#if !defined(AFX_DEMODLG_H__2521FCEC_AC2F_4881_8862_12E0AC226FC1__INCLUDED_)
#define AFX_DEMODLG_H__2521FCEC_AC2F_4881_8862_12E0AC226FC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog
#include "HalconWnd.h"

class CDemoDlg : public CDialog
{
// Construction
public:
	CDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDemoDlg)
	enum { IDD = IDD_DEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CHalconWnd m_wndHalcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRectangle1();
	afx_msg void OnRectangle2();
	afx_msg void OnCircle();
	afx_msg void OnEllipse();
	afx_msg void OnPolygon();
	afx_msg void OnZoomout();
	afx_msg void OnZoomin();
	afx_msg void OnZoom100();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMODLG_H__2521FCEC_AC2F_4881_8862_12E0AC226FC1__INCLUDED_)
