#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib, "Gdiplus.lib")

VOID OnPaint(HDC hdc)
{
     //lines
     HPEN hPen;
     hPen = CreatePen(PS_DASH, 3, 0x00FF7F7F);
     Graphics graphics(hdc);
     Pen pen(Color(255, 255, 0, 255));
     graphics.DrawLine(&pen, 0, 0, 1000, 0);

     //M
     //cloud 

 
         MoveToEx(hdc, 100, 100, NULL);
          LineTo(hdc, 100, 200);
          MoveToEx(hdc, 100, 100, NULL);
          LineTo(hdc, 150, 150);
          MoveToEx(hdc, 150, 150, NULL);
          LineTo(hdc, 200, 100);
          MoveToEx(hdc, 200, 100, NULL);
          LineTo(hdc, 200, 200);
     
     //polyline A
     SelectObject(hdc, hPen);
     MoveToEx(hdc, 250, 200, NULL);
     POINT arr[4];

          arr[0].x = 270;
          arr[0].y = 100;

          arr[1].x = 290;
          arr[1].y = 200;

          arr[2].x = 280;
          arr[2].y = 150;

          arr[3].x = 260;
          arr[3].y = 150;
     
     PolylineTo(hdc, arr, 4);

     RoundRect(hdc, 350, 350, 400, 400, 10, 10);
     Ellipse(hdc, 350, 350, 400, 400);
     Chord(hdc, 350, 350, 400, 400, 350, 350, 400, 400);
     SelectObject(hdc, GetStockObject(BLACK_BRUSH));
     Pie(hdc, 410, 350, 460, 400, 400, 350, 500, 100);

     DeleteObject(hPen);
     SelectObject(hdc, GetStockObject(BLACK_PEN));
     SelectObject(hdc, GetStockObject(NULL_BRUSH));
     //arc
     Arc(hdc, 500, 100, 600, 200, 500, 100, 600, 200);

     Rectangle(hdc, 50, 50, 310, 255);

     

}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int iCmdShow)
{
     HWND hWnd;
     MSG msg;
     WNDCLASS wndClass;
     GdiplusStartupInput gdiplusStartupInput;
     ULONG_PTR gdiplusToken;

     GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

     wndClass.style = CS_HREDRAW | CS_VREDRAW;
     wndClass.lpfnWndProc = WndProc;
     wndClass.cbClsExtra = 0;
     wndClass.cbWndExtra = 0;
     wndClass.hInstance = hInstance;
     wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
     wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
     wndClass.hbrBackground = (HBRUSH)CreateSolidBrush(0xFF7F7F);
     wndClass.lpszMenuName = NULL;
     wndClass.lpszClassName = TEXT("DesenareLinii");

     RegisterClass(&wndClass);
    

     hWnd = CreateWindow(
          TEXT("DesenareLinii"),
          TEXT("desen linii"),
          WS_OVERLAPPEDWINDOW,
          CW_USEDEFAULT, CW_USEDEFAULT,
          350, 510,
          NULL,
          NULL,
          hInstance,
          NULL,
          );
     if (!hWnd)
     {
          MessageBox(NULL,
               TEXT("call to createwindow failed"),
               TEXT("DesenareLinii"),
               NULL);
          return 1;
     }

     ShowWindow(hWnd, iCmdShow);
     UpdateWindow(hWnd);

     while (GetMessage(&msg, NULL, 0, 0))
     {
          TranslateMessage(&msg);
          DispatchMessage(&msg);
     }
     GdiplusShutdown(gdiplusToken);
     return msg.wParam;
} // WinMain


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     PAINTSTRUCT ps;
     HDC hdc, hCompatibleDC;
     HANDLE hOldBitmap, hBitmap;
     BITMAP Bitmap;
     


     TCHAR greeting[] = _T("Elaborat de studentul Ghelas Marc, TI-141.");
     hBitmap = (HBITMAP)LoadImage(NULL, _T("E:\\example.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
 
     //hLocalDC = CreateCompatibleDC(NULL);
     switch (message)
     {
     
     case WM_PAINT:
          RECT rect, textrect;
          INT j, k;
          j = 330;
          k = 0;

          GetClientRect(hWnd, &rect);
          hdc = BeginPaint(hWnd, &ps);
          HBRUSH hBrush;
         // hBrush = CreateBrush( 0x00FF7F7F);

        //  DrawText(hdc, greeting, _tcslen(greeting), &textrect, DT_CALCRECT);
         // rect.top = rect.bottom / 2;
          DrawText(hdc, greeting, _tcslen(greeting), &rect, DT_CENTER);
          SelectObject(hdc, GetStockObject(BLACK_BRUSH));
          RoundRect(hdc, rect.left + 30, rect.top + 30, rect.right - 30, rect.bottom - 30, 30, 30);
          SelectObject(hdc, GetStockObject(WHITE_BRUSH));

          Rectangle(hdc, rect.left + 35, rect.top + 80, rect.right - 35, rect.bottom - 80);
          Ellipse(hdc,  150, rect.top + 400, rect.right - 150,  430);
          RoundRect(hdc, 160, rect.top + 410, rect.right - 160, 420, 3, 3);
          RoundRect(hdc,  235,  27, rect.right - 45, 31, 10, 10);
 
             //  hBitmap = (HBITMAP)LoadImage(NULL, _T("E:\\example.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
          
          GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
          hCompatibleDC = CreateCompatibleDC(hdc);
          hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
          if (hCompatibleDC){
               for (int i = 0; i < 240; i++){
                    StretchBlt(hdc, 45, 85, rect.right - j--, rect.bottom - 170,
                         hCompatibleDC, 0, 0, Bitmap.bmWidth,
                         Bitmap.bmHeight, SRCCOPY);
                    Sleep(1);
               }
          }
          SelectObject(hCompatibleDC, hOldBitmap);
         
          DeleteObject(hBitmap);
          
          DeleteDC(hCompatibleDC);
         // OnPaint(hdc);
          
          EndPaint(hWnd, &ps);
          return 0;
     case WM_DESTROY:
          PostQuitMessage(0);
          return 0;
     default:
          return DefWindowProc(hWnd, message, wParam, lParam);
          
     }
} //WndProc

