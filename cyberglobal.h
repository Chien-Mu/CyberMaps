#ifndef CYBERGLOBAL_H
#define CYBERGLOBAL_H

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
    float antX;
    float antY;
    Launch lau;
};

/* WAP,Wireless Access Point */
struct WAP{
    SSID_ptr SSID;                  //ID
    unsigned index;                 //tag
    unsigned antenna_size;
    Antenna *ant;
    float wapX;
    float wapY;
};

/// dst 空間要與 src 一樣
void cloneWAP(WAP *src, unsigned src_size,
              WAP *dst, SSID_ptr dst_ssid, Antenna *dst_ant, RSSI *dst_rssi);


#endif // CYBERGLOBAL_H
