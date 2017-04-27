
// library.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "library.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ClibraryApp

BEGIN_MESSAGE_MAP(ClibraryApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &ClibraryApp::OnAppAbout)
END_MESSAGE_MAP()


// ClibraryApp 构造

ClibraryApp::ClibraryApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("library.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 ClibraryApp 对象

ClibraryApp theApp;


// ClibraryApp 初始化

BOOL ClibraryApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("图书管理系统_张耀心"));


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 若要创建主窗口，此代码将创建新的框架窗口
	// 对象，然后将其设置为应用程序的主窗口对象
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 创建并加载框架及其资源
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);





	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int ClibraryApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// ClibraryApp 消息处理程序


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

// 用于运行对话框的应用程序命令
void ClibraryApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// ClibraryApp 自定义加载/保存方法

void ClibraryApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void ClibraryApp::LoadCustomState()
{
}

void ClibraryApp::SaveCustomState()
{
}

// ClibraryApp 消息处理程序

#include "book.h"
void showDetail(CListBox & m_listResult, CListBox & m_listDetail)
{
	Cbook m_bookSet;
	// titles
	CString  title[9];
	title[0] = "书号：		";
	title[1] = "类别：		";
	title[2] = "书名：		";
	title[3] = "出版社：		";
	title[4] = "年份：		";
	title[5] = "作者：		";
	title[6] = "价格：		";
	title[7] = "藏书总量：	";
	title[8] = "库存：		";

	m_listDetail.ResetContent();
	int curSel = m_listResult.GetCurSel(); // get current select item in listbox
	m_bookSet.SetAbsolutePosition(curSel + 1);
	// since the data types are different, I have no better idea to deal with them
	static CString tempStr;
	tempStr += title[0];
	tempStr += m_bookSet.m_id;
	m_listDetail.InsertString(0, tempStr);
	tempStr.Empty();
	tempStr += title[1];
	tempStr += m_bookSet.m_category;
	m_listDetail.InsertString(1, tempStr);
	tempStr.Empty();
	tempStr += title[2];
	tempStr += m_bookSet.m_name;
	m_listDetail.InsertString(2, tempStr);
	tempStr.Empty();
	tempStr += title[3];
	tempStr += m_bookSet.m_press;
	m_listDetail.InsertString(3, tempStr);
	tempStr.Empty();
	tempStr += title[4];
	CString year;
	year.Format(_T("%ld"), m_bookSet.m_year);
	tempStr += year;
	m_listDetail.InsertString(4, tempStr);
	tempStr.Empty();
	tempStr += title[5];
	tempStr += m_bookSet.m_author;
	m_listDetail.InsertString(5, tempStr);
	tempStr.Empty();
	tempStr += title[6];
	CString price;
	price.Format(_T("%.2f"), m_bookSet.m_price);
	tempStr += price;
	m_listDetail.InsertString(6, tempStr);
	tempStr.Empty();
	tempStr += title[7];
	CString total;
	total.Format(_T("%ld"), m_bookSet.m_total);
	tempStr += total;
	m_listDetail.InsertString(7, tempStr);
	tempStr.Empty();
	tempStr += title[8];
	CString stock;
	stock.Format(_T("%ld"), m_bookSet.m_stock);
	tempStr += stock;
	m_listDetail.InsertString(8, tempStr);
}
