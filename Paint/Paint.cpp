#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <Windows.h>
#include <windowsx.h>
#include <string>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
    MoveToEx(hdc, x1, y1, NULL);
    return LineTo(hdc, x2, y2);
}

int CALLBACK  wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
    MSG msg{};
    HWND hwnd{};
    WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = L"MyAppClass";
    wc.lpszMenuName = nullptr;
    wc.style = CS_VREDRAW | CS_HREDRAW;

    if (!RegisterClassEx(&wc))
    {
        return EXIT_FAILURE;
    }


    if (hwnd = CreateWindow(wc.lpszClassName, L"Paint", WS_OVERLAPPEDWINDOW, 0, 0, 1920, 1080, nullptr, nullptr, wc.hInstance, nullptr); 
        hwnd == INVALID_HANDLE_VALUE)
    {
        return EXIT_FAILURE;
    }
        
    ShowWindow(hwnd, nCmdShow); 
    UpdateWindow(hwnd);         

    while (GetMessage(&msg, nullptr, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg); 
    }

    return static_cast<int> (msg.wParam); 
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps; 
    LOGFONT lf;
    HFONT hFont;
    RECT r;
    HBRUSH hBrush;
    HPEN hPen;
    POINT pt;

    
    static COLORREF color = RGB(0, 0, 0);
    static bool isDraw = false;
    static int X1 = 0, Y1 = 0, X2 = 0, Y2 = 0;
    static int shape = 0, line = 1, curveCount = 0, polyCount = 0;
    static POINT curveLine[256];
    static POINT poly[256];
    static wchar_t text[256];
    static HWND hEdit;


    switch (messg)
    {
        case WM_CREATE:
        {
            HWND hButtonGreen = CreateWindow(
                L"BUTTON",
                L"Green",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, 100, 50, hWnd, reinterpret_cast<HMENU>(0), nullptr, nullptr
            );
            HWND hButtonBlack = CreateWindow(
                L"BUTTON",
                L"Black",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 50, 100, 50, hWnd, reinterpret_cast<HMENU>(1), nullptr, nullptr
            );
            HWND hButtonRed = CreateWindow(
                L"BUTTON",
                L"Red",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 100, 100, 50, hWnd, reinterpret_cast<HMENU>(2), nullptr, nullptr
            );
            HWND hButtonYellow = CreateWindow(
                L"BUTTON",
                L"Yellow",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 150, 100, 50, hWnd, reinterpret_cast<HMENU>(3), nullptr, nullptr
            );
            HWND hButtonBlue = CreateWindow(
                L"BUTTON",
                L"Blue",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 200, 100, 50, hWnd, reinterpret_cast<HMENU>(4), nullptr, nullptr
            );
            HWND hButtonLine = CreateWindow(
                L"BUTTON",
                L"Line",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 300, 100, 50, hWnd, reinterpret_cast<HMENU>(5), nullptr, nullptr
            );
            HWND hButtonRect = CreateWindow(
                L"BUTTON",
                L"Rectangle",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 350, 100, 50, hWnd, reinterpret_cast<HMENU>(6), nullptr, nullptr
            );
            HWND hLineSizeS = CreateWindow(
                L"Button",
                L"Small",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 800, 100, 50, hWnd, reinterpret_cast<HMENU>(7), nullptr, nullptr
            );
            HWND hLineSizeM = CreateWindow(
                L"Button",
                L"Medium",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 850, 100, 50, hWnd, reinterpret_cast<HMENU>(8), nullptr, nullptr
            );
            HWND hLineSizeL = CreateWindow(
                L"Button",
                L"Large",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 900, 100, 50, hWnd, reinterpret_cast<HMENU>(9), nullptr, nullptr
            );
            HWND hButtonCurve = CreateWindow(
                L"BUTTON",
                L"Curve",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 400, 100, 50, hWnd, reinterpret_cast<HMENU>(10), nullptr, nullptr
            );
            HWND hButtonPolygon = CreateWindow(
                L"BUTTON",
                L"Polygon",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 450, 100, 50, hWnd, reinterpret_cast<HMENU>(11), nullptr, nullptr
            );
            HWND hButtonElipse = CreateWindow(
                L"BUTTON",
                L"Elipse",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 500, 100, 50, hWnd, reinterpret_cast<HMENU>(12), nullptr, nullptr
            );
            HWND hButtonText = CreateWindow(
                L"BUTTON",
                L"Text",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 550, 100, 50, hWnd, reinterpret_cast<HMENU>(13), nullptr, nullptr
            );
            hEdit = CreateWindow(
                L"EDIT",
                L"Text",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                0, 600, 100, 50, hWnd, reinterpret_cast<HMENU>(14), nullptr, nullptr
            );
        }
        return 0;
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case 0:
                {
                    color = RGB(55, 255, 0);
                }
                break;
                case 1:
                {
                    color = RGB(0, 0, 0);
                }
                break;
                case 2:
                {
                    color = RGB(255, 0, 55);
                }
                break;
                case 3:
                {
                    color = RGB(255, 255, 0);
                }
                break;
                case 4:
                {
                    color = RGB(55, 0, 255);
                }
                break;
                case 5:
                {
                    shape = 0;
                }
                break;
                case 6:
                {
                    shape = 1;
                }
                break;
                case 7:
                {
                    line = 1;
                }
                break;
                case 8:
                {
                    line = 5;
                }
                break;
                case 9:
                {
                    line = 10;
                }
                break;
                case 10:
                {
                    shape = 2;
                }
                break;
                case 11:
                {
                    shape = 3;
                }
                break;
                case 12:
                {
                    shape = 4;
                }
                break;
                case 13:
                {
                    shape = 5;
                }
                break;

                default:
                    break;
            }
        }
        return 0;
        case WM_RBUTTONDOWN:
        {
            if (shape == 2)
            {
                memset(curveLine, 0, sizeof(POINT) * 256);
                curveCount = 0;
            }
            if (shape == 3)
            {
                memset(poly, 0, sizeof(POINT) * 256);
                polyCount = 0;
            }
        }
        break;
        case WM_LBUTTONDOWN:
        {
            HDC hdc = GetDC(hWnd);
            X1 = GET_X_LPARAM(lParam);
            Y1 = GET_Y_LPARAM(lParam);
            X2 = GET_X_LPARAM(lParam);
            Y2 = GET_Y_LPARAM(lParam);
            isDraw = true;

            if (shape == 2)
            {
                if (curveCount > 255)
                {
                    curveCount--;
                }
                curveLine[curveCount].x = GET_X_LPARAM(lParam);
                curveLine[curveCount].y = GET_Y_LPARAM(lParam);
                curveCount++;
                HPEN hPen2 = CreatePen(PS_SOLID, line, color);
                SelectObject(hdc, hPen2);
                for (int i = 0; i < curveCount - 1; i++)
                {
                    Line(hdc, curveLine[i].x, curveLine[i].y, curveLine[i + 1].x, curveLine[i + 1].y);
                }
                DeleteObject(hPen2);
            }
            if (shape == 3)
            {
                if (polyCount > 255)
                {
                    polyCount--;
                }
                poly[polyCount].x = GET_X_LPARAM(lParam);
                poly[polyCount].y = GET_Y_LPARAM(lParam);
                polyCount++;
                HBRUSH hBrush = CreateSolidBrush(color);
                SelectObject(hdc, hBrush);
                Polygon(hdc, poly, polyCount);
                DeleteObject(hBrush);
            }
            if (shape == 5)
            {
            
            }
         
        }
        break;
        case WM_LBUTTONUP:
        {
            isDraw = false;
            HDC hdc = GetDC(hWnd);
            switch (shape)
            {
                case 0:
                {
                    HPEN hPen2 = CreatePen(PS_SOLID, line, color); 
                    SelectObject(hdc, hPen2); 

                    Line(hdc, X1, Y1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

                    DeleteObject(hPen2);
                }
                break;
            }
        }
        break;
        case WM_MOUSEMOVE:
        {
            HDC hdc = GetDC(hWnd);
            if (isDraw)
            {
                switch (shape)
                {
                    case 1:
                    {
                        r.top = Y1;
                        r.left = X1;
                        r.right = X2;
                        r.bottom = Y2;
                        HBRUSH hBrush1 = CreateSolidBrush(RGB(255, 255, 255));
                        FillRect(hdc, &r, hBrush1);
                        DeleteObject(hBrush1);

                        X2 = GET_X_LPARAM(lParam);
                        Y2 = GET_Y_LPARAM(lParam);

                        r.top = Y1;
                        r.left = X1;
                        r.right = X2;
                        r.bottom = Y2;
                        HBRUSH hBrush2 = CreateSolidBrush(color);
                        FillRect(hdc, &r, hBrush2);
                        DeleteObject(hBrush2);
                    }
                    break;
                    case 4:
                    {
                        HPEN hPen2 = CreatePen(PS_NULL, line, RGB(255, 255, 255));
                        SelectObject(hdc, hPen2);
                        Ellipse(hdc, X1, Y1, X2, Y2);
                        DeleteObject(hPen2);

                        X2 = GET_X_LPARAM(lParam);
                        Y2 = GET_Y_LPARAM(lParam);

                        HBRUSH hBrush2 = CreateSolidBrush(color);
                        SelectObject(hdc, hBrush2);
                        Ellipse(hdc, X1, Y1, X2, Y2);
                        DeleteObject(hBrush2);
                    }
                    break;
                    case 5:
                    {
                        wcscpy_s(lf.lfFaceName, L"Times New Roman");
                        X2 = GET_X_LPARAM(lParam);
                        Y2 = GET_Y_LPARAM(lParam);
                        lf.lfHeight = Y2-Y1;
                        lf.lfStrikeOut = 0;
                        lf.lfUnderline = 0;
                        lf.lfWidth = X1-X2;
                        lf.lfWeight = 40;
                        lf.lfCharSet = DEFAULT_CHARSET;
                        lf.lfPitchAndFamily = DEFAULT_PITCH;
                        lf.lfEscapement = 0;

                        hFont = CreateFontIndirect(&lf);

                        SelectObject(hdc, hFont);
                        SetTextColor(hdc, color);
                        int textLen = GetWindowTextLengthA(hEdit) + 1;
                        TCHAR buff[1024];
                        GetWindowText(hEdit, buff, textLen);
                        TextOut(hdc, X1, Y1, buff, textLen);
                    }
                    break;
                    default:
                        break;
                }

            }

        }
        break;
        case WM_DESTROY:
        {
            PostQuitMessage(EXIT_SUCCESS); 
        }
        return 0;


        default:
        {
            return(DefWindowProc(hWnd, messg, wParam, lParam)); 
        }
    }
    return 0;
}