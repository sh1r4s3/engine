#include "events.hpp"

using namespace WndSysEvents;

template <typename T>
HashEvent<T>::HashEvent(int tblSz, std::function<int(const T&)> hashFunc)
  : mHashFunc(hashFunc), mTblSz(tblSz), mHashTbl(new event[tblSz]) {

  // TODO: check that mHashTbl not nullptr
  for (int i = 0; i < tblSz; mHashTbl[i++] = empty);
}

template <typename T>
event &HashEvent<T>::operator[](const T &sysEv) {
  return mHashTbl[mHashFunc(sysEv)];
}
