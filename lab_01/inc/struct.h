#ifndef STRUCT_H
#define STRUCT_H

#define MAX_MANTISSA 30

struct number
{
    char mantis_sign;
    int mantissa[MAX_MANTISSA];
    int mantissa_num;
    char exp_sign;
    int exp;
};

#endif // STRUCT_H
