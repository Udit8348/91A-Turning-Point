typedef struct{
	//Stores the current, unfiltered sensor value
	float rawValue;

	//Circular array with previous filtered values
	float prevValues[3];

	//avg of last 3 filtered values
	float avg;

}LRE_filter;

static LRE_filter fwVel;

/**

* initialize filter structure, fill prevValues array with starting sensor values
* @param instance of filter structure
* @param raw (unfiltered) input value
*/

void lrefInit(LRE_filter filter, float val)
{
	filter.rawValue = val;
	filter.prevValues[0] = filter.rawValue;
	filter.prevValues[1] = filter.rawValue;
	filter.prevValues[2] = filter.rawValue;

	filter.avg = (filter.prevValues[0] + filter.prevValues[1] + filter.prevValues[2])/3;
}

/**

* update filter structure, uses simple linear recursive exponential filter, also limits mem usage
*
* @param instance of filter structure
* @param weighting of the filter
* @param raw (unfiltered) input value
*/

float lrefUpdate(LRE_filter filter, float weight, float val)
{
	filter.rawValue = val;
	filter.prevValues[0] = filter.prevValues[1];	//2nd -> 3rd
	filter.prevValues[1] = filter.prevValues[2];	//1st -> 2nd

	float lreFilter = weight * filter.rawValue + (1 - weight) * filter.avg;
	filter.prevValues[2] = lreFilter;							//new -> 1st

	return lreFilter;
}
