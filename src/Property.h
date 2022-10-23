/* Property class, containing members that have
   private setter and public getter */
#include "Global.h"

template <typename T>
class Property
{
	T m_value;
	/* override implicit type cast */
	public:
		operator T() const;
	/* overload assignment */
	private:
		Property<T>& operator=(const T& value);

	friend class Global;
};


template <typename T> Property<T>::operator T() const
{
	return m_value;
}

template <typename T> Property<T>& Property<T>::operator=(const T& value)
{
	m_value = value;
	return *this;
}
