
// ScrollBarDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScrollBarDemo.h"
#include "ScrollBarDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CScrollBarDemoDlg 对话框



CScrollBarDemoDlg::CScrollBarDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SCROLLBARDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScrollBarDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR, m_scroll);
}

BEGIN_MESSAGE_MAP(CScrollBarDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CScrollBarDemoDlg 消息处理程序

BOOL CScrollBarDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SCROLLINFO sinfo = {};
	sinfo.cbSize = sizeof(SCROLLINFO);
	sinfo.fMask = SIF_RANGE | SIF_PAGE;
	sinfo.nMin = 0;
	sinfo.nMax = 100;
	sinfo.nPage = 10;
	m_scroll.SetScrollInfo(&sinfo);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CScrollBarDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CScrollBarDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CScrollBarDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//MFC滚动条demo
//在 initDlg中初始、并设置滚动条信息。
//nPos操作滚动条的pos
void CScrollBarDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//
	SCROLLINFO sinfo = {};
	pScrollBar->GetScrollInfo(&sinfo);

	int newPos = sinfo.nPos;
	switch (nSBCode)
	{
	case SB_THUMBTRACK:	//用户拖动滚动条
		newPos = nPos;
		break;
	case SB_LINELEFT:	//左边的按钮
		newPos -= 1;
		break;
	case SB_LINERIGHT:	//右边的按钮
		newPos += 1;
		break;
	case SB_PAGELEFT:	//按页滚动
		newPos -= 10;
		break;
	case SB_PAGERIGHT:	//按页滚动
		newPos += 10;
		break;
	default:
		break;
	}

	if (newPos > sinfo.nMax) newPos = sinfo.nMax;
	if (newPos < sinfo.nMin) newPos = sinfo.nMin;
		
	pScrollBar->SetScrollPos(newPos);//这句话直接对SCROLLINFO.nPos进行设置
	//有了newPos，之后是你真正要弄的逻辑了

	CString str;
	str.Format(L"当前位置：%d", newPos);
	SetDlgItemTextW(IDC_STATIC_SBINDEX, str);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
