#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <Windows.h>
#include <windowsx.h>
#include <string>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//void DrawRect(RECT r, int Y1, int Y2, int X1, int X2, HDC hdc, LPARAM lParam, COLORREF color)
//{
//
//}

int CALLBACK  wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
/*CALLBACK - #define ��� stdcall (���������� ��� �������, ���������� ������ ����� ��� �� ����� ������� ����
 wWinMain - �������������
 HINSTANCE  hInstance - ��������� �� ������ ������������ ������, �� ���������. ����� ������.
 HINSTANCE - �� ������������ ��� ���. ��� 16 ������ ������ �������.
 PWSTR szCmdLine - ��������� �� ������ UNICOD �������� �������������� ����. �� ���� ������ ���������.
 int nCmdShow - �������� ���������� �� �� ��� ����� ������������ ���� (�������, ���������, �� ���� ����� � �.�.).
*/
{
    MSG msg{};                             // ���������, ������� �������� � ���� ���������� � ����������� (����� Windows � ����� ��� ����� ������).
    HWND hwnd{};                          // ���������� ���� ( HANDLE ����. �� ������ ���� � ������� ��������� ���������� � ����� ����).
    WNDCLASSEX wc{ sizeof(WNDCLASSEX) }; // ��� ��������� �������� �� ����� �-�� ���� (� �������� ������� �������).���. ���������� �������������.
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    //wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
    //{
    //    switch (uMsg)
    //    {
    //    case WM_DESTROY:
    //    {
    //        PostQuitMessage(EXIT_SUCCESS);
    //    }
    //    return 0;
    //    }
    //    return DefWindowProc(hWnd, uMsg, wParam, lParam); // ���������� � ������ ���� ��������� �� ��������������
    //};
    wc.lpszClassName = L"MyAppClass";
    wc.lpszMenuName = nullptr;
    wc.style = CS_VREDRAW | CS_HREDRAW;
    /*
    wc.cbClsExtra = 0; �������� �� �������������� ��������� ������ �
    wc.cbWndExtra = 0; ������ ������ ���� (��� ������ ����� ���� ���������� � ����).

    hbrBackground - ��� ���� ��������� ���������� ����� ������� ���������� ����.
    GetStockObject - ���������� GDI ������ ������� �� ����� �������� � ���� HBRUSH.

    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);     - HANDLE �������.
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);   - HANDLE ������.
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION); - HANDLE ������ (������������ ������ ����� � ��������� ����).

    wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
    - ��� ��������� �������� �� ��������� ��������� (MSG msg{};)
      ��������� 4 ������������ ��������� � ���������� LRESULT (���������).
      HWND hWnd     - ���������� ���� � �������� �������� ���������.
      UINT uMsg     - ��� ���������.
      WPARAM wParam - ��������� � �� ��������� ����������� ��� ��������� ����������.
      LPARAM lParam - ��������� � �� ��������� ����������� ��� ��������� ����������.

      wc.lpszClassName = L"MyAppClass";   - ��� ������ (�����).
      wc.lpszMenuName = nullptr;          - ��������� �� ��� ����.
      wc.style = CS_VREDRAW | CS_HREDRAW; - ����� ���� (2 ����� �� ���������)



    */

    if (!RegisterClassEx(&wc))
    {
        return EXIT_FAILURE;
    }


    if (hwnd = CreateWindow(wc.lpszClassName, L"Paint", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr); 
        hwnd == INVALID_HANDLE_VALUE)
    {
        return EXIT_FAILURE;
    }
        
    /*
     if (!RegisterClassEx(&wc)) - ����������� � ������� ������ ������ ����.
      return EXIT_FAILURE;

     if (hwnd = CreateWindow(wc.lpszClassName, L"���������!", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr ); hwnd == INVALID_HANDLE_VALUE)
      return EXIT_FAILURE;
      - �������� ������ ����.
      wc.lpszClassName    - ��� ������.
      L"���������!"       - ��������� ����.
      WS_OVERLAPPEDWINDOW - ����� ���� (����� ���������� � msdn).
      0, 0,               - X � Y ���������� ���� (������������� �� ����� ������� �����).
      600, 600,           - ������, ������.


     */
    ShowWindow(hwnd, nCmdShow); // ����� ����
    UpdateWindow(hwnd);         // ����������� ���� (��������� HANDLE)

    while (GetMessage(&msg, nullptr, 0, 0)) // ���� ��������� ���������
    {
        TranslateMessage(&msg); // ������� �������������� ��������� ���������
        DispatchMessage(&msg);  // �������  ������� ��������� � ������� ��������� �� ���������
    }

    return static_cast<int> (msg.wParam); // ������������ �������� ����� �����



    // hWnd - ������������� ����.
    // nullptr - ������� ���������.
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc; //������ �������� ����������
    PAINTSTRUCT ps; //������ ��������� ��������� ������������ ������
    LOGFONT lf;
    HFONT hFont;
    RECT r;
    HBRUSH hBrush;
    HPEN hPen;
    POINT pt;
    
    static COLORREF color = RGB(0, 0, 0);
    static bool isDraw = false;
    static int X1 = 0, Y1 = 0, X2 = 0, Y2 = 0;
    static int shape = 0;

    //���� ��������� ���������
    switch (messg)
    {
        //��������� ���������
        //case WM_PAINT:
        //{
        //    hdc = BeginPaint(hWnd, &ps);

        //    //������ ���� �����
        //    wcscpy_s(lf.lfFaceName, L"Times New Roman"); //�������� � ������ �������� ������
        //    lf.lfHeight = 20;
        //    lf.lfItalic = 1;
        //    lf.lfStrikeOut = 0;
        //    lf.lfUnderline = 0;
        //    lf.lfWidth = 10;
        //    lf.lfWeight = 40;
        //    lf.lfCharSet = DEFAULT_CHARSET; //�������� �� ���������
        //    lf.lfPitchAndFamily = DEFAULT_PITCH; //�������� �� ���������
        //    lf.lfEscapement = 0;

        //    hFont = CreateFontIndirect(&lf);
        //    SelectObject(hdc, hFont);
        //    SetTextColor(hdc, RGB(0, 0, 255));
        //    TextOut(hdc, 80, 40, L"������� ����� ���!!", 20);

        //    //������ ������� �������������
        //    r.top = 100;
        //    r.left = 180;
        //    r.right = 400;
        //    r.bottom = 300;
        //    FillRect(hdc, &r, HBRUSH(CreateSolidBrush(RGB(255, 0, 55))));

        //    //������ ������ ������
        //    hBrush = CreateSolidBrush(RGB(10, 200, 100));
        //    SelectObject(hdc, hBrush);
        //    Ellipse(hdc, 20, 100, 200, 200);

        //    //������ ����������� �������������
        //    hBrush = CreateSolidBrush(RGB(250, 200, 100));
        //    SelectObject(hdc, hBrush);
        //    hPen = CreatePen(2, 2, RGB(0, 0, 255));
        //    SelectObject(hdc, hPen);
        //    RoundRect(hdc, 20, 250, 250, 350, 15, 15);


        //    ValidateRect(hWnd, NULL);
        //    EndPaint(hWnd, &ps);
        //}
        //break;
        //case WM_PAINT:
        //{

        //    hdc = BeginPaint(hWnd, &ps);
        //    r.top = X;
        //    r.left = Y;
        //    r.right = X + 50;
        //    r.bottom = Y + 50;
        //    FillRect(hdc, &r, HBRUSH(CreateSolidBrush(RGB(255, 0, 55))));

        //    ValidateRect(hWnd, NULL);
        //    EndPaint(hWnd, &ps);

        //}
        return 0;
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

                default:
                    break;
            }
        }
        return 0;
        case WM_LBUTTONDOWN:
        {
            X1 = GET_X_LPARAM(lParam);
            Y1 = GET_Y_LPARAM(lParam);
            X2 = GET_X_LPARAM(lParam);
            Y2 = GET_Y_LPARAM(lParam);
            isDraw = true;
            //DeleteObject(hBrush);
        }
        break;
        case WM_LBUTTONUP:
        {
            isDraw = false;
        }
        break;
        case WM_MOUSEMOVE:
        {
            HDC hdc = GetDC(hWnd);
            if (isDraw)
            {
                switch (shape)
                {
                    case 0:
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
                    default:
                        break;
                }

            }

        }
        break;

            //��������� ������ - ���������� ����
        case WM_DESTROY:
        {
            PostQuitMessage(EXIT_SUCCESS); //�������� ��������� ������ � ����� 0 - ���������� ����������
        }
        return 0;


        default:
        {
            return(DefWindowProc(hWnd, messg, wParam, lParam)); //����������� ������� ���������� �� �������������
        }
    }
    return 0;
}