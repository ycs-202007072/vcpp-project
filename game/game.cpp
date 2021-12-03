// game.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "game.h"

#include <stdlib.h>
#include <time.h> 

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAME));

    MSG msg;

    // 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, L"킹글킹글", WS_OVERLAPPEDWINDOW,
      10,10,1300,800,nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

RECT me;
RECT stage[10];
RECT item[5];
RECT lader[3];
RECT villan[6];

int r; // random 저장값

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WCHAR mmsg[128] = { 0, };
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
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

    case WM_CREATE:

        //나 크기설정(좌표)
        me.left = 330;
        me.top = 660;
        me.right = 370;
        me.bottom = 700;

        srand(time(NULL));

        //아이템 좌표
        {
            item[0].left = rand() % 1300;
            item[0].top = 660;
            item[0].right = item[0].left + 40;
            item[0].bottom = item[0].top + 40;

            item[1].left = (rand() % 600) + 660;
            item[1].top = 360;
            item[1].right = item[1].left + 40;
            item[1].bottom = item[1].top + 40;

            item[2].left = (rand() % 400) + 410;
            item[2].top = 260;
            item[2].right = item[2].left + 40;
            item[2].bottom = item[2].top + 40;

            item[3].left = (rand() % 300) + 960;
            item[3].top = 220;
            item[3].right = item[3].left + 40;
            item[3].bottom = item[3].top + 40;
        }

        //stage 좌표
        {
            //맵 설정
            stage[0].left = 0;
            stage[0].top = 700;
            stage[0].right = stage[0].right + 1300;
            stage[0].bottom = stage[0].top + 50;

            stage[1].left = 300;
            stage[1].top = 550;
            stage[1].right = 1300;
            stage[1].bottom = stage[1].top + 40;

            stage[2].left = 0;
            stage[2].top = 400;
            stage[2].right = 600;
            stage[2].bottom = stage[2].top + 40;

            stage[3].left = 700;
            stage[3].top = 400;
            stage[3].right = 1300;
            stage[3].bottom = stage[3].top + 40;

            stage[4].left = 150;
            stage[4].top = 300;
            stage[4].right = 400;
            stage[4].bottom = stage[4].top + 40;

            stage[5].left = 450;
            stage[5].top = 300;
            stage[5].right = 900;
            stage[5].bottom = stage[5].top + 40;

            stage[6].left = 0;
            stage[6].top = 100;
            stage[6].right = 1000;
            stage[6].bottom = stage[6].top + 40;

            stage[7].left = 950;
            stage[7].top = 140;
            stage[7].right = 980;
            stage[7].bottom = stage[7].top + 150;

            stage[8].left = 950;
            stage[8].top = 260;
            stage[8].right = 1300;
            stage[8].bottom = 290;
        }

        //사다리
        {
            lader[0].left = 50;
            lader[0].top = 100;
            lader[0].right = 100;
            lader[0].bottom = 400;

            lader[1].left = 330;
            lader[1].top = 400;
            lader[1].right = 380;
            lader[1].bottom = 550;

            lader[2].left = 1050;
            lader[2].top = 550;
            lader[2].right = 1100;
            lader[2].bottom = 700;
        }

        //적
        {
            villan[0].left = (rand() % 1000) + 260;
            villan[0].top = 660;
            villan[0].right = villan[0].left + 40;
            villan[0].bottom = villan[0].top + 40;

            villan[1].left = (rand() % 600) + 660;
            villan[1].top = 360;
            villan[1].right = villan[1].left + 40;
            villan[1].bottom = villan[1].top + 40;

            villan[2].left = (rand() % 400) + 410;
            villan[2].top = 260;
            villan[2].right = villan[2].left + 40;
            villan[2].bottom = villan[2].top + 40;

            villan[3].left = (rand() % 300) + 960;
            villan[3].top = 220;
            villan[3].right = villan[3].left + 40;
            villan[3].bottom = villan[3].top + 40;
        }

        break;

    case WM_PAINT:
    {
        int i = 0;
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        //stage 그려주는 반복문

        for (i = 0; i < 10; i++)
        {
            Rectangle(hdc, stage[i].left, stage[i].top, stage[i].right, stage[i].bottom);
        }


        //item 그려주는 반복문

        for (i = 0; i < 5; i++)
        {
            Rectangle(hdc, item[i].left, item[i].top, item[i].right, item[i].bottom);
        }

        //사다리

        for (i = 0; i < 3; i++)
        {
            Rectangle(hdc, lader[i].left, lader[i].top, lader[i].right, lader[i].bottom);
        }

        //적

        for (i = 0; i < 5; i++)
        {
            Ellipse(hdc, villan[i].left, villan[i].top, villan[i].right, villan[i].bottom);
        }

        //나

        Rectangle(hdc, me.left, me.top, me.right, me.bottom);



        EndPaint(hWnd, &ps);
    }
    break;

    case WM_KEYDOWN:
    {
         switch (wParam)
        {            // 좌, 상, 우, 하 키가 입력되었는지 확인
        case VK_LEFT:   // x 좌표의 이동 (left, right) -> 감소
         //좌
        {
            if (me.bottom = stage[0].top) {
                me.left -= 10;
                me.right -= 10;
            }
            else if (me.bottom = stage[1].top) {
                me.left -= 10;
                me.right -= 10;
            }
            else if (me.bottom = stage[2].top) {
                me.left -= 10;
                me.right -= 10;
            }
            else if (me.bottom = stage[3].top) {
                me.left -= 10;
                me.right -= 10;
            }
            else if (me.bottom = stage[4].top) {
                me.left -= 10;
                me.right -= 10;
            }
            else if (me.bottom = stage[5].top) {
                me.left -= 10;
                me.right -= 10;
            }
            else if (me.bottom = stage[6].top) {
                me.left -= 10;
                me.right -= 10;
            }
            else if (me.bottom = stage[7].top) {
                me.left -= 10;
                me.right -= 10;
            }
            else if (me.bottom = stage[8].top) {
                me.left -= 10;
                me.right -= 10;
            }


        }

        break;

        case VK_RIGHT:
            //우
        {
            if (me.bottom = stage[0].top) {
                me.left += 10;
                me.right += 10;
            }
            else if (me.bottom = stage[1].top) {
                me.left += 10;
                me.right += 10;
            }
            else if (me.bottom = stage[2].top) {
                me.left += 10;
                me.right += 10;
            }
            else if (me.bottom = stage[3].top) {
                me.left += 10;
                me.right += 10;
            }
            else if (me.bottom = stage[4].top) {
                me.left += 10;
                me.right += 10;
            }
            else if (me.bottom = stage[5].top) {
                me.left += 10;
                me.right += 10;
            }
            else if (me.bottom = stage[6].top) {
                me.left += 10;
                me.right += 10;
            }
            else if (me.bottom = stage[7].top) {
                me.left += 10;
                me.right += 10;
            }
            else if (me.bottom = stage[8].top) {
                me.left += 10;
                me.right += 10;
            }

        }

        break;

        case VK_UP:     // y 좌표의 이동 (top, botoom) -> 감소
        //상
        {
            if (me.left >= 50 && me.right <= 100) {
                if (me.bottom <= 400 && me.bottom > 105)
                {
                    me.top -= 10;
                    me.bottom -= 10;
                    break;
                }
            }

            if (me.left >= 330 && me.right <= 380) {
                if (me.bottom <= 550 && me.bottom > 400)
                {
                    me.top -= 10;
                    me.bottom -= 10;
                    break;
                }
            }

            if (me.left >= 1050 && me.right <= 1100) {
                if (me.bottom < 701 && me.bottom > 555)
                {
                    me.top -= 10;
                    me.bottom -= 10;
                    break;
                }


            }
        }
        
        break;

        
        case VK_DOWN:   // y 좌표의 이동 (top, botoom) -> 증가

        {
            if (me.left >= 50 && me.right <= 100) {
                if (me.bottom <= 390 && me.bottom >= 100)
                {
                    me.top += 10;
                    me.bottom += 10;

                }
            }

            if (me.left >= 330 && me.right <= 380) {
                if (me.bottom < 545 && me.bottom >= 400)
                {
                    me.top += 10;
                    me.bottom += 10;

                }
            }

            if (me.left >= 1050 && me.right <= 1100) {
                if (me.bottom < 701 && me.bottom > 555)
                {
                    me.top += 10;
                    me.bottom += 10;

                }


            }
        }

        break;
}
        

        // WM_PAINT를 강제로 프로그래머가 호출하는 방법
        InvalidateRect(hWnd, NULL, TRUE);
        
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
    }
}

// 정보 대화 상자의 메시지 처리기입니다.
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
