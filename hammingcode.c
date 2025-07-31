/*
Enter 4 data bits (space-separated): 1 0 0 1
Generated 7-bit Hamming code: 0 0 1 1 0 0 1
Simulate error? (y/n): n
No error detected in received code.
Extracted data bits: 1 0 0 1Output 2:
Enter 4 data bits (space-separated): 1 0 0 1
Generated 7-bit Hamming code: 0 0 1 1 0 0 1
Simulate error? (y/n): y
Enter bit position to flip (1-7): 4
ERROR!
Codeword after error: 0 0 1 0 0 0 1
Error detected at bit position 4 (counting from 1).
Corrected code: 0 0 1 1 0 0 1
Extracted data bits: 1 0 0 1
*/

#include <stdio.h>

void generateHammingCode(int data[], int hcode[]) {
    hcode[2] = data[0];
    hcode[4] = data[1];
    hcode[5] = data[2];
    hcode[6] = data[3];
    hcode[0] = hcode[2] ^ hcode[4] ^ hcode[6];
    hcode[1] = hcode[2] ^ hcode[5] ^ hcode[6];
    hcode[3] = hcode[4] ^ hcode[5] ^ hcode[6];
}

int main() {
    int data[4], hcode[7];
    printf("Enter 4 data bits (space-separated): ");
    for (int i = 0; i < 4; i++)
        scanf("%d", &data[i]);
    generateHammingCode(data, hcode);
    printf("Generated 7-bit Hamming code: ");
    for (int i = 0; i < 7; i++)
        printf("%d ", hcode[i]);
    printf("\n");

    char opt;
    printf("Simulate error? (y/n): ");
    scanf(" %c", &opt);
    if (opt == 'y' || opt == 'Y') {
        int pos;
        printf("Enter bit position to flip (1-7): ");
        scanf("%d", &pos);
        if (pos >= 1 && pos <= 7) {
            hcode[pos - 1] ^= 1;
            printf("Codeword after error: ");
            for (int i = 0; i < 7; i++)
                printf("%d ", hcode[i]);
            printf("\n");
        }
    }

    int p[3];
    p[0] = hcode[0] ^ hcode[2] ^ hcode[4] ^ hcode[6];
    p[1] = hcode[1] ^ hcode[2] ^ hcode[5] ^ hcode[6];
    p[2] = hcode[3] ^ hcode[4] ^ hcode[5] ^ hcode[6];
    int error_pos = p[2] * 4 + p[1] * 2 + p[0] * 1;
    if (error_pos == 0) {
        printf("No error detected in received code.\n");
    } else {
        printf("Error detected at bit position %d (counting from 1).\n", error_pos);
        hcode[error_pos - 1] ^= 1;
        printf("Corrected code: ");
        for (int i = 0; i < 7; i++)
            printf("%d ", hcode[i]);
        printf("\n");
    }

    printf("Extracted data bits: %d %d %d %d\n", hcode[2], hcode[4], hcode[5], hcode[6]);
    return 0;
}
