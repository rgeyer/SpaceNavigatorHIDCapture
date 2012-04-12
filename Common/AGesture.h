#ifndef __IGESTURE_H__
#define __IGESTURE_H__

#include <string>

using namespace std;

class AGesture
{
public:
	virtual ~AGesture() {}
	virtual long getValue() = 0;
	virtual bool equals(AGesture*);
};

#endif