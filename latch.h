// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

template<bool init>
class Latch
{
public:
  void Reset()
  {
    mValue = init;
  }

  operator bool() const
  {
    return mValue;
  }

  bool operator=(bool v)
  {
    return mValue = (v != init) ? v : mValue;
  }

private:
  bool mValue = init;
};
