import requests
host_url="http://192.168.1.188:7944"
request_url=host_url+"/status.html"
while 1:
    print("on off quit")
    command=input();
    if command =='on':
        try:
            res = requests.get(host_url+'/on')
        except:
            pass
    if command =='off':
        try:
            res = requests.get(host_url+'/off')
        except:
            pass
    if command == 'quit':
        break
