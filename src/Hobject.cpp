// HalconObjGc.cpp: implementation of the CHalconObjGc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Hobject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

Hobject CHobject::m_empty = NULL;

CHobject::CHobject()
{
	gen_empty_obj(&m_object);
	clear_obj(m_object);
}

CHobject::~CHobject()
{
	//MSG_TIP( m_strName + _T(" ~CHobject"));
	if(!IsEmpty())
	{
		clear_obj(m_object);
	}
}
CHobject::CHobject(const CHobject& obj)
{
}
const CHobject& CHobject::operator=(const CHobject& obj)
{
	return *this;
}
void CHobject::SetName(LPCTSTR szName)
{
	m_strName = szName;
}
CHobject::operator Hobject() const
{
	return m_object;
}

Hobject* CHobject::operator &()
{
	//MSG_TIP(_T("CHobject & operator"));
	return &m_object;
}

BOOL CHobject::IsEmpty()
{
	if(m_object == NULL)
		return TRUE;

	if(!m_empty)
		gen_empty_obj(&m_empty);

	Hlong nEqual = 0;
	test_equal_obj(m_object,m_empty,&nEqual);
	return nEqual;
}
Hobject CHobject::Detach()
{
	Hobject temp = m_object;
	m_object = NULL;
	return temp;
}