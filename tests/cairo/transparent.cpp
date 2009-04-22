/**
 *
 */

#include <iostream>
#include <cstdlib>
#include <cairo.h>
#include <cairo-xlib.h>

typedef struct
{
    long flags;
    long functions;
    long decorations;
    long inputMode;
    long status;

} MWMHints;

#define MWM_HINTS_FUNCTIONS     (1L << 0)
#define MWM_HINTS_DECORATIONS   (1L << 1)
#define MWM_HINTS_INPUT_MODE    (1L << 2)
#define MWM_HINTS_STATUS        (1L << 3)

#define PROP_MWM_HINTS_ELEMENTS 5

void    motif_wm_hints_remove_decoration(Display* dpy, Window wid)
{
  MWMHints      mwmhints;
  Atom          prop;

  memset(&mwmhints, 0, sizeof(mwmhints));

  prop = XInternAtom(dpy,
                     "_MOTIF_WM_HINTS",
                     False);
  mwmhints.flags = MWM_HINTS_DECORATIONS;
  mwmhints.decorations = 0;

  XChangeProperty(dpy, wid, prop, prop, 32, PropModeReplace,
                  (unsigned char *)&mwmhints,
                  PROP_MWM_HINTS_ELEMENTS);
}

int     main(int ac, char** av)
{
  bool  run = true;
  int   defaultHeight = 128;

  ::Display* dpy = ::XOpenDisplay(NULL);
  if (dpy == NULL)
    exit(1);

  ::Window parent = DefaultRootWindow(dpy);
  unsigned long valueMask = CWEventMask|CWBorderPixel;
  ::XSetWindowAttributes* attr = new XSetWindowAttributes;
  attr->border_pixel = 0;
  attr->background_pixel = 0;
  attr->event_mask = ExposureMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask;
  attr->override_redirect = true;

  ::Window win = XCreateWindow(dpy,
                               parent,
                               0, 0, //x, y
                               DisplayWidth(dpy, DefaultScreen(dpy)),   // W
                               //DisplayHeight(dpy, DefaultScreen(dpy)),  // H
                               defaultHeight,
                               0, //int border_width
                               DefaultDepth(dpy, 0), //int depth
                               InputOutput, //unsigned int class
                               DefaultVisual(dpy, 0), //visual pointer
                               valueMask, //unsigned long int valuemask
                               attr);

  //::XStoreName(dpy, win, "MESSAGE SERVICES");
  motif_wm_hints_remove_decoration(dpy, win);

  ::XSelectInput(dpy, win, StructureNotifyMask | ButtonPressMask);
  ::XMapWindow(dpy, win);

  ::XSync(dpy, false);

  ::XEvent evt;

  while (run)
  {
    ::XNextEvent(dpy, &evt);
    if (evt.type == ConfigureNotify)
    {
      ::XSync(dpy, false);
    }
    else if (evt.type == ButtonPress)
    {
      run = false;
    }
  }

  ::XDestroyWindow(dpy, win);
  ::XCloseDisplay(dpy);
  return (0);
}
