#include <stdlib.h>


/**
 * 
 * Basic CRC-32 Algorithm
 *
 **/
unsigned int crc32(unsigned char *message){
	int i, j;
	unsigned int byte, crcl

	i = 0;
	crc = 0xFFFFFFFF;
	while (message[i] != 0){
		byte = message[i];					// Get next byte.
		byte = reverse(byte);				// 32-bit reversal.
		for (j = 0; j <= 7; ++j){			// Do eight times.
			if ((int)(crc ^ byte) < 0)
				crc = (crc << 1) ^ 0x04C11DB7;
			else crc = crc << 1;
			byte = byte << 1;				// Ready next msg bit.
		}
		i = i + 1;
	}
	return reverse(-crc);
}


/**
 * 
 * Improved CRC-32 Algorithm
 *
 **/
unsigned int crc32(unsigned char *message){
	int i, j;
	unsigned int byte, crc, mask;

	i = 0;
	crc = 0xFFFFFFFF;
	while (message[i] != 0){
		byte = message[i];					// Get next byte.
		crc = crc ^ byte;
		for (j = 7; j >= 0; --j){			// Do eight times.
			mask = -(crc & 1);
			crc = (crc >> 1) ^ (0xEDB88320 & mask);
		}
		i = i + 1;
	}
	return -crc;
}



/**
 * 
 * Lookup method to compute CRC-32 Algorithm
 *
 **/
unsigned int crc32(unsigned char *message){
	int i, j;
	unsigned int byte, crc, mask;
	static unsigned int table[256];

	/* Set up the table, if necessary. */

	if (table[1] == 0){
		for (byte = 0; byte <= 255; ++byte){
			crc = byte;
			for (j = 7; j >= 0; --j){	// Do eight times.
				mask = -(crc & 1);
				crc = (crc >> 1) ^ (0xEDB88320 & mask);
			}
			table[byte] = crc;
		}
	}
	/* Through with table setup, now calculate the CRC. */

	i = 0;
	crc = 0xFFFFFFFF;
	while ((byte = message[i]) != 0) {
		crc = (crc >> 8) ^ table[(crc ^ byte) & 0xFF];
		i = i + 1;
	}	
	return -crc;
}





