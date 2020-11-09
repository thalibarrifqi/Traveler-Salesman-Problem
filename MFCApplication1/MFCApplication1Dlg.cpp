
// MFCApplication1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
	, m_iter(0)
	, m_kota(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iter);
	DDX_Text(pDX, IDC_EDIT2, m_kota);
	DDX_Control(pDX, IDC_PIC, m_pic);
	DDX_Control(pDX, IDC_START, m_tampil);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CMFCApplication1Dlg::OnBnClickedStart)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

typedef struct {
	int posX;
	int posY;
}Shape;

Shape elips[50];
int sizeElips = 1;
float x[100], y[100];
int s[100], sOpt[100], nKota;
float e, eOpt;
float dx, dy, d;
float hitungEnergi();

void BangkitkanDataKota() {
	srand(time(NULL));

	for (int i = 0; i < nKota; i++) {
		
		x[i] = (float)(10 * rand() / RAND_MAX);
		y[i] = (float)(10 * rand() / RAND_MAX);
		
		/*if (i > 20){
				x[i] = rand() % 100 + 10;
				y[i] = rand() % 100 + 10;
		}
		else{
				x[i] = rand() % 270;
				y[i] = rand() % 290;
		}*/
		x[i] = rand() % 300;
		y[i] = rand() % 300;
			
	}
}

void BangkitkanStateAwal() {
	for (int i = 0; i < nKota; i++) 
		s[i] = i;
	hitungEnergi();
}

void StateOptimal() {
	for (int i = 0; i < nKota; i++) 
		sOpt[i] = s[i];
	eOpt = e;
}

int akumulasi = 0;
void TampilkanState() {
	cout << akumulasi << " - ";
	for (int i = 0; i < nKota; i++) cout << sOpt[i] << " ";
	cout << " energi = " << eOpt << endl;
	akumulasi++;
}

float hitungEnergi() {
	float jarak = 0;
	int i, j;
	for (i = 0; i < nKota - 1; i++) {
		/*
		dx = sqrt(x[s[i]] - x[s[i + 1]]);
		dy = sqrt(y[s[i]] - y[s[i + 1]]);
		*/

		dx = (x[s[i]] - x[s[i + 1]]) * (x[s[i]] - x[s[i + 1]]);
		dy = (y[s[i]] - y[s[i + 1]]) * (y[s[i]] - y[s[i + 1]]);

		d = sqrt(dx + dy);
		jarak = jarak + d;
		//cout << jarak << endl;
	}
	/*
	dx = sqrt(x[s[nKota - 1]] - x[s[0]]);
	dy = sqrt(y[s[nKota - 1]] - y[s[0]]);
	*/
	dx = (x[s[nKota - 1]] - x[s[0]]) * (x[s[nKota - 1]] - x[s[0]]);
	dy = (y[s[nKota - 1]] - y[s[0]]) * (y[s[nKota - 1]] - y[s[0]]);
	d = sqrt(dx + dy);
	jarak = jarak + d;
	e = jarak;
	return jarak;
}

int k1, k2;
void UpdateState() {
	int k1, k2, i;

	for (i = 0; i < nKota; i++) s[i] = sOpt[i];
	k1 = int(nKota*(float)rand() / RAND_MAX);
	k2 = int((nKota - k1)*(float)rand() / RAND_MAX) + k1;
	for (i = k1; i <= k2; i++) {
		s[i] = sOpt[k2 + k1 - i];
	}
	hitungEnergi();

}
int i, maxIter;

/*void jalan()
{
	float p, To, Tn, T = 0.2;
	To = 0.1; Tn = 0.0001;
	BangkitkanDataKota();
	BangkitkanStateAwal();
	StateOptimal();
	TampilkanState();
	for (i = 0; i < maxIter; i++) {
		UpdateState();
		p = rand();
		if (p < exp(-(e - eOpt) / T)) StateOptimal();
		TampilkanState();
		T = To*(float)pow(Tn / To, i / nKota);
	}
	//m_status.Format("Player 1 mendapat tangga. Poin + 35 . Poin sekarang : %d", m_player1);
}*/

int counter = 0;
int CekSama(int jml)
{
	int tmp = 0;
	int stat = 0;
	for (int j = 0; j < jml; j++)
	for (int k = 0; k < jml; k++)
	{
		if (elips[j].posX == elips[k].posX && elips[j].posY == elips[k].posY);
		{
			tmp = elips[k].posX;
			elips[k].posX = elips[k].posY;
			elips[k].posY = tmp;
		}
	}

	return stat;
}


void CMFCApplication1Dlg::OnBnClickedStart()
{
	int tmp_acakX = 0;
	int tmp_acakY = 0;
	char cStr[50];
	char cpoint1[50], cpoint2[50];
	// TODO: Add your control notification handler code here
	/*CDC* pDc = m_pic.GetDC();
	CDC dcMem;
	CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
	CPen* poldPen = pDc->SelectObject(&pen);

	CDC* pDc1 = m_pic.GetDC();
	CDC dcMem1;
	CPen pen1(PS_SOLID, 4, RGB(255, 0, 255));
	CPen* poldPen1 = pDc1->SelectObject(&pen1);

	CDC* pDc2 = m_pic.GetDC();
	CDC dcMem2;
	CPen pen2(PS_SOLID, 1, RGB(0, 255, 0));
	CPen* poldPen2 = pDc2->SelectObject(&pen2);*/

	/*CDC* pDC = m_pic.GetDC();
	CDC dcMem;
	CPen pen(PS_SOLID, 0, RGB(255, 255, 255));
	CPen* pOldPen = pDC->SelectObject(&pen);

	CDC* pDC1 = m_pic.GetDC();
	CDC dcMem1;
	CPen pen1(PS_SOLID, 5, RGB(0, 0, 255));
	CPen* pOldPen1 = pDC1->SelectObject(&pen1);*/

	CDC* pDc = m_pic.GetDC();
	CDC dcMemm;
	CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen* pOldPen = pDc->SelectObject(&pen);

	CDC* pDc1 = m_pic.GetDC();
	CDC dcMem1;
	CPen pen1(PS_SOLID, 3, RGB(0, 0, 255));
	CPen* pOldPen1 = pDc1->SelectObject(&pen1);

	CDC* pDc2 = m_pic.GetDC();
	CDC dcMem2;
	CPen pen2(PS_SOLID, 2, RGB(255, 0, 0));
	CPen* pOldPen2 = pDc2->SelectObject(&pen2);

	CDC* pDc3 = m_pic.GetDC();
	CDC dcMem3;
	CPen pen3(PS_SOLID, 3, RGB(200, 200, 255));
	CPen* pOldPen3 = pDc3->SelectObject(&pen3);

	pDc->Rectangle(2, 2, 327, 300);
	UpdateData(TRUE);
	nKota = m_kota;
	UpdateData(TRUE);
	maxIter = m_iter;
	BangkitkanDataKota();

	for (int i = 0; i < m_kota; i++)
	{

		tmp_acakX = x[i];
		tmp_acakY = y[i];

		k1 = tmp_acakX;
		k2 = tmp_acakY;

		elips[i].posX = x[i];
		elips[i].posY = y[i];
	}

	while (CekSama(m_kota) != 0)
	{
		CekSama(m_kota);
	}
	
	// Rectangle (koordinatx, koordinaty, lebarRec, tinggiRec)
	// Lingkaran (koordinatx1, koordinaty1, koordinatx2, koordinaty2)
	// pDc1->Ellipse(m+30, 30, m+50, 50);
	// pDc1->Rectangle(2, 2, 327, 300);
	// pDc1->Ellipse(x[i], y[i], x[i] + 5, y[i] + 5);
	// pDc2->LineTo(x[i], y[i]);
	//TampilkanState();

	for (int i = 0; i < m_kota; i++)
	{
		//if (i % 2){
			pDc1->Ellipse((elips[i].posX * sizeElips) + 5, (elips[i].posY * sizeElips) + 5,
				(elips[i].posX * sizeElips) - sizeElips, (elips[i].posY * sizeElips) - sizeElips);
		//}
		/*else{
			pDc1->Rectangle((elips[i].posX * sizeElips) + 5, (elips[i].posY * sizeElips) + 5,
				(elips[i].posX * sizeElips) - sizeElips, (elips[i].posY * sizeElips) - sizeElips);
		}*/
	}

	int i;
	float p, To, Tn, T = 0.2;
	To = 0.1; Tn = 0.0001;
	BangkitkanStateAwal();
	StateOptimal();
	for (i = 0; i < m_iter; i++){
		UpdateState();
		p = rand();
		if (p < exp (-(e - eOpt) / T))
			StateOptimal();
		//TampilkanState();
		T = To*(float)pow(Tn / To, i / m_kota);

		pDc1->Rectangle(1, 1, 100, 100);
		pDc3->Rectangle(1, 1, 327, 300);
		
		for (int i = 0; i < m_kota; i++)
		{
			pDc1->Ellipse((elips[i].posX * sizeElips) + 5, (elips[i].posY * sizeElips) + 5,
					(elips[i].posX * sizeElips) - sizeElips, (elips[i].posY * sizeElips) - sizeElips);
		
		}
		
		for (int i = 0; i < m_kota; i++)
		{
			//input Sudah masuk
			if (i != (m_kota - 1))
			{
				pDc2->MoveTo((elips[sOpt[i]].posX * sizeElips) - sizeElips / 2, 
					(elips[sOpt[i]].posY * sizeElips) - sizeElips / 2);
				pDc2->LineTo((elips[sOpt[i + 1]].posX * sizeElips) - sizeElips / 2, 
					(elips[sOpt[i + 1]].posY * sizeElips) - sizeElips / 2);
			}
			else
			{
				pDc2->MoveTo((elips[sOpt[i - 1]].posX * sizeElips) - sizeElips / 2, 
					(elips[sOpt[i - 1]].posY * sizeElips) - sizeElips / 2);
				pDc2->LineTo((elips[sOpt[i]].posX * sizeElips) - sizeElips / 2, 
					(elips[sOpt[i]].posY * sizeElips) - sizeElips / 2);
			}
			if (i == m_kota - 1)
			{
				pDc2->MoveTo((elips[sOpt[m_kota - 1]].posX * sizeElips) - sizeElips / 2, 
					(elips[sOpt[m_kota - 1]].posY * sizeElips) - sizeElips / 2);
				pDc2->LineTo((elips[sOpt[0]].posX * sizeElips) - sizeElips / 2, 
					(elips[sOpt[0]].posY * sizeElips) - sizeElips / 2);
			}
		}
		Sleep(1);
	}
}