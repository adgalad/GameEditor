
#include "Window.h"




int SDL_main (int argc, char **argv)
{
    
    Window win;
    win.OnInit();
    
    
    return win.OnExecute();
}
