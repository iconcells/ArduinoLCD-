# Pre-work - *Arduino Temperature  LCD*

**Arduino Temperature LCD** is an ioT project to show the input from the temperature sensor into the LCD display.  The background color of the LCD will be changed based on the temperature change 

Develop by: **Kenneth Ng**

Time spent: **5** hours spent in total

Update:  **11/10/2015 Added LCD background color change**

## User Stories

I have done mutiple ioT projects in the past.  It always took me a lot of time to remember all the library changes when the hardware has changed or updated.  I am going to document all required changes as my reference:

* [X] LCD library is not always work for Ardrino 1.6 use the library \<rgb_lcd.h\> for Galileo Gen2 and Grove LCD from Grove toolkit
* [X] Andrino libraries is stored in **Document/Andrino** folder by default
* [X] Try to run the examples from the library to ensure all the hardware are running as expected with the default code
* [X] I counldn't get the Gen2 board WiFi to work.  The "multiple wifi.h exists" still a main issue.  I found out the ~/Documents/Arduino/libraries and ~/Library/Arduino15/packages/Intel/hardware/i586/1.6.2+1.0 both can store the libarary.  **It 's confusing**
* [X] After I gave up and use Edison chips board, I found out I need to remove the ~/Library/Arduino15/ folder and add the new board, tools, board and serach 656 to reinstall
* [X] Check the port setting if you keep getting timeout error.  Seems when you load a new app, the port might just to the different one
* [X] WiFi works in Edison..  