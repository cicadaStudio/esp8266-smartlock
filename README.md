# ESP8266 开发经验
2018-4-9 @davidliyutong
## 简介
一个可以用python控制的，基于HTTP请求的智能LED。
## 配置Arduino IDE
#### 安装驱动
- Windows 下即插即用
- Mac 下需要安装CH340 驱动，下载地址为  
 http://www.wch.cn/download/CH341SER_MAC_ZIP.html
#### 安装ESP8266 开发版
1. 在 Arduino IDE 的偏好设置中添加开发版管理网站  
 http://arduino.esp8266.com/stable/package_esp8266com_index.json
2. 工具>开发版>开发版管理器 安装ESP8266定义
3. 重启 Arduino IDE  
4. 工具>开发版 中选择 ```Generic ESP8266```

#### ESP8266 开发配置

  - 编程器选择默认的 AVRISP mkII
  - **Flash Mode** 选择 ```DOUT```
## 烧录器的使用
**跳帽** 的作用是让相关端口短接，因为没有电表，因此也不了解短接之后端口的电位。  
使ESP8266工作需要用跳帽或导线短接```SW```*（对应CH_PD，从ESP8266工作特性来看应该被置高了）*，此外刷写ESP8266还需要短接```GPIO0```*（从ESP8266工作特性来看应该被置低了）*

#### 刷写ESP8266需要如此操作
1. 把ESP8266 插入烧写器
2. 将 ```SW``` 和 ```GPIO0``` 用跳帽或导线短接
3. 把烧写器插入电脑USB接口
4. 在Arduino中选择ESP8266对应的串口
5. Arduino 中编译上传，此时ESP8266 写入指示灯闪烁
6. 上传完成，拔掉 ```GPIO0``` 的跳帽或导线，**拔掉后再连接** ```SW``` 的（这是为了重置ESP8266，转换状态）
7. ESP8266 开始执行程序

#### 若要再次写入程序
1. 用跳帽或导线连接 ```GPIO0``` ，**拔掉后再连接** ```SW``` 的
2. Arduino 中编译上传，此时ESP8266 写入指示灯闪烁
3. 上传完成，拔掉 ```GPIO0``` 的跳帽或导线，**拔掉后再连接** ```SW``` 的

## 小技巧
- Arduino 事例有现成的Example可以实验，大部分只需要修改Wifi 的```SSID```和```PSK```  
- 可以用导线，开关和面包版快速复位，实现快速转换模式，从而免去插拔USB
