//
// cairo.cpp for OZAXE in /home/christian/workspace/ozaxe/trunk/bin/linux32/tests/cairo
// 
// Made by Christian KAKESA
// Login   <christian@epita.fr>
// 
// Started on  Fri Jun  1 03:48:55 2007 Christian KAKESA
// Last update Thu Jun 14 02:05:35 2007 Christian KAKESA
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

# ifdef WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
# endif // WIN32

#include <cairo.h>
#include <cairo-xlib.h>


/*
using namespace std;

int	main(int ac, char **av)
{

  const cairo_antialias_t       gl_antialias = CAIRO_ANTIALIAS_GRAY;

  cairo_surface_t*      p_cs    = cairo_image_surface_create_from_png("e-texteditor.png");
  cairo_t*              p_ctx   = cairo_create(p_cs);

  cairo_set_antialias(p_ctx, gl_antialias);


  cairo_select_font_face (p_ctx, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size (p_ctx, 32.0);
  cairo_set_source_rgb (p_ctx, 0.0, 0.0, 1.0);
  cairo_move_to (p_ctx, 10.0, 50.0);
  cairo_show_text (p_ctx, "Hello, world");
  cairo_destroy (p_ctx);
  cairo_surface_write_to_png (p_cs, "hello.png");

  while (1);

  cairo_surface_destroy (p_cs);

  return (0);
}

*/

#define PI 3.1415926535

extern "C" {


  typedef struct win {
      Display *dpy;
      int scr;

      Window win;
      GC gc;

      int width, height;
      KeyCode quit_code;
  } win_t;

  static void triangle(cairo_t *cr);
  static void square(cairo_t *cr);
  static void bowtie(cairo_t *cr);
  static void win_init(win_t *win);
  static void win_deinit(win_t *win);
  static void win_draw(win_t *win);
  static void win_handle_events(win_t *win);

int
main(int argc, char *argv[])
{
  win_t win;

  win.dpy = XOpenDisplay(0);

  if (win.dpy == NULL) {
    fprintf(stderr, "Failed to open display\n");
    return 1;
  }

  win_init(&win);

  win_draw(&win);

  win_handle_events(&win);

  win_deinit(&win);

  XCloseDisplay(win.dpy);

  return 0;
}

static void
win_draw(win_t *win)
{
  cairo_surface_t *surface;
  cairo_t *cr;
  Visual *visual = DefaultVisual(win->dpy, DefaultScreen (win->dpy));

  XClearWindow(win->dpy, win->win);

  surface = cairo_xlib_surface_create (win->dpy, win->win, visual,
                                       win->width, win->height);
  cr = cairo_create(surface);

  cairo_set_source_rgb(cr, 1, 1, 1);

  cairo_set_line_width(cr, 5);

  cairo_new_path(cr);
  cairo_move_to(cr,10,10);
  cairo_rel_line_to(cr,400,0);
  cairo_rel_line_to(cr,0,300);
  cairo_rel_line_to(cr,-400,0);
  cairo_close_path(cr);
  cairo_fill(cr);

  cairo_new_path(cr);
  cairo_set_source_rgb(cr,0,1,0);
  cairo_move_to(cr,11,11);
  cairo_rel_line_to(cr,398,0);
  cairo_rel_line_to(cr,0,10);
  cairo_rel_line_to(cr,-398,0);
  cairo_close_path(cr);
  cairo_fill(cr);

  cairo_new_path(cr);
  cairo_set_source_rgb(cr,1,0,0);
  cairo_arc(cr,405,15,5,0,2*PI);
  cairo_close_path(cr);
  cairo_fill(cr);
    
  if (cairo_status (cr)) {
    printf("Cairo is unhappy: %s\n",
           cairo_status_to_string (cairo_status (cr)));
    exit(0);
  }

  cairo_destroy(cr);
  cairo_surface_destroy (surface);
}

static void
win_init(win_t *win)
{
  Window root;

  win->width = 640;
  win->height = 480;

  root = DefaultRootWindow(win->dpy);
  win->scr = DefaultScreen(win->dpy);
  
  //win->win = XCreateSimpleWindow(win->dpy, root, 0, 0,
  //                               win->width, win->height, 0,
  //                               0L, 0L);
  win->win = XCreateSimpleWindow(win->dpy, root, 0, 0,
                                 win->width, win->height, 0,
                                 BlackPixel(win->dpy, win->scr), BlackPixel(win->dpy, win->scr));

  

  win->quit_code = XKeysymToKeycode(win->dpy, XStringToKeysym("Q"));

  XSelectInput(win->dpy, win->win,
                KeyPressMask
                |StructureNotifyMask
               |ExposureMask);

  XMapWindow(win->dpy, win->win);
}

static void
win_deinit(win_t *win)
{
  XDestroyWindow(win->dpy, win->win);
}

static void
win_handle_events(win_t *win)
{
  XEvent xev;

  while (1) {
    XNextEvent(win->dpy, &xev);
    switch(xev.type) {
      case KeyPress:
      {
        XKeyEvent *kev = &xev.xkey;
            
        if (kev->keycode == win->quit_code) {
          return;
        }
      }
      break;
      case ConfigureNotify:
      {
        XConfigureEvent *cev = &xev.xconfigure;

        win->width = cev->width;
        win->height = cev->height;
      }
      break;
      case Expose:
      {
        XExposeEvent *eev = &xev.xexpose;

        if (eev->count == 0)
          win_draw(win);
      }
      break;
    }
  }
}

}
