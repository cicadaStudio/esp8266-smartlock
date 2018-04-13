host_url="http://192.168.1.188:7944"
request_url=host_url+"/status.html"
import requests
def get_AP_info():
    ssid=''
    password=''
    print('Pls input ssid and password')
    print('ssid:')
    ssid=input()
    print('password:')
    password=input()
    return({'ssid':ssid,'password':password})
def set_esp(ap_info):
    res = requests.get("http://192.168.4.1/"+ap_info['ssid']+"="+ap_info['password']+"="+request_url)
    #还需加入超时检测
    return(res.text)
print("connect to AP:ESP8266 and press inter")
no_sense=input()
set_esp(get_AP_info())
