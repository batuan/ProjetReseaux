for vm in ./VM*
do 
	cd ./$vm
	vagrant halt & 
	cd ..
done 
clear