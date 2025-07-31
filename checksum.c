/*
Experiment-3
write a program to implement data link layer framing method checksum.
Description: The checksum method is widely used in data link layer protocols for error
detection. A checksum is calculated over the data and appended to the frame. The receiver
recalculates the checksum and compares it with the received one to detect errors introduced
during transmission.
Explanation:
• Framing: Uses 0x7E as the start-of-frame (SOF) and 0x7F as the end-of-frame (EOF)
delimiter bytes (can be set as per protocol).
• Checksum Calculation: Sums all data bytes modulo 256 (one-byte checksum).
• Sender: Packs data, checksum, and delimiters into a frame.
• Receiver: Checks frame delimiters, extracts data, recalculates checksum, and compares
with received checksum.
• Error Detection: If frame structure or checksum doesn't match, an error is detected.

*/


#include <stdio.h>
#include <string.h>

unsigned char calculate_checksum(const char *data) {
    unsigned int sum = 0;
    for (int i = 0; data[i] != '\0'; i++) {
        sum += (unsigned char)data[i];
    }
    return (unsigned char)(sum % 256);
}

void send_frame(const char *data, unsigned char *frame, int *frame_len) {
    unsigned char checksum = calculate_checksum(data);
    int data_len = strlen(data);
    frame[0] = 0x7E;
    memcpy(&frame[1], data, data_len);
    frame[1 + data_len] = checksum;
    frame[2 + data_len] = 0x7F;
    *frame_len = 3 + data_len;
}

int receive_frame(const unsigned char *frame, int frame_len, char *out_data) {
    if (frame[0] != 0x7E || frame[frame_len - 1] != 0x7F) {
        printf("Frame error: Invalid framing bytes.\n");
        return 0;
    }
    int data_len = frame_len - 3;
    memcpy(out_data, &frame[1], data_len);
    out_data[data_len] = '\0';
    unsigned char received_checksum = frame[1 + data_len];
    unsigned char calc_checksum = calculate_checksum(out_data);
    if (received_checksum != calc_checksum) {
        printf("Checksum error!\n");
        return 0;
    }
    return 1;
}

int main() {
    char data[100];
    unsigned char frame[110];
    char received_data[100];
    int frame_len;

    printf("Enter data to send: ");
    scanf("%s", data);
    send_frame(data, frame, &frame_len);
    printf("Transmitted Frame (in hex): ");
    for (int i = 0; i < frame_len; i++) {
        printf("%02X ", frame[i]);
    }
    printf("\n");

    if (receive_frame(frame, frame_len, received_data)) {
        printf("Received data: %s\n", received_data);
        printf("No error detected in frame.\n");
    }
    return 0;
}




/*
Output 1:
Enter data to send: HELLO
Transmitted Frame (in hex): 7E 48 45 4C 4C 4F 26 7F
Received data: HELLO
No error detected in frame.
Output 2:
Enter data to send: Hello
Transmitted Frame (in hex): 7E 48 65 6C 6C 6F F4 7F
Checksum error!
*/
