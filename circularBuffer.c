/* circularBuffer.c
 * Pascal-Emmanuel Lachance
 * https://www.github.com/Raesangur 
 * 
 * Generic circular buffer
 */
/*****************************************************************************/
/* File includes */
#include <stdlib.h>
#include <stdbool.h>
#include "circularBuffer.h"

/*****************************************************************************/
/* Private functions declarations */
bool circularBuffer_errorChecker(circularBuffer_t* buff);

/*****************************************************************************/
/* Public function definitions */
circularBuffer_t* circularBuffer_create(circularBuffer_t* buff, uint16_t number, uint8_t size)
{
	/* Dynamic memory allocation */
	/* Allocate memory for the circularBuffer structure */
	buff = (circularBuffer_t*)malloc(sizeof(circularBuffer_t));
	if (buff == NULL)
	{
		return NULL;
	}
	/* Allocates memory for number elements of size bytes */
	buff->buffer = malloc(number * size);
	if (buff->buffer == NULL)
	{
		return NULL;
	}

	/* Fill in default parameters */
	buff->num = number;                 /* Number of elements in the array */
	buff->size = size;                  /* Size (in bytes) of each element */

	/* Pointer points to the start of the array */
	buff->ptr = buff->buffer;

	/* Other pointer points to the end of the array */
	buff->maxPtr = (uint8_t*)buff->buffer + (size * number);

	return buff;                        /* Return buffer once it is created */
}

void circularBuffer_delete(circularBuffer_t* buff)
{
	/* Make sure there are no errors */
	if (buff->buffer == NULL)
	{
		return;
	}
	if (circularBuffer_errorChecker(buff) == false)
	{
		return;                         /* Return in the case of an error */
	}

	/* Free allocated memory */
	free(buff->buffer);

	/* Reset pointers */
	buff->buffer = NULL;
	buff->ptr = NULL;
	buff->maxPtr = NULL;
}

void circularBuffer_insert(circularBuffer_t* buff, void* data)
{
	/* Make sure there are no errors */
	if (circularBuffer_errorChecker(buff) == false)
	{
		return;                         /* Return in the case of an error */
	}
	if (data == NULL)
	{
		return;                         /* Return in the case of an error */
	}


	uint8_t i;
	for (i = 0; i < buff->size; i++)
	{
		*(uint8_t*)buff->ptr = *(uint8_t*)data;             /* Assign one byte of the value in the array */

		/* Increment pointers positions */
		buff->ptr = (uint8_t*)buff->ptr + 1;
		data = (uint8_t*)data + 1;

		/* Check pointer value */
		if (buff->ptr > buff->maxPtr)
		{
			buff->ptr = buff->buffer;   /* Reser pointer position */
			break;
		}
	}


	/* Check position of pointer */
	if (buff->ptr >= buff->maxPtr)
	{
		buff->ptr = buff->buffer;       /* Reset pointer position */
	}
}

void* circularBuffer_getElement(circularBuffer_t* buff, uint16_t num)
{
	/* Make sure there are no errors */
	if (circularBuffer_errorChecker(buff) == false)
	{
		return NULL;                    /* Return in the case of an error */
	}
	if (num >= buff->num)
	{
		return NULL;
	}

	/* Return the address of the element in the array */
	return (uint8_t*)buff->buffer + (num * buff->size);
}

/*****************************************************************************/
/* Private functions definitions */
bool circularBuffer_errorChecker(circularBuffer_t* buff)
{
	if (buff == NULL)
	{
		return false;                   /* FAILURE */
	}
	if (buff->buffer == NULL)
	{
		return false;                   /* FAILURE */
	}
	if (buff->ptr == NULL)
	{
		return false;                   /* FAILURE */
	}

	return true;                        /* SUCCESS : No errors */
}