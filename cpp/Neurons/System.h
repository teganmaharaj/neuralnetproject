#ifndef __SYSTEM__
#define __SYSTEM__

class System
{
  public:
  static bool isRunning;
  int layerOn;
  void on(){isRunning = true;}
  void off(){isRunning = false;}
};

#endif
