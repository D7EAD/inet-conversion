/*

	inet-conversion : dotted-decimal -> numeric (and vice-versa) conversion for internet protocol version 4 addresses:
		I wrote this up out of boredom mostly--plus it's cool to visualize IP format conversion in action.

		This is only for internet family INET and not INET6, although the process for family 6 addresses is pretty much
		the same--with respective bit shift adjustments.

		Real world examples of these conversion implementations can be found in functions inet_ntoa and inet_aton/inet_pton.

	explanation & illustration:
		Below you can find implementations with the below functions, as well as an illustration and explanation of what they
		actually do when given their respective data.

-----------------------------------------------------------------------------------------------------------------------------------------

	function v4ToInt : INET (V4) to numeric representation
		This function takes four octets of an INET family address in dotted-decimal format and bit shifts each respective octet
		to the left along a total of 32 bits and adds them together. Below you can find an illustration:

			 v4ToInt({138, 2, 244, 72}) -> | octet 1: 138 -> 10001010 |
	                                               | octet 2: 2   -> 00000010 |
						       | octet 3: 244 -> 11110100 |
						       | octet 4: 72  -> 01001000 |

		138 << 24 -> 10001010 00000000 00000000 00000000 : shift octet 1 to its respective position along a 32 bit uint
		2   << 16 -> 00000000 00000010 00000000 00000000 : shift octet 2 to its respective position along a 32 bit uint
		244 << 8  -> 00000000 00000000 11110100 00000000 : shift octet 3 to its respective position along a 32 bit uint
		72  << 0  -> 00000000 00000000 00000000 01001000 : shift octet 4 to its respective position along a 32 bit uint
		          == 10001010 00000010 11110100 01001000 : 2315449416 is the numeric form of 138.2.244.72

-----------------------------------------------------------------------------------------------------------------------------------------

	function intToV4 : numeric representation to INET (V4) dotted-decimal notation
		This function takes a 32-bit unsigned integer, bit shifts each respective octet to the far right and performs a bitwise OR (&)
		operation on the bit shifted octet--this results in the respective dotted-decimal notation octet value.

		intToV4(2315449416) -> 2315449416 = 10001010 00000010 11110100 01001000

			                    10001010 00000010 11110100 01001000
		-------------------------------------------------------------------------------
		(2315449416 >> 24) & 255 -> 00000000 00000000 00000000 10001010
					  & 00000000 00000000 00000000 11111111
					                             = 10001010 -> 138
		(2315449416 >> 16) & 255 -> 00000000 00000000 10001010 00000010
					  & 00000000 00000000 00000000 11111111
					                             = 00000010 -> 2
		(2315449416 >> 8)  & 255 -> 00000000 10001010 00000010 11110100
			                  & 00000000 00000000 00000000 11111111
				                                     = 11110100 -> 244
		(2315449416 >> 0)  & 255 -> 10001010 00000010 11110100 01001000
				          & 00000000 00000000 00000000 11111111
								     = 01001000 -> 72
		-------------------------------------------------------------------------------
				          = 10001010.00000010.11110100.01001000 == 138.2.244.72

		*IP addresses are never negative--they are unsigned. They do not utilize binary-one padding for right shifts.
		Signed and unsigned numbers pad differently in right shifts. Left shifts always pad with zero.
			i.e.                                   10001010 00000010 11110100 01001000
				unsigned : 2315449416 >> 24 -> 00000000 00000000 00000000 10001010
				signed   : 2315449416 >> 24 -> 11111111 11111111 11111111 10001010
				Think of right shifting an unsigned value as Java's >>> operator. :)
*/
#include <stdio.h>
#include <stdlib.h>

void v4ToInt(const char* octets[4]) {
	printf("%u\n",
		(atoi(octets[0]) << 24) + (atoi(octets[1]) << 16) + (atoi(octets[2]) << 8) + (atoi(octets[3]) << 0)
	);
}

void intToV4(unsigned int decimalRep) {
	printf("%u.%u.%u.%u\n",
		(decimalRep >> 24) & 0xFF,
		(decimalRep >> 16) & 0xFF,
		(decimalRep >> 8)  & 0xFF,
		(decimalRep >> 0)  & 0xFF
	);
}
