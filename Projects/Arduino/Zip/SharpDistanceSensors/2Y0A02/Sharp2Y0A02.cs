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
 * 17 Sep 2010, Mark Harris - Initial code, maths and development [ markh@rris.com.au ]
 * 27 Sep 2010, Mark Harris - Rewrote maths functions
 */

using System;
using Microsoft.SPOT;
using GHIElectronics.NETMF.Hardware;
using GHIElectronics.NETMF.System;
using Microsoft.SPOT.Hardware;

namespace Ascended.Sensors.Distance
{
    /// <summary>
    /// Driver for Sharp 2Y0A02Y (Infrared Proximity Sensor Short Range - Sharp GP2Y0A02YK0F).
    /// Sparkfun SKU: sku: SEN-08958
    /// 
    /// Class written by Mark Harris, mark@ascended.com.au/markh@rris.com.au
    /// </summary>
    public class Sharp2Y0A02 : DistanceSensorBase
    {
        /// <summary>
        /// Create a new instance of Sharp2Y0A02. You should sleep for *at least* 50ms after instanciating this class.
        /// The sensor does not produce accurate results for at least this time.
        /// </summary>
        /// <param name="pin">Pin the sensor's vout is connected to.</param>
        public Sharp2Y0A02(Cpu.Pin pin)
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

            if (x > 1070)
                return -0.0000000129160529187899 * MathEx.Pow(x, 3) + 
                    0.000074668328419507 * MathEx.Pow(x, 2) - 
                    0.163349193981596 * x + 158.377258922674;

            return 0.000000000000053734206056545 * MathEx.Pow(x, 6) -
                0.000000000313691823316425 * MathEx.Pow(x, 5) +
                0.000000758126712861021 * MathEx.Pow(x, 4) -
                0.000971172449681592 * MathEx.Pow(x, 3) +
                0.695910941119956 * MathEx.Pow(x, 2) - 264.815386704063 * x +
                41964.7253572646;
        }
    }
}
