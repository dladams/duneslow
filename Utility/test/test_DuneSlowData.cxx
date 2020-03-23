// test_DuneSlowData.cxx
//
// David Adams
// Marach 2020
//
// Test DuneSlowData.

#include "../DuneSlowData.h"
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

#undef NDEBUG
#include <cassert>

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::istringstream;
using std::vector;

//**********************************************************************

int test_DuneSlowData() {
  const string myname = "test_DuneSlowData: ";
#ifdef NDEBUG
  cout << myname << "NDEBUG must be off." << endl;
  abort();
#endif
  string line = "-----------------------------";

  cout << myname << line << endl;
  float scale = 100.0;
  cout << myname << "Create object." << endl;
  DuneSlowData dsd("hvraw");

  cout << myname << line << endl;
  cout << myname << "Check object." << endl;
  cout << myname << "   tref: " << dsd.tref() << endl;
  assert( dsd.tref() > 0 );

  cout << myname << line << endl;
  cout << myname << "Done." << endl;
  return 0;
}

//**********************************************************************

int main(int argc, char* argv[]) {
  return test_DuneSlowData();
}

//**********************************************************************
