 #instantiation du simulateur
set ns [new Simulator]

#instantiation du fichier de traces
set file1 [open out.tr w]
$ns trace-all $file1

#instantiation du fichier de traces pour NAM
set file2 [open out.nam w]
$ns namtrace-all $file2

#procédure pour lancer auto le visualisateur NAM à la fin de la simu
proc finish {} {
	global ns file1 file2
	$ns flush-trace
	close $file1
	close $file2
	exec nam out.nam &
	exit 0
}

#couleurs
$ns color 1 Blue
$ns color 2 Red

#instantation de deux noeuds 
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]


#instantiation d'une ligne de communication full duplex entre les noeuds n0 et n1
$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 1.5Mb 20ms DropTail

#positionnement graphique des lignes de communication
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right


#instantiation d'une connexions :
#pour n0
set tcp [new Agent/TCP]
$tcp set class_ 1
#pour n1
set udp [new Agent/UDP]
$udp set class_ 2
#pour n3
set sink [new Agent/TCPSink]
set null [new Agent/Null]

#on dirige les packets TCP vers sink
$ns attach-agent $n0 $tcp
$ns attach-agent $n3 $sink

#et UDP vers null
$ns attach-agent $n1 $udp
$ns attach-agent $n3 $null

#on crée les connections
$ns connect $tcp $sink
$ns connect $udp $null

#tous les paquets TCP seront tagués par un 1, et les paquets UDP par 2
$tcp set fid_ 1
$udp set fid_ 2

#instantiation des types des source FTP et CBR
set ftp [new Application/FTP]
$ftp set type_ FTP
$ftp set packetSize_ 1000
$ftp attach-agent $tcp

set cbr [new Application/Traffic/CBR]
$cbr set type_ CBR
$cbr set packetSize_ 1000
$cbr set rate_ 1mb
$cbr attach-agent $udp


#scénario de début et de fin de génération des paquets par cbr0
$ns at 1.0 "$ftp start"
$ns at 5.0 "$ftp stop"

$ns at 2.0 "$cbr start"
$ns at 4.0 "$cbr stop"

#la simulation va durer 5 secondes de temps simulé
$ns at 5.0 "finish"

# début de la simulation
$ns run

#Exercice 2
#3.Taille paquets TCP : 1040 -> 1000 octets pour les données + 40 d'en-tête
#4.Le temps de traitement est null, on cherche le temps de transmission en TCP et UDP (depuis out.tr) 
#  temps de transmission TCP : 4ms
#  temps de transmission UDP : 4ms
#  Temps de transmission : Connexion = 2Mb = 2 000 000b, Paquet = 1000 octets = 8000b, donc 8 000/2 000 000= 4ms
#  Temps de propagation : 10 ms
#  C'est le même temps de transmission sur le lien 2Mbs en UDP et TCP, car les paquets envoyés sont de même taille et les capacités des liens pareils
#5. Tous les lignes 718 : grep 718$ out.tr
#6. Temps d'attente = Différence entre le (+ : arrivée file) et le (- : départ file) = 21ms sur le noeud 2 (environ, en utilisant out.tr)
#7. Pareil pour tous les paquets TCP, car il n'y a pas de fil d'attente
