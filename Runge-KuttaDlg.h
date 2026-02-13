
// Runge-KuttaDlg.h : файл заголовка
//

#pragma once
#include"Drawer.h"


// диалоговое окно CRungeKuttaDlg
class CRungeKuttaDlg : public CDialogEx
{
	// Создание
public:
	CRungeKuttaDlg(CWnd* pParent = NULL);	// стандартный конструктор

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RUNGE_KUTTA_DIALOG };
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


	// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	Drawer drv;
	Drawer graphX;
	Drawer graphX2;
	Drawer graphX3;
	Drawer graphX4;
	Drawer graphX5;
	Drawer graphX6;

	bool STOP;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	// начальный угол отклонения
	double v0;
	CEdit v0ctrl;

	afx_msg void OnStnClickedGraphX6();
};
