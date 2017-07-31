#include "cyberglobal.h"

void cloneWAP(WAP *src, unsigned src_size,
              WAP *dst, SSID_ptr dst_ssid, Antenna *dst_ant, RSSI *dst_rssi){

    int jj=0,kk=0;
    for(unsigned i=0;i<src_size;i++){
        dst[i] = src[i];
        dst[i].SSID = &dst_ssid[i];
        //ssid by value
        for(unsigned ii=0;src[i].SSID[0][ii] != '\0';ii++)
            dst_ssid[i][ii] = src[i].SSID[0][ii];

        dst[i].ant = &dst_ant[jj]; //by address, jj 0 2 4
        for(unsigned j=0;j<src[i].antenna_size;j++){
            dst_ant[jj++] = src[i].ant[j]; //by value, jj 0123456,j 01 01 01
            dst[i].ant[j].rssis = &dst_rssi[kk];
            for(unsigned k=0;k<src[i].ant[j].rssis_size;k++){
                dst_rssi[kk++] = src[i].ant[j].rssis[k];
                dst[i].ant[j].rssis[k].SSID = &dst_ssid[ src[i].ant[j].rssis[k].SSID_index ];
            }
        }
    }
}
