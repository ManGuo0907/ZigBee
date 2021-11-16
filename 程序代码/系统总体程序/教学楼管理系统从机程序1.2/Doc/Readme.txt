
项目硬件连接：

光照强度传感器+OLED屏显示
OLED使用软件IIC
PB6 -- SCL; PB7 -- SDA
光照强度BH1750   GY-302
IIC通信协议
SCL -- PB6   SDA -- PB7
ADDR -- GND 
指纹识别模块——USART3
温湿度传感器——PB13
MG90S舵机 —— PA8，TIM——CH1
注意：！！！  按键key2不可用
时间：2020/8/23

修改内容：
（1）增加粉尘传感器，使用ADC1收集电压信号
粉尘传感器GP2Y10 ———— ADC——PA0   LED——PC14
（2）增加两个LED指示灯
白色——PA4   蓝色——PA5
时间：2020/8/24