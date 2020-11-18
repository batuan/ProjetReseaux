for vm in ./VM*
do 
	cd ./$vm
	vagrant up & 
	cd ..
done 
clear