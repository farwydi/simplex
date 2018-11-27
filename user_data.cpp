#include <iostream>
#include <fstream>
#include "user_data.h"

using namespace std;

void error (int err_no)
{
  switch (err_no)
  {
    case 0:
      cout << "\nВы ввели некорректное значение.\n" << endl;
      break;
    case 1:
      cout << "\nВы не можете задать менее двух ограничений.\n" << endl;
      break;
    case 2:
      cout << "\nВы не можете задать больше 500 ограничений.\n" << endl;
      break;
    case 3:
      cout << "\nВы не можете задать менее двух переменных.\n" << endl;
      break;
    case 4:
      cout << "\nВы не можете задать более 500 уравнений.\n" << endl;
      break;
    default:
      break;
  }
}

void user_data::get_data_from_user ()
{
  string num_limits, num_vars, s_var, fr_m, sn, func, w;
  int i, j;
  bool validator = false;
  ifstream data_file ("./test.txt");

  do
  {
    getline (data_file, num_limits);
    cout << "Введите количество ограничений в системе: " << num_limits << endl;
    if (atoi (num_limits.c_str ()) < 2)
      error (1);

    else if (atoi (num_limits.c_str ()) > 500)
      error (2);
    else
      validator = true;

  }
  while (!validator);

  num_l = atoi (num_limits.c_str ());
  validator = false;

  do
  {
    getline (data_file, num_vars);
    cout << "Введите количество переменных в системе ограничений: " << num_vars << endl;
    if (atoi (num_vars.c_str ()) < 2)
      error (3);
    else if (atoi (num_vars.c_str ()) > 500)
      error (4);
    else
      validator = true;
  }
  while (!validator);

  num_v = atoi (num_vars.c_str ());
  validator = false;

  function = new double[num_v];
  system = new double *[num_l];
  for (i = 0; i < num_l; i++)
    system[i] = new double[num_v];
  fm = new double[num_l];
  sign = new int[num_l];

  cout << "\nЗаполните коэффициенты при целевой функции.\n" << endl;

  for (i = 0; i < num_v; i++)
  {
    do
    {
      getline (data_file, func);
      cout << "Введите коэффициент целевой фукнции при x" << i + 1 << ": " << func << endl;
      if (atof (func.c_str ()) == 0)
        error (0);
      else
      {
        validator = true;
        function[i] = atof (func.c_str ());
      }
    }
    while (!validator);
    validator = false;
  }

  do
  {
    getline (data_file, w);
    cout << "Введите направление целевой функции ( min, max ) : " << w << endl;
    if (w == "max" || w == "MAX" || w == "min" || w == "MIN")
    {
      validator = true;
      way = w == "max" || w == "MAX";
    }
    else
      error (0);

  }
  while (!validator);
  cout << "\nЗаполните систему ограничений.\n" << endl;

  for (i = 0; i < num_l; i++)
  {
    cout << "Заполните " << i + 1 << "-е ограничение." << endl << endl;
    for (j = 0; j < num_v; j++)
    {
      do
      {
        getline (data_file, s_var);
        cout << "Введите коэффициэнт при x" << j + 1 << ": " << s_var << endl;
        if (atof (s_var.c_str ()) == 0)
          error (0);
        else
        {
          validator = true;
        }
      }
      while (!validator);
      system[i][j] = atof (s_var.c_str ());
      validator = false;
    }

    do
    {
      getline (data_file, sn);
      cout << "Введите знак при " << i + 1 << "-м ограничении ( <=, =, >= ) : " << sn << endl;
      if (sn == "<=" || sn == "=" || sn == ">=")
      {
        validator = true;
        if (sn == "<=")
          sign[i] = 0;
        if (sn == "=")
          sign[i] = 1;
        if (sn == ">=")
          sign[i] = 2;
      }
      else
        error (0);
    }
    while (!validator);

    validator = false;

    do
    {
      getline (data_file, fr_m);
      cout << "Введите свободный член при " << i + 1 << "-м ограничении: " << fr_m << endl;
      if (atof (fr_m.c_str ()) == 0)
        error (0);
      else
        validator = true;
    }
    while (!validator);

    fm[i] = atof (fr_m.c_str ());
    validator = false;

    cout << endl;
  }

  data_file.close ();
}
