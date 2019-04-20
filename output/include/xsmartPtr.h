//2019/4/17
//��װ��������ָ��,���xShareable��������ʹ�á�ָ�������xShareable������

template<typename ElementType>

class xsmartPtr
{
public:
	explicit xsmartPtr(ElementType* ptr = NULL) : _pointer(ptr) {
		if (NULL != _pointer) {
			_pointer->inc();
		}
	}
	xsmartPtr(const xsmartPtr &other) : _pointer(other._pointer) {
		if (NULL != _pointer) {
			_pointer->inc();
		}
	}
	template <typename U>
	xsmartPtr(const xsmartPtr<U> &other) : _pointer(NULL) {
		_pointer = other.get();
		if (NULL != _pointer) {
			_pointer->inc();
		}
	}
	~xsmartPtr() {
		if (NULL != _pointer) {
			if (_pointer->dec() == 0) {
				delete _pointer;
				_pointer = NULL;
			}
		}
	}
	xsmartPtr & operator=(const xsmartPtr& r) {
		if(_pointer != r._pointer) { //�Ѿ��ж�(this != &r)
			if (NULL != r._pointer) {
				r._pointer->inc();
			}

			ElementType *ptr = _pointer;
			_pointer = r._pointer;
			if (NULL != ptr) {
				if(ptr->dec() == 0){
					delete ptr;
					ptr = NULL;
				}
			}
		}

		return *this;
	}
	ElementType* get() const {
		return _pointer;
	}
	ElementType* operator->() const {
		return _pointer;
	}
	ElementType& operator*() const {
		return *_pointer;
	}
	bool is_valid() const {
		return _pointer ? true : false;
	}
private:
	ElementType* _pointer;  /** �ײ���Դָ��*/
};
