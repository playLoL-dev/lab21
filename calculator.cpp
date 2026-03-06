#include <windows.h>
#include <stdio.h>

#define ID_BTN_ADD 101
#define ID_BTN_SUB 102
#define ID_BTN_MUL 103
#define ID_BTN_DIV 104

HWND t1, t2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        
        case WM_CREATE: {
            CreateWindow("STATIC", "Please input two numbers", 
                WS_VISIBLE | WS_CHILD | SS_CENTER, 
                20, 15, 200, 25, hwnd, NULL, NULL, NULL);

            t1 = CreateWindow("EDIT", "", 
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 
                20, 45, 200, 25, hwnd, NULL, NULL, NULL);

            t2 = CreateWindow("EDIT", "", 
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 
                20, 80, 200, 25, hwnd, NULL, NULL, NULL);

            CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 45, 120, 30, 30, hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 85, 120, 30, 30, hwnd, (HMENU)ID_BTN_SUB, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 125, 120, 30, 30, hwnd, (HMENU)ID_BTN_MUL, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 165, 120, 30, 30, hwnd, (HMENU)ID_BTN_DIV, NULL, NULL);
            break;
        }

        case WM_COMMAND: {
            if (LOWORD(wParam) >= 101 && LOWORD(wParam) <= 104) {
                char val1[100], val2[100], resStr[100];
                float num1, num2, result = 0;
                GetWindowText(t1, val1, 100);
                GetWindowText(t2, val2, 100);
                num1 = atof(val1);
                num2 = atof(val2);

                switch(LOWORD(wParam)) {
                    case ID_BTN_ADD: result = num1 + num2; break;
                    case ID_BTN_SUB: result = num1 - num2; break;
                    case ID_BTN_MUL: result = num1 * num2; break;
                    case ID_BTN_DIV: result = num1 / num2; break;
                }

                sprintf(resStr, "%.6f", result);
                MessageBox(hwnd, resStr, "Result", MB_OK);
            }
            break;
        }

        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wParam;
            SetBkColor(hdcStatic, RGB(255, 255, 255));
            SetTextColor(hdcStatic, RGB(0, 0, 0));
            return (INT_PTR)CreateSolidBrush(RGB(255, 255, 255));
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc, 0, sizeof(wc));
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    
    wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 0)); 
    wc.lpszClassName = "WindowClass";
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "My Calculator", 
        WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, 
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}