// ShowPixelView.cpp : implementation of the CShowPixelView class
//

#include "stdafx.h"
#include "ShowPixel.h"
#include "MainFrm.h"
#include "ShowPixelDoc.h"
#include "ShowPixelView.h"
#include "PixelDlg.h"
#include "DlgTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
class CShowPixelDoc;
/////////////////////////////////////////////////////////////////////////////
// CShowPixelView

IMPLEMENT_DYNCREATE(CShowPixelView, CView)

BEGIN_MESSAGE_MAP(CShowPixelView, CView)
	//{{AFX_MSG_MAP(CShowPixelView)
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CShowPixelView::CShowPixelView()
{
	// TODO: add construction code here
	b_Static = FALSE;
	b_Created = FALSE;
	m_pDlg = new CPixelDlg(this);
	m_testDlg = new CDlgTest(this);
	pGrayData = new BYTE[10 * 10];
	//	x=0;y=0;
	
}

CShowPixelView::~CShowPixelView()
{
	delete[]pGrayData;
	delete m_pDlg;
	delete m_testDlg;
}

BOOL CShowPixelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CShowPixelView drawing

void CShowPixelView::OnDraw(CDC* pDC)
{
	CShowPixelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (pDoc->lpBits != NULL)
	{
		StretchDIBits(pDC->m_hDC, 0, 0,
			(int)(pDoc->nWidth), (int)(pDoc->nHeight), 0, 0, pDoc->nWidth, pDoc->nHeight,
			pDoc->lpBits, (BITMAPINFO *)(pDoc->lpBitmap), DIB_RGB_COLORS, SRCCOPY);//显示位图
	}
	if (m_hRC == NULL)
	{
		//	MessageBox("m_hRc==NULL!");
		return;
	}
	if (pGrayData == NULL)
	{
		//	MessageBox("pGrayData==NULL!");
		return;
	}
	if (!b_Created)
	{
		m_pDlg->Create();
		m_testDlg->Create();

		CRect rect;
		m_pDlg->GetWindowRect(&rect);
		m_pDlg->MoveWindow(500, 50, rect.Width(), rect.Height());//靠右显示

	
		b_Created = TRUE;
	}

}

/////////////////////////////////////////////////////////////////////////////
// CShowPixelView diagnostics

#ifdef _DEBUG
void CShowPixelView::AssertValid() const
{
	CView::AssertValid();
}

void CShowPixelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShowPixelDoc* CShowPixelView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShowPixelDoc)));
	return (CShowPixelDoc*)m_pDocument;
}
#endif //_DEBUG

////////////////////////////////////////////////////////////////////////////
// CShowPixelView message handlers


void CShowPixelView::drawPixel(CPoint point)
{
	
	CShowPixelDoc* pDoc = GetDocument();
	int x, y;
	x = point.x; y = pDoc->nHeight - point.y;
	int i, j, h;

	//显示区域像素
	CRect rect;
	CString str1;
	m_pDlg->GetDlgItem(IDC_GrayDis2)->GetClientRect(&rect);//
	int xstep, ystep, x0, y0;
	xstep = rect.Width() / (WIDTH);
	ystep = rect.Height() / (HEIGHT);

	x0 = rect.Width() - xstep * (WIDTH);//
	y0 = rect.Height() - ystep * (HEIGHT);//
	
	CDC* dc = m_pDlg->GetDlgItem(IDC_GrayDis2)->GetDC();
	dc->SelectStockObject(WHITE_BRUSH);
	dc->Rectangle(rect.left - 2, rect.top - 2, rect.right + 2, rect.bottom + 2);  //move 会多次画图，防止覆盖

	CString strBits;
	int ii, jj;
	BYTE gray, r, g, b;
	for (j = 0; j < HEIGHT; j++)
	{
		jj = y - WIDTH/2 + j;
		jj = jj<0 ? 0 : jj;
		jj = jj>pDoc->nHeight ? pDoc->nHeight : jj;
		//显示每一行像素
		CString lineStr="";
		for (i = 0; i < WIDTH; i++)
		{
			
			ii = x - HEIGHT/2 + i;
			ii<0 ? 0 : ii;
			ii>pDoc->nWidth ? pDoc->nWidth : ii;
			if (pDoc->nColorBits == 8)
			{
				gray = pDoc->lpBits[(jj+1)*pDoc->nByteWidth + ii+3];  //2 ,2 调整两幅图数据对齐
			}
			else if (pDoc->nColorBits == 24)
			{
				gray = (BYTE)((pDoc->lpBits[jj*pDoc->nByteWidth + ii * 3] * 15
					+ pDoc->lpBits[jj*pDoc->nByteWidth + ii * 3 + 1] * 75
					+ pDoc->lpBits[jj*pDoc->nByteWidth + ii * 3 + 2] * 38) / 128);
			}
			strBits.Format("%d", gray);
			switch (gray / 50)
			{
			case 0:
			case 1://0--29
				r = gray; b = gray; g = gray;
				break;
			case 2://30--59
				r = 0; b = gray + 100; g = 0;
				break;
			case 3://60--79
				r = 0; g = gray + 50; b = 0;
				break;
			case 4:
			case 5://200-255
				r = gray; g = 0, b = 0;
				break;
			}
			dc->SetTextColor(RGB(r, g, b));
			dc->TextOut(x0 + i*xstep, y0 + (HEIGHT - j-1)*ystep, strBits);//需要改的地方，HEIGHT - j-1
		
			CString str="";
			str.Format("%d ",gray);
			lineStr += str;
		}		
	}
	ReleaseDC(dc);

}


void CShowPixelView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CShowPixelDoc* pDoc = GetDocument();
	char p1[20], p2[4];
	//得到主框架对象的指针
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	//pFrame->m_wndStatusBar.SetPaneText(0,m_doing,TRUE);
	if (point.x > pDoc->nWidth || point.y > pDoc->nHeight)
	{
		strcpy(p1, "超出图像范围！");
		pFrame->m_wndStatusBar.SetPaneText(1, p1, TRUE);
		pFrame->m_wndStatusBar.SetPaneText(2, p1, TRUE);
		pFrame->m_wndStatusBar.SetPaneText(3, p1, TRUE);
		return;
	}
	int x, y;
	x = point.x; y = pDoc->nHeight - point.y;
	if (pDoc->nColorBits == 24)
	{
		sprintf(p2, "%d", pDoc->lpBits[y*pDoc->nByteWidth + x * 3]);
		strcpy(p1, "蓝色分量：");
		strcat(p1, p2);
		pFrame->m_wndStatusBar.SetPaneText(1, p1, TRUE);
		sprintf(p2, "%d", pDoc->lpBits[y*pDoc->nByteWidth + x * 3 + 1]);
		strcpy(p1, "绿色分量：");
		strcat(p1, p2);
		pFrame->m_wndStatusBar.SetPaneText(2, p1, TRUE);
		sprintf(p2, "%d", pDoc->lpBits[y*pDoc->nByteWidth + x * 3 + 2]);
		strcpy(p1, "红色分量：");
		strcat(p1, p2);
		pFrame->m_wndStatusBar.SetPaneText(3, p1, TRUE);
	}
	else if (pDoc->nColorBits == 8)
	{
		sprintf(p2, "%d", pDoc->lpBits[y*pDoc->nByteWidth + x]);
		strcpy(p1, "像素值：");
		strcat(p1, p2);
		pFrame->m_wndStatusBar.SetPaneText(1, p1, TRUE);
		pFrame->m_wndStatusBar.SetPaneText(2, "0", TRUE);
		pFrame->m_wndStatusBar.SetPaneText(3, "0", TRUE);
	}
	sprintf(p2, "%d", x);
	strcpy(p1, "列：");
	strcat(p1, p2);
	pFrame->m_wndStatusBar.SetPaneText(4, p1, TRUE);
	sprintf(p2, "%d", y);
	strcpy(p1, "行：");
	strcat(p1, p2);
	pFrame->m_wndStatusBar.SetPaneText(5, p1, TRUE);

	if (b_Created == TRUE&&b_Static == FALSE)
	{
		point1.x = point.x;
		point1.y = pDoc->nHeight - point.y;
		int i, j, h;
		int cout[256];
		for (i = 0; i < 256; i++)
		{
			cout[i] = 0;
		}
		//显示区域像素值，带滚动条区域
		CRect rect;
		CString str1;
		m_pDlg->GetDlgItem(IDC_GrayDis)->GetClientRect(&rect);//
		int xstep, ystep, x0, y0;
		xstep = rect.Width() / 11;
		ystep = rect.Height() / 11;
	
		x0 = rect.Width() - xstep * 10;//
		y0 = rect.Height() - ystep * 10;//

		CDC* dc = m_pDlg->GetDlgItem(IDC_GrayDis)->GetDC();
		dc->SelectStockObject(WHITE_BRUSH);
		dc->Rectangle(rect.left - 2, rect.top - 2, rect.right + 2, rect.bottom + 2);
		//画行列
		dc->TextOut(2, 0, "V/H");
		for (i = 0; i < 10; i++)//
		{
			str1.Format("%d", x - 5 + i);//这里改5换成10
			dc->TextOut(x0 + i*xstep, 0, str1);
			str1.Format("%d", y - 5 + i);//
			dc->TextOut(0, y0 + i*ystep, str1);
		}
		////////////画出矩形中间的分割线
		dc->MoveTo(rect.left - 2, y0 - 2);
		dc->LineTo(rect.right + 2, y0 - 2);
		dc->MoveTo(x0 - 5, rect.top-2);
		dc->LineTo(x0 - 5, rect.bottom - 2);
		CString strBits;
		int ii, jj;
		BYTE gray, r, g, b;

		for (j = 0; j < 10; j++)
		{
			jj = y - 5 + j;
			jj = jj<0 ? 0 : jj;
			jj = jj>pDoc->nHeight ? pDoc->nHeight : jj;
			//显示每一行像素
			for (i = 0; i < 10; i++)
			{
				ii = x - 5 + i;
				ii<0 ? 0 : ii;
				ii>pDoc->nWidth ? pDoc->nWidth : ii;
				if (pDoc->nColorBits == 8)
				{
					gray = pDoc->lpBits[jj*pDoc->nByteWidth + ii];
				}
				else if (pDoc->nColorBits == 24)
				{
					gray = (BYTE)((pDoc->lpBits[jj*pDoc->nByteWidth + ii * 3] * 15
						+ pDoc->lpBits[jj*pDoc->nByteWidth + ii * 3 + 1] * 75
						+ pDoc->lpBits[jj*pDoc->nByteWidth + ii * 3 + 2] * 38) / 128);
				}
				strBits.Format("%d", gray);
				switch (gray / 50)
				{
				case 0:
				case 1://0--29
					r = gray; b = gray; g = gray;
					break;
				case 2://30--59
					r = 0; b = gray + 100; g = 0;
					break;
				case 3://60--79
					r = 0; g = gray + 50; b = 0;
					break;
				case 4:
				case 5://200-255
					r = gray; g = 0, b = 0;
					break;
				}
				dc->SetTextColor(RGB(r, g, b));
				dc->TextOut(x0 + i*xstep, y0 + (9 - j)*ystep, strBits);//需要改的地方，9！！！！
				cout[gray]++;
			}
		}

		ReleaseDC(dc);


		drawPixel(point);

		m_pDlg->m_vScroll.SetScrollPos(0);
		m_pDlg->scrollinfo1.nPos = 0;
		m_pDlg->m_hScroll.SetScrollPos(0);
		m_pDlg->scrollinfo0.nPos = 0;


		//显示图像
		m_pDlg->GetDlgItem(IDC_CLICKAREA)->GetClientRect(&rect);//对话框类的接口
		CDC* pdc = m_pDlg->GetDlgItem(IDC_CLICKAREA)->GetDC();
		int xx = x - 15 > 0 ? x - 15 : 0;
		xx = xx<pDoc->nWidth - 30 ? xx : pDoc->nWidth - 30;
		int yy = y - 15>0 ? y - 15 : 0;
		yy = yy < pDoc->nHeight - 30 ? yy : pDoc->nHeight - 30;
		StretchDIBits(pdc->m_hDC, 0, 0, rect.Width(), rect.Height(), xx, yy, 30, 30,
			pDoc->lpBits, (BITMAPINFO *)(pDoc->lpBitmap), DIB_RGB_COLORS, SRCCOPY);
		ReleaseDC(pdc);

		//绘制直方图
		m_pDlg->GetDlgItem(IDC_ZHIFANGTU)->GetClientRect(&rect);
		pdc = m_pDlg->GetDlgItem(IDC_ZHIFANGTU)->GetDC();
		pdc->SelectStockObject(WHITE_BRUSH);
		pdc->Rectangle(rect);

		CPen mPen(PS_SOLID, 0, (COLORREF)0x000000ff);

		pdc->MoveTo(5, rect.Height() - 10); //移动到点
		pdc->LineTo(5, 5);  //画线
		pdc->LineTo(3, 10);
		pdc->MoveTo(5, 5);
		pdc->LineTo(7, 10);
		pdc->MoveTo(5, rect.Height() - 10);
		pdc->LineTo(rect.Width() - 5, rect.Height() - 10);
		pdc->LineTo(rect.Width() - 10, rect.Height() - 8);
		pdc->MoveTo(rect.Width() - 5, rect.Height() - 10);
		pdc->LineTo(rect.Width() - 10, rect.Height() - 12);
		pdc->SelectObject(&mPen);
		for (i = 0; i<256; i++)
		{
			h = 5 * ((int)(cout[i] / 100.0*(rect.Height() - 15)));
			h = h>rect.Height() - 15 ? rect.Height() - 15 : h;
			pdc->MoveTo(6 + (int)(i / 256.0*(rect.Width() - 10)), rect.Height() - 10);
			pdc->LineTo(6 + (int)(i / 256.0*(rect.Width() - 10)),
				rect.Height() - 10 - h);
		}


		ReleaseDC(pdc);
		//////////////////////////////
		//3D
		///////////////////////////////
		nWidth = 10;
		nHeight = 10;
		nBitCount = pDoc->nColorBits;
		nWidthBytes = pDoc->nByteWidth;
		m_fxAngle = m_fzAngle = 0.0;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (pDoc->nColorBits == 8)
				{
					gray = pDoc->lpBits[(yy + j)*nWidthBytes + i + xx];
				}
				else if (pDoc->nColorBits == 24)
				{
					gray = (BYTE)((pDoc->lpBits[(yy + j)*nWidthBytes + (i + xx) * 3] * 15
						+ pDoc->lpBits[(yy + j)*nWidthBytes + (i + xx) * 3 + 1] * 75
						+ pDoc->lpBits[(yy + j)*nWidthBytes + (i + xx) * 3 + 2] * 38) / 128);
				}
				pGrayData[j * 10 + i] = gray;
			}
		}
		Invalidate(0);
	}


	if (m_bClickEmpty)     {
		CClientDC dc(this);

		CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));

		CBrush *POldBrush = dc.SelectObject(pBrush);

		int nOldMode = dc.SetROP2(R2_NOTXORPEN);

		dc.Rectangle(&CRect(point1, end_Point));

		dc.Rectangle(&CRect(point1, point));

		end_Point = point;

		dc.SelectObject(POldBrush);

		dc.SetROP2(nOldMode);

	}

	CView::OnMouseMove(nFlags, point);
}

void CShowPixelView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CShowPixelDoc* pDoc = GetDocument();
	
	if (m_bClickEmpty)      {
		m_bClickEmpty = false;

		CClientDC dc(this);

		CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));

		CBrush *POldBrush = dc.SelectObject(pBrush);

		int nOldMode = dc.SetROP2(R2_NOTXORPEN);

		dc.Rectangle(&CRect(point1, end_Point));

		dc.SelectObject(POldBrush);

		dc.SetROP2(nOldMode);

		CString row_str;
		row = end_Point.y - point1.y; //行数
		CString col_str;
		col = end_Point.x - point1.x; //列数	
		if (row<=0||col<=0)
		{
			row_str.Format("鼠标选中区域不清楚！默认行为：10");
			col_str.Format("鼠标选中区域不清楚！默认列为：10");
			row = col = 10;
		}
		else
		{
			row_str.Format("鼠标选中区域行数：%d", row);
			col_str.Format("鼠标选中区域列数：%d", col);
		}
		m_pDlg->m_imageInfoList.AddString(row_str);
		m_pDlg->m_imageInfoList.AddString(col_str);

	}
	if (m_bCaptured)
	{
		::ReleaseCapture();
		m_bCaptured = FALSE;
	}

	m_pDlg->m_hScroll.SetScrollRange(0, row-7);
	m_pDlg->m_vScroll.SetScrollRange(0, col-7);
	
	int i, j, h;
	int cout[256];
	for (i = 0; i < 256; i++)
	{
		cout[i] = 0;
	}
	//显示区域像素值，带滚动条区域
	CRect rect;
	CString str1;
	m_pDlg->GetDlgItem(IDC_GrayDis)->GetClientRect(&rect);//
	int xstep, ystep, x0, y0;
	xstep = rect.Width() / 11;
	ystep = rect.Height() / 11;

	x0 = rect.Width() - xstep * 10;//
	y0 = rect.Height() - ystep * 10;//

	CDC* dc = m_pDlg->GetDlgItem(IDC_GrayDis)->GetDC();
	dc->SelectStockObject(WHITE_BRUSH);
	dc->Rectangle(rect.left - 2, rect.top - 2, rect.right + 2, rect.bottom + 2);
	//画行列
	dc->TextOut(2, 0, "V/H");

	int y = pDoc->nHeight - point1.y;
	for (i = 0; i < 10; i++)//
	{
		str1.Format("%d", point1.x - 5 + i);//这里改5换成10
		dc->TextOut(x0 + i*xstep, 0, str1);
		str1.Format("%d", y- 5 + i);//
		dc->TextOut(0, y0 + i*ystep, str1);
	}
	////////////画出矩形中间的分割线
	dc->MoveTo(rect.left - 2, y0 - 2);
	dc->LineTo(rect.right + 2, y0 - 2);
	dc->MoveTo(x0 - 5, rect.top - 2);
	dc->LineTo(x0 - 5, rect.bottom - 2);
	CString strBits;
	int ii, jj;
	BYTE gray, r, g, b;
	for (j = 0; j < 10; j++)
	{
		jj =y - 5 + j;
		jj = jj<0 ? 0 : jj;
		jj = jj>pDoc->nHeight ? pDoc->nHeight : jj;
		//显示每一行像素
		for (i = 0; i < 10; i++)
		{
			ii = point1.x - 5 + i;
			ii<0 ? 0 : ii;
			ii>pDoc->nWidth ? pDoc->nWidth : ii;
			if (pDoc->nColorBits == 8)
			{
				gray = pDoc->lpBits[jj*pDoc->nByteWidth + ii];
			}
			else if (pDoc->nColorBits == 24)
			{
				gray = (BYTE)((pDoc->lpBits[jj*pDoc->nByteWidth + ii * 3] * 15
					+ pDoc->lpBits[jj*pDoc->nByteWidth + ii * 3 + 1] * 75
					+ pDoc->lpBits[jj*pDoc->nByteWidth + ii * 3 + 2] * 38) / 128);
			}
			strBits.Format("%d", gray);
			switch (gray / 50)
			{
			case 0:
			case 1://0--29
				r = gray; b = gray; g = gray;
				break;
			case 2://30--59
				r = 0; b = gray + 100; g = 0;
				break;
			case 3://60--79
				r = 0; g = gray + 50; b = 0;
				break;
			case 4:
			case 5://200-255
				r = gray; g = 0, b = 0;
				break;
			}
			dc->SetTextColor(RGB(r, g, b));
			dc->TextOut(x0 + i*xstep, y0 + (9 - j)*ystep, strBits);//需要改的地方，9！！！！
			cout[gray]++;
		}
	}

	ReleaseDC(dc);


	//drawPixel(point);

	m_pDlg->m_vScroll.SetScrollPos(0);
	m_pDlg->scrollinfo1.nPos = 0;
	m_pDlg->m_hScroll.SetScrollPos(0);
	m_pDlg->scrollinfo0.nPos = 0;


	//显示图像
	m_pDlg->GetDlgItem(IDC_CLICKAREA)->GetClientRect(&rect);//对话框类的接口
	CDC* pdc = m_pDlg->GetDlgItem(IDC_CLICKAREA)->GetDC();
	int xx = point1.x;
	int yy = point1.y;
	StretchDIBits(pdc->m_hDC, 0, 0, rect.Width(), rect.Height(), xx, yy, row, col,
		pDoc->lpBits, (BITMAPINFO *)(pDoc->lpBitmap), DIB_RGB_COLORS, SRCCOPY);
	ReleaseDC(pdc);

	//m_pDlg->GetDlgItem(IDC_CLICKAREA)->GetClientRect(&rect);//对话框类的接口
	//CDC* pdc = m_pDlg->GetDlgItem(IDC_CLICKAREA)->GetDC();
	//int xx = x - 15 > 0 ? x - 15 : 0;
	//xx = xx<pDoc->nWidth - 30 ? xx : pDoc->nWidth - 30;
	//int yy = y - 15>0 ? y - 15 : 0;
	//yy = yy < pDoc->nHeight - 30 ? yy : pDoc->nHeight - 30;
	//StretchDIBits(pdc->m_hDC, 0, 0, rect.Width(), rect.Height(), xx, yy, 30, 30,
	//	pDoc->lpBits, (BITMAPINFO *)(pDoc->lpBitmap), DIB_RGB_COLORS, SRCCOPY);
	//ReleaseDC(pdc);

	//绘制直方图
	m_pDlg->GetDlgItem(IDC_ZHIFANGTU)->GetClientRect(&rect);
	pdc = m_pDlg->GetDlgItem(IDC_ZHIFANGTU)->GetDC();
	pdc->SelectStockObject(WHITE_BRUSH);
	pdc->Rectangle(rect);

	CPen mPen(PS_SOLID, 0, (COLORREF)0x000000ff);

	pdc->MoveTo(5, rect.Height() - 10); //移动到点
	pdc->LineTo(5, 5);  //画线
	pdc->LineTo(3, 10);
	pdc->MoveTo(5, 5);
	pdc->LineTo(7, 10);
	pdc->MoveTo(5, rect.Height() - 10);
	pdc->LineTo(rect.Width() - 5, rect.Height() - 10);
	pdc->LineTo(rect.Width() - 10, rect.Height() - 8);
	pdc->MoveTo(rect.Width() - 5, rect.Height() - 10);
	pdc->LineTo(rect.Width() - 10, rect.Height() - 12);
	pdc->SelectObject(&mPen);
	for (i = 0; i<256; i++)
	{
		h = 5 * ((int)(cout[i] / 100.0*(rect.Height() - 15)));
		h = h>rect.Height() - 15 ? rect.Height() - 15 : h;
		pdc->MoveTo(6 + (int)(i / 256.0*(rect.Width() - 10)), rect.Height() - 10);
		pdc->LineTo(6 + (int)(i / 256.0*(rect.Width() - 10)),
			rect.Height() - 10 - h);
	}
	ReleaseDC(pdc);
	Invalidate(0);

	CView::OnLButtonUp(nFlags, point);
}

void CShowPixelView::OnLButtonDown(UINT nFlags, CPoint point)
{

	// TODO: Add your message handler code here and/or call default
	CShowPixelDoc* pDoc = GetDocument();
	b_Static = !b_Static;
	if (b_Static == TRUE)
	{
		/*pre_rect = CRect(point.x - WIDTH/2, point.y - HEIGHT/2, point.x + WIDTH/2, point.y + HEIGHT/2);
		CDC *pDC = GetDC();
		pDC->SelectStockObject(NULL_BRUSH);
		pDC->SelectStockObject(WHITE_PEN);
		pDC->Rectangle(pre_rect);
		ReleaseDC(pDC);
		point1.x = point.x;
		point1.y = pDoc->nHeight - point.y;*/
	}
	else
	{
		InvalidateRect(pre_rect);
	}
	m_bClickEmpty = TRUE;
	point1 = point;
	end_Point = point;
	::SetCapture(this->GetSafeHwnd());
	m_bCaptured = TRUE;
	CView::OnLButtonDown(nFlags, point);
}

void CShowPixelView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if (!b_Created)
	{
		m_pDlg->Create();
		m_testDlg->Create();
		CRect rect;
		m_pDlg->GetWindowRect(&rect);
		m_pDlg->MoveWindow(500, 50, rect.Width(), rect.Height());//对话框刚出来靠右显示	
		b_Created = TRUE;
	}

}

void CShowPixelView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	switch (nChar){
	case VK_UP:
		m_fxAngle++;
		Invalidate(0);
		break;
	case VK_DOWN:
		m_fxAngle--;
		Invalidate(0);
		break;
	case VK_LEFT:
		m_fzAngle++;
		Invalidate(0);
		break;
	case VK_RIGHT:
		m_fzAngle--;
		Invalidate(0);
		break;
	default:
		break;
	}
}

int CShowPixelView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	// Define pixel format
	PIXELFORMATDESCRIPTOR pfd;
	int nPixelFormat;
	memset(&pfd, NULL, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	// Set pixel format
	//CClientDC dc(this);
	if (!b_Created)
	{
		m_pDlg->Create();
		m_testDlg->Create();

		CRect rect;
		m_pDlg->GetWindowRect(&rect);
		m_pDlg->MoveWindow(600, 10, rect.Width(), rect.Height());//靠右显示
		b_Created = TRUE;
	}

	return 0;
}





void CShowPixelView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	b_Static = FALSE;
	MessageBox("double", "提示");
	CView::OnLButtonDblClk(nFlags, point);
}


void CShowPixelView::Test()
{
	MessageBox("调用成功！！");

}
