#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/shape.h>
#include <Imlib.h>

int main(int argc, char **argv)
{
  Display *disp;
  ImlibData *id;
  XSetWindowAttributes *attr;
  Window win;
  ImlibImage *im;
  Pixmap p,m;
  int w,h;
    
  /* Be nice and tell the user if they don't, to provide a file as an arg */
  if (argc <= 1)
  {
    printf("Usage:\n %s image_file\n", argv[0]);
    exit(1);
  }
  /* Connect to the default Xserver */
  disp = XOpenDisplay(NULL);
  /* Immediately afterwards Intitialise Imlib */
  id = Imlib_init(disp);

  /* Load the image specified as the first argument */
  im = Imlib_load_image(id, argv[1]);
  /* Suck the image's original width and height out of the Image structure */
  w = im->rgb_width;
  h = im->rgb_height;
  /* Create a Window to display in */
  win = XCreateWindow(disp,DefaultRootWindow(disp),0,0,w,h,0,id->x.depth,
                    InputOutput,id->x.visual,0,attr);
  XSelectInput(disp,win,StructureNotifyMask);
  /* Put the Image in the window, at the window's size and apply a shape mask */
  /* if applicable, or remove one if not */
  Imlib_apply_image(id,im,win);
  /* Actually display the window */
  XMapWindow(disp,win);
  /* Synchronise with the Xserver */
  XSync(disp,False);
  /* Event loop to handle resizes */   
  for(;;)
  {
    XEvent ev;
     
    /* Sit and wait for an event to happen */ 
    XNextEvent(disp,&ev);
    if (ev.type==ConfigureNotify)
    {
      /* Put the Image in the window, at the window's size and apply a shape mask */
      /* if applicable, or remove one if not */
      Imlib_apply_image(id,im,win);
      /* Synchronise with the Xserver */
      XSync(disp,False);
    }
  }
}
