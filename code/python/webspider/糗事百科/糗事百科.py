# -*- coding: utf-8 -*-
import urllib2
import urllib
import re
import thread
import time
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

#---------------------
class Spider_Model:

    def __init__(self):
        self.page = 1
        self.pages = []
        self.enable = False

    def GetPage(self,page):
        print("获取第%s页..." % page)
        myUrl = "http://www.qiushibaike.com/8hr/page/" + page
        user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2504.0 Safari/537.36'
        headers = { 'User-Agent' : user_agent }
        req = urllib2.Request(myUrl, headers = headers)
        myResponse = urllib2.urlopen(req)
        myPage = myResponse.read()
        #encode的作用是将unicode编码转换成其他编码的字符串
        #decode的作用是将其他编码的字符串转换成unicode编码
        unicodePage = myPage#.decode("utf-8")
        #print unicodePage
        
        # 找出所有class="content"的div标记
        #re.S是任意匹配模式，也就是.可以匹配换行符
        myItems = re.findall(r'<div class="content">(.*?)<!--',unicodePage,re.S | re.M)
        items = []
        for item in myItems:
            # item 中第一个是div的标题，也就是时间
            # item 中第二个是div的内容，也就是内容
            #print "i in m",item#.decode("utf-8")
            items.append(item.replace("<br/>","\n"))
        return items

    # 用于加载新的段子
    def LoadPage(self):
        # 如果用户未输入quit则一直运行
        while self.enable:
            # 如果pages数组中的内容小于2个
            if len(self.pages) < 2:
                try:
                    # 获取新的页面中的段子们
                    myPage = self.GetPage(str(self.page))
                    self.page += 1
                    self.pages.append(myPage)
                except Exception as e:
                    print 'except:', e
                    print '无法链接糗事百科！\n'
            else:
                time.sleep(1)

    def ShowPage(self,nowPage,page):
        for items in nowPage:
            print u'\n 第%d页' % page , items
            myInput = raw_input()
            if myInput == "quit":
                self.enable = False
                break

    def Start(self):
        self.enable = True
        page = self.page

        #print u'正在加载中请稍候......'

        # 新建一个线程在后台加载段子并存储
        thread.start_new_thread(self.LoadPage,())

        #----------- 加载处理糗事百科 -----------
        while self.enable:
            # 如果self的page数组中存有元素
            if self.pages:
                nowPage = self.pages[0]
                del self.pages[0]
                self.ShowPage(nowPage,page)
                page += 1


#----------- 程序的入口处 -----------
print """
---------------------------------------
   
---------------------------------------
"""
myModel = Spider_Model()
myModel.Start()