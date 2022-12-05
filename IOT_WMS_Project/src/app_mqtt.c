///*
// * Copyright (c) 2006-2021, RT-Thread Development Team
// *
// * SPDX-License-Identifier: Apache-2.0
// *
// * Change Logs:
// * Date           Author       Notes
// * 2022-12-02     Yifang       the first version
// */
//#include <rtthread.h>
//#include <rtdevice.h>
//#include "hal_data.h"
//#include "dhtxx.h"
//
//
//rt_thread_t measure_thread = RT_NULL ;
//#define DATA_PIN   BSP_IO_PORT_08_PIN_00
//
//void measure_thread_entry(void)
//{
//    float Temp_data,Humi_data,Light_data;
//    dht_device_t sensor = dht_create(DATA_PIN);
//
////    while(1)
////    {
//        //读取温度数据并上报
////        Temp_data = read_temp();
////        onenet_mqtt_upload_digit("DHT_Temp", temp);
//
//        //读取湿度数据并上报
////        Humi_data = read_humi();
////        onenet_mqtt_upload_digit("DHT_Humi", humi);
//
//        //读取光照数据并上传
////        Light_data = isl29_read_data();
////        onenet_mqtt_upload_digit("Isl29_light", Light_data);
////    }
//
//    if(dht_read(sensor))
//    {
//        rt_int32_t temp = dht_get_temperature(sensor);
//        rt_int32_t humi = dht_get_humidity(sensor);
//
//        for(int i=0; i<5; i++)
//        {
//            rt_kprintf("Temp: %d.%d 'C,  Humi: %d.%d '% \n", temp/10, temp%10, humi/10, humi%10);
//
//            onenet_mqtt_upload_digit("DHT_Temp", temp);
//            onenet_mqtt_upload_digit("DHT_Humi", humi);
//
//            Light_data = isl29_thread();
//            onenet_mqtt_upload_digit("Isl29_light", Light_data);
//        }
//    }
//    else
//    {
//        rt_kprintf("Read dht sensor failed.\n");
//    }
//
//    dht_delete(sensor);
//
////    rt_thread_delete(measure_thread);
//}
//
//void measure_init(void)
//{
//    measure_thread = rt_thread_create("measure_thread", measure_thread_entry, RT_NULL, 2048, 4, 500);
//    if(measure_thread != RT_NULL)
//    {
//        rt_thread_startup(measure_thread);
//    }
//
//}
//MSH_CMD_EXPORT(measure_init,measure init);
