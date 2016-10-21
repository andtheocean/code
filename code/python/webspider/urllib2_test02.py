# -*- coding: utf-8 -*-
# @Author: copbint
# @Date:   2016-03-08 12:26:52
# @Last Modified by:   copbint
# @Last Modified time: 2016-03-08 12:28:36
import urllib2
req =  urllib2.Request('http://www.baidu.com')
response = urllib2.urlopen(req)
the_page = response.read()
print the_page