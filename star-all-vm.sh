for vm in ./VM*
do 
	cd ./$vm
	vagrant up && vagrant ssh
	cd ..
done 
clear