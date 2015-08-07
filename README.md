# tools
简单工具, 例如文本文件转换，log信息侦测。

### Projects
* altium_to_allegro_telesis_file 
  把Altium Disegner 生成的telesis网表文件转换成allegro可以识别的网表文件
* serial-read-cmp
  读取调试串口的打印log的信息，然后跟指定的字符串比较，如果log信息包含指定的字符串，就说明捕捉到想要的信息，进而进行相应的操作，如reboot板子，或者控制GPIO触发继电器给板子重新上电
