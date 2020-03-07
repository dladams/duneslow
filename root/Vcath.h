// Vcath.h
//
// David Adams
// March 2020
//
// Evaluate PDSP cathode voltage based on Heiziger voltage.
//
// See https://indico.fnal.gov/event/20939/contribution/1/material/slides/0.pdf.
//
// Units are MOhm and kV.

class Vcath {

public:

  float rfilt;  // 90 or 47
  float rfc = 1369.0;
  float rterm = 7.0;
  float rbeam = 61601.0;
  float vterm = 1.165;

  Vcath(float a_rfilt) : rfilt(a_rfilt) { };

  float get(float vheinz) {
    float num = vheinz/rfilt + vterm/rfc;
    float den = 1.0/rfc + 1.0/rfilt + 1.0/rbeam;
    return num/den;
  }

};
    

