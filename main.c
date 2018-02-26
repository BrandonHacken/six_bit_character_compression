//
//  main.c
//  char_Six_Bit_Encoder_Version_1.1
//
//  Created by Mr. Penguin on 2/15/18.
//  Copyright © 2018 Mr. Penguin. All rights reserved.
//

#include <stdio.h>
#include <string.h>


int main(int argc, const char * argv[]) {
    // insert code here...
    char small_String[] = "azAZgG";
    char large_String[] = "Directions: 55 feet north, 78 feet west\n";
    int count_char;
    int long long char_Result = 0;
    int long long result = 0;
    int i=0;
    int char_String_Length = strlen(small_String);
    char char_String[char_String_Length];
    printf("%i\n",char_String_Length);
    memcpy(char_String, small_String, char_String_Length);
    while (i < char_String_Length) {
        if ('a' <= char_String[i] && char_String[i] <= 'z') {
            char_Result = char_String[i] - 'a' + 1;
        }
        else if ('A' <= char_String[i] && char_String[i] <= 'Z') {
            char_Result = (-1)*(char_String[i] - 'A' + 1);
        }
        if (i > 0){
        result = (result << 6) | char_Result;
        }
        else {
            result = char_Result;
        }
        i++;
    }
    printf("%ill\n",result);
    
    // Check Encoding
    i = 0;
    char decode;
    int temp = 0b111111;
    while (i < char_String_Length) {
        decode = (result & temp);
        result = result >> 6;
        if (decode >= 1 && decode <= 26){
            // lower case letter A through Z
            decode = decode - 1 + 'a';
        }
        else if (decode >= 33 && decode <= 59){
            // Upper case letter a through z
            decode = decode ^ 0b111111;
            decode = decode + 'A';
        }
        else {
            
        }
        printf("letter: %i\n", decode);
        i++;
    }
    return 0;
}
