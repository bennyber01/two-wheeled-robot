#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>

#define SLAVE_ADDRESS        0x09

#pragma pack(push, 1) // exact fit - no padding
struct Numbers
{
    char c;
    long l;
    float d;
};
#pragma pack(pop) //back to whatever the previous packing mode was

const char * i2cDevName = "/dev/i2c-4";

int main()
{
    // Open up the I2C bus
    int file = open(i2cDevName, O_RDWR);
    if (file == -1)
    {
        fprintf(stderr, "Bad devide name %s\r\n", i2cDevName);
        exit(1);
    }
    else
        printf("*** Device '%s' opened successfully.\r\n", i2cDevName);


    // Specify the address of the slave device.
    if (ioctl(file, I2C_SLAVE, SLAVE_ADDRESS) < 0)
    {
        fprintf(stderr, "Failed to acquire bus access '%x' and/or talk to slave\r\n", SLAVE_ADDRESS);
        exit(1);
    }
    else
        printf("*** Acquired bus access to a slave device adr: %x.\r\n", SLAVE_ADDRESS);

    Numbers numbers;
    numbers.c = 117;
    numbers.l = 876543210;
    numbers.d = 1234.567;

//    printf("sizeof(numbers.c) = %d, numbers.c = %02x.\r\n", sizeof(numbers.c), numbers.c);
//    printf("sizeof(numbers.l) = %d, numbers.l = %08lx.\r\n", sizeof(numbers.l), numbers.l);
//    long dd;
//    memcpy(&dd, &numbers.d, 4);
//    printf("sizeof(numbers.d) = %d, numbers.d = %08lx.\r\n", sizeof(numbers.d), dd);
//    printf("sizeof(numbers) = %d.\r\n", sizeof(numbers));


    printf("*** Send to the i2c bus.\r\n");
    printf("numbers.c = %d.\r\n", numbers.c);
    printf("numbers.l = %ld.\r\n", numbers.l);
    printf("numbers.d = %lf.\r\n", numbers.d);

    // Write a byte to the slave.
    if (write(file, &numbers, sizeof(numbers)) != sizeof(numbers))
    {
        fprintf(stderr, "Failed to write to the i2c bus adr: %x.\r\n", SLAVE_ADDRESS);
        exit(1);
    }
    else
        printf("*** Wrote to the i2c bus adr: %x.\r\n", SLAVE_ADDRESS);

    // Read a byte from the slave.
    Numbers n = {0};
    if (read(file, &n, sizeof(n)) != sizeof(n))
    {
        fprintf(stderr, "Failed to read from the i2c bus.\r\n");
        exit(1);
    }
    else
    {
        printf("*** Read from the i2c bus.\r\n");
        printf("n.c = %d.\r\n", n.c);
        printf("n.l = %ld.\r\n", n.l);
        printf("n.d = %lf.\r\n", n.d);
    }

    close(file);

    return 0;
}
