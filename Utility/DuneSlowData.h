// DuneSlowData.h
//
// David Adams.
// March 2020
//
// Class to access DUNE slow data downloaded by Hector Carranza at UTA.

#include <string>
#include "dune/DuneCommon/TPadManipulator.h"
#include "TGraph.h"

class DuneSlowData {

public:

  using Name = std::string;
  using LongIndex = unsigned long;
  using Time = unsigned int;
  struct TimeValue {
    Time time;
    float value;
    TimeValue() : time(0), value(0.0) { }
    TimeValue(Time a_time, float a_value) : time(a_time), value(a_value) { }
  };
  using TimeValueVector = std::vector<TimeValue>;

  // Ctor.
  // Key values:
  //   hvraw - Raw HV from the cathode power supply
  //   vbpmon - Voltage across the beam plug monitor resistor.
  //   pump - LAr pump setting (0 = off)
  DuneSlowData(Name key);

  // Reference time: June 1, 2108
  Time tref() const { return m_tref; }

  // Channel description.
  Name key() const { return m_key; }
  Name dcsLabel() const { return m_dcsLabel; }
  LongIndex dcsId() const { return m_dcsId; }
  float graphScale() const { return m_graphScale; }

  // # values.
  unsigned int size() const { return m_tvs.size(); }
  TimeValue getTimeMin() const { return m_tvTimeMin; }
  TimeValue getTimeMax() const { return m_tvTimeMax; }
  TimeValue getValueMin() const { return m_tvValueMin; }
  TimeValue getValueMax() const { return m_tvValueMax; }
  //float get(Index time) const;

  // Graph.
  TGraph& graph();
  TPadManipulator& pad();
  TPadManipulator& draw();

  // Reset the time range for the pad.
  // Time syntax is "YYYY-MM-DD HH:MM:SS".
  void setTimeRange();
  void setTimeRange(Time t1, Time t2);
  void setTimeRange(Name st1, Name st2);

private:

  Name m_key;
  Name m_dcsLabel;
  LongIndex m_dcsId;
  Time m_tref;
  TimeValueVector m_tvs;
  TimeValue m_tvTimeMin;
  TimeValue m_tvTimeMax;
  TimeValue m_tvValueMin;
  TimeValue m_tvValueMax;
  Name m_title;
  Name m_yTitle;
  float m_graphScale;
  TGraph m_gr;
  TPadManipulator m_pad;

};
