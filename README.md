# circularBuffer
Generic circular buffers in C

HOW TO USE:

1. Create a circularBuffer_t pointer;
2. Assign the pointer using the circularBuffer_create() function.
   -circularBuffer_create() takes 3 parameters:
      - the pointer created in step 1
      - the number of elements in the buffer
      - the size in bytes of each elements
   -circularBuffer_create() will handle the memory allocation and return a pointer to the buffer if successful
    (if there was an error, the function will return NULL)
3. Insert new elements in the buffer using circularBuffer_insert().
4. Get the value of the elements using circularBuffer_getElement().



# ************ EXAMPLE CODE ************
```
#include "circularBuffer.h"

int main()
{
  /* Creation of the circularbuffer */
	static circularBuffer_t* cb = NULL;
	cb = circularBuffer_create(cb, 100, sizeof(float));

	float f = 0.0f;
	for (uint16_t i = 0; i < cb->num; i++)
	{
		circularBuffer_insert(cb, &f);
		f++;
	}
	
	float* temp;
	for (uint8_t i = 0; i < cb->num; i++)
	{
		temp = (float*)circularBuffer_getElement(cb, i);
		printf("%f \n", *temp);
	}

	uint16_t originalBytes = cb->num * cb->size;
	uint16_t fullBytes = originalBytes + sizeof(circularBuffer_t);
	float gain = (fullBytes * 100.0) / originalBytes;

	printf("This array takes %d bytes \n", fullBytes);
	printf("A normal array would have taken %d bytes \n", originalBytes);
	printf("There is a %f%% size ratio \n", gain);
}
```

The code above returns:  
```
0.000000  
1.000000  
2.000000  

...

98.000000  
99.000000  
This array takes 416 bytes  
A normal array would have taken 400 bytes  
There is a 104% size ratio  
```
