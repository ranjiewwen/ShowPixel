#pragma once


// CDlgTest 对话框

class CDlgTest : public CDialog
{
	DECLARE_DYNAMIC(CDlgTest)

public:
	CDlgTest(CView*);   // 标准构造函数
	BOOL Create();
	virtual ~CDlgTest();
	CView* m_pView;
// 对话框数据
	enum { IDD = IDD_DIALOGTest };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
