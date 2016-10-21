# # -*- coding: utf-8 -*-
# # @Author: copbint
# # @Date:   2016-03-16 23:43:54
# # @Last Modified by:   copbint
# # @Last Modified time: 2016-03-17 00:29:21
# import urllib
# import urllib2
# import cookielib
# import re
# import sys
# reload(sys)
# sys.setdefaultencoding('utf-8')
 
# #山东大学绩点运算
# class xjtu:
 
#     def __init__(self):
#         self.loginUrl = 'https://cas.xjtu.edu.cn/login?service=http%3A%2F%2Fssfw.xjtu.edu.cn%2Findex.portal'
#         self.cookies = cookielib.CookieJar()
#         self.postdata = urllib.urlencode({
#                 'username':       'pengningjun',
#                 'password' :      '931212',
#                 'code'    :       '',
#                 'lt':             'LT-93492-36taRk2ljabcHpbMxWoiHW0V9lccLr',
#                 'execution':      'e1s1',
#                 'eventId'  :     'submit',
#                 'submit' :        'ç»å½',
#          })
#         # self.opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(self.cookies))
 
#     def getPage(self):
#         user_agent = 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:39.0) Gecko/20100101 Firefox/39.0'
#         headers =  {'(Request-Line)':  'POST /login?service=http%3A%2F%2Fssfw.xjtu.edu.cn%2Findex.portal HTTP/1.1',
#                     'Host':   'cas.xjtu.edu.cn',
#                     'User-Agent' : user_agent,
#                     'Accept':  'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
#                     'Accept-Language': 'en-US,en;q=0.5',
#                     'Accept-Encoding':    'gzip, deflate',
#                     'Referer':    'https://cas.xjtu.edu.cn/login?service=http%3A%2F%2Fssfw.xjtu.edu.cn%2Findex.portal',
#                     'Cookie': 'JSESSIONID=AA35201924AB222E4E6EA652B1EFEA35; CASTGC=TGT-13653-LJg5hVeogasUvdmYA4WmCre67ozHzbBO7GFJ5Y6CkUHZcmnDe9-gdscas01',
#                     'Content-Type':   'application/x-www-form-urlencoded',
#                     'Content-Length':  '142'}
#         request  = urllib2.Request(
#             url = self.loginUrl,
#             data = self.postdata,
#             headers = headers)
#         # result = self.opener.open(request)
#         result = urllib2.urlopen(request)
#         #打印登录内容
#         print result.read().decode('utf-8')
 
# sdu = xjtu()
# sdu.getPage()
# 
#coding:utf-8
import cookielib
import urllib
import urllib2

filename = 'cookie.txt'
#声明一个MozillaCookieJar对象实例来保存cookie，之后写入文件
cookie = cookielib.MozillaCookieJar(filename)
opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookie))
postdata = urllib.urlencode({
    'username':'pengningjun',
    'password':'931212'       #此处为用户名和密码
        })
#登录师生服务端的URL
loginUrl='https://cas.xjtu.edu.cn/login?service=http%3A%2F%2Fssfw.xjtu.edu.cn%2Findex.portal'
#模拟登录，并把cookie保存到变量
result = opener.open(loginUrl,postdata)
#保持cookie到cookie.txt中
cookie.save(ignore_discard=True,ignore_expires=True)
#利用cookie请求访问另一个网址，此网址是综合信息门户
myxjtuUrl='https://cas.xjtu.edu.cn/login'#?service=http://my.xjtu.edu.cn/Login'
#访问综合信息门户
result = opener.open(myxjtuUrl)
print result.read()