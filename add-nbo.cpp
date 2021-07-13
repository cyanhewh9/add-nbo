#include <stdio.h>
#include <stdint.h>
#include <cstdio>


uint32_t my_ntohl(uint32_t num) {
    __asm("bswap %0" : "=r" (num));
    return num;
}

uint32_t read_data(FILE *fp)
{
    uint32_t data = 0;
    fread(&data, 4, 1, fp);
    return my_ntohl(data);
}

void add_nbo(FILE *first_bin, FILE *second_bin)
{
    uint32_t first_data = read_data(first_bin);
    uint32_t second_data = read_data(second_bin);
    uint32_t add_result = first_data + second_data;
   
    printf(
        "%u(0x%x) + %u(0x%x) = %u(0x%x)\n", 
        first_data, 
        first_data,
        second_data,
        second_data,
        add_result,
        add_result
    );
}

int main(int argc, char *argv[])
{
    FILE *first_bin = 0;
    FILE *second_bin = 0;

    if (argc < 3)
    {
        printf("Useage: %s <file1> <file2>\n", argv[0]);
        return 0;
    }

    first_bin = fopen(argv[1], "rb");
    second_bin = fopen(argv[2], "rb");
    if (!first_bin || !second_bin)
    {
        printf("file open error!!\n");
        return 0;
    }
    add_nbo(first_bin, second_bin);

    fclose(first_bin);
    fclose(second_bin);
}
