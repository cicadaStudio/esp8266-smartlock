import requests#import requests library
host_url="http://192.168.1.188:7944" #define the location of HTTP server. It can be a local address or a remote address
request_url=host_url+"/status.html" #request url that returns the status of led.
def get_AP_info():
    ssid=''
    password=''
    print('Pls input ssid and password') #instruct the user to input the ssid of their home Wi-Fi
    print('ssid:')
    ssid=input()
    print('password:')  #instruct the user to input the PSK of their home Wi-Fi
    password=input()
    return({'ssid':ssid,'password':password}) #return a dict including the ssid and the PSK
def set_esp(ap_info):
    res = requests.get("http://192.168.4.1/"+ap_info['ssid']+"="+ap_info['password']+"="+request_url) #192.168.4.1 is esp8266's default ip address when it serves as an access point. the requests sends ssid, PSK and the location of HTTP server to esp8266
    #还需加入超时检测
    return(res.text)
print("connect to AP:ESP8266 and press inter") #instruct the user to connect to the Soft Access Point esp8266 created
no_sense=input()
set_esp(get_AP_info())
