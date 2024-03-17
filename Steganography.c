/*Alexander Leon */


#include <stdio.h>
#define DOT 0x2E
#define SPACE 0x20

int main() {
    int c;
    int spaceCount = 0;
    int bitCount = 0;
    int byte = 0;
    int messageEndedProperly = 0;
    int statusCode = 0;

    while ((c = getchar()) != EOF) {
        if (c == DOT) {
            spaceCount = 0;
            while ((c = getchar()) == SPACE) {
                spaceCount++;
            }

            if (spaceCount == 1) {

                byte = byte << 1;
                bitCount++;
            } else if (spaceCount == 2) {

                byte = (byte << 1) | 1;
                bitCount++;
            } else if (spaceCount >= 3) {

                messageEndedProperly = 1;
                break;
            }

            if (bitCount == 8) {

                putchar(byte);

                byte = 0;
                bitCount = 0;
            }
        }
    }

    if (!messageEndedProperly) {
        statusCode = 2;
    } else if (bitCount != 0) {

        statusCode = 1;
    }
    return statusCode;

}


