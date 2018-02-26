//
//  main.c
//  char_Six_Bit_Encoder
//
//  Created by Mr. Penguin on 2/26/18.
//  Copyright © 2018 Mr. Penguin. All rights reserved.
//
int main(int argc, const char * argv[]) {
    char small_String[] = "BAaaZB";  // small example string
    char large_String[] = "abcdefghijklmnopqrstuv";  // big example string
    int char_String_Length = strlen(large_String);  // find the length of the string CHANGE PARAMETER DEPEMNDING ON YOUR INPUT
    char char_String[char_String_Length];  // create an array to store up to 10 characters
    memcpy(char_String, large_String, char_String_Length); // CHANGE MIDDLE PARAMETER DEPEMNDING ON YOUR INPUT
    printf("%s\n", char_String);
    int i=0;  // integer that counts from 0 to (64/6 = 10 characters)
    int j=0;  // integer that counts from 0 to count_Char
    char_String_Length = strlen(char_String);  // find the length of the string
    int count_Char_Remainder = char_String_Length;  // needed in case there is less than 10 chars stored in a 64 bit integer
    if (count_Char_Remainder > 10) {
        count_Char_Remainder = 10;
    }
    int count_Char = ceil(char_String_Length * 0.1);  // integer that tracks the number of 64 bit integers needed for the string
    printf("the number of loops of 10 characters: %i \n",count_Char);
    int char_Result = 0;  // pack the 6-bit values into an 8-bit char_Result
    int long long result[count_Char];  // pack the 6-bit values into a 64-bit long long int
    
    result[j] = 0;
    while (i < count_Char_Remainder && j < count_Char) {
        if ('a' <= char_String[i] && char_String[i] <= 'z') {
            char_Result = char_String[i] - 'a' + 1;  // ex: if char = a - a = 0 next 0 + 1 = 1 signifying the char was the first letter in the alphabet
            //printf(" test: %i here %i \n", i, char_Result);
        }
        else if ('A' <= char_String[i] && char_String[i] <= 'Z') {
            char_Result = (char_String[i] - 'A' + 33);  // ex: if char = A - A = 0 next 0 + 1 = 1 signifying the char was the first letter in the alphabet and then add 32 which is making the 6th bit a 1 to signify the char is a upper case letter
            //printf(" test: %i here %i \n", i, char_Result);
        }
        
        result[j] = (result[j] << 6) | char_Result;  // shift and then replace the 6 least important bits from result with the 6 least important bits from char_Result
        
        if (i == count_Char_Remainder-1){
            printf("result: %ill \n",result[j]);
            j++;
            result[j] = 0;
            count_Char_Remainder = count_Char_Remainder + 10;
            if (j == count_Char-1) {
                count_Char_Remainder = count_Char_Remainder -10 + (char_String_Length % 10);
                //printf("newest %i\n",count_Char_Remainder);
            }
        }
        
        i++;
    }
    
    
    
    // Check Encoding
    j = 1;
    int now = 9;
    int nowtemp = 0;
    long long int temp = 0b111111;
    int decode = 0;
    char decodenow[char_String_Length];
    while(j <= count_Char) {
        //printf("WHAT IS count_Char_Remainder %i\n",count_Char_Remainder);
        for(i = now; i >= nowtemp; i--) {
            decode = result[j-1] & temp;
            result[j-1] = result[j-1] >> 6;
            if (decode >= 1 && decode <= 26){  // check for lower case letters a-z logic a = 1 and z == 26
                // lower case letter A through Z
                decode = decode - 1 + 'a';
            }
            else if (decode >= 33 && decode <= 58){ // check for upper case letters A-Z logic A = 1+32 and Z = 26+32
                // Upper case letter a through z
                decode = ((decode - 33) + 'A');
            }
            decodenow[i] = (char)decode;
        }
        j++;
        if (j == count_Char){
            nowtemp = now + 1;
            now = now + (char_String_Length % 10);
        }
        else {
            nowtemp = now+1;
            now = now + 10;
        }
    }
    /*for ( i =0 ; i < char_String_Length; i++){
        printf("%c \n", decodenow[i]);
    }*/
    printf("word: %s \n", decodenow);
    return 0;
}
