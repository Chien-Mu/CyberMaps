#ifndef CYBERGLOBAL_H
#define CYBERGLOBAL_H

#define SSID_SIZE 100
typedef char **SSID_arr;
typedef char *SSID;

#define DEVICE_ANT 2                //每台設備固定天線數


/* RSSI,Received signal strength indication */
struct RSSI{
    SSID ssid;                      //Source device ID
    unsigned ssid_index;            //Source device tag
    float dBm;                      //Received signal strength
};

struct Distance{
    SSID ssid;                      //Source device ID
    unsigned ssid_index;            //Source device tag
    float distance;
};

struct Launch{
    float dBm;                      //wifi signal strength
};

struct Antenna{
    unsigned rssis_size;
    RSSI *rssis;
    float antX;
    float antY;
    Launch lau;
};

/* WAP,Wireless Access Point */
struct WAP{
    SSID ssid;                      //ID
    unsigned index;                 //tag
    unsigned antenna_size;
    Antenna *ant;
    unsigned dist_size;
    Distance *dist;
    float wapX;
    float wapY;
};

struct lastDistance{
    float distance;
    unsigned index1;
    unsigned index2;
};


#endif // CYBERGLOBAL_H
