#include "string.h"
#include <stdio.h>
//#include <iostream>

int main(int argc, char const *argv[])
{
    tinystl::string s1("123");
    tinystl::string s2(s1);
    tinystl::string s3 = "123";
    tinystl::string s4 = s3;
    printf("s1:%s\n", s1.c_str());
    return 0;
}
