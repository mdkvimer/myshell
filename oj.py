#!/usr/bin/env ptython 
# check for oj

import os
import time
import urllib

def count_string(weburl,string_tobe_find):
    try:
        web = urllib.urlopen(weburl).read()
    except:
        return -1
    string = str(web)

    return string.count(string_tobe_find)

def check():
    status = count_string('http://acm.cjlu.edu.cn/status.php',"waiting")

    if status == -1: 
        os.system("/usr/local/fetion/fetion --sid=phone id --pwd=5566mdk --to=phone number --msg-utf8=mdk-OJ-down!")
        #print time.ctime(time.time()),"OJ index can'n open","please check for oj"
    elif status > 1: 
        os.system("/usr/local/fetion/fetion --sid=phone id --pwd=5566mdk --to=phone number --msg-utf8=mdk-OJ-down!")
        #print time.ctime(time.time()),"OJ waiting now","please deal with"
    else:
        os.system("/usr/local/fetion/fetion --sid=phone id --pwd=5566mdk --to=phone number --msg-utf8=mdk-OJ-normal!")
        #print time.ctime(time.time()),"Oj normal now!"

if __name__ == '__main__':
    print "\t OJ check now  by --python mdk"
    from time import sleep        
    check()
    #check()
    sleep(5)
