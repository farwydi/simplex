#include "simplex.h"

int main ()
{
  setlocale (LC_ALL, "Russian");
  auto *ud = new simplex;
  ud->get_data_from_user ();
  ud->init ();
  ud->gen_plane ();
  return 0;
}
