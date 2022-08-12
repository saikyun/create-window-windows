#include <windows.h>
#include <stdio.h>

HINSTANCE hinst;

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_DESTROY:
      PostQuitMessage(WM_QUIT);
      break;

    case WM_PAINT:
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);

      FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+2));

      EndPaint(hwnd, &ps);
      return 0;

    default:
      return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }

  return 0;
}

BOOL InitApplication(HINSTANCE hinstance) {
  WNDCLASSEX wcx;

  wcx.cbSize = sizeof(wcx);
  wcx.style = CS_HREDRAW | CS_VREDRAW;
  wcx.lpfnWndProc = MainWndProc;
  wcx.cbClsExtra = 0;
  wcx.cbWndExtra = 0;
  wcx.hInstance = hinstance;
  wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcx.hbrBackground = GetStockObject(BLACK_BRUSH);
  wcx.lpszMenuName = "MainMenu";
  wcx.lpszClassName = "MainWClass";
  wcx.hIconSm = LoadImage(hinstance, MAKEINTRESOURCE(5), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON),
GetSystemMetrics(SM_CYSMICON),
LR_DEFAULTCOLOR);

  return RegisterClassEx(&wcx);
}

BOOL InitInstance(HINSTANCE hinstance, int nCmdShow) {
  HWND hwnd;

  hinst = hinstance;

  hwnd = CreateWindow(
    "MainWClass",
    "Sample",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    (HWND) NULL,
    (HMENU) NULL,
    hinstance,
    (LPVOID) NULL);

  if (!hwnd) return FALSE;

  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);
  return TRUE;
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  MSG msg;

  if (!InitApplication(hinstance)) return FALSE;
  if (!InitInstance(hinstance, nCmdShow)) return FALSE;

  BOOL fGotMessage;
  while ((fGotMessage = GetMessage(&msg, (HWND) NULL, 0, 0)) != 0 && fGotMessage != -1) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return msg.wParam;
    UNREFERENCED_PARAMETER(lpCmdLine);
}