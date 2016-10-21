# -*- coding: utf-8 -*-
# @Author: copbint
# @Date:   2016-03-16 23:38:08
# @Last Modified by:   copbint
# @Last Modified time: 2016-03-16 23:43:04
 
import urllib
import urllib2
import cookielib
import re
 
#山东大学绩点运算
class SDU:
 
    def __init__(self):
        self.loginUrl = 'http://jwxt.sdu.edu.cn:7890/pls/wwwbks/bks_login2.login'
        self.cookies = cookielib.CookieJar()
        self.postdata = urllib.urlencode({
            'stuid':'201200131012',
            'pwd':'xxxxxx'
         })
        self.opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(self.cookies))
 
    def getPage(self):
        request  = urllib2.Request(
            url = self.loginUrl,
            data = self.postdata)
        result = self.opener.open(request)
        #打印登录内容
        print result.read().decode('gbk')
 
sdu = SDU()
sdu.getPage()