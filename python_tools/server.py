status = 1

def application(environ, start_response):
    global status
    command=environ['PATH_INFO']
    print(environ)
    if command == '/on':
        status = 1
    if command == '/off':
        status = 0
    print(status)
    start_response('200 OK', [('Content-Type', 'text/plain')])
    if command =='/remote_address':
        return[bytes(environ['REMOTE_ADDR'])]
    if command!='/status.html':
        return ['done!']
    if status == 0:
        return [b'0']
    if status == 1:
        return [b'1']

# server.py
# 从wsgiref模块导入:
from wsgiref.simple_server import make_server
# 创建一个服务器，IP地址为空，端口是7944，处理函数是application:
httpd = make_server('', 7944, application)
print('Serving HTTP on port 7944...')
# 开始监听HTTP请求:
httpd.serve_forever()
