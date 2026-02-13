
// Runge-KuttaDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "Runge-Kutta.h"
#include "Runge-KuttaDlg.h"
#include "afxdialogex.h"
#include "Mayatnik.h"
#include "Mayatnik-2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// диалоговое окно CRungeKuttaDlg
CRungeKuttaDlg::CRungeKuttaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RUNGE_KUTTA_DIALOG, pParent)
	, v0(7000)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRungeKuttaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, v0);
	DDV_MinMaxDouble(pDX, v0, -11200, 11200);
	DDX_Control(pDX, IDC_EDIT1, v0ctrl);
}

BEGIN_MESSAGE_MAP(CRungeKuttaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CRungeKuttaDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CRungeKuttaDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRungeKuttaDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// обработчики сообщений CRungeKuttaDlg

BOOL CRungeKuttaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	drv.Create(GetDlgItem(IDC_MAYATNIC_PICTURE)->GetSafeHwnd());
	graphX.Create(GetDlgItem(IDC_GRAPH_X)->GetSafeHwnd());
	graphX2.Create(GetDlgItem(IDC_GRAPH_X2)->GetSafeHwnd());
	graphX3.Create(GetDlgItem(IDC_GRAPH_X3)->GetSafeHwnd());
	graphX4.Create(GetDlgItem(IDC_GRAPH_X4)->GetSafeHwnd());
	graphX5.Create(GetDlgItem(IDC_GRAPH_X5)->GetSafeHwnd());
	graphX6.Create(GetDlgItem(IDC_GRAPH_X6)->GetSafeHwnd());
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CRungeKuttaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CRungeKuttaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRungeKuttaDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	//блокируем изменияемые окна
	v0ctrl.EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
	UpdateData(TRUE);

	if (IsDlgButtonChecked(IDC_RADIO1) == BST_CHECKED)
	{
		Mayatnik may(v0);//fi0,L,h,wh
		may.Start(*this);
	}
	if (IsDlgButtonChecked(IDC_RADIO2) == BST_CHECKED)
	{
		Mayatnik2 may(v0);//fi0,L,h,wh
		may.Start(*this);
	}

	//разблокируем изменияемые окна
	v0ctrl.EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
}


void CRungeKuttaDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	STOP = true;
	CDialogEx::OnOK();
}


void CRungeKuttaDlg::OnBnClickedButton2()
{
	// TODO: добавьте свой код обработчика уведомлений
	STOP = true;
}
