# -*- coding: utf-8 -*-
# @Author: copbint
# @Date:   2016-03-15 23:39:19
# @Last Modified by:   copbint
# @Last Modified time: 2016-03-16 12:28:39


import urllib
import urllib2
import re
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

class Tool:
    #pattern_removeImg = re.compile('<img.*?height.*?>')
    removeImg = re.compile('<img.*?height.*?>')
    pattern_removeAddr = re.compile('')
    #删除超链接标签
    removeAddr = re.compile('<a.*?>|</a>')
    #把换行的标签换为\n
    replaceLine = re.compile('<tr>|<div>|</div>|</p>')
    #将表格制表<td>替换为\t
    replaceTD= re.compile('<td>')
    #把段落开头换为\n加空两格
    replacePara = re.compile('<p.*?>')
    #将换行符或双换行符替换为\n
    replaceBR = re.compile('<br><br>|<br>')
    #将其余标签剔除
    removeExtraTag = re.compile('<.*?>')
    def replace(self,x):
        x = re.sub(self.removeImg,"",x)
        x = re.sub(self.removeAddr,"",x)
        x = re.sub(self.replaceLine,"\n",x)
        x = re.sub(self.replaceTD,"\t",x)
        x = re.sub(self.replacePara,"\n    ",x)
        x = re.sub(self.replaceBR,"\n",x)
        x = re.sub(self.removeExtraTag,"",x)
        #strip()将前后多余内容删除
        return x.strip()



class BAIUDTIEBA:
    def __init__(self,baseUrl,seeLZ,floorTag):
        self.baseURL = baseUrl
        self.seeLZ = "?see_lz="+str(seeLZ)
        self.tool = Tool()
        self.file = None
        self.floor = 1
        self.defaultTitle = u'百度贴吧'
        self.floorTag = floorTag
        self.count = int(0)

    def getPage(self,pageNum):
        try:
            url = self.baseURL + self.seeLZ + "&pn=" + str(pageNum)
            request = urllib2.Request(url)
            response = urllib2.urlopen(request)
            return response.read().decode('utf-8')
        except urllib2.URLError,e:
            if hasattr(e,"reason"):
                print u"unalbe to connect to BAIUDTIEBA,the reason is ",e.reason
                return None

    def getTitle(self,page):
        #page = self.getPage(1)
        pattern = re.compile("<title>(.*?)</title>",re.S)
         # pattern = re.compile('title="(.*?) "',re.S)

        title = re.search(pattern,page)
        if title:
            return title.group(1).strip()
        else:
            return None

    def getPageNum(self,page):
        #page = self.getPage(1)
        #pattern = re.compile('class="l_reply_num".*?<span.*?</span>.*?<span.*?>(.*?)</span',re.S)
        pattern = re.compile('class="red">(\d)<',re.S)
        number = re.search(pattern,page)
        if number:
            return number.group(1).strip()
        else:
            return None



    def getContent(self,page):
        pattern = re.compile('<div id="post_content_.*?>(.*?)</div>',re.S)
        items = re.findall(pattern,page)
        contents = []
        for item in items:
            self.count = self.count + 1
            content = "\n" + self.tool.replace(item) + "\n"
            if len(content)>140:
                contents.append(content.encode('utf-8'))
        return contents
      #获取每一层楼的内容,传入页面内容
    # def getContent(self,page):
    #     #匹配所有楼层的内容
    #     pattern = re.compile('<div id="post_content_.*?>(.*?)</div>',re.S)
    #     items = re.findall(pattern,page)
    #     contents = []
    #     for item in items:
    #         self.count = self.count + 1
    #         #将文本进行去除标签处理，同时在前后加入换行符
    #         content = "\n"+self.tool.replace(item)+"\n"
    #         contents.append(content.encode('utf-8'))
    #     return contents     


    def setFileTitle(self,title):
        if title is not None:
            self.file = open(title + ".txt",'w+')
        else:
            self.file = open(self.defaultTitle + ".txt",'w+')

    def writeData(self,contents):#is the name of the value suitable?
        for item in contents:
            if self.floorTag == 1:
                floorLine = "\n" + str(self.floor) + u"-----------------------------------------------------------------------------------------\n"
                self.file.write(floorLine)
            self.file.write(item)
            self.floor += 1

    def start(self):
        homePage = self.getPage(1)
        pageNum = self.getPageNum(homePage)
        title = self.getTitle(homePage)
        self.setFileTitle(title)

        if pageNum == None:
            print "URL is out of operation,please try again "
            return
        try:
            print "total " + str(pageNum) + " page"
            for i in range(1,int(pageNum)+1):
                print "now is writing the data of page " + str(i)
                page = self.getPage(i)

                contents = self.getContent(page)
                self.writeData(contents)
            self.file.close()
        except IOError,e:
            print "encotered writing error   reaon:" + e.message

        finally:
            print "write down"





url = "http://tieba.baidu.com/p/3138733512"
seeLZ = 1
floorTag = 1
tieba = BAIUDTIEBA(url,seeLZ,floorTag)
tieba.start()
print tieba.count





