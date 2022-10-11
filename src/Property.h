/* Property class, containing members that have
   private setter and public getter */
#include "Global.h"

template <typename T>
class Property
{
	T m_value;
	/* override implicit type cast */
	public:
		operator T() const
		{
			return m_value;
		}
	/* overload assignment */
	private:
		Property<T>& operator= (const T& value)
		{
			m_value = value;
			return *this;
		}

		friend class Global;
};
