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
    int time;                       //接收到的計時時間
};

struct Distance{
    SSID ssid;                      //Source device ID
    unsigned ssid_index;            //Source device tag
    float distance;                 //計算結果距離
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
    float wapX;                     //計算結果位置
    float wapY;
    float realWapX;                 //實際位置
    float realWapY;
};

struct lastDistance{
    float distance;                 //從多根天線計算結果距離
    float realDistance;             //實際距離
    unsigned index1;
    unsigned index2;
    float dBm;                      //拿來計算的rssi
    int time;                       //接收到的計時時間
};


#endif // CYBERGLOBAL_H
