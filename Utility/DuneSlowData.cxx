// DuneSlowData.cxx

#include "DuneSlowData.h"
#include "TDatime.h"
#include "TAxis.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;


DuneSlowData::DuneSlowData(Name key) :
m_graphScale(1.0), m_pad(1400, 500) {
  using NameVector = std::vector<Name>;
  using Index = unsigned int;
  TDatime refdate(2018, 6,1, 0, 0, 0);
  m_tref = refdate.Convert();
  const Name myname = "DuneSlowData::ctor: ";
  Name fpre;
  NameVector fnams;
  if ( key == "hvraw" ) {
    m_key = "hvraw";
    m_dcsLabel = "Voltage Raw";
    m_dcsId  = 0;
    m_yTitle = "Raw voltage [kV]";
    m_title = "HV supply voltage";
    m_graphScale = 0.001;
    fpre = "/pnfs/dune/persistent/users/hectorc/HV_supplyrawV_averg_5min/Vraw_averg_";
    Name flab = "NP04averg_HVvoltage_";
    fnams.push_back(fpre + "2018/" + flab + "01-10-2018_01-11-2018.txt");
    fnams.push_back(fpre + "2018/" + flab + "01-11-2018_01-12-2018.txt");
    fnams.push_back(fpre + "2018/" + flab + "01-12-2018_01-01-2019.txt");
    fnams.push_back(fpre + "2019/" + flab + "01-01-2019_01-02-2019.txt");
    fnams.push_back(fpre + "2019/" + flab + "01-02-2019_01-03-2019.txt");
    fnams.push_back(fpre + "2019/" + flab + "01-03-2019_01-04-2019.txt");
    fnams.push_back(fpre + "2019/" + flab + "01-04-2019_01-05-2019.txt");
    fnams.push_back(fpre + "2019/" + flab + "01-05-2019_01-06-2019.txt");
    fnams.push_back(fpre + "2019/" + flab + "01-06-2019_01-07-2019.txt");
    fnams.push_back(fpre + "2019/" + flab + "01-07-2019_01-08-2019.txt");
    fnams.push_back(fpre + "2019/" + flab + "01-08-2019_01-09-2019.txt");
    fnams.push_back(fpre + "2019/" + flab + "01-09-2019_01-10-2019.txt");
    fnams.push_back(fpre + "2019/" + flab + "01-10-2019_01-11-2019.txt");
    fnams.push_back(fpre + "2019/" + flab + "01-11-2019_01-12-2019.txt");
    fnams.push_back(fpre + "2019/" + flab + "01-12-2019_01-01-2020.txt");
  } else if ( key == "vbpmon" ) {
    m_key = "vbpmon";
    m_dcsLabel = "GroundPlanes_Ch14";
    m_dcsId  = 47895881449754;
    m_yTitle = "-Voltage [V]";
    m_title = "Beam plug monitor voltage";
    m_graphScale = -1.0;
    fpre = "/pnfs/dune/persistent/users/hectorc/groundplanes_Ch14_averg_5min/GPaverg_CH14_";
    fnams.push_back(fpre + "2019/NP04averg_HVGP_CH14_01-10-2018_01-01-2019.txt");
    fnams.push_back(fpre + "2018/NP04averg_HVGP_CH14_01-01-2019_01-04-2019.txt");
    fnams.push_back(fpre + "2019/NP04averg_HVGP_CH14_01-04-2019_01-07-2019.txt");
    fnams.push_back(fpre + "2019/NP04averg_HVGP_CH14_01-07-2019_01-10-2019.txt");
    fnams.push_back(fpre + "2019/NP04averg_HVGP_CH14_01-10-2019_01-01-2020.txt");
  } else if ( key == "pump" ) {
    m_key = "pump";
    m_dcsLabel = "??";
    m_dcsId  = 0;
    m_yTitle = "Rate [%]";
    m_title = "LAr pump rate";
    Name flab = "NP04averg_LArinlet_";
    fpre = "/pnfs/dune/persistent/users/hectorc/lar_inlet_valve_averg_5min/" + flab;
    fnams.push_back(fpre + "01-10-2018_01-01-2019.txt");
    fnams.push_back(fpre + "01-01-2019_01-04-2019.txt");
    fnams.push_back(fpre + "01-04-2019_01-07-2019.txt");
    fnams.push_back(fpre + "01-07-2019_01-10-2019.txt");
    fnams.push_back(fpre + "01-10-2019_01-01-2020.txt");
  } else {
    cout << myname << "ERROR: Unknown key: " << key << endl;
    return;
  }
  cout << myname << "File count is " << fnams.size() << endl;
  // Fetch the time-value array.
  bool first = true;
  for ( Name fnam : fnams ) {
    ifstream fin(fnam.c_str());
    if ( ! fin ) {
      cout << myname << "Unable to open " << fnam << endl;
      continue;
    }
    Index count = 0;
    Name line;
    while ( ! std::getline(fin, line).eof() ) {
      if ( line.size() == 0 ) break;
      ++count;
      TimeValue tv;
      istringstream sslin(line);
      sslin >> tv.time;
      if ( tv.time < tref() ) continue;
      tv.time -= tref();
      sslin >> tv.value;
      m_tvs.push_back(tv);
      if ( first ) {
        m_tvTimeMin = tv;
        m_tvTimeMax = tv;
        m_tvValueMin = tv;
        m_tvValueMax = tv;
        first = false;
      } else {
        if ( tv.time  <  m_tvTimeMin.time   ) m_tvTimeMin  = tv;
        if ( tv.time  >= m_tvTimeMax.time   ) m_tvTimeMax  = tv;
        if ( tv.value <  m_tvValueMin.value ) m_tvValueMin = tv;
        if ( tv.value >= m_tvValueMax.value ) m_tvValueMax = tv;
      }
    }
    cout << myname << "Line count for " << fnam << " is " << count << endl;
  }
  cout << myname << "Value count is " << size() << endl;
}

TGraph& DuneSlowData::graph() {
  if ( m_gr.GetN() == 0 ) {
    for ( const TimeValue& tv : m_tvs ) {
      m_gr.SetPoint(m_gr.GetN(), tv.time, graphScale()*tv.value);
    }
    m_gr.GetXaxis()->SetTimeFormat("20%y-%m-%d%F2018-06-01 00:00:00");
    m_gr.GetXaxis()->SetTimeDisplay(1);
    m_gr.GetXaxis()->SetTitle("Date");
    m_gr.GetYaxis()->SetTitle(m_yTitle.c_str());
    m_gr.SetTitle(m_title.c_str());
  }
  return m_gr;
}

TPadManipulator& DuneSlowData::pad() {
  const Name myname = "DuneSlowData::pad: ";
  if ( m_pad.graph() == nullptr ) {
    m_pad.add(&graph());
    m_pad.setTimeOffset(tref());
    m_pad.setTimeFormatX("20%y-%m-%d");
    float y1 = graphScale()*getValueMin().value;
    float y2 = graphScale()*getValueMax().value;
    if ( graphScale() < 0.0 ) {
      float ytmp = y1;
      y1 = y2;
      y2 = ytmp;
    }
    float dy = 0.01*(y2 - y1);
    y1 = y1 - dy;
    y2 = y2 + dy;
    cout << myname << "Y12: " << y1 << ", " << y2 << endl;
    m_pad.setRangeY(y1, y2);
    //m_pad.addAxis();
    if ( y1*y2 < 0.0 ) {
      m_pad.addHorizontalLine(0.0);
    }
    setTimeRange();
  }
  return m_pad;
}

TPadManipulator& DuneSlowData::draw() {
  pad().draw();
  return pad();
}

void DuneSlowData::setTimeRange() {
  float x1 = m_tvTimeMin.time;
  float x2 = m_tvTimeMax.time;
  float dx = 0.01*(x2 - x1);
  x1 = x1 > dx ? x1 - dx : 0.0;
  x2 = x2 + dx;
  return setTimeRange(x1, x2);
}

void DuneSlowData::setTimeRange(Time t1, Time t2) {
  if ( t1 >= t2 ) return;
  m_pad.setRangeX(t1, t2);
  Time hour = 3600;
  Time day = 24*hour;
  Time week = 7*day;
  Time fourWeek = 4*week;
  Time dt = t2 - t1;
  float tmod = fourWeek;
  if ( dt < 10*hour ) tmod = hour;
  else if ( dt < 10*day ) tmod = day;
  else if ( dt < 10*week ) tmod = week;
  Time t0 = tref();
  cout << tmod << endl;
  m_pad.addVerticalModLines(tmod, t0);
}

void DuneSlowData::setTimeRange(Name st1, Name st2) {
  Time t1 = TDatime(st1.c_str()).Convert() - tref();
  Time t2 = TDatime(st2.c_str()).Convert() - tref();
  setTimeRange(t1, t2);
}
