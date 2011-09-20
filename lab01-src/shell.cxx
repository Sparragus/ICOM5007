#include <iostream>

#include "command.h"

int main()
{

  bool exit_requested = true;

  command cmd;
  do
  {
    if (!cmd.readline())
    {
      cmd.print_usage();
    }
    else
    {
      cmd.execute();
    }
  } while (!cmd.exit_requested());

  return 0;
}
