typedef struct{
	//Stores the current, unfiltered sensor value
	float rawValue;

	//Circular array with previous filtered values
	float prevValues[3];

	//sum of all the values in the array
	float total
		
	//Avg of last 3 filtered values
	float avg;
	
	//Oldest index in the array
	int index;

}LRE_filter;

//Placeholder instance of the LRE_filter object
static LRE_filter FooBar;

//set the number of previous values stored by the filter
#define SAMPLES 3

/**

* initialize filter structure, fill prevValues array with starting sensor value, calculate avg value
* @param instance of filter structure
* @param raw (unfiltered) input value
*/

void lrefInit(LRE_filter filter, float val)
{
	//Set starting sensor value
	filter.rawValue = val;
	filter.total = 0;
	filter.index = 0;
	
	for(int i = 0; i < SAMPLES - 1; i++){
		filter.prevValues[i] = filter.rawValue;
		filter.total+= filter.prevValues[i];	//@@might need to preform sum once the entire array is populated
	}
	
	filter.avg = filter.total/3;
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

	//Calculate new filtered value
	float newVal = weight * filter.rawValue + (1 - weight) * filter.avg;
	
	//Update sum by adding new value and subtracting oldest value
	filter.total = filter.total + newVal - filter.prevValues[filter.index]
		
	//Replace oldest array value with newest value
	filter.prevValues[filter.index] = newVal;
		
	//Increment the index of the oldest value
	if(filter.index < SAMPLES -1){
		filter.index++;
	}else{
		filter.index = 0;
	}	
	
		//add circular logic
		
	//Update avg
	filter.avg = filter.total/SAMPLES;

	//Return filtered value
	return lreFilter;
}
