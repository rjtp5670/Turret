# Turret

- Author: Designed by David Park (Park Huck Gu Se)
- No Licesense
- Contact: rjtp5670@gmail.com

This is my personal Arduino Project back in my college life.
All the code may not be perfect for advanced user. But it's easy for rookies as the source is hard-coded.

![](/imgs/Turret/turret.gif)

The laser module on a tower alarm a person detected within set range.
The main sensing compononet is P.I.R and sonar sensor. Servo motor will rotate and search the place near than target the object detected.

The formula to get angle is the "Arctan" which converts a tan reversly.

![](/imgs/Turret/Arctan_Formula.jpg)

> Get angle using Arctan (turret.ino includes this part)

For more information, see https://www.spikevm.com/calculators/framing/arctan-angle.php

## What needed

- Servo Motor (SG-90 / MG995 )
- Laser Module
- Arduino Uno
- P.I.R Sensor
- Sonar Sensor.

![](/imgs/Turret/turret_intro.png)

![](/imgs/Turret/turret_exp.png)

![](/imgs/Turret/turret_hardware.png)
