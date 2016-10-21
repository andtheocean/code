import urllib2

url = "http://qlogo1.store.qq.com/qzone/416501600/416501600/100?10"
request = urllib2.Request(url)
data = urllib2.urlopen(request).read()
file = open('photo2','wb')
file.write(data)
# file.flush()
file.close()
# -*-coding:utf-8-*- 

# import os
# import uuid
# import urllib2
# import cookielib
# import sys

# reload(sys)
# sys.setdefaultencoding('utf-8')

# def get_file_extension(file):  
#     return os.path.splitext(file)[1]  

# def mkdir(path):
#     path=path.strip()
#     path=path.rstrip("\\")

#     if not os.path.exists(path):
#         os.makedirs(path)
        
#     return path

# def unique_str():
#     return str(uuid.uuid1())


# def get_file(url):
#     try:
#         cj=cookielib.LWPCookieJar()
#         opener=urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
#         urllib2.install_opener(opener)
        
#         req=urllib2.Request(url)
#         operate=opener.open(req)
#         data=operate.read()
#         return data
#     except BaseException, e:
#         print e
#         return None
    

# def save_file(path, file_name, data):
#     if data == None:
#         return
    
#     mkdir(path)
#     if(not path.endswith("/")):
#         path=path+"/"
#     file=open(path+file_name, "wb")
#     file.write(data)
#     file.flush()
#     file.close()
 

# print get_file_extension("123.jpg");
# print unique_str()

# url="http://qlogo1.store.qq.com/qzone/416501600/416501600/100?0";
# save_file("d:/ljq/", "123.jpg", get_file(url))