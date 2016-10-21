# -*- coding: utf-8 -*-
# @Author: copbint
# @Date:   2016-03-11 20:55:44
# @Last Modified by:   copbint
# @Last Modified time: 2016-03-12 23:57:46
#   程序：爬虫
#   版本：0.1
#   作者：copbint
#   日期：2016-03-11
#   语言：Python 2.7
#   操作：输入学号和密码
#   功能：输出成绩的加权平均值也就是绩点
#---------------------------------------
#
#
import urllib
import urllib2
import cookielib

# def get_jsessionid():
#     url = 'http://web.cqust.edu.cn/userPasswordValidate.portal'
#     response = urllib.urlopen(url)
#     sid = str(response.headers['Set-Cookie'])[11:43]
#     return sid
#     
#     

def make_cookie(name, value):
    return cookielib.Cookie(
        version=0,
        name=name,
        value=value,
        port=None,
        port_specified=False,
        domain="xxxxx",
        domain_specified=True,
        domain_initial_dot=False,
        path="/",
        path_specified=True,
        secure=False,
        expires=None,
        discard=False,
        comment=None,
        comment_url=None,
        rest=None
    )
 
cookie = cookielib.CookieJar()

cookie.set_cookie(make_cookie("JSESSIONID", "0000HgQ8cKqYxgRExuJeyDC_N_g:19api1md3"))

#cookie =get_jsessionid()
opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookie))

postdata = urllib.urlencode({
    'Login.Token1':'2013442707',
    'Login.Token2':'123789',
    'goto':'http://web.cqust.edu.cn:9080/loginSuccess.portal',
    'gotoOnFail':'http://web.cqust.edu.cn:9080/loginFailure.portal',
    })
req = urllib2.Request(
    #url = 'http://web.cqust.edu.cn:9080/index.portal',
    url = 'http://web.cqust.edu.cn:9080/userPasswordValidate.portal',
    data = postdata
)

result = opener.open(req)
print result.read()




 
# 
# 
# import requests
# import sys
# reload(sys)   
# sys.setdefaultencoding('utf8')
# hea = {'User-Agent':'Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.118 Safari/537.36',
#        'Referer'   : 'http://202.115.67.50/service/login.jsp'}
# url = 'http://202.115.67.50/servlet/UserLoginSQLAction'
# data ={  
#     'Login.Tocken1':'2013442707',
#     'Login.Tocken2':'123789',
#     'goto':'http://web.cqust.edu.cn:9080/loginSuccess.portal',
#     'gotoOnFail':'http://web.cqust.edu.cn:9080/loginFailure.portal',
# }
# loginhtml = requests.post(url,data = data,headers = hea)
 
# url2 = 'http://202.115.67.50/student/score/MyScorePoint.jsp?QueryScoreType=FromTerm&term_value=71&B3=%E6%89%A7%E8%A1%8C%E6%9F%A5%E8%AF%A2'
# head1 = {'User-Agent':'Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.118 Safari/537.36'} 
# scorehtml = requests.get(url2,cookies = loginhtml.cookies,headers=head1)
# print loginhtml.text






#cook = {"coodie":""}
#url = ''
#html = requests.get(url,cookies = cook).content
#
#html = requests.get(url,cookies = cook).txt
#html = bytes(bytearray(html,encoding = 'utf-8'))
#
#seletor = etree.HTML(html)
#content = selector.xpath('//span[@class="ctt"]')
#for each in content:
#   text = each.xpath('string(.)')
#   b = 1
#   print text