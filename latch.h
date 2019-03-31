#include <functional>
#include <array>

template<bool init>
class Latch
{
public:
	operator bool() const
	{
		return mValue;
	}

	bool operator=(bool v)
	{
		mValue = (v != init) ? v : mValue;

		if (CallbackT& cb = mCallback[unsigned(v)])
		{
			cb();
		}

		return mValue;
	}

	using CallbackT = std::function<void(void)>;

	CallbackT onAssigned(bool v, CallbackT callback)
	{
		mCallback[unsigned(v)].swap(callback);
		return callback;
	}

private:
	bool mValue = init;
	std::array<CallbackT, 2> mCallback;
};