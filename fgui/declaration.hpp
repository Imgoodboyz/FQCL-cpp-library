#ifndef FGUI
#define FGUI

enum FGUI_panel
{
    MainWin,
    Button,
    Label,
    SubWin
};

class pas
{
    public:
    int x;
    int y;
    float w;
    float h;
};

typedef void (*FGUI_clbk)(void*);

#endif