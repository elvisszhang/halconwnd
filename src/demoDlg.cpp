// demoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "demoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_RECTANGLE1, OnRectangle1)
	ON_BN_CLICKED(IDC_RECTANGLE2, OnRectangle2)
	ON_BN_CLICKED(IDC_CIRCLE, OnCircle)
	ON_BN_CLICKED(IDC_ELLIPSE, OnEllipse)
	ON_BN_CLICKED(IDC_POLYGON, OnPolygon)
	ON_BN_CLICKED(IDC_ZOOMOUT, OnZoomout)
	ON_BN_CLICKED(IDC_ZOOMIN, OnZoomin)
	ON_BN_CLICKED(IDC_ZOOM100, OnZoom100)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	//halcon´°¿Ú
	CRect rect;
	GetClientRect(&rect);
	CRect rectHalcon(0,40,rect.Width(),rect.Height() - 60);
	if (! m_wndHalcon.Create (NULL,_T("HALWINDOW"),WS_TABSTOP | WS_CHILD | WS_HSCROLL| WS_VSCROLL | WS_VISIBLE ,rect, this,12331))
	{
		AfxMessageBox(_T("FAILED TO CREATE IMAGE WINDOW"));
		return TRUE;
	}
	::MoveWindow(m_wndHalcon.m_hWnd,0,40,rect.Width(),rect.Height() - 60,TRUE);
	
	//ÏÔÊ¾Í¼Ïñ
	if(! m_wndHalcon.LoadImage("demo.jpg") )
	{
		AfxMessageBox( m_wndHalcon.GetLastError() );
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CDemoDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if( m_wndHalcon.OnMouseWheel(nFlags,zDelta,pt) )
	{
		this->Invalidate();
	}	
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CDemoDlg::OnRectangle1() 
{
	m_wndHalcon.DrawRectangle1();
}

void CDemoDlg::OnRectangle2() 
{
	m_wndHalcon.DrawRectangle2();	
}

void CDemoDlg::OnCircle() 
{
	m_wndHalcon.DrawCircle();	
}

void CDemoDlg::OnEllipse() 
{
	m_wndHalcon.DrawEllipse();		
}

void CDemoDlg::OnPolygon() 
{
	m_wndHalcon.DrawPolygon();		
	
}

void CDemoDlg::OnZoomout() 
{
	m_wndHalcon.ZoomOut();		
	
}

void CDemoDlg::OnZoomin() 
{
	m_wndHalcon.ZoomIn();		
	
}

void CDemoDlg::OnZoom100() 
{
	m_wndHalcon.Zoom(1);		
	
}
