// #############################################################################
// # File create_test_binary.h
// # UE Informatique systemes - Polytech Sorbonne - 2024/2025 - S7
// # Authors: Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################
#include <stdio.h>
#include <stdint.h>

/* We need to test out the functions read_ui8, read_ui16 and read_ui32. That is the
reason why we need to create a binary file that includes such information */
int main()
{
    FILE *file = fopen("test_binary.bin", "wb");
    if (file == NULL)
    {
        perror("Error creating file");
        return 1;
    }

    // Write 8-bit integers
    uint8_t ui8_values[] = {1, 2, 3, 4, 5};
    fwrite(ui8_values, sizeof(uint8_t), 5, file);

    // Write 16-bit integers
    uint16_t ui16_values[] = {256, 512, 1024, 2048, 4096};
    fwrite(ui16_values, sizeof(uint16_t), 5, file);

    // Write 32-bit integers
    uint32_t ui32_values[] = {65536, 131072, 262144, 524288, 1048576};
    fwrite(ui32_values, sizeof(uint32_t), 5, file);

    fclose(file);
    printf("test_binary.bin created successfully.\n");
    return 0;
}