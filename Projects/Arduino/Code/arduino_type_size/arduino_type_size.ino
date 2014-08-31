// Arduino DatatypeSize v2 - Display information about data types used in Arduino
// Created by Michael 'TeX' Hex - http://www.texhex.info/
//
// Full list of all data types:
// http://arduino.cc/en/Reference/HomePage -> Section "Data Types"  
//
// Additonal references:
// http://www.arduino.cc/playground/Code/DatatypePractices
// http://arduino.cc/en/Reference/VariableDeclaration
//
// Any text in this sketch is taken from the Arduino homepage, 
// licensed under a Creative Commons Attribution-ShareAlike 3.0 License. 
//


void setup() {    
  Serial.begin(9600); 
}

void loop() {
 Serial.println("--- Variable type: Size in SRAM (bytes) ---");


 // C standard data type "unsigned int length 8 bits". 
 // Occupies one byte of memory.
 // http://arduino.cc/forum/index.php/topic,41590.0.html
 // http://en.wikipedia.org/wiki/Stdint.h#Fixed_width_integer_types
 Serial.print("uint8_t: ");
 Serial.println(sizeof(uint8_t));

 // A boolean holds one of two values, true or false. 
 // Each boolean variable occupies one byte of memory.
 // http://arduino.cc/en/Reference/BooleanVariables
 Serial.print("boolean: ");
 Serial.println(sizeof(boolean));

 // A data type that takes up 1 byte of memory that stores a character value. 
 // Character literals are written in single quotes, like this: 'A' (for multiple
 // characters - strings - use double quotes: "ABC"). 
 // http://arduino.cc/en/Reference/Char
 Serial.print("char: ");
 Serial.println(sizeof(char));

 // An unsigned data type that occupies 1 byte of memory. Same as the byte datatype. 
 // The unsigned char datatype encodes numbers from 0 to 255.
 // For consistency of Arduino programming style, the byte data type is to be preferred. 
 // http://arduino.cc/en/Reference/UnsignedChar
 Serial.print("unsigned char: ");
 Serial.println(sizeof(unsigned char));
 
 // A byte stores an 8-bit unsigned number, from 0 to 255. 
 // http://arduino.cc/en/Reference/Byte
 Serial.print("byte: ");
 Serial.println(sizeof(byte));
 
 // Integers are your primary datatype for number storage, and store a 2 byte value. 
 // This yields a range of -32,768 to 32,767 (minimum value of -2^15 and a maximum value of (2^15) - 1). 
 // http://arduino.cc/en/Reference/Int
 Serial.print("int: ");
 Serial.println(sizeof(int));

 // Unsigned ints (unsigned integers) are the same as ints in that they store a 2 byte value. 
 // Instead of storing negative numbers however they only store positive values, yielding a 
 // useful range of 0 to 65,535 (2^16) - 1). 
 // http://arduino.cc/en/Reference/UnsignedInt
 Serial.print("unsigned int: ");
 Serial.println(sizeof(unsigned int));

 // A word stores a 16-bit unsigned number, from 0 to 65535.
 // Same as an unsigned int. 
 // http://arduino.cc/en/Reference/Word
 Serial.print("word: ");
 Serial.println(sizeof(word));
 
 // Long variables are extended size variables for number storage, and store 32 bits (4 bytes), 
 // from -2,147,483,648 to 2,147,483,647. 
 // http://arduino.cc/en/Reference/Long 
 Serial.print("long: ");
 Serial.println(sizeof(long));

 // Unsigned long variables are extended size variables for number storage, and store 32 bits (4 bytes). 
 // Unlike standard longs unsigned longs won't store negative numbers, making their range from 0 
 // to 4,294,967,295 (2^32 - 1). 
 // http://arduino.cc/en/Reference/UnsignedLong
 Serial.print("unsigned long: ");
 Serial.println(sizeof(unsigned long));

 // Datatype for floating-point numbers, a number that has a decimal point.
 // Floating-point numbers can be as large as 3.4028235E+38 and as low as -3.4028235E+38. 
 // They are stored as 32 bits (4 bytes) of information. 
 // http://arduino.cc/en/Reference/Float
 Serial.print("float: ");
 Serial.println(sizeof(float));
 
 // Double precision floating point number. Occupies 4 bytes. 
 // The double implementation on the Arduino is currently exactly the same as the float, 
 // with no gain in precision.
 // http://arduino.cc/en/Reference/Double
 Serial.print("double: ");
 Serial.println(sizeof(double));
 

 delay(8500);
}

