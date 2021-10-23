cat $1 | awk -F ',' '{print $2}' | sort --numeric | uniq -c
#prova
