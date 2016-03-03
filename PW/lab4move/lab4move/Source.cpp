#include <string.h>
#include <tchar.h>
#include <objidl.h>
#include <gdiplus.h>
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
using namespace Gdiplus;
#pragma comment (lib, "Gdiplus.lib")


struct
{
     int x, y;
} pos = { 0 };

struct
{
     float x, y;
} stretch = { 1 };

struct
{
     int x;
} rotate = { 0 };
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
     wndClass.hbrBackground = (HBRUSH)CreateSolidBrush(0xFFFFFF);
     wndClass.lpszMenuName = NULL;
     wndClass.lpszClassName = TEXT("Lab4");

     RegisterClass(&wndClass);


     hWnd = CreateWindow(
          TEXT("Lab4"),
          TEXT("Laborator nr. 4"),
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
     RECT rect;
     int i=0;
     
     GetClientRect(hWnd, &rect);
     int j, k;


     TCHAR greeting[] = _T("Elaborat de studentul Ghelas Marc, TI-141.");
     hBitmap = (HBITMAP)LoadImage(NULL, _T("E:\\example.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

     //hLocalDC = CreateCompatibleDC(NULL);
     switch (message)
     {
     case WM_PAINT:
     {
                       GetClientRect(hWnd, &rect);
                       hdc = BeginPaint(hWnd, &ps);
                       HBRUSH hBrush;
                       
                            Graphics graphics(hdc);
                            ImageAttributes IAttr;
                            
                            RectF destination(45, 85, rect.right - 85, rect.bottom - 170);
                            Color colorRGB(0, 0, 0);
                            
                            IAttr.SetWrapMode(WrapModeClamp, colorRGB);
                            Image image(L"E:\\example.BMP");
                            
                            graphics.TranslateTransform(pos.x+45, pos.y+85);
                            graphics.RotateTransform(rotate.x);
                            graphics.TranslateTransform(-45.0f, -85.0f);
                            graphics.ScaleTransform(stretch.x, stretch.y);
                            graphics.DrawImage(&image, destination, 0, 0, 290, 450, UnitPixel, &IAttr);
                           
                            
                            
                            

                       //Graphics graphics(hdc);
                       //
                       //Pen pen(Color(255, 0, 0, 255));
                       //
                       //Matrix matrix;
                       //matrix.Translate(250.0f, 200.0f);
                       //matrix.RotateAt(rotate.x, PointF(250.0f, 200.0f), MatrixOrderAppend);
                       //
                       //graphics.SetTransform(&matrix);
                       //graphics.DrawRectangle(&pen, -40, -20, 80, 40);
                          

                       //GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
                       //hCompatibleDC = CreateCompatibleDC(hdc);
                       //hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
                       //if (hCompatibleDC){
                       //
                       //     StretchBlt(hdc, pos.x + 45, pos.y + 85, stretch.x - 85, stretch.y - 170,
                       //          hCompatibleDC, 0, 0, Bitmap.bmWidth,
                       //          Bitmap.bmHeight, SRCCOPY);
                       //
                       //
                       //}
                       //
                       //SelectObject(hCompatibleDC, hOldBitmap);
                       //DeleteObject(hBitmap);
                       //DeleteDC(hCompatibleDC);
                       EndPaint(hWnd, &ps);
                       break;
     }
     case WM_KEYDOWN:
     
                         switch (wParam)
                         {
                         case VK_RIGHT:
                              pos.x+=5;
                              InvalidateRect(hWnd, NULL, TRUE);
                              break;         
                         case VK_LEFT:       
                              pos.x-=5;       
                              i++;
                              InvalidateRect(hWnd, NULL, TRUE);
                              break;        
                         case VK_UP:        
                              pos.y-=5;      
                              InvalidateRect(hWnd, NULL, TRUE);
                              break;         
                         case VK_DOWN:       
                              pos.y+=5;       
                              InvalidateRect(hWnd, NULL, TRUE);
                              break;
                         case 0x41:
                              stretch.x+=0.1f;
                              InvalidateRect(hWnd, NULL, TRUE);
                              break;
                         case 0x5A:
                             // i++;
                         case 'z':
                              stretch.y+=0.1f;
                              InvalidateRect(hWnd, NULL, TRUE);
                              break;
                         case 0x53:
                              stretch.x-=0.1f;
                              InvalidateRect(hWnd, NULL, TRUE);
                              break;
                         case 0x58:
                              stretch.y-=0.1f;
                              InvalidateRect(hWnd, NULL, TRUE);
                              break;
                         case 0x31:
                              rotate.x++;
                              InvalidateRect(hWnd, NULL, TRUE);
                              
                              break;
                         case 0x32:
                              rotate.x--;
                              InvalidateRect(hWnd, NULL, TRUE);
                              break;
                         }

                         break;
      

     case WM_DESTROY:
     {
          PostQuitMessage(0);
     }
          return 0;
     default:
          return DefWindowProc(hWnd, message, wParam, lParam);

     }
} //WndProc    

