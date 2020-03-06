// PdspHv.C

#include "PdspHv.h"

PdspHv::PdspHv() {
  using Name = std::string;
  using NameVector = std::vector<Name>;
  using Index = unsigned int;
  TDatime refdate(2018, 6,1, 0, 0, 0);
  m_tref = refdate.Convert();
  const Name myname = "PdspHv::ctor: ";
  NameVector fnams;
  Name fpre = "/pnfs/dune/persistent/users/hectorc/HV_voltage_averg_5min/Vaverg_";
  fnams.push_back(fpre + "2018/NP04averg_HVvoltage_01-10-2018_01-11-2018.txt");
  fnams.push_back(fpre + "2018/NP04averg_HVvoltage_01-11-2018_01-12-2018.txt");
  fnams.push_back(fpre + "2018/NP04averg_HVvoltage_01-12-2018_01-01-2019.txt");
  fnams.push_back(fpre + "2019/NP04averg_HVvoltage_01-01-2019_01-02-2019.txt");
  fnams.push_back(fpre + "2019/NP04averg_HVvoltage_01-02-2019_01-03-2019.txt");
  fnams.push_back(fpre + "2019/NP04averg_HVvoltage_01-03-2019_01-04-2019.txt");
  fnams.push_back(fpre + "2019/NP04averg_HVvoltage_01-04-2019_01-05-2019.txt");
  fnams.push_back(fpre + "2019/NP04averg_HVvoltage_01-05-2019_01-06-2019.txt");
  fnams.push_back(fpre + "2019/NP04averg_HVvoltage_01-06-2019_01-07-2019.txt");
  fnams.push_back(fpre + "2019/NP04averg_HVvoltage_01-07-2019_01-08-2019.txt");
  fnams.push_back(fpre + "2019/NP04averg_HVvoltage_01-08-2019_01-09-2019.txt");
  fnams.push_back(fpre + "2019/NP04averg_HVvoltage_01-09-2019_01-10-2019.txt");
  fnams.push_back(fpre + "2019/NP04averg_HVvoltage_01-10-2019_01-11-2019.txt");
  fnams.push_back(fpre + "2019/NP04averg_HVvoltage_01-11-2019_01-12-2019.txt");
  fnams.push_back(fpre + "2019/NP04averg_HVvoltage_01-12-2019_01-01-2020.txt");
  cout << myname << "File count is " << fnams.size() << endl;
  for ( Name fnam : fnams ) {
    ifstream fin(fnam.c_str());
    if ( ! fin ) {
      cout << myname << "Unable to open " << fnam << endl;
      continue;
    }
    Index count = 0;
    string line;
    while ( ! std::getline(fin, line).eof() ) {
      if ( line.size() == 0 ) break;
      ++count;
      TimeValue tv;
      istringstream sslin(line);
      sslin >> tv.time;
      if ( tv.time < tref() ) continue;
      tv.time -= tref();
      sslin >> tv.value;
      tv.value *= 0.001;
      m_tvs.push_back(tv);
    }
    cout << myname << "Line count for " << fnam << " is " << count << endl;
  }
  cout << myname << "Value count is " << size() << endl;
}

TGraph& PdspHv::graph() {
  if ( m_gr.GetN() == 0 ) {
    for ( const TimeValue& tv : m_tvs ) {
      m_gr.SetPoint(m_gr.GetN(), tv.time, tv.value);
    }
    m_gr.GetXaxis()->SetTimeFormat("20%y-%m-%d%F2018-06-01 00:00:00");
    m_gr.GetXaxis()->SetTimeDisplay(1);
    m_gr.GetXaxis()->SetTitle("Date");
    m_gr.GetYaxis()->SetTitle("Raw voltage [kV]");
    m_gr.SetTitle("ProtoDUNE SP cathode voltage");
  }
  return m_gr;
}
