Sharp IR Sensors library for Arudino
by Marcal - 2014

CURRENT VERSION

Release 1.0 09-JANUARY-2014

1- Import the library into your sketch (you’ve already added the library to your system):
#include <SharpIR.h>

2- Initialize the library:
SharpIR sharp(ir, 25, 93, model);

where:
ir: the pin where your sensor is attached.
25: the number of readings the library will make before calculating an average distance.
93: the difference between two consecutive measurements to be taken as valid (in %)
model: is an int that determines your sensor:  1080 for GP2Y0A21Y, 20150 for GP2Y0A02Y (working distance range according to the datasheets)

3- get the distance:
int dis=sharp.distance(); 