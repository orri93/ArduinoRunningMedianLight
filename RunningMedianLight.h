//
//    FILE: RunningMedianLight.h
//  AUTHOR: Rob dot Tillaart at gmail dot com
//          
// PURPOSE: Lightweight RunningMedian library for Arduino
// VERSION: 0.0.1
// HISTORY: See RunningMedianLight.cpp
//
// Released to the public domain
//

#ifndef RunningMedian_h
#define RunningMedian_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <inttypes.h>

#define RUNNING_MEDIAN_LIGHT_VERSION "0.0.1"

// should at least be 5 to be practical
// odd size results in a 'real' middle element.
// even size takes the lower of the two middle elements
#ifndef MEDIAN_COUNT
#define MEDIAN_COUNT 8
#endif

#ifndef MEDIAN_UNDEFINED
#define MEDIAN_UNDEFINED NAN
#endif

#ifndef MEDIAN_TYPE
#define MEDIAN_TYPE float
#endif

class RunningMedianLight
{
public:
  RunningMedianLight();

  void add(const MEDIAN_TYPE & value);
  float median();  // returns the median == middle element

protected:
  uint8_t _cnt;
  uint8_t _idx;

  MEDIAN_TYPE _ar[MEDIAN_COUNT];
  uint8_t _p[MEDIAN_COUNT];

  bool _sorted;

  void sort();
};

#endif
// END OF FILE