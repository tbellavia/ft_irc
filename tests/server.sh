#!/bin/bash


launch(){
	docker run -d --name inspircd -p 127.0.0.1:6667:6667 \
	-e "INSP_CONNECT_PASSWORD=pass" \
	-e "INSP_ENABLE_DNSBL=no" \
	inspircd/inspircd-docker
}

stop(){
	docker container rm -f inspircd
}

usage(){
	echo "usage: server.sh launch|stop"
	exit 1
}

if [[ "$#" -ne 1 ]]
then
	usage
fi

flag="$1"

case "$flag" in
	"launch")
		launch
		;;
	"stop")
		stop
		;;
	*)
		usage
		;;
esac
