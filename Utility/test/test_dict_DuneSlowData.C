void test_dict_DuneSlowData() {
  string myname = "test_DuneSlowData.C: ";
  string className = "DuneSlowData";
  cout << myname << "Fetching class " << className << endl;
  TClass tc(className.c_str());
  if ( tc.GetClassInfo() == nullptr ) {
    cout << myname << "Info no not found for class " << className << endl;
    exit(1);
  }
  tc.Print();
  cout << myname << "Done." << endl;
  exit(0);
}
