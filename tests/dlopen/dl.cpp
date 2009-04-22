#include <iostream>
#include <cstdlib>
#include <dlfcn.h>

int main(int ac, char **av)
{
  (void)ac;
  (void)av;
  void *handle;
  double (*cosine)(double);
  char *error;
 
  handle = dlopen ("/usr/lib/libm.so", RTLD_LAZY);
  if (!handle) {
    std::cerr << dlerror() << std::endl;
    exit(1);
  }
 
  cosine = reinterpret_cast<double (*)(double)>(dlsym(handle, "cos"));
  if ((error = dlerror()) != NULL) {
    std::cerr << error << std::endl;
    exit(1);
  }
 
  std::cout <<  (*cosine)(2.0) << std::endl;
  dlclose(handle);
  return (EXIT_SUCCESS);
} 
