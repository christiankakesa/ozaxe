#include <iostream>
#include <glibmm/ustring.h>

#include <ozaxelib/OzaxeLib.h>
#include <MessageServices.h>

using namespace OzaxeLib::System;

int	main(int ac, char** av)
{
  (void) ac;
  (void) av;
  const Glib::ustring lib_path = "libozaxeplugin_messageservices.so";
  CLibrary libmessageservices;
  if (!libmessageservices.Load(lib_path))
    {
      std::cout << "Impossible to load library !!!" << std::endl;
      return (1);
    }
  messageservices_t pMessageServices_New = reinterpret_cast<messageservices_t>(libmessageservices.GetAddr("MessageServices_New"));
  messageservices_destroy_t pMessageServices_Destroy = reinterpret_cast<messageservices_destroy_t>(libmessageservices.GetAddr("MessageServices_Destroy"));
  MessageServices* ms = pMessageServices_New();
  Glib::ustring text("TITLE:OZAXE IS VERY POWERFULL !!!");
  ms->PrintText(text);
  pMessageServices_Destroy(ms);
  libmessageservices.UnLoad();
  return (EXIT_SUCCESS);
}
