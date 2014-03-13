#include "common.h"

QString int_to_QString(int val) {
  std::ostringstream stm;
  stm << val;
  return QString::fromStdString(stm.str());
}

QString double_to_QString(double val, int fixed) {
  std::ostringstream stm;
  if (fixed) stm << std::fixed << val; else stm << val;
  return QString::fromStdString(stm.str());
}
