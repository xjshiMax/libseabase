//2021/3/17

#include"xEmutex.h"
using namespace SEABASE;

//µ¥ÀýÄ£Ê½
namespace SEABASE
{
	template<class obj >
	class SingletonObj:private Noncopyable
	{
	public:
		static obj& getInstance()
		{
			  xGuard<xEmutex> guard(&m_lock);
			  return *m_pobj;

		}
	public:
		static xEmutex m_lock;
	private:
		static obj*m_pobj;
	};
	template<class obj >
	xEmutex SingletonObj<obj>::m_lock;

	template<class obj >
	obj* SingletonObj<obj>::m_pobj = new obj;
}

