/*
* Copyright (C) 2015 Project http://www.wino-board.de/
* based on code by ITEAD Studio Teams (C) 2015 ITEADLIB_Arduino_WeeESP8266
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/
// #warning "wino.cpp v1.5 loaded"

#define WINO_CPP
#include "wino.h"


#define LOG_OUTPUT_DEBUG            (1)
#define LOG_OUTPUT_DEBUG_PREFIX     (1)

#define logDebug(arg)\
    do {\
        if (LOG_OUTPUT_DEBUG)\
        {\
            if (LOG_OUTPUT_DEBUG_PREFIX)\
            {\
                Serial.print("[LOG Debug: ");\
                Serial.print((const char*)__FILE__);\
                Serial.print(",");\
                Serial.print((unsigned int)__LINE__);\
                Serial.print(",");\
                Serial.print((const char*)__FUNCTION__);\
                Serial.print("] ");\
            }\
            Serial.print(arg);\
        }\
    } while(0)

#ifdef ESP8266_USE_SOFTWARE_SERIAL
ESP8266::ESP8266(SoftwareSerial &uart, uint32_t baud): m_puart(&uart)
{
//    m_puart->begin(baud);
//    rx_empty();
}
#else

WiFiESP::WiFiESP(HardwareSerial &uart, uint32_t baud): m_puart(&uart)
{
//    extern void setup(void);
//    setup();
//    m_puart->begin(baud);
//    rx_empty();
}
#endif

bool isserver = 0;

bool WiFiESP::getStatus(void)
{   uint8_t attempt=10;
    while(attempt&&(!eAT()))
        attempt--;
    return !!attempt;
    //return(eAT());
}

bool WiFiESP::restart(void)
{
    unsigned long start;
    if (eATRST()) {
        delay(2000);
        start = millis();
        while (millis() - start < 3000) {
            if (eAT()) {
                delay(1500); /* Waiting for stable */
                return true;
            }
            delay(100);
        }
    }
    return false;
}

String WiFiESP::info(void)
{
    String version;
    eATGMR(version);
    return version;
}

bool WiFiESP::setMode(uint8_t mode)
{   uint8_t old_mode;
    switch(mode)
        {   case 0: // Set operation mode to staion.
                    if (!qATCWMODE(&old_mode)) {
                        return false;
                    }
                    if (old_mode == 1) {
                        return true;
                    } else {
                        if (sATCWMODE(1) && restart()) {
                            return true;
                        } else {
                            return false;
                        }
                    }
                    break;
            case 1: // Set operation mode to softap.
                    if (!qATCWMODE(&old_mode)) {
                        return false;
                    }
                    if (old_mode == 2) {
                        return true;
                    } else {
                        if (sATCWMODE(2) && restart()) {
                            return true;
                        } else {
                            return false;
                        }
                    }
                    break;
            case 2: // Set operation mode to station + softap.
                    if (!qATCWMODE(&old_mode)) {
                        return false;
                    }
                    if (old_mode == 3) {
                        return true;
                    } else {
                        if (sATCWMODE(3) && restart()) {
                            return true;
                        } else {
                            return false;
                        }
                    }
                    break;
            case 3: off();
                    delay(100);
                    pinMode(13,OUTPUT);
                    digitalWrite(13,LOW);
                    delay(100);
                    #ifdef __SAMD21G18A__
                        #define WIFI_EN_PIN 14
                    #endif
                    pinMode(WIFI_EN_PIN,OUTPUT);
                    digitalWrite(WIFI_EN_PIN,HIGH);
                    m_puart->begin(baud_default);
                    rx_empty();
                    break;
        }
}

String WiFiESP::list(void)
{
    String list;
    eATCWLAP(list);
    return list;
}

bool WiFiESP::join(String ssid, String pwd)
{
    return sATCWJAP(ssid, pwd);
}

bool WiFiESP::leave(void)
{
    return eATCWQAP();
}

bool WiFiESP::config(String ssid, String pwd, uint8_t chl, uint8_t ecn)
{
    return sATCWSAP(ssid, pwd, chl, ecn);
}

String WiFiESP::getDevices(void)
{
    String list;
    eATCWLIF(list);
    return list;
}

String WiFiESP::getipStatus(void)
{
    String list;
    eATCIPSTATUS(list);
    return list;
}

String WiFiESP::getip(void)
{
    String list;
    eATCIFSR(list);
	
	//Station IP output
	String  ip = list;
	int start = ip.indexOf("STAIP") + 7;
	int ende = ip.indexOf("\"", start);
	list = ip.substring(start, ende);
	
    return list;
}

String WiFiESP::getmac(void)
{
    String list;
    eATCIFSR(list);
  
  //Station MAC output
  String  mac = list;
  int start = mac.indexOf("STAMAC") + 8;
  int ende = mac.indexOf("\"", start);
  list = mac.substring(start, ende);
  
    return list;
}

bool WiFiESP::mux(uint8_t mux_enable)
{
    if(mux_enable==0)
        return sATCIPMUX(1);
    else
        return sATCIPMUX(0);
}

bool WiFiESP::setTCPServerTimeout(uint32_t timeout)
{
    return sATCIPSTO(timeout);
}

bool WiFiESP::sleep(uint32_t timeout)
{
    return sATGSLP(timeout);
}
bool WiFiESP::sleepmode(uint32_t mode)
{
    return sATSLEEP(timeout);
}

bool WiFiESP::start(uint32_t port)
{
    if (sATCIPSERVER(1, port)) {
        return true;
    }
    return false;
}

bool WiFiESP::stop(void)
{
    sATCIPSERVER(0);
    restart();
    return false;
}

bool WiFiESP::write(const uint8_t *buffer, uint32_t len)
{
    return sATCIPSENDSingle(buffer, len);
}

bool WiFiESP::write(uint8_t mux_id, const uint8_t *buffer, uint32_t len)
{
    return sATCIPSENDMultiple(mux_id, buffer, len);
}

/*added ----------------------------------------------------------------------------*/
bool WiFiESP::writeln(String data)
{
		char buffer[data.length()+1];
		data.toCharArray(buffer,data.length()+1);
		return sATCIPSENDSingle((const uint8_t*)buffer, strlen(buffer));
}

bool WiFiESP::writeln(uint8_t mux_id, String data)
{
		char buffer[data.length()+1];
		data.toCharArray(buffer, data.length()+1);
		return sATCIPSENDMultiple(mux_id, (const uint8_t*)buffer, strlen(buffer) );
}


uint32_t WiFiESP::read(uint8_t *buffer, uint32_t buffer_size, uint32_t timeout)
{
    return recvPkg(buffer, buffer_size, NULL, timeout, NULL);
}

uint32_t WiFiESP::read(uint8_t mux_id, uint8_t *buffer, uint32_t buffer_size, uint32_t timeout)
{
    uint8_t id;
    uint32_t ret;
    ret = recvPkg(buffer, buffer_size, NULL, timeout, &id);
    if (ret > 0 && id == mux_id) {
        return ret;
    }
    return 0;
}

uint32_t WiFiESP::read(uint8_t *coming_mux_id, uint8_t *buffer, uint32_t buffer_size, uint32_t timeout)
{
    return recvPkg(buffer, buffer_size, NULL, timeout, coming_mux_id);
}

String WiFiESP::readln(uint32_t timeout)
{
	String response = "";
	uint8_t buffer[1024] = {0};
	uint32_t len = wifi.read(buffer, sizeof(buffer), timeout);
    if (len > 0) {
        for(uint32_t i = 0; i < len; i++) {
			response.concat((char)buffer[i]); 
        }
        return response;
    }
}
String WiFiESP::readln(uint8_t *coming_mux_id, uint32_t timeout)
{
	String response = "";
	uint8_t buffer[1024] = {0};
	uint32_t len = wifi.read(coming_mux_id, buffer, sizeof(buffer), timeout);
    if (len > 0) {
        for(uint32_t i = 0; i < len; i++) {
			response.concat((char)buffer[i]); 
        }
        return response;
    }
}

  

/*----------------------------------------------------------------------------*/
/* +IPD,<id>,<len>:<data> */
/* +IPD,<len>:<data> */

uint32_t WiFiESP::recvPkg(uint8_t *buffer, uint32_t buffer_size, uint32_t *data_len, uint32_t timeout, uint8_t *coming_mux_id)
{
    String data;
    char a;
    int32_t index_PIPDcomma = -1;
    int32_t index_colon = -1; /* : */
    int32_t index_comma = -1; /* , */
    int32_t len = -1;
    int8_t id = -1;
    bool has_data = false;
    uint32_t ret;
    unsigned long start;
    uint32_t i;
    
    if (buffer == NULL) {
        return 0;
    }
    
    start = millis();
    while (millis() - start < timeout) {
        if(m_puart->available() > 0) {
            a = m_puart->read();
            data += a;
        }
        
        index_PIPDcomma = data.indexOf("+IPD,");
        if (index_PIPDcomma != -1) {
            index_colon = data.indexOf(':', index_PIPDcomma + 5);
            if (index_colon != -1) {
                index_comma = data.indexOf(',', index_PIPDcomma + 5);
                /* +IPD,id,len:data */
                if (index_comma != -1 && index_comma < index_colon) { 
                    id = data.substring(index_PIPDcomma + 5, index_comma).toInt();
                    if (id < 0 || id > 4) {
                        return 0;
                    }
                    len = data.substring(index_comma + 1, index_colon).toInt();
                    if (len <= 0) {
                        return 0;
                    }
                } else { /* +IPD,len:data */
                    len = data.substring(index_PIPDcomma + 5, index_colon).toInt();
                    if (len <= 0) {
                        return 0;
                    }
                }
                has_data = true;
                break;
            }
        }
    }
    
    if (has_data) {
        i = 0;
        ret = len > buffer_size ? buffer_size : len;
        start = millis();
        while (millis() - start < 3000) {
            while(m_puart->available() > 0 && i < ret) {
                a = m_puart->read();
                buffer[i++] = a;
            }
            if (i == ret) {
                rx_empty();
                if (data_len) {
                    *data_len = len;    
                }
                if (index_comma != -1 && coming_mux_id) {
                    *coming_mux_id = id;
                }
                return ret;
            }
        }
    }
    return 0;
}

void WiFiESP::rx_empty(void) 
{
    while(m_puart->available() > 0) {
        m_puart->read();
    }
}

String WiFiESP::recvString(String target, uint32_t timeout)
{
    String data;
    char a;
    unsigned long start = millis();
    while (millis() - start < timeout) {
        while(m_puart->available() > 0) {
            a = m_puart->read();
			if(a == '\0') continue;
            data += a;
        }
        if (data.indexOf(target) != -1) {
            break;
        }   
    }
    return data;
}

String WiFiESP::recvString(String target1, String target2, uint32_t timeout)
{
    String data;
    char a;
    unsigned long start = millis();
    while (millis() - start < timeout) {
        while(m_puart->available() > 0) {
            a = m_puart->read();
			if(a == '\0') continue;
            data += a;
        }
        if (data.indexOf(target1) != -1) {
            break;
        } else if (data.indexOf(target2) != -1) {
            break;
        }
    }
    return data;
}

String WiFiESP::recvString(String target1, String target2, String target3, uint32_t timeout)
{
    String data;
    char a;
    unsigned long start = millis();
    while (millis() - start < timeout) {
        while(m_puart->available() > 0) {
            a = m_puart->read();
			if(a == '\0') continue;
            data += a;
        }
        if (data.indexOf(target1) != -1) {
            break;
        } else if (data.indexOf(target2) != -1) {
            break;
        } else if (data.indexOf(target3) != -1) {
            break;
        }
    }
    return data;
}

bool WiFiESP::recvFind(String target, uint32_t timeout)
{
    String data_tmp;
    data_tmp = recvString(target, timeout);
    if (data_tmp.indexOf(target) != -1) {
        return true;
    }
    return false;
}

bool WiFiESP::recvFindAndFilter(String target, String begin, String end, String &data, uint32_t timeout)
{
    String data_tmp;
    data_tmp = recvString(target, timeout);
    if (data_tmp.indexOf(target) != -1) {
        int32_t index1 = data_tmp.indexOf(begin);
        int32_t index2 = data_tmp.indexOf(end);
        if (index1 != -1 && index2 != -1) {
            index1 += begin.length();
            data = data_tmp.substring(index1, index2);
            return true;
        }
    }
    data = "";
    return false;
}

bool WiFiESP::eAT(void)
{
    rx_empty();
    m_puart->println("AT");
    return recvFind("OK");
}

bool WiFiESP::eATRST(void) 
{
    rx_empty();
    m_puart->println("AT+RST");
    return recvFind("OK");
}

bool WiFiESP::eATGMR(String &version)
{
    rx_empty();
    m_puart->println("AT+GMR");
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", version); 
}

bool WiFiESP::qATCWMODE(uint8_t *mode) 
{
    String str_mode;
    bool ret;
    if (!mode) {
        return false;
    }
    rx_empty();
    m_puart->println("AT+CWMODE?");
    ret = recvFindAndFilter("OK", "+CWMODE:", "\r\n\r\nOK", str_mode); 
    if (ret) {
        *mode = (uint8_t)str_mode.toInt();
        return true;
    } else {
        return false;
    }
}

bool WiFiESP::sATCWMODE(uint8_t mode)
{
    String data;
    rx_empty();
    m_puart->print("AT+CWMODE=");
    m_puart->println(mode);
    
    data = recvString("OK", "no change");
    if (data.indexOf("OK") != -1 || data.indexOf("no change") != -1) {
        return true;
    }
    return false;
}

bool WiFiESP::sATCWJAP(String ssid, String pwd)
{
    String data;
    rx_empty();
    m_puart->print("AT+CWJAP=\"");
    m_puart->print(ssid);
    m_puart->print("\",\"");
    m_puart->print(pwd);
    m_puart->println("\"");
    
    data = recvString("OK", "FAIL", 10000);
    if (data.indexOf("OK") != -1) {
        return true;
    }
    return false;
}

bool WiFiESP::eATCWLAP(String &list)
{
    String data;
    rx_empty();
    m_puart->println("AT+CWLAP");
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", list, 10000);
}

bool WiFiESP::eATCWQAP(void)
{
    String data;
    rx_empty();
    m_puart->println("AT+CWQAP");
    return recvFind("OK");
}

bool WiFiESP::sATCWSAP(String ssid, String pwd, uint8_t chl, uint8_t ecn)
{
    String data;
    rx_empty();
    m_puart->print("AT+CWSAP=\"");
    m_puart->print(ssid);
    m_puart->print("\",\"");
    m_puart->print(pwd);
    m_puart->print("\",");
    m_puart->print(chl);
    m_puart->print(",");
    m_puart->println(ecn);
    
    data = recvString("OK", "ERROR", 5000);
    if (data.indexOf("OK") != -1) {
        return true;
    }
    return false;
}

bool WiFiESP::eATCWLIF(String &list)
{
    String data;
    rx_empty();
    m_puart->println("AT+CWLIF");
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", list);
}
bool WiFiESP::eATCIPSTATUS(String &list)
{
    String data;
    delay(100);
    rx_empty();
    m_puart->println("AT+CIPSTATUS");
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", list);
}

bool WiFiESP::connect(String protocol, String addr, uint32_t port)
{
    String data;
    rx_empty();
    m_puart->print("AT+CIPSTART=\"");
    m_puart->print(protocol);
    m_puart->print("\",\"");
    m_puart->print(addr);
    m_puart->print("\",");
    m_puart->println(port);
    
    data = recvString("OK", "ERROR", "ALREADY CONNECT", 10000);
    if (data.indexOf("OK") != -1 || data.indexOf("ALREADY CONNECT") != -1) {
        return true;
    }
    return false;
}

bool WiFiESP::connect(uint8_t mux_id, String protocol, String addr, uint32_t port)
{
    String data;
    rx_empty();
    m_puart->print("AT+CIPSTART=");
    m_puart->print(mux_id);
    m_puart->print(",\"");
    m_puart->print(protocol);
    m_puart->print("\",\"");
    m_puart->print(addr);
    m_puart->print("\",");
    m_puart->println(port);
    
    data = recvString("OK", "ERROR", "ALREADY CONNECT", 10000);
    if (data.indexOf("OK") != -1 || data.indexOf("ALREADY CONNECT") != -1) {
        return true;
    }
    return false;
}
bool WiFiESP::sATCIPSENDSingle(const uint8_t *buffer, uint32_t len)
{
    rx_empty();
    m_puart->print("AT+CIPSEND=0,");
    m_puart->println(len);
    if (recvFind(">", 5000)) {
        rx_empty();
        for (uint32_t i = 0; i < len; i++) {
            m_puart->write(buffer[i]);
        }
        return recvFind("SEND OK", 10000);
    }
    return false;
}
bool WiFiESP::sATCIPSENDMultiple(uint8_t mux_id, const uint8_t *buffer, uint32_t len)
{
    rx_empty();
    m_puart->print("AT+CIPSEND=");
    m_puart->print(mux_id);
    m_puart->print(",");
    m_puart->println(len);
    if (recvFind(">", 5000)) {
        rx_empty();
        for (uint32_t i = 0; i < len; i++) {
            m_puart->write(buffer[i]);
        }
        return recvFind("SEND OK", 10000);
    }
    return false;
}

bool WiFiESP::disconnect(uint8_t mux_id)
{
    String data;
    rx_empty();
    m_puart->print("AT+CIPCLOSE=");
    m_puart->println(mux_id);
    
    data = recvString("OK", "link is not", 5000);
    if (data.indexOf("OK") != -1 || data.indexOf("link is not") != -1) {
        return true;
    }
    return false;
}

bool WiFiESP::disconnect(void)
{
    rx_empty();
    m_puart->println("AT+CIPCLOSE");
    return recvFind("OK", 5000);
}

bool WiFiESP::eATCIFSR(String &list)
{
    rx_empty();
    m_puart->println("AT+CIFSR");
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", list);
}
bool WiFiESP::sATCIPMUX(uint8_t mode)
{
    String data;
    rx_empty();
    m_puart->print("AT+CIPMUX=");
    m_puart->println(mode);
    
    data = recvString("OK", "Link is builded");
    if (data.indexOf("OK") != -1) {
        return true;
    }
    return false;
}
bool WiFiESP::sATCIPSERVER(uint8_t mode, uint32_t port)
{
	String data;
	m_puart->println("AT+CIPMUX=1");
	data = recvString("OK", 1000);
	
    if (mode) {
        rx_empty();
        m_puart->print("AT+CIPSERVER=1,");
        m_puart->println(port);
        
        data = recvString("OK", "no change");
        if (data.indexOf("OK") != -1 || data.indexOf("no change") != -1) {
            return true;
        }
        return false;
    } else {
        rx_empty();
        m_puart->println("AT+CIPSERVER=0");
        return recvFind("\r\r\n");
    }
}
bool WiFiESP::sATCIPSTO(uint32_t timeout)
{
    rx_empty();
    m_puart->print("AT+CIPSTO=");
    m_puart->println(timeout);
    return recvFind("OK");
}

bool WiFiESP::sATGSLP(uint32_t timeout)
{
    rx_empty();
    m_puart->print("AT+GSLP=");
    m_puart->println(timeout);
    return recvFind("OK");
}

bool WiFiESP::sATSLEEP(uint32_t mode)
{
    rx_empty();
    m_puart->print("AT+SLEEP=");
	if (mode == 1){
		m_puart->println(1);
	} elseif (mode == 2){
		m_puart->println(2);
	} else {
		m_puart->println(0);
	}
    
    return recvFind("OK");
}

void WiFiESP::on(uint32_t baud)
{   baud_default=baud;
    pinMode(13,INPUT);
    digitalWrite(13,LOW); // disable pull-up
    delay(100);
    pinMode(WIFI_EN_PIN,OUTPUT);
    digitalWrite(WIFI_EN_PIN,HIGH);
    m_puart->begin(baud);
    rx_empty();
}

void WiFiESP::off(void)
{
    pinMode(WIFI_EN_PIN,OUTPUT);
    digitalWrite(WIFI_EN_PIN,LOW);
}

bool WiFiESP::wait(uint32_t timeout)
{
	String data;
    data = recvString("WIFI GOT IP", timeout);
    if (data.indexOf("WIFI GOT IP") != -1) {
        return true;
    }
    return false;
}
