# -*- coding: utf-8 -*-
# @Author: copbint
# @Date:   2016-03-14 12:39:19
# @Last Modified by:   copbint
# @Last Modified time: 2016-03-15 16:17:03
import urllib
import urllib2
import re
import sys
from datetime import date
reload(sys)
sys.setdefaultencoding('utf-8')
for pagenumber in range(5):
    url = "http://www.qiushibaike.com/hot/page"+str(pagenumber) 
    header ={"User-Agent":'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)'}

    request = urllib2.Request(url,headers = header)
    response = urllib2.urlopen(request)
    content = response.read().decode('utf-8')

    #to get the joke
    pattern =  re.compile('<div class="content">(.*?)<!--',re.S)
    items   = re.findall(pattern,content)

    filename = date.today().strftime("%Y-%m-%d")
    print filename
    # f = open('xiushibaike.txt','w')
    # for i in range(len(items)):
    #      f.write(items[i].encode('utf-8'))
    # f.close()



