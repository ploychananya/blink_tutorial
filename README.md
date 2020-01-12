# Installing NodeJS
https://phoenixnap.com/kb/install-node-js-npm-on-windows


# Starting NodeJS server
    sudo npm i  
    //apply this line only the first time starting nodejS server.
    // this line will install all needed packages.
    sudo npm start 
    // apply everytime you want to work with it. 

# Flash httpServer.ino to Esp8266(Node mcu V3) via ARDUINO IDE

# open WiFi hotspot for Esp8266
    set ssid = AP
    set password = 123456789


# install Postman to see how it work.
    https://www.getpostman.com/downloads/   
    
    1.make a request
    2. choose POST method and assign "localhost:8080/api/blink" this to url panel
    3. click "Body" --> choose "raw" --> choose "JSON"  and put this json information below

        {
            "ip_node_mcu":"192.168.137.189",
            "led": "1",
            "delay":"500"
        }

    ip_node_mcu = ip Address of Node mcu assigned by access point .
    led = 1 or 0 to make led on or off.
    delay = time delay (2000 = 2 sec)
