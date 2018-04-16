status = 1 #store the state of the LED 1 for on and 0 for off

def application(environ, start_response):
    global status
    command=environ['PATH_INFO'] #extract the pathe_infor from GET requests
    #print(environ)
    if command == '/on': #we want to turn the LED on
        status = 1 #change the state
    if command == '/off': #we want to turn the LED on
        status = 0 #change the state
    #print(status)
    start_response('200 OK', [('Content-Type', 'text/plain')])
    if command!='/status.html':
        return ['done!'] #if we do on or off option, the server return a message "done!"
    if status == 0:
        return [b'0'] #if we GET the status, the server return the value of 'status' as a BYTE type
    if status == 1:
        return [b'1']

# server.py
# import the 'make_server' fonction from wsgiref
from wsgiref.simple_server import make_server
# create a server at port 7944, using the application defined above
httpd = make_server('', 7944, application)
print('Serving HTTP on port 7944...')
# start listion http requests forever
httpd.serve_forever()
