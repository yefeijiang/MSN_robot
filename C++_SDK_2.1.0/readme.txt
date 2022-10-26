1. About C++ SDK
   C++ SDK of iBot Platform lets you create your own robot using the classical C++
language, both in Visual C++ or Borland C++. You can follow the DemoBot to create your 
own powerful robot. The description of functions and events can be found in head file and
source files of the DemoBots.

2. File List

readme.txt         this file
iBotPlatform.dll   C++ SDK Dynamic Link Library
iBotPlatform.h     C++ SDK Head File
DemoBot.exe        Demo Bot, created by Borland C++ Builder 6.0
/DemoBot           Source File of Demo Bot

3. Update History

Version 1.1.0.4 (2006-7-12)
(1)add supports of font name, font color and font style of the message
(2)add supports of user's initial status and client id
(3)fix some bugs on auto reconnection

Version 1.1.1.0 (2006-8-2)
(1)add supports of customer activity name
(2)add supports of sending typing message
(3)add supports of change the display name of robot
(4)add supports of change the personal message of robot
(5)add supports of change the display picture of robot

Version 1.1.2 (2006-11-14)
(1)add event when a user add the bot to his/her friend list
(2)add event when a user remove the bot to his/her friend list

Version 2.0  (2007-6-20)
(1) in event OnSessionOpen, supports four types of open mode
(1) add event OnActivityRespond, supports four types of responding action
(2) add event OnException
(3) add function InviteUser (only for Enterprise Version)
(4) add function CreateSession (only for Enterprise Version)
(5) add function PushMsg (only for Enterprise Version)

Version 2.1 (2007-10-31)
(1) add event OnUserStatusChanged
(2) add event OnUserPersonalMessageChanged
(3) add event OnSendFileRespond
(4) add event OnSendBackgroundRespond
(5) add event OnSendWebcamRespond
(6) add function SendFile
(7) add function SendBackground
(8) add function SendInk
(9) add function SendVoiceclip
(10) add function SendWebcam
(11) change name of function "InviteUser" to "InviteUserToSession"
(12) add two paremeters (corresponding user & bot accounts) to event "OnException"
