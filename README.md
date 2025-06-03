# 前言

项目主要功能：

智能台灯和风扇，支持语音控制风扇的转速，手机端控制灯的亮灭，并实时显示温湿度传感器采集的数据

主控板 stm32f103c8t6，外接 ESP8266，作为 wifi 模块，使用机智云平台，与手机端通信，stm32f103c8t6 使用串口 2 与 ESP8266 通信

stm32f103c8t6 使用串口 1 与天问模块通信，天问模块用于用户进行语音控制。

DHT11实时采集温湿度数据，将数据实时显示在 OLED 显示屏，同时将数据通过串口 2 发送至 ESP8266，ESP8266 通过机智云协议再将数据打包发送至手机端，**实现实时显示温湿度传感器采集的数据**

定时器 3 的通道 1 和通道 2 设置不同的占空比，分别输出 PWM 波，控制 LED 灯和风扇，从而实现亮度和转速的调节。同时天问模块也可以通过串口 1 发送指令到主控板，改变风扇占空比，从而 **实现语音控制风扇的转速**，**手机端也可以发送指令控制 LED 的亮灭**

同时定时器1提供1ms的中断，为机智云提供时间帧

文件结构：

- Demo：测试代码
- Emulation：仿真程序
- Report：报告和 PPT（报告很垃圾，建议大家重新写，PPT 可以，尤其是机智云模块，**是作者我用心打磨**）
- 点亮 E 只大马猴：来源于他 b 站提供的资料**（强烈推荐）**

![image-20250603083250329](D:/06-Documents/Blog/source/images/image-20250603083250329.png)

## 辰哥单片机设计

代码的 **全部** 来源，将辰哥提供的代码进行了整合，并修改了引脚设置，稍作修改

![image-20250513084858100](D:/06-Documents/Blog/source/images/image-20250513084858100.png)



- ESP8266

  【ESP8266 模块（WIFI STM32）】https://www.bilibili.com/video/BV1oSxteYEZy?vd_source = fe8f5a276c042b87f677f1cf9bad7567

- 机智云搭建

  【手把手带你搭建机智云平台】https://www.bilibili.com/video/BV1HY2HY9EJh?vd_source = fe8f5a276c042b87f677f1cf9bad7567

- 天问

  【ASRPRO 语音模块（STM32）】https://www.bilibili.com/video/BV1dtKWeYEnm?vd_source = fe8f5a276c042b87f677f1cf9bad7567

- DHT11

  【DHT11 温湿度传感器详解（STM32）】https://www.bilibili.com/video/BV182421Z7by?vd_source = fe8f5a276c042b87f677f1cf9bad7567

- BH1750（由于不知名 bug，最终把它舍弃）

  【BH1750 光照强度传感器详解（STM32）】https://www.bilibili.com/video/BV14T421678Q?vd_source = fe8f5a276c042b87f677f1cf9bad7567

- 风扇

  【风扇模块（直流 5V STM32）】https://www.bilibili.com/video/BV1a1tCegErN?vd_source = fe8f5a276c042b87f677f1cf9bad7567

- 大功率 LED

  【大功率 LED 模块（5V STM32）】https://www.bilibili.com/video/BV1cvsQeMEdf?vd_source = fe8f5a276c042b87f677f1cf9bad7567

- 四针 OLED

  【OLED 显示屏详解(IIC 协议 0.96 寸 STM32）】https://www.bilibili.com/video/BV17Z421K7vV?vd_source = fe8f5a276c042b87f677f1cf9bad7567



上述模块，辰哥在 CSDN 上发布了全部相关内容，文字部分，大家如果不想看视频，直接看 CSDN 文字部分也行。

![image-20250513085143572](D:/06-Documents/Blog/source/images/image-20250513085143572-1747097554902-1.png)

## 点亮 E 只大马猴

不聪明的智能管家系统，主要涉及原理图搭建，**PCB 绘制（最终舍弃**），代码的整体框架设计参考。

另外给大家推荐这个 up 主，**幽默风趣，很有意思**

![image-20250513084937866](D:/06-Documents/Blog/source/images/image-20250513084937866.png)

【STM32+PCB 设计+物联网，手牵手带你从零开始画板子+写代码】https://www.bilibili.com/video/BV18arkYjEuL?vd_source = fe8f5a276c042b87f677f1cf9bad7567



## 仿真文件

原理图 ，非常重要，我们代码框架就是按照此进行开发

注意：

- 电源模块就是摆设，我们最终舍弃
- 光传感器模块因为 bug，舍弃

**硬件电路的引脚连接，代码的整体框架设计，完全按照这个开发**

![image-20250513085752644](D:/06-Documents/Blog/source/images/image-20250513085752644.png)

![img](D:/06-Documents/Blog/source/images/b633188864be4a72b4820ff7a742b617.png)



## 代码

测试代码，主要是测试各个模块（**来源辰哥**，**修改了引脚和 PWM 模块，以及串口通信模块**）

- OLED，测试四针 OLED 能否正常使用
- DHT11：测试传感器能否正常采集数据
- BH1750：舍弃
- Airpro：测试天问与主控板能否正常通信
- DHT11+BH1750：舍弃
- fan：测试风扇是否可以控制转速（**未测试**）
- LED：测试大功率 LED 模块是否可以控制亮度，其中使用的是呼吸灯
- fan+LED：将风扇和 LED 的 PWM 输出代码结合，对辰哥的代码进行修改（只测试了 LED 模块）
- Airpro+fan+LED：**目前的总代码，测试成功**，**包含机智云**
- Airpro+fan+LED-副本：测试天问能否控制 LED 的亮灭
- ESP8266：空
- 机智云：测试机智云协议

![image-20250513090054344](D:/06-Documents/Blog/source/images/image-20250513090054344.png)

## 实物

这是我们的实物连接图，用面包板连，确实很丑

![image-20250603081651084](D:/06-Documents/Blog/source/images/image-20250603081651084.png)

这是我们使用机智云开发的移动界面

![image-20250603081743747](D:/06-Documents/Blog/source/images/image-20250603081743747.png)

## 材料

如果大家想要复刻我的项目的话，不可避免的要去买材料，我材料大概花了160多块钱，当然是和队友AA的，其实买材料的话大家只要看准型号和封装，去淘宝上随便找一家买就行，建议还是只买一家，省钱。

下面是我采购的材料

<img src="D:/06-Documents/Blog/source/images/113511fe4fecaaa2946a0d3ee4cb2bd.jpg" alt="113511fe4fecaaa2946a0d3ee4cb2bd" style="zoom:25%;" />



<img src="D:/06-Documents/Blog/source/images/d10d3cc6babe4d55524cfd94a2aa5b4.jpg" alt="d10d3cc6babe4d55524cfd94a2aa5b4" style="zoom:25%;" />

## 小结

我个人认为该项目是一个比较好的嵌入式练手项目，开发也不是很难，而且也很有趣，值得入手。

如果想要真正搞懂这个项目：

- 先看网课
- 然后使用 deepseek 看代码

我感觉最多就是花几天的时间。

如果对大家有所帮助，**希望大家帮忙点亮 star**，有问题欢迎私信 3042898802@qq.com，希望大家一起学习成长

**最后就是感谢辰哥，感觉大马猴，你们开源的无私帮助，帮了我很大的忙**
