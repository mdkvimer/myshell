#!/bin/bash
for URL in http://acm.cjlu.edu.cn http://192.168.1.106/JudgeOnline/  http://192.168.1.106/CJLU-ACM/forum.php http://10.131.10.118 
do
HTTP_CODE=`curl -o /dev/null -s -w "%{http_code}" "${URL}"`

if [ $HTTP_CODE = 200 ]
then
	echo "$URL is Ok" | mail -s "Http_check" root@localhost
else
	/usr/local/fetion/fetion  --sid=418860718 --pwd=5566mdk --to=phone number --msg-utf8="$URL is Error;Error  code is $HTTP_CODE"
fi
done
