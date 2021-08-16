# FRAM-master-MOD
FRAM-master-MOD - это модифицированная библиотека для работы с FRAM FM24C04B на Arduino.

*************************************

  Автор:  B@tto
  Контакты: batto@hotmail.fr
  Сайт: battomicro.wordpress.com
  Версия: 1.0
  Создана: 15.04.2014г. (начальный выпуск)
  Ссылка на проект: https://github.com/battosai30/FRAM

*************************************
  
  Внёс доработку в библиотеку и в пример: Otto
  Версия: 1.1
  Изменён: 13.08.2021г.
 
 
*************************************

FRAM Library for Arduino and Energia
*************************************
  Пример использования библиотеки FRAM на микросхеме: FM24C04B
     Микросхема имеет на борту 4-Kbit(512 x 8).
     Другими словами, имеем 2 страницы по 256 ячеек,итого с двух страниц доступно 512 ячеек памяти (одна ячейка 8 бит).

  Возможные комбинации адресов (всего 4 комбинации):
       0x50   // адрес первой страницы FM24C04B-G. Адрес второй страницы получается автоматически прибавлением единицы к первому адресу - 0x51
       0x52   // адрес первой страницы FM24C04B-G. Адрес второй страницы получается автоматически прибавлением единицы к первому адресу - 0x53
       0x54   // адрес первой страницы FM24C04B-G. Адрес второй страницы получается автоматически прибавлением единицы к первому адресу - 0x55
       0x56   // адрес первой страницы FM24C04B-G. Адрес второй страницы получается автоматически прибавлением единицы к первому адресу - 0x5

  I2C адреса страниц выставляются комбинированием контактов A1 и A2 (смотреть в даташите).
  Адрес страницы 1-байтный(8бит), поэтому число ячеек на странице 256.

  P.S. Библиотека не учитывает то, что было написано.
  Это означает, что, например, если вы напишете длинное число на странице = 0, адрес = 20,
  а после того, как вы напишете целое число на странице = 0 и адресе = 22,
  ваше длинное число будет повреждено, потому что вы перезаписали его последние два байта.


*************************************
Авторский текст:

Description
This library is designed to use FM24C04B 4Kb Serial 5V F-RAM Memory.
Datasheet : http://datasheet.octopart.com/FM24C04B-G-Ramtron-datasheet-11038332.pdf

Memory is organised in two pages, each page have 512 byte blocks of memory. So, a record is defined by his page and his adress in the page.

Download zip 
Put the FRAM folder in "hardware\libraries\". 
In the Arduino IDE, create a new sketch (or open one) and 
select from the menubar "Sketch->Import Library->FRAM".
Once the library is imported, an "#incude <FRAM.h>" line will appear at the top of your sketch. 
You have to add manually "#include <Wire.h>".

Creation
 FRAM(int address) -> Create instance of MCP3424.Address is A2A1 (refer to datasheet). For example, if pins A2 and A1 are high, the instanciation would be "MCP3424 MCP(3)" because A2=1 A1=1 so in binary 11 and 3 in decimal.
 
Methods
	
The available methods do how they are named. 

void WriteLong(byte Page, byte Address, long Data); ==> write a long at page Page and address Adress. Takes 4 bytes
long ReadLong(byte Page,byte Address); ==> return the long stored at page Page and address Adress
void WriteInt(byte Page,byte Address, int Data); ==> same WriteLong but for int. Takes 2 bytes
int ReadInt(byte Page,byte Address); ==> same as ReadLong but for int
void WriteByte(byte Page,byte Address,byte Data); ==> same WriteLong but for byte. Takes 1 bytes
byte ReadByte(byte Page,byte Address);==> same as ReadLong but for byte

Example
FRAM_EXAMPLE -> simple write / serial read back

Cautions

- Take care of the supply voltage : the range is 4,5V - 5,5V. If you apply 4V it won't work (which can happen easily is you use USB supply).
- For the same reason, you may need a level shifter to interface it with 3.3V microcontrollers  
- The library doesn't take account of what have been written. That means if for example you write a long at page=0 address=20 and after you write an integer at page=0 and address=22, your long is corrupted because you overwrited its last two bytes 