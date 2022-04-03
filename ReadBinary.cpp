/**
* Description: Program that reads from a binary file into a struct and prints information given from a sensor.
* File: ReadBinary.cpp
* Version: 1.0
* Author: Sebastiano Bäcklund <sl222sw@student.lnu.se>
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>

using std::cout;
using std::cerr;
using std::endl;
using std::fixed;
using std::setprecision;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

const char SENSOR = 'A';
const string SENS_FILE = "A.txt";
const string FNAME = "files/timelog.dat";

struct DataRecord {
    char logger;
    double temp;
    time_t locTime;
};

int main() {
    ifstream timeFile(FNAME, ios::binary); // ifstream object, opening using binary mode
    ofstream out(SENS_FILE, ios::out | ios::app); // ofstream object using out or append mode
    DataRecord log;
    char buffer[100];

    if (!timeFile.is_open()) {
        cerr<<"Failed to open the file "<<FNAME<<"!";
        return 1;
    } else if (out.fail()) {
        cerr<<"Failed to open the file "<<SENS_FILE;
        return 1;
    }

    out<<"Data A"<<endl;

    while (timeFile.read((char*) &log, sizeof(DataRecord))) {
        // casting the adress of log to char*
        // reading a block of data, the size of struct DataRecord from ifstream timeFile
        if (log.logger == SENSOR) {
            // if struct member logger matches the sensor we're looking for
            // format the time, write it to the buffer
            strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", localtime(&log.locTime));
            // write to file
            out<<fixed<<setprecision(1)<<log.temp<<", "<<buffer<<endl;
        }
    }

    // close files
    timeFile.close();
    out.close();
    return 0;
}