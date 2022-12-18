
<!-- PROJECT LOGO -->
## UDP Client-Server time service
 
<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#introduction">Introduction</a></li>
        <li><a href="#functionalities">Functionalities</a></li>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li><a href="#usage">Knowledge</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

###  Introduction
Time service in UDP-User Datagram Protocol in both Server and Client sides.
The advantages of UDP is the speed and high performances for transmit packets for applications that don't need verification or correction.


### Functionalities

The service includes 13 different options:
1. <b> GetTime</b> - current date and time request
2. <b>GetTimeWithoutDate</b> - only time request
3. <b>GetTimeSinceEpoch </b>- seconds since 1.1.1970 request 
4. <b>GetClientToServerDelayEstimation </b>- estimation of delaying between client and server requset - sending consecutively 100 messages from Client to Server.
    Calculating difference between each two messages' time stamp's from the Server and calculate the total time stamp's avarage
5. <b>MeasureRTT</b> - measure RTT from Client to Server request - the time that takes to message to be trnasmitted.
    Sending 100 messages from the Client and get answer message from the Server in every sent message from the Client. Calculating the total time stamp's avarage
6. <b>GetTimeWithoutDateOrSeconds </b> - time without seconds request
7. <b>GetYear</b> - year request
8. <b>GetMonthAndDay </b> - month and day request
9. <b>GetSecondsSinceBeginingOfMonth </b> - number of seconds since the beginning og the month request
10. <b> GetWeekOfYear </b> - number of week in the year request 
11. <b>GetDaylightSavings</b> - checking daylight saving time request -  1 if it's ON  
12. <b>GetTimeWithoutDateInCity </b> - time request in:Tokyo, Melbourne, San Francisco ,Porto and UTC
13. <b>MeasureTimeLap </b> - estimation from first "MeasureTimeLap" request to the second one. If 3 minutes are passed the server will stop the estimation. 
### Built With
* C language
* Winsock2 library
* [Time library](https://www.tutorialspoint.com/c_standard_library/time_h.htm)

## Knowledge
* Socket API
* DNS records
