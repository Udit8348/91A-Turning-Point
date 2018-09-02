//set the number of previous values stored by the filter
#define MAX_SAMPLES 3

//Data structure for the linear recursive exponential (LRE) filter 
typedef struct{
	//Stores the current, unfiltered input value
	float rawValue;

	//Circular array with previous filtered values, size based on max number of prev samples considered
	float prevValues[MAX_SAMPLES];

	//sum of all the values in the array
	float total;
		
	//Avg of values in the array
	float avg;
	
	//Oldest index in the array
	int index;

}LRE_filter;

//Placeholder instance of the LRE_filter object
static LRE_filter FooBar;

/**

* initialize filter structure, fill prevValues array with starting input value, calculate avg value
*
* @param instance of filter structure	-->(filter)
* @param raw (unfiltered) input value	-->(val)
*/

void lrefInit(LRE_filter filter, float val)
{
	//Set starting sensor value
	filter.rawValue = val;
	filter.total = 0;
	filter.index = 0;
	
	//Populate array, and get initial sum of the values in the array
	for(int i = 0; i < MAX_SAMPLES; i++){
		filter.prevValues[i] = filter.rawValue;
		filter.total+= filter.prevValues[i];	//@@might need to preform sum once the entire array is populated
	}
	
	//Calculate the average value of the array
	filter.avg = filter.total/MAX_SAMPLES;
}

/**

* update filter structure, uses simple linear recursive exponential filter, also limits mem usage
*
* @param instance of filter structure	-->(filter)
* @param weighting of the filter		-->(weight)
* @param raw (unfiltered) input value	-->(val)
*/

float lrefUpdate(LRE_filter filter, float weight, float val)
{
	filter.rawValue = val;

	//Calculate new filtered value
	float newVal = weight * filter.rawValue + (1 - weight) * filter.avg;
	
	//Update sum by adding new value and subtracting oldest value
	filter.total = filter.total + newVal - filter.prevValues[filter.index];
		
	//Replace oldest array value with newest value
	filter.prevValues[filter.index] = newVal;
		
	//Increment the index of the oldest value, return to start of the array at the end of the array
	if(filter.index < MAX_SAMPLES){
		filter.index++;	
	}else{
		filter.index = 0;
	}	
		
	//Update avg
	filter.avg = filter.total/MAX_SAMPLES;

	//Return filtered value
	return newVal;
}
