// PdspHv.h
//

class PdspHv {

public:

  using Time = unsigned int;
  struct TimeValue {
    Time time;
    float value;
    TimeValue() : time(0), value(0.0) { }
    TimeValue(Time a_time, float a_value) : time(a_time), value(a_value) { }
  };
  using TimeValueVector = std::vector<TimeValue>;

  // Ctor.
  PdspHv();

  // Reference time: June 1, 2108
  Time tref() const { return m_tref; }

  // # values.
  unsigned int size() const { return m_tvs.size(); }

  // Graph.
  TGraph& graph();

private:

  Time m_tref;
  TimeValueVector m_tvs;
  TGraph m_gr;

};
