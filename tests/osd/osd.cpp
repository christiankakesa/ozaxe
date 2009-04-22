#include <stdio.h>
#include <unistd.h>
#include <xosd.h>

// voir aussi les méthodes :
// Change la taille de la barre de pourcentage et du slider
// int xosd_set_bar_length(xosd * osd, int length);
// Temps d'attente si rien n'est affiché
// int xosd_wait_until_no_display(xosd * osd);
// Masque l'osd
// int xosd_hide(xosd * osd);
// Affiche l'osd (attention pas de show après un display)
// int xosd_show(xosd * osd); //Attention pas de show après un display
// Modification de l'offset pour le shadow
// int xosd_set_shadow_offset(xosd * osd, int shadow_offset);
// Modification de l'offset pour le outline
// int xosd_set_outline_offset(xosd * osd, int outline_offset);
// Modification de la couleur du outline
// int xosd_set_outline_colour(xosd * osd, const char *colour);
// Modification de la couleur du shadow
// int xosd_set_shadow_colour(xosd * osd, const char *colour);
// Modification de l'offset sur l'axe horizontal
// int xosd_set_horizontal_offset(xosd * osd, int offset);
// Modification de l'offset sur l'axe vertical
// int xosd_set_vertical_offset(xosd * osd, int offset);
// Permet de faire scroller naturellement l'affichage
// int xosd_scroll(xosd * osd, int lines);

int	main(int ac, char** av)
{
  (void) ac;
  (void) av;
  // couleurs
  int r = -1, g = -1, b = -1;
  // code de retour
  int ret = 0;
  // nombres de lignes pour l'affichage
  int numLines = 5;
  // timeout d'affichage
  int timeout = 5;
  // font
  //  const char* font = "-b&h-lucida-bold-*-normal-sans-*-560-*-*-*-*-iso8859-1";
  const char* font = "-Adobe-Courier-Bold-R-Normal--*-420-*-*-m-*-ISO8859-1";
  // couleur
  const char* color = "#751EAC";
  // ligne 1
  const char* line1 = "Ligne 1";
  // ligne 2
  const char* line2 = "Ligne 2";
  // ligne 3
  const char* line3 = "Ligne 3";
  // pourcentage
  int percent = 90;
  //slider
  int slider = 30;
  
  // allocation d'un pointeur xosd
  xosd *ptrOsd = xosd_create(numLines);
  //récupération du nombre de lignes
  numLines = xosd_get_number_lines(ptrOsd);
  printf("xosd_get_number_lines [lines : %d]\n", numLines);
  
  // alignement horizontal
  ret = xosd_set_align(ptrOsd, XOSD_center);
  printf("xosd_set_align ret = %d\n", ret);
  
  // alignement vertical
  ret = xosd_set_pos(ptrOsd, XOSD_top);
  printf("xosd_set_pos ret = %d\n", ret);
  
  // font de l'osd
  ret = xosd_set_font(ptrOsd, font);
  printf("xosd_set_align [font : %s] ret = %d\n", font, ret);
  
  // couleur de l'osd
  ret = xosd_set_colour(ptrOsd, color);
  printf("xosd_set_colour [color : %s] ret = %d\n", color, ret);
  // récupération de la couleur de l'osd
  ret = xosd_get_colour(ptrOsd, &r, &g, &b);
  printf("xosd_get_colour [r : %d, g : %d, b : %d] ret = %d\n", r, g, b, ret);
  
  // affichage d'une chaine ligne 1
  ret = xosd_display(ptrOsd, 0, XOSD_string, line1);
  printf("xosd_display [str : %s] ret = %d\n", line1, ret);
  // affichage d'une chaine ligne 2
  ret = xosd_display(ptrOsd, 1, XOSD_string, line2);
  printf("xosd_display [str : %s] ret = %d\n", line2, ret);
  // affichage d'une chaine ligne 3
  ret = xosd_display(ptrOsd, 2, XOSD_string, line3);
  printf("xosd_display [str : %s] ret = %d\n", line3, ret);
  // affichage d'une barre de pourcentage ligne 4
  ret = xosd_display(ptrOsd, 3, XOSD_percentage, percent);
  printf("xosd_display [percent : %d] ret = %d\n", percent, ret);
  // affichage d'un slider ligne 5
  ret = xosd_display(ptrOsd, 4, XOSD_slider, slider);
  printf("xosd_display [slider : %d] ret = %d\n", slider, ret);
  
  // test si l'ods est déjà affiché ou non
  ret = xosd_is_onscreen(ptrOsd);
  printf("xosd_is_onscreen ret = %d\n", ret);
  
  // masque l'osd dans 'timeout' secondes
  ret = xosd_set_timeout(ptrOsd, timeout);
  printf("xosd_set_timeout [timeout : %d s.] ret = %d\n", timeout, ret);
  
  //attente avant le release de l'osd
  sleep(10);
  // test si l'ods est déjà affiché ou non
  ret = xosd_is_onscreen(ptrOsd);
  printf("xosd_is_onscreen ret = %d\n", ret);
  // libération de l'osd
  // Note : si l'osd n'avait pas de timeout il serait automatiquement enlevé
  ret = xosd_destroy(ptrOsd);
  printf("xosd_destroy ret = %d\n", ret);
  return 0;
}
