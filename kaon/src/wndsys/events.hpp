#include <functional>

namespace WndSysEvents {
  enum event {
    empty = 0,
    keyPress,
    draw,
    error
  };

  template <typename T>
  class HashEvent {
  private:
    int mTblSz;
    std::function<int(const T&)> mHashFunc;
    event *mHashTbl;

  public:
    HashEvent(int tblSz, std::function<int(const T&)> hashFunc)
      : mHashFunc(hashFunc), mTblSz(tblSz), mHashTbl(new event[tblSz]) {

      // TODO: check that mHashTbl not nullptr
      for (int i = 0; i < tblSz; mHashTbl[i++] = empty);
    }

    event& operator[] (const T& sysEv) {
      // TODO: inform about an error
      int idx = mHashFunc(sysEv);
      if (idx < 0 || idx >= mTblSz) {
        idx = 0;
      }
      return mHashTbl[idx];
    }
  };
}
