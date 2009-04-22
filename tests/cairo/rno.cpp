#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>

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
  Display* dpy = XOpenDisplay(NULL);

  if (dpy)
  {
    Window wid = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy),
                                     100, 100, 320, 240, 1, 1, 0);

    motif_wm_hints_remove_decoration(dpy, wid);

    XMapWindow(dpy, wid);

    while (1)
    {
      XEvent evt;

      XNextEvent(dpy, &evt);
    }
  }

  return (0);
}
