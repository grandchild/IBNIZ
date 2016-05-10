#include "ibniz.h"

#if defined(WIN32)
#include <windows.h>

void clipboard_load()
{
  HGLOBAL data;
  if (!IsClipboardFormatAvailable(CF_TEXT)) 
    return; 
  if (!OpenClipboard(NULL)) 
    return; 
  data = GetClipboardData(CF_TEXT);
  if(data)
  {
    char*t=(char*)GlobalLock(data);
    int lgt=strlen(t);
    if(clipboard) free(clipboard);
    clipboard=malloc(strlen(t)+1);
    strcpy(clipboard,t);
    GlobalUnlock(data);
  }
  CloseClipboard();
}

void clipboard_store()
{
  HGLOBAL buffer;

  if (!OpenClipboard(NULL)) 
    return; 
  EmptyClipboard();
  
  buffer = GlobalAlloc(GMEM_DDESHARE,strlen(clipboard)+1);
  if(!buffer)
  {
    CloseClipboard();
    return;
  }
  buffer = (char*)GlobalLock(buffer);
  strcpy(buffer,clipboard);
  GlobalUnlock(buffer);
  SetClipboardData(CF_TEXT,buffer);
  CloseClipboard();
}


#elif defined(X11) && !defined(FB)
#include <SDL2/SDL.h>

void clipboard_load()
{
  clipboard = SDL_GetClipboardText();
}

void clipboard_store()
{
  SDL_SetClipboardText(clipboard);
}
#else

void clipboard_load()
{
}

void clipboard_store()
{
}

#endif
