#pragma once

class HasDPSUpgrade {
public:
  virtual void updateDPSRatio(double ratio) = 0;
  virtual void updateDPSValue(int value) = 0;
};