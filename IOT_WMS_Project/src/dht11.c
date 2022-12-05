/*
 * Copyright (c) 2020, RudyLo <luhuadong@163.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-02-18     luhuadong    the first version
 * 2020-10-05     luhuadong    v0.9.0
 */

//#include <rtthread.h>
//#include <rtdevice.h>
//#include <board.h>
//#include "dhtxx.h"
//
//#include "hal_data.h"
//#include "onenet.h"
//
//#define DATA_PIN                 0x0800
//#define TEST_COUNT               50
//
//static float Humi_Data = 0.0;
//static float Temp_Data = 0.0;
//
//static void read_humi_entry(void *args)
//{
//    rt_device_t humi_dev = RT_NULL;
//    struct rt_sensor_data sensor_data;
//
//    humi_dev = rt_device_find(args);
//    if (!humi_dev)
//    {
//        rt_kprintf("Can't find humi device.\n");
//        return;
//    }
//
//    if (rt_device_open(humi_dev, RT_DEVICE_FLAG_RDWR))
//    {
//        rt_kprintf("Open humi device failed.\n");
//        return;
//    }
//
////    for (int i=0; i<TEST_COUNT; i++)
//    while(1)
//    {
//        if (1 != rt_device_read(humi_dev, 0, &sensor_data, 1))
//        {
//            rt_kprintf("Read humi data failed.\n");
//        }
//        else
//        {
//            Humi_Data = sensor_data.data.humi;
//            onenet_mqtt_upload_digit("DHT_Humi", Humi_Data);
//            rt_kprintf("\n[%d] Humi: %d.%d%\n", sensor_data.timestamp, sensor_data.data.humi/10, sensor_data.data.humi%10);
//        }
//        rt_thread_mdelay(3000);
//    }
//
//    rt_device_close(humi_dev);
//}
//
//static void read_temp_entry(void *args)
//{
//    rt_device_t temp_dev = RT_NULL;
//    struct rt_sensor_data sensor_data;
//
//    temp_dev = rt_device_find(args);
//    if (!temp_dev)
//    {
//        rt_kprintf("Can't find temp device.\n");
//        return;
//    }
//
//    if (rt_device_open(temp_dev, RT_DEVICE_FLAG_RDWR))
//    {
//        rt_kprintf("Open temp device failed.\n");
//        return;
//    }
//
////    for (int i=0; i<TEST_COUNT; i++)
//    while(1)
//    {
//        if (1 != rt_device_read(temp_dev, 0, &sensor_data, 1))
//        {
//            rt_kprintf("Read temp data failed.\n");
//        }
//        else
//        {
//            Temp_Data = sensor_data.data.temp;
//            onenet_mqtt_upload_digit("DHT_Temp", Temp_Data);
//            rt_kprintf("\n[%d] Temp: %d.%d\n", sensor_data.timestamp, sensor_data.data.temp/10, sensor_data.data.temp%10);
//        }
//        rt_thread_mdelay(3000);
//    }
//
//
//    rt_device_close(temp_dev);
//}
//
//
//int dhtxx_read_Thread(void)
//{
//    rt_thread_t humi_thread, temp_thread;
//
//    humi_thread = rt_thread_create("humi_th", read_humi_entry,
//                                   "humi_dht", 1024,
//                                    4, 20);
//
//
//    temp_thread = rt_thread_create("temp_th", read_temp_entry,
//                                   "temp_dht", 1024,
//                                    4, 20);
//
//    if (humi_thread)
//        rt_thread_startup(humi_thread);
//
//    if (temp_thread)
//        rt_thread_startup(temp_thread);
//
//}
//MSH_CMD_EXPORT(dhtxx_read_Thread, read dhtxx sensor data);
//
//
//static int rt_hw_dht_port(void)
//{
//    struct rt_sensor_config cfg;
//
//    cfg.intf.type = RT_SENSOR_INTF_ONEWIRE;
//    cfg.intf.user_data = (void *)DATA_PIN;
//    rt_hw_dht_init("dht", &cfg);
//
//    return RT_EOK;
//}
//INIT_COMPONENT_EXPORT(rt_hw_dht_port);



#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "dhtxx.h"
#include "onenet.h"
//#include "hal_data.h"
#define DATA_PIN   0x0800
float Humi_Data = 0.0;
double Temp_Data = 0.0;

/* cat_dhtxx sensor data by dynamic */
void cat_dhtxx(void)
{
    dht_device_t sensor = dht_create(DATA_PIN);
    if(dht_read(sensor))
    {
        rt_int32_t temp = dht_get_temperature(sensor);
        rt_int32_t humi = dht_get_humidity(sensor);

        Temp_Data = (float)temp / 10.0;
        onenet_mqtt_upload_digit("DHT_Temp",Temp_Data);
        rt_thread_mdelay(3000);

        Humi_Data = (float)humi / 10;
        onenet_mqtt_upload_digit("DHT_Humi", Humi_Data);
        rt_thread_mdelay(3000);

        rt_kprintf("\nTemp: %d.%d'C,  Humi: %d'%\n", temp/10, temp%10, humi/10);
    }
    else
    {
        rt_kprintf("Read dht sensor failed.\n");
    }
    rt_thread_mdelay(1);
    dht_delete(sensor);
}
MSH_CMD_EXPORT(cat_dhtxx, read dhtxx humidity and temperature);


static int rt_hw_dht_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.type = RT_SENSOR_INTF_ONEWIRE;
    cfg.intf.user_data = (void *)DATA_PIN;
    rt_hw_dht_init("dht", &cfg);

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_dht_port);
