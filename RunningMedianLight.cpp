//
//    FILE: RunningMedian.cpp
//  AUTHOR: Rob.Tillaart at gmail.com
// VERSION: 0.1.15
// PURPOSE: RunningMedian library for Arduino
//
// HISTORY:
// 0.1.00 - 2011-02-16 initial version
// 0.1.01 - 2011-02-22 added remarks from CodingBadly
// 0.1.02 - 2012-03-15 added
// 0.1.03 - 2013-09-30 added _sorted flag, minor refactor
// 0.1.04 - 2013-10-17 added getAverage(uint8_t) - kudo's to Sembazuru
// 0.1.05 - 2013-10-18 fixed bug in sort; removes default constructor; dynamic memory
// 0.1.06 - 2013-10-19 faster sort, dynamic arrays, replaced sorted float array with indirection array
// 0.1.07 - 2013-10-19 add correct median if _cnt is even.
// 0.1.08 - 2013-10-20 add getElement(), add getSottedElement() add predict()
// 0.1.09 - 2014-11-25 float to double (support ARM)
// 0.1.10 - 2015-03-07 fix clear
// 0.1.11 - 2015-03-29 undo 0.1.10 fix clear
// 0.1.12 - 2015-07-12 refactor constructor + const
// 0.1.13 - 2015-10-30 fix getElement(n) - kudos to Gdunge
// 0.1.14 - 2017-07-26 revert double to float - issue #33
// 0.1.15 - 2018-08-24 make runningMedian Configurable #110
//
// Released to the public domain
//

#include "RunningMedianLight.h"

RunningMedianLight::RunningMedianLight() : _cnt(0), _idx(0), _sorted(false) {
}

// adds a new value to the data-set
// or overwrites the oldest if full.
void RunningMedianLight::add(const MEDIAN_TYPE& value) {
  _ar[_idx++] = value;
  if (_idx >= MEDIAN_COUNT) _idx = 0; // wrap around
  if (_cnt < MEDIAN_COUNT) _cnt++;
  _sorted = false;
}

MEDIAN_TYPE RunningMedianLight::median()
{
  if (_cnt == 0) return MEDIAN_UNDEFINED;

  if (_sorted == false) sort();

  if (_cnt & 0x01) return _ar[_p[_cnt/2]];
  else return (_ar[_p[_cnt/2]] + _ar[_p[_cnt/2 - 1]]) / 2;
}

/*
MEDIAN_TYPE RunningMedian::average()
{
  if (_cnt == 0) return MEDIAN_UNDEFINED;

  float sum = 0;
  for (uint8_t i=0; i< _cnt; i++) sum += _ar[i];
  return sum / _cnt;
}
*/

void RunningMedianLight::sort()
{
  // bubble sort with flag
  for (uint8_t i = 0; i < _cnt-1; i++)
  {
    bool flag = true;
    for (uint8_t j = 1; j < _cnt-i; j++)
    {
      if (_ar[_p[j-1]] > _ar[_p[j]])
      {
        uint8_t t = _p[j-1];
        _p[j-1] = _p[j];
        _p[j] = t;
        flag = false;
      }
    }
    if (flag) break;
  }
  _sorted = true;
}

// END OF FILE