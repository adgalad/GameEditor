
#include "Window.h"




int SDL_main (int argc, char **argv)
{
    
    Editor win;
    win.OnInit();
    
    
    return win.OnExecute();
}
