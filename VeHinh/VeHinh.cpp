// VeHinh.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "VeHinh.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HMENU hMenu;
HBRUSH hBrush;
HPEN hPen;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_VEHINH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VEHINH));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VEHINH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_VEHINH);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
   HWND hWnd = CreateWindowW(szWindowClass, TEXT("Vẽ Hình"), WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, hMenu, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int luu = -1;//luu hinh
    static int luumn = -1;
    static int luuvien = -1;
    HDC hdc;
    static int x, y, x1, y1;

    POINT sao[8];

    static POINT pt[1000];
    static int n = 0;

    static int m = 1, s = 0;
    static TCHAR text[100];
   

    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 9999, 1000, NULL);
        break;

    case WM_TIMER:
        if (s == 0 && m == 0) {
            MessageBox(NULL, TEXT("Het gio"), TEXT("Thong bao"), MB_OK | MB_ICONINFORMATION);
            KillTimer(hWnd, NULL);
        }
        if (s > 0 && s <= 59) {
            s--;
        }
        else {
            if (s == 0) {
                m--;
                s = 59;
            }
        }
        wsprintf(text, L"Thoi gian %d: %d", m, s);
        hdc = GetDC(hWnd);
        TextOut(hdc, 0, 0, text, 50);
        ReleaseDC(hWnd, hdc);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_H32771:
                luu = 0;
                break;
            case ID_H32772:
                luu = 1;
                break;
            case ID_H32773:
                luu = 2;
                break;
            case ID_M32774:
                luumn = 0;
                break;
            case ID_M32775:
                luumn = 1;
                break;
            case ID_32776:
                luuvien = 0;
                break;
            case ID_32777:
                luuvien = 1;
                break;
            case ID_H32778:
                if (MessageBox(NULL, TEXT("Bạn có muốn thoát không?"), TEXT("Thông báo"), MB_ICONQUESTION | MB_YESNO) == IDYES)
                    DestroyWindow(hWnd);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        hdc = GetDC(hWnd);
        if (luu == 2) {
            pt[n].x = x;
            pt[n].y = y;
            n++;
            SetPixel(hdc, x, y, RGB(0, 0, 0));
        }
        ReleaseDC(hWnd, hdc);
        break;
    case WM_RBUTTONDOWN:
        hdc = GetDC(hWnd);
        Polyline(hdc, pt, n);
        ReleaseDC(hWnd, hdc);
        break;
    case WM_LBUTTONUP:
        x1 = LOWORD(lParam);
        y1 = HIWORD(lParam);
        hdc = GetDC(hWnd);

        if (luu == 0) {
            if (luumn == 0) {
                hBrush = CreateSolidBrush(RGB(0, 255, 0));
                SelectObject(hdc, hBrush);
                if (luuvien == 0) {
                    hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
                    SelectObject(hdc, hPen);
                }
                else if (luuvien == 1) {
                    hPen = CreatePen(PS_SOLID, 2, RGB(64, 224, 208));
                    SelectObject(hdc, hPen);
                }
            }
            else if (luumn == 1) {
                hBrush = CreateSolidBrush(RGB(0, 0, 255));
                SelectObject(hdc, hBrush);
                if (luuvien == 0) {
                    hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
                    SelectObject(hdc, hPen);
                }
                else if (luuvien == 1) {
                    hPen = CreatePen(PS_SOLID, 2, RGB(64, 224, 208));
                    SelectObject(hdc, hPen);
                }
            }
            Rectangle(hdc, x, y, x1, y1);
        }
        if (luu == 1) {
            if (luumn == 0) {
                hBrush = CreateSolidBrush(RGB(0, 255, 0));
                SelectObject(hdc, hBrush);
                if (luuvien == 0) {
                    hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
                    SelectObject(hdc, hPen);
                }
                else if (luuvien == 1) {
                    hPen = CreatePen(PS_SOLID, 2, RGB(64, 224, 208));
                    SelectObject(hdc, hPen);
                }
            }
            else if (luumn == 1) {
                hBrush = CreateSolidBrush(RGB(0, 0, 255));
                SelectObject(hdc, hBrush);
                if (luuvien == 0) {
                    hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
                    SelectObject(hdc, hPen);
                }
                else if (luuvien == 1) {
                    hPen = CreatePen(PS_SOLID, 2, RGB(64, 224, 208));
                    SelectObject(hdc, hPen);
                }
            }
            //Hinh sao 4 canh
            sao[0].x = (x + x1) / 2;
            sao[0].y = y;
            sao[1].x = (3 * x + 5 * x1) / 8;
            sao[1].y = (5 * y + 3 * y1) / 8;
            sao[2].x = x1;
            sao[2].y = (y + y1) / 2;
            sao[3].x = (3 * x + 5 * x1) / 8;
            sao[3].y = (3 * y + 5 * y1) / 8;
            sao[4].x = (x + x1) / 2;
            sao[4].y = y1;
            sao[5].x = (5 * x + 3 * x1) / 8;
            sao[5].y = (3 * y + 5 * y1) / 8;
            sao[6].x = x;
            sao[6].y = (y + y1) / 2;
            sao[7].x = (5 * x + 3 * x1) / 8;
            sao[7].y = (5 * y + 3 * y1) / 8;
            Polygon(hdc, sao, 8);
        }
        
        ReleaseDC(hWnd, hdc);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
