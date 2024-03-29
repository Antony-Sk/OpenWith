## OpenWith

Утилита "openwith" позволяет разработчикам приложений регистрировать обработчики на событие открытия файлов. Файл `include/api.h` содержит функцию 
```cpp
reg_format(
	std::string format, 
	std::string exec_path,
	std::string[] exec_args
)
```
которая позволяет это сделать.

`format` - это расширение на которое регистрируется обработчик (например `txt`, `png`, `pdf`)

`exec_path` - путь до исполняемого файла обработчика (`texteditor`, `gedit`, ...)

`exec_args` - массив аргументов, которые передаются в обработчик (`--filename`, `-c`)

Директория `demo` содержит простой пример регистрации приложения `pluma` на расширение `txt` (для запуска можно поменять на любой другой редактор `gedit`, `kate` ...)

Папка `daemon` содержит код для программы-демона, который хранит и вызывает зарегистрированные обработчики. Именно к нему через `dbus` обращается функция `reg_format()`.

`openwith` содержит код самой утилиты. Она также использует `dbus` но уже с целью не зарегистрировать, а вызвать обработчик.

### Build

Зависимости: `qdbus`

Установка: `sudo apt install qdbus`

Собирается командой:

```bash
mkdir build
cd build
cmake ..
make ..
```

Исполняемые файлы будут лежать в `build` в соответствующих поддиректориях

Чтобы после этого собрать `deb` пакет:
```bash
cp openwith/src/openwith ../daemon/deb/openwith/usr/local/bin
cd ../daemon/deb
dpkg-deb --build openwith
```

### Example

Собрать проект, запустить демона, зарегистрировать `pluma` для  `txt` и попытаться открыть `a.txt`:
```
$ mkdir build
$ cd build
$ cmake ..
> ...
$ make ..
> ...
$ ./daemon/src/daemon &
$ ./demo/src/reg_handlers_demo
> Handler registered
$ echo "Hello" > a.txt
$ ./openwith/src/openwith a.txt
<Pluma opens>
```
В файле 'demo/src/main.cpp' можно поменять команду и расширение и зарегистрировать другие обработчики

### Todo

* Сейчас обработчик на какой-либо формат перезаписывает старый. Можно сделать чтобы хранились все обработчики и `openwith` позволял выбирать из списка
* Если будет вызвана ошибка при вызове обработчика, об этом никто не узнает, кроме демона. Можно возвращать ошибку в `openwith` при возникновении такой ситуации
* Добавить функцию для удаления обработчика