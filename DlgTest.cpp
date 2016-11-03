// DlgTest.cpp : 实现文件
//

#include "stdafx.h"
#include "ShowPixel.h"
#include "DlgTest.h"
#include "afxdialogex.h"


// CDlgTest 对话框

IMPLEMENT_DYNAMIC(CDlgTest, CDialogEx)

CDlgTest::CDlgTest(CView *pView)
{
	m_pView = pView;
}

CDlgTest::~CDlgTest()
{
}

void CDlgTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}
BOOL CDlgTest::Create()
{
	return CDialog::Create(CDlgTest::IDD);
}

BEGIN_MESSAGE_MAP(CDlgTest, CDialog)
END_MESSAGE_MAP()


// CDlgTest 消息处理程序
