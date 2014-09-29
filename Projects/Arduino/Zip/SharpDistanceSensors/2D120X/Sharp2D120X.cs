//           Ascended International
//
//             Copyright (c) 2010
//
//            All Rights Reserved
// ------------------------------------------------------------------------------
//    * DO NOT REMOVE THIS HEADER. DO NOT MODIFY THIS HEADER *
/**********************************************************************************
 * You may use this class for non-commerical purposes. If you wish to use this    *
 * software for a commercial pupose please contact Ascended International at:     *
 * mark@ascended.com.au                                                           *
 *                                                                                *
 * When using this free class, no warranty express or implied is offered.         *
 * In no event shall Ascended International, any of it's employees or shareholds  *
 * be held liable for any direct, indirect, special, exemplary, incidental or     *
 * consequential damages however caused.                                          *
 *                                                                                *
 * If you modify this class, please add your name and the date below as a         *
 * contributor, without removing this notice or modifying it in any way, shape    *
 * or form.                                                                       *
 **********************************************************************************/ 
/*
 Contributors:
 * 16 Sep 2010, Mark Harris - Initial code, maths and development [ markh@rris.com.au ]
 * 17 Sep 2010, Mark Harris - increased accuracy of 4th order poly by 6 decimal places
 * 26 Sep 2010, Mark Harris - Rewrote poly functions to get accuracty within 1mm
 */

using System;
using Microsoft.SPOT;
using Ascended.Sensors.Interfaces;
using GHIElectronics.NETMF.Hardware;
using GHIElectronics.NETMF.System;
using Microsoft.SPOT.Hardware;

namespace Ascended.Sensors.Distance
{
    /// <summary>
    /// Driver for Sharp 2D120X (Infrared Proximity Sensor Short Range - Sharp GP2D120XJ00F).
    /// Sparkfun SKU: sku: SEN-08959
    /// TinyCLR SKU: GP2D120
    /// 
    /// Class written by Mark Harris, mark@ascended.com.au/markh@rris.com.au
    /// </summary>
    public class Sharp2D120X : DistanceSensorBase
    {
        /// <summary>
        /// Create a new instance of Sharp2D120X. You should sleep for *at least* 50ms after instanciating this class.
        /// The sensor does not produce accurate results for at least this time.
        /// </summary>
        /// <param name="pin">Pin the sensor's vout is connected to.</param>
        public Sharp2D120X(Cpu.Pin pin)
        {
            sensor = new AnalogIn((AnalogIn.Pin)pin);
            sensor.SetLinearScale(0, 3300);

            UseMovingAverage = false;
            MovingAverageSize = 5;

            UseAveraging = true;
            AverageSampleCount = 10;

            movingValues = new double[MovingAverageSize];
            FillMovingAverageValues();
        }

        protected override double ReadSensorValue()
        {
            int x = sensor.Read();

            // please do not change this unless you *really* know what you are doing. This took many hours to get right.
            if (x > 670)
            {
                // handles 5cm ~23cm very accurately
                return -0.00000000000000814807570435057 * MathEx.Pow(x, 5) +
                    0.0000000000677479681464555 * MathEx.Pow(x, 4) -
                    0.000000223468684525594 * MathEx.Pow(x, 3) +
                    0.000369147142846821 * MathEx.Pow(x, 2) -
                    0.313961024650693 * x +
                    121.96816964022;
            }
            else
            {
                // actually accurate from 17cm ~ 36cm however the above function is more accurate
                return 0.00000000000000814807570435057 * MathEx.Pow(x, 5) +
                    0.0000000000677479681464555 * MathEx.Pow(x, 4) -
                    0.000000223468684525594 * MathEx.Pow(x, 3) +
                    0.000369147142846821 * MathEx.Pow(x, 2) -
                    0.313961024650693 * x + 
                    121.96816964022;
;

            }
        }
    }
}
