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
 * 26 Sep 2010, Mark Harris - Initial code, maths and development [ markh@rris.com.au ]
*/

using System;
using Microsoft.SPOT;
using GHIElectronics.NETMF.Hardware;
using GHIElectronics.NETMF.System;
using Microsoft.SPOT.Hardware;

namespace Ascended.Sensors.Distance
{
    public class Sharp2Y0A21 : DistanceSensorBase
    {
        /// <summary>
        /// Create a new instance of Sharp2Y0A21. You should sleep for *at least* 50ms after instanciating this class.
        /// The sensor does not produce accurate results for at least this time.
        /// 
        /// Class written by Mark Harris, mark@ascended.com.au/markh@rris.com.au
        /// </summary>
        /// <param name="pin">Pin the sensor's vout is connected to.</param>
        public Sharp2Y0A21(Cpu.Pin pin)
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

            if (x > 970) // less than 28cm
            {
                return 0.00000000131735227029556 * MathEx.Pow(x, 4) - 
                    0.00000588207740775979 * MathEx.Pow(x, 3) + 
                    0.00984274026340972 * MathEx.Pow(x, 2) - 
                    7.34230389208274 * x + 
                    2091.1617416433;

            }
            else if (x > 680) // less than ~44cm
            {
                return -0.00000000000000850459495296198 * MathEx.Pow(x, 6) + 
                    0.0000000000404907863601567 * MathEx.Pow(x, 5) - 
                    0.0000000786246323722896 * MathEx.Pow(x, 4) + 
                    0.00007932114058495 * MathEx.Pow(x, 3) - 
                    0.0434598791721258 * MathEx.Pow(x, 2) + 
                    12.0026030117761 * x - 
                    1199.16124650975;
            }
            else // not so accurate, sensor absolute max limit 60cm.
            {
                return -0.00000740565636533214 * MathEx.Pow(x, 3) +
                    0.0166287013999877 * MathEx.Pow(x, 2) -
                    12.5032985098457 * x +
                    3186.33733622086;

            }
        }
    }
}
