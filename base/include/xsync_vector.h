//2019/3/17 by xjshi
//线程安全vector 
#include "xsema.h"
#include "xAutoLock.h"
#include <vector>

namespace SEABASE
{
	template <typename ElemType>
	class xSyncVector
	{
	private:
		xSemaphore* m_psem;
		xMutex m_mutex;
		std::queue<ElemType> m_queue;
	public:
		xSyncVector()
		{
			m_psem=new xSemaphore;
		}
		~xSyncVector()
		{
			if(m_psem!=NULL)
				delete m_pse;m
		}
		int32_t put(ElemType elem)
		{
			xAutoLock L(m_mutex);
			try{
			m_queue.push(elem);
			}catch(std::bad_alloc &){
				return -1;
			}
			m_psem->signal();
			return 0;
		}
		int32_t get(ElemType&elem,int millisecond)
		{
			int32_t ret = m_psem->wait(millisecond);
			if(0 == ret)
			{
				xAutoLock L(m_mutex);
				elem = m_queue.front();
				m_queue.pop();
			}
			else
			{
				return -1;
			}
			return 0;
		}

		int32_t size() {
			return (int32_t)m_queue.size();
		}
		void clear()
		{
			xAutoLock L(m_mutex);
			while(m_queue.size()){
				m_queue.pop();
			}
		}
	protected:
		xSyncVector(const SyncVector&);
		xSyncVector& operator=(const SyncVector&);
	}
}