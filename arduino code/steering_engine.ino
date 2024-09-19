
void setup() {
  //硬件串口波特率
  Serial.begin(9600);
  
  
}

void loop() {
   //执行分组动作，动作需要在小程序上进行训练，0A是固定值，19代表执行ID为19编号的动作组，id值从小程序中按键管理里面获取
  delay(5000);//休息5000毫秒
 // Serial.write("$0A19!");
  //控制单个舵机直接运行，格式：1A为固定写法，002表示舵机编号，三位数；030表示舵机旋转的角度值，三位数，取值范围从000-180内
  Serial.write("$1A002030!");//2号舵机执行30度
  delay(300);//休息200毫秒
  Serial.write("$1A002050!");//2号舵机执行50度
  delay(300);//休息200毫秒
  Serial.write("$1A002070!");//2号舵机执行70度
  delay(300);//休息200毫秒
  Serial.write("$1A002050!");//2号舵机执行50度
  delay(300);//休息200毫秒
}
