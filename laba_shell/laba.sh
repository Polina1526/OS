#!/bin/sh
# shebang
p=0  # обнуляем счетчки
prer () {  # функция обработки прерывания
  p=`expr $p + 1`  # увеличиваем счетчик прерываний
  if [ $p -eq 1 ]; then  # при первом прерывании
    echo " Interruption # 1"  # выводится сообщение
  fi
  if [ $p -eq 2 ]; then  # при втором прерывании
    echo " Interruption # 2"  # перезапуск программы
    echo " Restart the programm"
    continue
  fi
  if [ $p -eq 3 ]; then  # при третьем прерывании
    echo " Interruption #3 is the last interruption"
    rm laba21.bat
    echo " Making an exit!"  # завершение программы
    exit 1
  fi
}
touch laba21.bat  # создание командного файла
while true  # бесконечный цикл
  trap prer 2  # прерывания
  do
  echo "Enter the c-file name (without extension):"
  read a
  sleep 1
  echo "reading file name..."
  sleep 3
  echo "creating command file..."
  sleep 3
  echo "$a" | (read b;
  echo "#!/bin/bash" > laba21.bat;
  echo "gcc -o $b.exe $b.c" >> laba21.bat;
  echo "$b.exe" >> laba21.bat)
  echo "file laba21.bat created"
  break
  done