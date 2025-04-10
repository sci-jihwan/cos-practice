#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdbool.h>

#define BIT_VECTOR_LENGTH 4
#define MSB_INDEX (BIT_VECTOR_LENGTH - 1)
#define LSB_INDEX 0

void print_command(char *argv[]);
int check_validity(char *input);
void init_bit_vector(char *input, char *bv);
void print_bit_vector(char *bv);
unsigned int b2u(char *bv);

// 보수 & 덧셈 관련 함수 선언
int b2t(char *bv);
void bit_addition(char *bv1, char *bv2, char *result);
unsigned int unsigned_addition(char *bv1, char *bv2);
int twos_complement_addition(char *bv1, char *bv2);
int ones_complement_addition(char *bv1, char *bv2);
int sign_magnitude_addition(char *bv1, char *bv2);

int main(int argc, char *argv[])
{
    char bv1[BIT_VECTOR_LENGTH];
    char bv2[BIT_VECTOR_LENGTH];

    if (argc != 3)
    {
        printf("Error: invalid number of arguments\n");
        print_command(argv);
    }

    if (!(check_validity(argv[1]) && check_validity(argv[2])))
    {
        printf("Error: invalid arguments\n");
        print_command(argv);
    }

    init_bit_vector(argv[1], bv1);
    init_bit_vector(argv[2], bv2);

    printf("== INPUT BIT VECTORS ==\n");
    print_bit_vector(bv1);
    print_bit_vector(bv2);

    printf("\n== ADDITION RESULTS ==\n");
    printf("Unsigned: %u\n", unsigned_addition(bv1, bv2));
    printf("Two's Complement: %d\n", twos_complement_addition(bv1, bv2));
    printf("One's Complement: %d\n", ones_complement_addition(bv1, bv2));
    printf("Sign-Magnitude: %d\n", sign_magnitude_addition(bv1, bv2));

    return 0;
}

void print_command(char *argv[])
{
    printf("Command: %s <first bit vector> <second bit vector>\n", argv[0]);
    printf("Example: %s 0100 1000\n", argv[0]);
    exit(1);
}

int check_validity(char *input)
{
    int len = strlen(input);
    if (len != BIT_VECTOR_LENGTH)
        return false;

    for (int i = 0; i < len; i++)
    {
        if (!(input[i] == '0' || input[i] == '1'))
            return false;
    }

    return true;
}

void init_bit_vector(char *input, char *bv)
{
    char c;
    int i, len;
    len = strlen(input);

    for (int i = 0; i < len; i++)
    {
        c = input[i];
        bv[MSB_INDEX - i] = (c == '0') ? 0 : 1;
    }
}

void print_bit_vector(char *bv)
{
    printf("Bit Vector: ");
    for (int i = MSB_INDEX; i >= LSB_INDEX; i--)
        printf("%d", bv[i]);
    printf("\n");
}

unsigned int b2u(char *bv)
{
    unsigned int value = 0;
    for (int i = MSB_INDEX; i >= LSB_INDEX; i--)
    {
        value = (value << 1) | bv[i];
    }
    return value;
}

int b2t(char *bv)
{
    // Two's complement to int
    if (bv[MSB_INDEX] == 0)
        return (int)b2u(bv);
    else
    {
        // 음수면 반전 + 1
        char inv[BIT_VECTOR_LENGTH];
        for (int i = 0; i < BIT_VECTOR_LENGTH; i++)
            inv[i] = 1 - bv[i];

        char plus1[BIT_VECTOR_LENGTH] = {0};
        plus1[LSB_INDEX] = 1;

        char result[BIT_VECTOR_LENGTH];
        bit_addition(inv, plus1, result);

        return -1 * (int)b2u(result);
    }
}

void bit_addition(char *bv1, char *bv2, char *result)
{
    int carry = 0;
    for (int i = LSB_INDEX; i <= MSB_INDEX; i++) {
        int sum = bv1[i] + bv2[i] + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }
}

unsigned int unsigned_addition(char *bv1, char *bv2)
{
    char result[BIT_VECTOR_LENGTH];
    bit_addition(bv1, bv2, result);
    return b2u(result);
}

int twos_complement_addition(char *bv1, char *bv2)
{
    char result[BIT_VECTOR_LENGTH];
    bit_addition(bv1, bv2, result);
    return b2t(result);
}

int ones_complement_addition(char *bv1, char *bv2)
{
    char inv_bv2[BIT_VECTOR_LENGTH];
    for (int i = 0; i < BIT_VECTOR_LENGTH; i++) {
        inv_bv2[i] = 1 - bv2[i];
    }

    char result[BIT_VECTOR_LENGTH];
    bit_addition(bv1, inv_bv2, result);

    // carry 추가
    int carry = 0;
    if (bv1[MSB_INDEX] + inv_bv2[MSB_INDEX] >= 2) carry = 1;

    if (carry) {
        int i = LSB_INDEX;
        while (i <= MSB_INDEX && carry) {
            result[i] += 1;
            carry = result[i] / 2;
            result[i] %= 2;
            i++;
        }
    }

    return b2t(result);
}

int sign_magnitude_addition(char *bv1, char *bv2)
{
    int sign1 = bv1[MSB_INDEX];
    int sign2 = bv2[MSB_INDEX];

    char mag1[BIT_VECTOR_LENGTH] = {0};
    char mag2[BIT_VECTOR_LENGTH] = {0};
    for (int i = 0; i < MSB_INDEX; i++) {
        mag1[i] = bv1[i];
        mag2[i] = bv2[i];
    }

    char result[BIT_VECTOR_LENGTH] = {0};

    if (sign1 == sign2) {
        // 같은 부호 --> 절댓값 더하고 부호 유지
        bit_addition(mag1, mag2, result);
        result[MSB_INDEX] = sign1;
    } else {
        // 부호 다르면 --> 큰 값에서 작은 값 빼기
        unsigned int val1 = b2u(mag1);
        unsigned int val2 = b2u(mag2);

        unsigned int diff;
        if (val1 >= val2) {
            diff = val1 - val2;
            result[MSB_INDEX] = sign1;
        } else {
            diff = val2 - val1;
            result[MSB_INDEX] = sign2;
        }

        for (int i = LSB_INDEX; i < MSB_INDEX; i++) {
            result[i] = (diff >> i) & 1;
        }
    }

    // 부호 반영해서 정수로 변환
    int value = 0;
    for (int i = MSB_INDEX - 1; i >= LSB_INDEX; i--) {
        value = (value << 1) | result[i];
    }
    if (result[MSB_INDEX] == 1) value *= -1;

    return value;
}
