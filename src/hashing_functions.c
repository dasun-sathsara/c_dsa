// Attribution: https://github.com/TheAlgorithms/C

/* String hash function */

unsigned long string_hash(void *string)
{
    /* This is the djb2 string hash function */

    unsigned long result = 5381;
    unsigned char *p;

    p = (unsigned char *)string;

    while (*p != '\0')
    {
        result = ((result << 5) ^ result) ^ (*p);
        ++p;
    }

    return result;
}

unsigned long int_hash(void *vlocation)
{
    int *location;

    location = (int *)vlocation;

    return (unsigned long)*location;
}
