#ifndef GLOBAL_H
#define GLOBAL_H

#define SSID_SIZE 100
typedef char (*SSID_ptr)[SSID_SIZE];

/* RSSI,Received signal strength indication */
struct RSSI{
    SSID_ptr SSID;                  //Source device ID
    unsigned SSID_index;            //Source device tag
    float dBm;                      //Received signal strength
    float distance;
};

struct Launch{
    float dBm;                      //wifi signal strength
    float distance;
};

struct Antenna{
    unsigned rssis_size;
    RSSI *rssis;
    int antX;
    int antY;
    Launch lau;
};

/* WAP,Wireless Access Point */
struct WAP{
    SSID_ptr SSID;                  //ID
    unsigned index;                 //tag
    unsigned antenna_size;
    Antenna *ant;
    int wapX;
    int wapY;
};

#endif // GLOBAL_H
