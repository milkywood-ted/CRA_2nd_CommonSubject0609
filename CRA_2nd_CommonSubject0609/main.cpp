

//int mission1();
int mission2();

#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#else

int main()
{
	mission2();
}
#endif