#include <windows.h>
#include <stdlib.h>

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp,LPARAM lp);
void AddMenus(HWND);
void AddControls(HWND);
HMENU hMenu;
//HWND  hEdit;
HWND hName,hAge,hOut;


#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInst, LPSTR args, int ncmdshow)
{
    //MessageBox(NULL,"HELLO", "MY FIRST GUI", MB_OK);
    WNDCLASSW wc={0};

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor=LoadCursor(NULL,IDC_ARROW);
    wc.hInstance= hInst;
    wc.lpszClassName=L"myWindowClass";
    wc.lpfnWndProc=WindowProcedure;

    if(!RegisterClassW(&wc))
         return -1;

    CreateWindowW(L"myWindowClass",L"My Window",WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100,500,500,NULL,NULL,NULL,NULL);
    MSG msg = {0};
    while (GetMessage(&msg, NULL, NULL, NULL))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);

    }
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp,LPARAM lp)
{
    switch (msg)
    {
    case WM_COMMAND:
         switch(wp)
          {
              case FILE_MENU_EXIT:
                  DestroyWindow(hWnd);
                  break;
              case FILE_MENU_NEW:
                  MessageBeep(MB_ICONINFORMATION);
                  break;
              case GENERATE_BUTTON:
                  char name[30],age[10],out[50];

                  GetWindowText(hName,name,30);
                  GetWindowText(hAge,age,10);

                  strcpy(out,name);
                  strcat(out," is ");
                  strcat(out,age);
                  strcat(out," years old.");

                  SetWindowText(hOut,out);

                  break;

          }
          break;

    case WM_ACTIVATE:
        AddMenus(hWnd);
        AddControls(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd,msg,wp,lp);
    }
}

void AddMenus(HWND hWnd)
{
  hMenu = CreateMenu();
  HMENU hFilemenu = CreateMenu();
  HMENU hSubMenuOpen = CreateMenu();

  AppendMenu(hSubMenuOpen,MF_STRING, 1,"Open File");
  AppendMenu(hSubMenuOpen,MF_STRING, 1,"Open Project");
  //AppendMenu(hSubMenuOpen,MF_STRING, CHANGE_TITLE,"Change Title");

  AppendMenu(hFilemenu,MF_STRING, FILE_MENU_NEW,"New");
  AppendMenu(hFilemenu,MF_POPUP,(UINT_PTR) hSubMenuOpen,"Open");
  AppendMenu(hFilemenu,MF_STRING, FILE_MENU_EXIT,"Close");

  AppendMenu(hMenu,MF_POPUP, (UINT_PTR)hFilemenu,"File");
  AppendMenu(hMenu,MF_STRING, 2,"Edit");
  AppendMenu(hMenu,MF_STRING, 3,"View");
  AppendMenu(hMenu,MF_STRING, 4,"Help");
  SetMenu(hWnd,hMenu);
}

void AddControls(HWND hWnd)
 {
  CreateWindowW(L"static",L"Name:",WS_VISIBLE | WS_CHILD ,100,100,50,25,hWnd,NULL,NULL,NULL);
  hName=CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD |WS_BORDER,150,100,75,25,hWnd,NULL,NULL,NULL);

  CreateWindowW(L"static",L"Age:",WS_VISIBLE | WS_CHILD ,100,150,50,25,hWnd,NULL,NULL,NULL);
  hAge=CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD |WS_BORDER,150,150,75,25,hWnd,NULL,NULL,NULL);

  CreateWindowW(L"Button",L"Generate",WS_VISIBLE | WS_CHILD ,120,200,100,30,hWnd,(HMENU)GENERATE_BUTTON,NULL,NULL);
  hOut=CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD |WS_BORDER,120,250,200,25,hWnd,NULL,NULL,NULL);
 }
