#!/bin/bash
VOIX=./speak/linux/voices/mb/fr1
# on teste si la lecture est en cours, pour l'arrêter le cas échéant
if [ ! -z $(ps -A | grep mbrola | awk '{ print $1 }' ) ]; then
     kill $(ps -A | grep mbrola | awk '{ print $1 }' )
 
else
	# On traduit la sélection en phonèmes grâce à espeak, et on l'envoie à Mbrola
	xclip -o | ./speak/linux/speak -vmb/mb-fr1 -s 150 -p 40 "$@" | ./speak/linux/mbrola $VOIX - -.au | aplay -f S16_BE -r16000
fi

