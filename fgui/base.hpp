#include <windows.h>
#include "declaration.hpp"
#include <vector>
#include <string>
#include <functional>
#include <iostream>

class AppID
{
    private:
    static LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
    {return DefWindowProc(hwnd,msg,wp,lp);}
    std::string classname;
    WNDCLASSEX wc;
    public:
    AppID(const std::string& clsname, HINSTANCE hInstance) {classname = clsname;
        wc.cbSize        = sizeof(WNDCLASSEX);               // Size of the structure in bytes
    wc.style         = CS_HREDRAW | CS_VREDRAW;          // Class styles (e.g., redraw on resize)
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;                                // Extra bytes to allocate for this class
    wc.cbWndExtra    = 0;                                // Extra bytes to allocate for this window
    wc.hInstance     = hInstance;                        // Handle to the application instance
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);  // Large icon (Alt+Tab)
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);      // Cursor displayed over the window
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);       // Background brush color
    wc.lpszMenuName  = NULL;                             // Name of the class menu resource
    wc.lpszClassName = classname.c_str();                // Unique identifier for the window class
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);  // Small icon (title bar and taskbar
    RegisterClassEx(&wc); // Register the window class with the system
    }
    const char* clsnm() { return wc.lpszClassName; }
    HINSTANCE hinstance() { return wc.hInstance; }
};

template <FGUI_panel panel_type>
class Panel {};

template<>
class Panel<MainWin>
{
    private:

    COLORREF clr;

    bool drag;

    HWND parent;

    HWND hwnd;

    public:

    std::function<void()> onclick;
    std::function<void()> onhover;
    std::function<void()> onrclick;

    Panel(AppID wndid,const char* title, int x, int y, int width, int height, bool bodydrag = false)
    {
        drag = bodydrag;

        hwnd = CreateWindowEx
        (
            0,
            wndid.clsnm(),
            title,
            WS_OVERLAPPEDWINDOW| WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
            x,y,width,height,
            NULL,
            NULL,
            wndid.hinstance(),
            this
        );
        SetWindowLongPtr(hwnd,GWLP_USERDATA,(LONG_PTR)this);
        SetWindowLongPtr(hwnd,GWLP_WNDPROC,(LONG_PTR)WndProc);
    }
    void Setcolor(COLORREF iclr) {clr = iclr;}

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        Panel<MainWin>* win = reinterpret_cast<Panel<MainWin>*>(GetWindowLongPtr(hwnd,GWLP_USERDATA));
        switch (uMsg)
        {
            case WM_NCDESTROY:
                PostQuitMessage(0);
                break;
            case WM_LBUTTONDOWN:
                if (win && win->onclick) {win->onclick();}
                break;
            case WM_RBUTTONDOWN:
                if (win && win->onrclick) {win->onrclick();}
                break;
            case WM_MOUSEMOVE:
                if (win && win->onhover) {win->onhover();}
                break;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    HWND id() { return hwnd; }
};

template<>
class Panel<Label>
{
    private:
        pas Pas;
        HWND parent;
        HWND hwnd;
        bool drag;
        COLORREF clr;
        std::string content;
        int fs;
        int pad;
    public:
    Panel(AppID wndid,HWND iparent,std::string icontent,int ix,int iy,int iw,int ih,int padding,bool idrag)
    {
        Pas.x = ix;
        Pas.y = iy;
        Pas.w = iw;
        Pas.h = ih;
        drag = idrag;
        content = icontent;
        hwnd = CreateWindowEx(
            0,
            wndid.clsnm(),
            "string",
            WS_CHILD  | WS_VISIBLE,
            200,200,iw,ih,
            iparent,
            NULL,
            wndid.hinstance(),
            this
        );
        EnableWindow(hwnd,TRUE);
        SetWindowLongPtr(hwnd,GWLP_USERDATA,(LONG_PTR)this);
        SetWindowLongPtr(hwnd,GWLP_WNDPROC,(LONG_PTR)WndProc);
    }
    void SetPadding(int i) {pad = i;}
    bool FontSize(int i) {fs = i;}
    int FontSize() {return fs;}
    bool alowdrag() {return drag;}
    pas GetPAS() {return Pas;}
    HWND id() {return hwnd;}
    int GetPadding() {return pad;}
    std::string GetText() {return content;}

    static LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
    {
        Panel<Label>* lb = reinterpret_cast<Panel<Label>*>(GetWindowLongPtr(hwnd,GWLP_USERDATA));
        switch(msg)
        {
            case WM_MOUSEMOVE:
                break;
            case WM_NCDESTROY:
                delete lb;
                break;
            case WM_ERASEBKGND:
                return 1;
            case WM_LBUTTONDOWN:
            {
                    if (lb && lb->alowdrag()) 
                {
                    PostMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, lp);
                }
                return 0; // Đã xử lý xong, không cho DefWindowProc làm loạn
            }
            case WM_PAINT:
            {
                pas p = lb->GetPAS();
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(lb->id(),&ps);
                {
                    SetBkColor(hdc,RGB(200,200,200));
                    HBRUSH br = CreateSolidBrush(RGB(200,200,200));
                    HBRUSH ob = (HBRUSH)SelectObject(hdc,br);

                    HFONT hFont = CreateFont(lb->FontSize(), 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
                        OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, 
                        VARIABLE_PITCH, TEXT("Arial"));

                    HFONT of = (HFONT)SelectObject(hdc,hFont);
                    
                    SIZE sz;
                    GetTextExtentPoint32(hdc,lb->GetText().c_str(),lb->GetText().length(),&sz);
                    int w = sz.cx;
                    int h = sz.cy;

                    p.w = w + (lb->GetPadding()*2);
                    p.h = h + (lb->GetPadding()*2);

                    RECT r = {0, 0 ,w + (lb->GetPadding()*2),h + (lb->GetPadding()*2)};

                    FillRect(hdc,&r,br);
                    TextOut(hdc,lb->GetPadding(),lb->GetPadding(),lb->GetText().c_str(),lb->GetText().length());
                    SelectObject(hdc,hFont);
                    SelectObject(hdc,br);
                    DeleteObject(br);
                    DeleteObject(hFont);

                }
                EndPaint(hwnd,&ps);
                break;
            }
            case HTCLIENT:
                if (lb->alowdrag()) return HTCAPTION;
                break;
        }
        return DefWindowProc(hwnd,msg,wp,lp);
    }
};

template<>
class Panel<SubWin>
{
    private:
        HWND parent;
        HWND hwnd;
        bool drag;
        COLORREF clr;
    public:
    Panel(AppID wndid,const char* title, int x, int y, int width, int height, bool bodydrag = false)
    {
        drag = bodydrag;

        hwnd = CreateWindowEx
        (
            0,
            wndid.clsnm(),
            title,
            WS_OVERLAPPEDWINDOW| WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
            x,y,width,height,
            NULL,
            NULL,
            wndid.hinstance(),
            this
        );
        SetWindowLongPtr(hwnd,GWLP_USERDATA,(LONG_PTR)this);
        SetWindowLongPtr(hwnd,GWLP_WNDPROC,(LONG_PTR)WndProc);
    }
        std::function<void()> onclick;
        std::function<void()> onhover;
        std::function<void()> onrclick;
        HWND id() {return hwnd;}
        static LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
        {
            Panel<SubWin>* win = reinterpret_cast<Panel<SubWin>*>(GetWindowLongPtr(hwnd,GWLP_USERDATA));
            switch (msg)
            {
                case WM_NCDESTROY:
                    delete win;
                    break;
                case WM_LBUTTONDOWN:
                    if (win && win->onclick) {win->onclick();}
                    break;
                case WM_RBUTTONDOWN:
                    if (win && win->onrclick) {win->onrclick();}
                    break;
                case WM_MOUSEMOVE:
                    if (win && win->onhover) {win->onhover();}
                    break;
            }
            return DefWindowProc(hwnd,msg,wp,lp);
        }
        ~Panel() = default;

};

template<>
class Panel<Button>
{
    private:

    pas Pas;

    COLORREF clr;

    COLORREF bclr;

    HWND parent;

    HWND hwnd;
    
    public:

    std::function<void()> onclick;

    std::function<void()> onhover;

    std::function<void()> onrclick;

    Panel(AppID wndid,HWND parent,const char* title, int x, int y, int width, int height)
    {
        Pas.x = x;
        Pas.y = y;
        Pas.w = width;
        Pas.h = height;
        this->parent = parent;
        hwnd = CreateWindowEx
        (
            0,
            wndid.clsnm(),
            title,
            WS_CHILD | WS_VISIBLE,
            x,y,width,height,
            parent,
            NULL,
            wndid.hinstance(),
            this
        );
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
    }
    void onpaint() {InvalidateRect(hwnd,NULL,0);}
    void SetPS(pas iPAS) {Pas = iPAS;InvalidateRect(hwnd,NULL,FALSE);}
    void BgColor(COLORREF iclr) {clr = iclr;InvalidateRect(hwnd,NULL,FALSE);}
    void BdColor(COLORREF iclr) {bclr = iclr;InvalidateRect(hwnd,NULL,FALSE);}
    COLORREF GetColor() {return clr;}
    COLORREF GetBColor() {return bclr;} 
    pas GetPAS() {return Pas;}
    HWND id() { return hwnd; }

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        Panel<Button>* btn = reinterpret_cast<Panel<Button>*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        switch (uMsg)
        {
            case WM_NCDESTROY:
                delete btn;
                break;
            case WM_ERASEBKGND:
                return 1;
            case WM_PAINT:
                {
                    pas Pas = btn->GetPAS();
                    PAINTSTRUCT ps;
                    HDC hdc = BeginPaint(hwnd,&ps);
                    {
                        HBRUSH brush = CreateSolidBrush(btn->GetColor());
                        HBRUSH pen = CreateSolidBrush(btn->GetBColor());

                        HBRUSH ob = (HBRUSH)SelectObject(hdc,brush);

                        RECT r = {0,0,(int)Pas.w,(int)Pas.h};
                        RECT r2 = {0,0,(int)Pas.w,(int)Pas.h};

                        FillRect(hdc,&r2,brush);
                        FrameRect(hdc,&r,pen);

                        SelectObject(hdc,ob);

                        DeleteObject(brush);
                        DeleteObject(pen);
                    }
                    EndPaint(hwnd,&ps);
                }
                return 0;
            case WM_LBUTTONDOWN:
                if (btn && btn->onclick)
                {
                    btn->onclick();
                }
                break;
            case WM_MOUSEMOVE:
                if (btn && btn->onhover)
                    btn->onhover();
            break;
            case WM_RBUTTONDOWN:
                if (btn && btn->onrclick)
                    btn->onrclick();
                break;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    ~Panel() = default;
};