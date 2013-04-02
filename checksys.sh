#!/bin/bash
#set -x
# get address ip
IP="192.168.1.106"
#getnumcpu
cpu_num=`grep -c 'model name' /proc/cpuinfo`
#get 15 minutus
load_15=`uptime | awk '{print $12}'`
#calcue
average_load=`echo "scale=2;a=$load_15/$cpu_num;if(length(a)==scale(a)) print 0;print a" |bc`
average_int=`echo $average_load | cut -f 1 -d "."`
load_warm=0.70
  #echo $average_load $average_int
if (($average_int  > 0)); then
<<<<<<< HEAD
	/usr/local/fetion/fetion --sid=phone id --pwd=5566mdk --to=phone number  --msg-utf8="mdk,$IP server cpu load over the warning 1.0,please deal with"
else
	load_now=`expr $average_load \> $load_warm`
	if (($load_now == 1)); then
		/usr/local/fetion/fetion --sid=phone id --pwd=5566mdk --to=phone number --msg-utf8="mdk,$IP server cpu load_15 over the warning  $load_warn,please deal with"
=======
	/usr/local/fetion/fetion --sid=418860718 --pwd=5566mdk --to=phonenumber  --msg-utf8="mdk,$IP server cpu load over the warning 1.0,please deal with"
else
	load_now=`expr $average_load \> $load_warm`
	if (($load_now == 1)); then
		/usr/local/fetion/fetion --sid=418860718 --pwd=5566mdk --to=phonenumber --msg-utf8="mdk,$IP server cpu load_15 over the warning  $load_warn,please deal with"
>>>>>>> 58042165ec4f4b3a3388feb42dc65274868bc1da
	fi
fi

# check users
users=`uptime | awk '{print $6}'`
if (($users >= 5));then 
<<<<<<< HEAD
	/usr/local/fetion/fetion --sid=phone id --pwd=5566mdk --to=phone number --msg-utf8="mdk,$IP server have $users users  in the system,please deal with"
=======
	/usr/local/fetion/fetion --sid=418860718 --pwd=5566mdk --to=phonenumber --msg-utf8="mdk,$IP server have $users users  in the system,please deal with"
>>>>>>> 58042165ec4f4b3a3388feb42dc65274868bc1da
fi
#check cpu_use
cpu_idle=`top -b -n 1 | grep Cpu | awk '{print $5}' | cut -f 1 -d "."`
if (($cpu_idle < 20)); then
<<<<<<< HEAD
	/usr/local/fetion/fetion --sid=phone id --pwd=5566mdk --to=phone number --msg-utf8="mdk,$IP server $cpu_idle hava over 80%,please deal with"
=======
	/usr/local/fetion/fetion --sid=418860718 --pwd=5566mdk --to=phonenumber --msg-utf8="mdk,$IP server $cpu_idle hava over 80%,please deal with"
>>>>>>> 58042165ec4f4b3a3388feb42dc65274868bc1da
fi
#check for swap
swap_total=`free -m | grep Swap | awk '{print $2}'`
swap_free=`free -m | grep Swap | awk '{print $4}'`
swap_used=`free -m | grep Swap | awk '{print $3}'`
if ((swap_used != 0)); then
	swap_per=0`echo "scale=2;$swap_free/$swap_total" | bc`
	swap_warn=0.20
	swap_now=`expr $swap_per \> $swap_warn`
	if ((swap_now == 0)); then
<<<<<<< HEAD
		/usr/local/fetion/fetion --sid=phone id --pwd=5566mdk --to=18767161672 --msg-utf8="mdk,$IP server have used over 80% swapfree,please deal with "
=======
		/usr/local/fetion/fetion --sid=418860718 --pwd=5566mdk --to=phonenumber --msg-utf8="mdk,$IP server have used over 80% swapfree,please deal with "
>>>>>>> 58042165ec4f4b3a3388feb42dc65274868bc1da
	fi
fi
