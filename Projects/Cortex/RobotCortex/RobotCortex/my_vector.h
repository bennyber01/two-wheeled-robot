#pragma once

#include <assert.h>

#define ASSERT(a) assert(a)
#define NULL  0
#define FALSE 0
#define TRUE  1

template <class MY_VECTOR_TYPE>
class my_vector
{
public:
	my_vector()
	{
		arr = NULL;
		reset();
	}

	~my_vector() { reset(); }

	void reset()
	{
		if (arr)
			delete [] arr;
		arr = NULL;
		arrSize = freePlace = 0;
	}

	void clear() { freePlace = 0; }

	int size() const { return freePlace; }

	bool push_back(const MY_VECTOR_TYPE & obj)
	{
		if (freePlace >= arrSize)
		{
			int newArrSize = 2 * freePlace + 5;
			MY_VECTOR_TYPE * newArr = new MY_VECTOR_TYPE[newArrSize];

			if (!newArr)
			{
				ASSERT(FALSE);
				return false;
			}

			if (arr)
			{
				for (int i = 0; i < arrSize; ++i)
					newArr[i] = arr[i];

				delete [] arr;
			}
	
			arr = newArr;
			arrSize = newArrSize;
		}

		arr[freePlace] = obj;
		++freePlace;
		return true;
	}

	MY_VECTOR_TYPE & operator [] (int i)
	{
		ASSERT(i >= 0 && i < arrSize);

		return arr[i];
	}

	const MY_VECTOR_TYPE & operator [] (int i) const
	{
		ASSERT(i >= 0 && i < arrSize);

		return arr[i];
	}

private:
	MY_VECTOR_TYPE * arr;
	int arrSize;
	int freePlace;
};
