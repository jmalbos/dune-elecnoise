/// ----------------------------------------------------------------------------
/// File     : FileIO.cpp
/// Author   : Justo Martin-Albo
/// Creation : 9 July 2018
/// ----------------------------------------------------------------------------

#include "FileIO.h"

#include <iostream>


FileReader::FileReader(char const * filename)
{
  file_.open(filename, std::fstream::in);
  if (file_.is_open()) std::cout << "Success!" << std::endl;
}
