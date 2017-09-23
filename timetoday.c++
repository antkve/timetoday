#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
using namespace std;

-- If you change these you gotta change the ones in timetoday.cpp
string tagNames [6] = { "code", "workweb", "work", "web", "graphic", "play" };
string LOGDIR = "/home/anthony/bin";

string LOGFILE = LOGDIR.append("/timelog.txt");

fstream timelog;
string fileString;
string dateAndTime;
string tagstring;
int tagNumber;

int secsOnTags [6] = {0, 0, 0, 0, 0, 0};

string month;
int day;
int hour;
int minute;
int second;

string lastMonth;
int lastDay;
int lastHour;
int lastMinute;
int lastSecond;
int lastTag;

int secondsSince;

bool firstTime;

int main() {
  timelog.open(LOGFILE);
  if(timelog.is_open()){
    firstTime = true;
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    int today = aTime->tm_mday;
    

    while(getline(timelog, fileString)) {
      
      dateAndTime = fileString;
      getline(timelog, fileString);
      stringstream tagstream (fileString);
      tagstream >> tagNumber;
    
      
      dateAndTime = dateAndTime.erase(0, dateAndTime.find(" ") + 1);
      
      month = dateAndTime.substr(0, dateAndTime.find(" "));
      dateAndTime = dateAndTime.erase(0, dateAndTime.find(" ") + 1);
      
      stringstream dayStream (dateAndTime.substr(0, 2));
      dayStream >> day; 
      dateAndTime = dateAndTime.erase(0, 3);
      
      stringstream hourStream (dateAndTime.substr(0, dateAndTime.find(":")));
      hourStream >> hour;
      dateAndTime = dateAndTime .erase(0, dateAndTime.find(":") + 1);

      stringstream minuteStream (dateAndTime.substr(0, dateAndTime.find(":")));
      minuteStream >> minute;
      dateAndTime = dateAndTime.erase(0, dateAndTime.find(":") + 1);

      stringstream secondStream (dateAndTime.substr(0, dateAndTime.find(" ")));
      secondStream >> second;
      if (firstTime) {

        lastMonth = month;
        lastDay = day;
        lastHour = hour;
        lastMinute = minute;
        lastSecond = second;
      

      }

      
      if ((lastTag != -1) && (lastMonth == month) && (today == day)) {
        
        secsOnTags[lastTag] += (day - lastDay) * 86400 
          + (hour - lastHour) * 3600 
          + (minute - lastMinute) * 60 
          + (second - lastSecond);

      }

      lastMonth = month;
      lastDay = day;
      lastHour = hour;
      lastMinute = minute;
      lastSecond = second;
      lastTag = tagNumber;
      firstTime = false;
    }

    for (int i=0; i<6; i++){

      cout << tagNames[i] << ": " 
        << secsOnTags[i]
        << endl;
   
    }

  }
  
}
