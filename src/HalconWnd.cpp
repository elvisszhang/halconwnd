// HalconWnd.cpp : implementation file
//

#include "stdafx.h"
#include "HalconWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHalconWnd

CHalconWnd::CHalconWnd()
{
	m_hWindow = NULL;
	m_bDrawingArea = FALSE;
	m_nLastHorzPos = 0;
	m_nLastVertPos = 0;
	m_dbZoomFactor = 1.0;
}

CHalconWnd::~CHalconWnd()
{
}


BEGIN_MESSAGE_MAP(CHalconWnd, CWnd)
	//{{AFX_MSG_MAP(CHalconWnd)
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHalconWnd message handlers

int CHalconWnd::OnCreate(LPCREATESTRUCT cs) 
{
	if (CWnd::OnCreate(cs) == -1)
		return -1;
	//this->InitHalcon(0,0,cs->cx,cs->cy);
	return 0;
}

void CHalconWnd::SetHalconError(Herror hr)
{
	char szErrorMsg[1024];
	get_error_text(hr,szErrorMsg);
	m_strLastError = szErrorMsg;
}
BOOL CHalconWnd::InitHalcon(int x,int y,int w,int h)
{
	Herror hr;
	set_window_attr("background_color", "black");
	set_check("~father");
	if(m_hWindow)
		close_window(m_hWindow);
	hr = open_window(x, y, w, h, (Hlong)m_hWnd, "visible", "", &m_hWindow);
	if(hr != H_MSG_OK)
	{
		this->SetHalconError(hr);
		return FALSE;
	}
	set_check("father");
	return TRUE;
}
CString CHalconWnd::GetLastError()
{
	return m_strLastError;
}
BOOL CHalconWnd::LoadImage(LPCSTR szImagePath)
{
	Herror hr;
	
	//读入图像数据
	hr = read_image(&m_hoImage,szImagePath);
	if(hr != H_MSG_OK)
	{
		m_strLastError = _T("加载图像失败");
		return FALSE;
	}
	
	//获取图像高宽
	hr = get_image_size(m_hoImage,&m_nImageWidth,&m_nImageHeight);
	if(hr != H_MSG_OK)
	{
		m_strLastError = _T("获取图像尺寸失败");
		return FALSE;
	}
	
	//初始化窗口
	if(! this->InitHalcon(0,0,m_nImageWidth,m_nImageHeight) )
		return FALSE;

	//设置当前显示范围
	hr = set_part(m_hWindow,0, 0, m_nImageHeight, m_nImageWidth );
	if(hr != H_MSG_OK)
	{
		m_strLastError = _T("设置显示范围出错");
		return FALSE;
	}
	hr = disp_obj(m_hoImage,m_hWindow);
	if(hr != H_MSG_OK)
	{
		m_strLastError = _T("显示图像出错");
		return FALSE;
	}


	//缩放1.0倍
	this->Zoom(m_dbZoomFactor);
	return TRUE;
}

void CHalconWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int minpos = 0;
	int maxpos = 0;
	GetScrollRange(SB_HORZ, &minpos, &maxpos); 
	maxpos = GetScrollLimit(SB_HORZ);
 
	// Get the current position of scroll box.
	int curpos = GetScrollPos(SB_HORZ);
 
	// Determine the new position of scroll box.
	switch (nSBCode)
	{
	case SB_LEFT:      // Scroll to far left.
		curpos = minpos;
		break;
 
	case SB_RIGHT:      // Scroll to far right.
		curpos = maxpos;
		break;
 
	case SB_ENDSCROLL:   // End scroll.
		break;
 
	case SB_LINELEFT:      // Scroll left.
		if (curpos > minpos)
			curpos--;
		break;
 
	case SB_LINERIGHT:   // Scroll right.
		if (curpos < maxpos)
			curpos++;
		break;
 
	case SB_PAGELEFT:    // Scroll one page left.
		{
			// Get the page size. 
			SCROLLINFO   info;
			GetScrollInfo(SB_HORZ, &info, SIF_ALL);
 
			if (curpos > minpos)
				curpos = max(minpos, curpos - (int) info.nPage);
		}
		break;
 
	case SB_PAGERIGHT:      // Scroll one page right.
		{
			// Get the page size. 
			SCROLLINFO   info;
			GetScrollInfo(SB_HORZ, &info, SIF_ALL);
 
			if (curpos < maxpos)
				curpos = min(maxpos, curpos + (int) info.nPage);
		}
		break;
 
	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		curpos = nPos;      // of the scroll box at the end of the drag operation.
		break;
 
	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		curpos = nPos;     // position that the scroll box has been dragged to.
		break;
	}
 
	// Set the new position of the thumb (scroll box).
	SetScrollPos(SB_HORZ, curpos);
	ScrollWindow(m_nLastHorzPos-curpos,0);
 
	m_nLastHorzPos = curpos;
	UpdateWindow();
	
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CHalconWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int minpos = 0;
	int maxpos = 0;
	GetScrollRange(SB_VERT, &minpos, &maxpos); 
	maxpos = GetScrollLimit(SB_VERT);
 
	// Get the current position of scroll box.
	int curpos = GetScrollPos(SB_VERT);
 
	// Determine the new position of scroll box.
	switch (nSBCode)
	{
	case SB_LEFT:      // Scroll to far left.
		curpos = minpos;
		break;
 
	case SB_RIGHT:      // Scroll to far right.
		curpos = maxpos;
		break;
 
	case SB_ENDSCROLL:   // End scroll.
		break;
 
	case SB_LINELEFT:      // Scroll left.
		if (curpos > minpos)
			curpos--;
		break;
 
	case SB_LINERIGHT:   // Scroll right.
		if (curpos < maxpos)
			curpos++;
		break;
 
	case SB_PAGELEFT:    // Scroll one page left.
		{
			// Get the page size. 
			SCROLLINFO   info;
			GetScrollInfo(SB_VERT, &info, SIF_ALL);
 
			if (curpos > minpos)
				curpos = max(minpos, curpos - (int) info.nPage);
		}
		break;
 
	case SB_PAGERIGHT:      // Scroll one page right.
		{
			// Get the page size. 
			SCROLLINFO   info;
			GetScrollInfo(SB_VERT, &info, SIF_ALL);
 
			if (curpos < maxpos)
				curpos = min(maxpos, curpos + (int) info.nPage);
		}
		break;
 
	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		curpos = nPos;      // of the scroll box at the end of the drag operation.
		break;
 
	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		curpos = nPos;     // position that the scroll box has been dragged to.
		break;
	}
 
	// Set the new position of the thumb (scroll box).
	SetScrollPos(SB_VERT, curpos);
	ScrollWindow(0,m_nLastVertPos - curpos);
 
	m_nLastVertPos = curpos;
	UpdateWindow();
	
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CHalconWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if(m_bDrawingArea)
		return FALSE;

/*	static DWORD dwLastTick = timeGetTime();
	if( timeGetTime() - dwLastTick <= 300 )
	{
		return FALSE;
	}
	dwLastTick = timeGetTime();
*/	
	if(zDelta < 0)
		return this->ZoomOut();
	else
		return this->ZoomIn();

}
BOOL CHalconWnd::DrawRectangle1()
{
	if(m_bDrawingArea)
		return FALSE;
	double Row1,Column1,Row2,Column2;
	m_bDrawingArea = TRUE;
	Herror hr = draw_rectangle1(m_hWindow,&Row1,&Column1,&Row2,&Column2);
	m_bDrawingArea = FALSE;
	return hr == H_MSG_OK;
}
BOOL CHalconWnd::DrawRectangle2()
{
	if(m_bDrawingArea)
		return FALSE;
	double Row,Column,Phi,Length1,Length2;
	m_bDrawingArea = TRUE;
	Herror hr = draw_rectangle2(m_hWindow,&Row, &Column, &Phi, &Length1, &Length2);
	m_bDrawingArea = FALSE;
	return hr == H_MSG_OK;
}
BOOL CHalconWnd::DrawCircle()
{
	if(m_bDrawingArea)
		return FALSE;
	double Row,Column,Radius;
	m_bDrawingArea = TRUE;
	Herror hr = draw_circle(m_hWindow,&Row,&Column,&Radius);
	m_bDrawingArea = FALSE;
	return hr == H_MSG_OK;
}
BOOL CHalconWnd::DrawEllipse()
{
	if(m_bDrawingArea)
		return FALSE;
	double Row,Column,Phi,Radius1,Radius2;
	m_bDrawingArea = TRUE;
	Herror hr = draw_ellipse(m_hWindow,&Row, &Column, &Phi, &Radius1, &Radius2);
	m_bDrawingArea = FALSE;
	return hr == H_MSG_OK;
}
BOOL CHalconWnd::DrawPolygon()
{
	if(m_bDrawingArea)
		return FALSE;
	CHobject polygon;
	m_bDrawingArea = TRUE;
	Herror hr = draw_polygon(&polygon,m_hWindow);
	m_bDrawingArea = FALSE;
	return hr == H_MSG_OK;
}

BOOL CHalconWnd::DrawRegion()
{
	if(m_bDrawingArea)
		return FALSE;
	CHobject region;
	m_bDrawingArea = TRUE;
	Herror hr = draw_region(&region,m_hWindow);
	m_bDrawingArea = FALSE;
	return hr == H_MSG_OK;
}

BOOL CHalconWnd::DrawArea(UINT nMode)
{
	switch(nMode)
	{
	case DRAW_RECTANGLE1:
		return this->DrawRectangle1();
	case DRAW_RECTANGLE2:
		return this->DrawRectangle2();
	case DRAW_CIRCLE:
		return this->DrawCircle();
	case DRAW_ELLIPSE:
		return this->DrawEllipse();
	case DRAW_POLYGON:
		return this->DrawPolygon();
	case DRAW_REGION:
		return this->DrawRegion();
	default:
		return FALSE;
	}
}
BOOL CHalconWnd::IsDrawingArea()
{
	return m_bDrawingArea;
}

BOOL CHalconWnd::ZoomIn()
{
	return this->Zoom(m_dbZoomFactor*1.10);
}
BOOL CHalconWnd::ZoomOut()
{
	return this->Zoom(m_dbZoomFactor*0.90);
}
double CHalconWnd::GetZoomFactor()
{
	return m_dbZoomFactor;
}

BOOL CHalconWnd::Zoom(double dbFactor)
{
	//缩放率控制
	if(dbFactor < 0.1)
		dbFactor = 0.1;
	if(dbFactor > 5 )
		dbFactor = 5;
	m_dbZoomFactor = dbFactor;

	//获取窗口大小
	int nZoomWidth = (int)(dbFactor * m_nImageWidth);
	int nZoomHeight = (int)(dbFactor * m_nImageHeight);

	//设置窗口大小
	Herror hr;
	clear_window(m_hWindow);
	hr = set_window_extents(m_hWindow,0,0,nZoomWidth,nZoomHeight);

	//显示图像
	hr = disp_obj(m_hoImage,m_hWindow);
	if(hr != H_MSG_OK)
		return FALSE;

	//设置滚动条范围
	CRect rect;
	GetClientRect(rect);
	if( nZoomWidth > rect.Width() )
	{
		ShowScrollBar(SB_HORZ,TRUE);
		SetScrollRange(SB_HORZ,0,nZoomWidth - rect.Width() ,TRUE);
		SetScrollPos(SB_HORZ,0);
		m_nLastHorzPos = 0;
	}
	else
	{
		ShowScrollBar(SB_HORZ,FALSE);
		SetScrollPos(SB_HORZ,0);
	}

	if( nZoomHeight > rect.Height() )
	{
		ShowScrollBar(SB_VERT,TRUE);
		SetScrollRange(SB_VERT,0,nZoomHeight - rect.Height() ,TRUE);
		SetScrollPos(SB_VERT,0);
		m_nLastVertPos = 0;
	}
	else
	{
		ShowScrollBar(SB_VERT,FALSE);
		SetScrollPos(SB_VERT,0);
	}


	return TRUE;
}