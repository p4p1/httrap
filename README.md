# httrap
simple web trap to monitor requests.

![trap boiz](https://raw.githubusercontent.com/p4p1/trap/master/assets/logo.jpg)

## Usage:
```
Usage: ./httrap [-hs] [-p port no] [-f file name] [-d dir name]
Usage: ./json_httrap [-hl] [-m METHOD] [-f LOG_FILE_NAME] [-d LOG_FILE_DIR]
```

## Installation:
Copy paste those commands to a terminal
```
git clone https://github.com/p4p1/httrap.git /tmp/httrap
sudo make clean install -C /tmp/httrap
echo "Installation complete, enjoy the software :)"
```

## Example log file output
```
time:{time of request}
GET / HTTP/1.1
Host: {data}
Connection: {data}
Upgrade-Insecure-Requests: {data}
User-Agent: {data}
Accept: {data}
Accept-Encoding: {data}
Accept-Language: {data}
Cookie: {data}
```

## Example json output:
``` json
{
  "time": "CURRENT DATE",
  "latest_log": "GET REQUEST HEADER"
}
```

