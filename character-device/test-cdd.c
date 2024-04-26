#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_LENGTH 256
static char receive[BUFFER_LENGTH];

int main(int argc, char *argv[]) 
{
    int fd = 0;
    int ret = 0;
    char *filename = "/dev/cddchar";
    char stringToSend[BUFFER_LENGTH];

    printf("Starting device test code example...\n");
    /* open() return a file descriptor */
    fd = open(filename, O_RDWR);
    
    if (fd == -1){
        printf("Can not open file %s\n", filename);
        return -1;
    }

    printf("Type in a short string to send to the kernel module:\n");
    scanf("%[^\n]%*c", stringToSend);                // Read in a string (with spaces)
    printf("Writing message to the device [%s].\n", stringToSend);
    /* write */
    ret = write(fd, stringToSend, strlen(stringToSend));
    if (ret < 0)
        printf("Write file fail\n");

    printf("Press ENTER to read back from the device...\n");
    getchar();
    
    /* read */
    printf("Reading from the device...\n");
    ret = read(fd, receive, BUFFER_LENGTH);        // Read the response from the LKM
    if (ret < 0){
        perror("Failed to read the message from the device.");
    }
    printf("The received message is: [%s]\n", receive);

    /* close */
    ret = close(fd);
    if (ret < 0)
        printf("Close file failed\n");
    printf("Test Done\n");
    return 0;
}