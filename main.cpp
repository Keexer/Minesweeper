#include "window.h"

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  Window w;
  
  if (w.init(1080, 720))
  {
    w.run();
  }

  return 0;
}