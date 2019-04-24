// HalconObjGc.h: interface for the CHalconObjGc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HALCONOBJGC_H__C1CF909E_BB10_4E96_A7D0_1D2299A60658__INCLUDED_)
#define AFX_HALCONOBJGC_H__C1CF909E_BB10_4E96_A7D0_1D2299A60658__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHobject
{
public:
	CHobject();
	~CHobject();
	void SetName(LPCTSTR szName);
	operator Hobject() const; 
	Hobject* operator &();
	BOOL IsEmpty();
	Hobject Detach();
private:
	CHobject(const CHobject& obj);
	const CHobject& operator=(const CHobject& obj);
private:
	static Hobject m_empty;
	Hobject m_object;
	CString m_strName;
};


#endif // !defined(AFX_HALCONOBJGC_H__C1CF909E_BB10_4E96_A7D0_1D2299A60658__INCLUDED_)
