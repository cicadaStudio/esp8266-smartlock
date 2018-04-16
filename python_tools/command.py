import requests #import requests library
host_url="http://192.168.1.188:7944" #define the location of HTTP server. It can be a local address or a remote address
request_url=host_url+"/status.html" #request url that returns the status of led.
while 1:    #runs forever
    print("on off quit") #instruct the user
    command=input();
    if command =='on': # led on
        try:
            res = requests.get(host_url+'/on') #use the GET methode to change the current state.
        except:
            pass
    if command =='off':
        try:
            res = requests.get(host_url+'/off')#use the GET methode to change the current state.
        except:
            pass
    if command == 'quit':
        break #quit 
