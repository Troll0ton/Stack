//! @file error_data.h

#ifndef   ERROR_DATA_H
#define   ERROR_DATA_H

//-----------------------------------------------------------------------------

struct Error_info
{
    unsigned error_code;
    char *error_output;
};

//-----------------------------------------------------------------------------

#ifndef   datas1
#define   datas1

const struct Error_info error_arr[]
{
    {(1 << 0),  "|||ATTENTION||| the integrity of error codes violated!           \n\n"},
    {(1 << 1),  "ERROR - the integrity of first canary is broken                    \n"},
    {(1 << 2),  "ERROR - the integrity of second canary is broken                   \n"},
    {(1 << 3),  "ERROR - incorrect memory allocation for stack's data (NULL-pointer)\n"},
    {(1 << 4),  "ERROR - stack overflow                                             \n"},
    {(1 << 5),  "ERROR - incorrect capacity value (below zero)                      \n"},
    {(1 << 6),  "ERROR - incorrect capacity value (below zero)                      \n"},
    {(1 << 7),  "ERROR - incorrect memory allocation for stack (NULL-pointer)       \n"},
    {(1 << 8),  "ERROR - data integrity breach (invalid hash)                       \n"},
};

#endif

//-----------------------------------------------------------------------------

struct Verificator
{
    unsigned error_code;
    bool     statement;
};

//-----------------------------------------------------------------------------

#ifndef   datas2
#define   datas2

struct Verificator verify_arr[]
{
    {(1 << 0),  false},
    {(1 << 1),  false},
    {(1 << 2),  false},
    {(1 << 3),  false},
    {(1 << 4),  false},
    {(1 << 5),  false},
    {(1 << 6),  false},
    {(1 << 7),  false},
    {(1 << 8),  false},
};

#endif

//-----------------------------------------------------------------------------

#endif //ERROR_DATA_H
