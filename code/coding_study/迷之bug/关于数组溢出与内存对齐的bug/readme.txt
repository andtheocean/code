在ubuntu14.4上  
数组溢出刚好覆盖了其后计数的char变量  导致计数到了固定的地方之后又重新开始计数
但是如果是int类型则由于内存对齐  刚好中间空了字节  没有导致任何问题

在winxp 的vs2010上
由于后面定义的变量反倒存前内存地址较小的地方，则没有这个问题

