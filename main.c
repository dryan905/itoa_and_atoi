#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Function to reverse the order of the characters 
void reverse(uint8_t * ptr_1, uint8_t length) 
{ 
	uint8_t start = 0; 
	uint8_t end = length -2;
    uint8_t temp;

    while (start < end)
    {
        temp = *(ptr_1+start);
        *(ptr_1+start) = *(ptr_1+end);
        *(ptr_1+end) = temp;

        start++;
        end--;
    }
}

// A function to calculate the twos complement of a binary number
void twos_compliment(uint8_t * addr, uint8_t index){

	// Invert all bits
	for(int i=0; i < index-1; i++){

			if (*addr == '0')
				*addr = '1';
			else if (*addr == '1')	
				*addr = '0';

			addr++;
		}

		// Avoid the '\0' character 
		addr--;

		// Add 1 to the binary number
		int carry = 1;
		for(int i=0;i < index-1; i++){
        	if(*addr == '1' && carry == 1)
        	{
            	*addr = '0';
        	}
        	else if(*addr == '0' && carry == 1)
        	{
            	*addr = '1';
            	carry = 0;
        	}
			addr--;
		}
}

// Implementation of itoa() 
uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base)
{ 
	int32_t copy_of_data = data;
    uint8_t * base_addr = ptr; 
	_Bool isNegative = 0;
    uint8_t index = 0;

	// Case for handling 0 input
	if (data == 0) 
	{ 
		*(ptr++) = '0'; 
		*(ptr++) = '\0';
		index = 2; 
		return index; 
	} 

	// Needed to handle negative numbers with base 10
	if (data < 0 && base == 10) 
	{ 
		isNegative = 1; 
		data = -data; 			// Invert so you are dealing with postive numbber
		
	} 

	// Needed to handle negative numbers with base 2
	if (data < 0 && base == 2) 
	{ 
		isNegative = 1;
		data = -data;			// Invert so you are dealing with postive numbber
		copy_of_data = data;	//Copy of data is needed to calculate range.
	} 

	// Process individual digits 
	while (data != 0) 
	{ 
		int32_t rem = data % base; 
		*ptr = (rem > 9)? (uint8_t)((rem - 10) + 'A') : (uint8_t)(rem + '0'); 
		data = data/base; 
        index++;
		ptr++;
	} 

	// Calculate the number of bits needed to represent a signed number in binary.
	int upper_range = (1<<index-1)-1;
	if (copy_of_data > upper_range && isNegative)
	{
		*(ptr++) = '0';
		index++;	
	}
	

	// If number is negative and base 10, append '-' 
	if (isNegative && base == 10){
        *(ptr++) = '-';
        index++;
    }

	*ptr = '\0'; // Append string terminator 
    index++;

	// Reset pointer to base address and reverse the order of characters 
	ptr = base_addr;
	reverse(ptr, index);

	// Calculate the twos compilment of number if negative and base is 2
	if (isNegative && base == 2){
		ptr = base_addr;
		twos_compliment(ptr, index);
    } 
	ptr = base_addr;
	return index; 
} 

// Implementation of atoi() 
int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base){

	int32_t result = 0; 	// Initialize result
	int32_t value_dec = 0; 	// Initialize result
	int32_t sign = 1; 		// Initialize sign as positive
	int32_t power = 1; 		// Initialize power
	int starting_index = 0;	// Initialize the starting index for character

	// If number is negative, then update sign and starting index 
	if (*ptr == '-') { 
		sign = -1; 
		starting_index = 1;
	}

	// If number is binary negative, then update sign 
	if (base == 2 && *ptr == '1') { 
		sign = -1; 
	} 
	 
	
	uint8_t  i = digits -2;
	int len = digits -2;
	
	while(len >= starting_index)
	{
		uint8_t value_char = *(ptr + i); 
		value_dec = (value_char > '9')? (int32_t)((value_char - 'A') + 10) : (int32_t)(value_char - '0');
		result += value_dec * power;
		power = power * base;
		len--;
		i--;
	}

	// Return result with sign 
	return sign * result;
}



int main(){
    int32_t data = -59;
    uint8_t *ptr = (uint8_t *)malloc(10);
	uint8_t * base_addr = ptr;
    int32_t base = 2;
    uint8_t ans;

    ans = my_itoa(data, ptr, base);
	for (uint8_t i = 0; i < ans; i++)
	{
		printf("*ptr[%d]: %c\n", i, *(ptr+i));
	}
	

    printf("Answer: %d\n", ans);

	//  uint8_t *ptr = (uint8_t *)malloc(10);
	//  uint8_t * base_addr = ptr;
	//  int32_t value = 0;

	//  *(ptr++) = '1';
	//  *(ptr++) = '1';		// Index: 0
	//  *(ptr++) = '0';		// Index: 1
	//  *(ptr++) = '1';		// Index: 2
	//  *(ptr) = '\0';			// Index: 3

	//  value = my_atoi(base_addr, 3, base);
	//  printf("Answer: %d\n", value);


	


    free(ptr);

    return 0;

}


