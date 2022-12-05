/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-02     Yifang       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>

#include "sensor_renesas_isl29035.h"
#include "onenet.h"

#define ISL29035_I2C_BUS "i2c1"

static float light_data = 0;

int rt_hw_isl29035_port(void)
{
    struct rt_sensor_config cfg;
    cfg.intf.dev_name  = ISL29035_I2C_BUS;
    rt_hw_isl29035_init("isl29035", &cfg);
    return RT_EOK;
}
INIT_ENV_EXPORT(rt_hw_isl29035_port);

float isl29_thread_entry(void *parameter)
{
    rt_device_t dev = RT_NULL;
    struct rt_sensor_data data;
    rt_size_t res;

    /* 查找isl29传感器  */
    dev = rt_device_find("li_isl29");
    if (dev == RT_NULL)
    {
        rt_kprintf("Can't find device:li_isl29\n");
        return;
    }

    /* 以只读模式打开isl29 */
    if (rt_device_open(dev, RT_DEVICE_FLAG_RDONLY) != RT_EOK)
    {
        rt_kprintf("open device(li_isl29) failed!");
        return;
    }


//    for (int i=0; i<50; i++)
//    while(1)
    {
        /* 从传感器读取一个数据 */
        res = rt_device_read(dev, 0, &data, 1);

        if (1 != res)
        {
            rt_kprintf("read data(li_isl29) failed!size is %d", res);
        }
        else
        {
            light_data = data.data.light;

            onenet_mqtt_upload_digit("Isl29_light", light_data);
            rt_kprintf("light:%d lux\n", data.data.light);
            rt_thread_mdelay(3000);
        }
        rt_device_close(dev);
    }
}

int isl29_thread(void)
{
    rt_thread_t tid;    /* 线程句柄 */

    tid = rt_thread_create("isl29_thread",
                            isl29_thread_entry,
                            RT_NULL,
                            1024,
                            4,
                            20);
   if(tid != RT_NULL)
   {
        /* 线程创建成功，启动线程 */
        rt_thread_startup(tid);
   }

   return 0;
}
MSH_CMD_EXPORT(isl29_thread, isl29 thread);
